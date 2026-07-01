#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json
import time

from http import HTTPStatus
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from urllib.parse import parse_qs, urlparse


QUEUE_REVIEW_FIELDS = [
  "review_status",
  "review_speed_limit_mph",
  "review_sign_type",
  "review_bbox",
  "review_ignore_reason",
  "review_notes",
]

LABEL_FIELDNAMES = [
  "record_key",
  "review_status",
  "review_speed_limit_mph",
  "review_sign_type",
  "review_bbox",
  "review_ignore_reason",
  "review_notes",
  "reviewed_at_unix",
]

HTML = r"""<!doctype html>
<html>
<head>
  <meta charset="utf-8">
  <title>Speed Limit Review</title>
  <style>
    :root { color-scheme: dark; font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif; }
    body { margin: 0; background: #111; color: #eee; }
    header { display: flex; align-items: center; gap: 16px; padding: 10px 14px; background: #1b1b1b; border-bottom: 1px solid #333; position: sticky; top: 0; z-index: 2; }
    button, select, input, textarea { background: #222; color: #eee; border: 1px solid #555; border-radius: 6px; padding: 7px 9px; font: inherit; }
    button { cursor: pointer; }
    button:hover { background: #333; }
    button.primary { background: #285f9f; border-color: #3f7ec8; }
    button.warn { background: #6b3b18; border-color: #9a5a25; }
    main { display: grid; grid-template-columns: minmax(360px, 1fr) 420px; gap: 12px; padding: 12px; }
    .images { display: grid; gap: 12px; align-content: start; }
    .panel { background: #181818; border: 1px solid #303030; border-radius: 8px; padding: 10px; }
    .imageWrap { display: grid; place-items: center; background: #050505; border-radius: 6px; min-height: 160px; overflow: hidden; }
    img { max-width: 100%; max-height: 52vh; object-fit: contain; }
    .crop img { image-rendering: auto; max-height: 28vh; }
    .meta { display: grid; gap: 5px; font-size: 13px; color: #ddd; }
    .meta code { color: #cfe5ff; overflow-wrap: anywhere; }
    .buttons { display: flex; flex-wrap: wrap; gap: 6px; margin: 8px 0; }
    .buttons button.active { outline: 2px solid #ddd; background: #345; }
    textarea { width: 100%; min-height: 70px; box-sizing: border-box; }
    .speed button { min-width: 42px; }
    .muted { color: #aaa; }
    .status { white-space: nowrap; }
    @media (max-width: 980px) { main { grid-template-columns: 1fr; } img { max-height: 45vh; } }
  </style>
</head>
<body>
  <header>
    <button id="prevBtn">Prev</button>
    <button id="nextBtn" class="primary">Next</button>
    <select id="filter">
      <option value="unreviewed">Unreviewed</option>
      <option value="all">All</option>
      <option value="school">School Zone</option>
      <option value="priority">Priority 30-65</option>
      <option value="disagreement">Disagreement</option>
      <option value="negative">Negatives</option>
    </select>
    <span class="status" id="status"></span>
    <span class="muted">Keys: j/k next/prev, 0 ignore, s school, r regulatory, a advisory</span>
  </header>
  <main>
    <section class="images">
      <div class="panel crop">
        <div class="muted">Crop</div>
        <div class="imageWrap"><img id="cropImg"></div>
      </div>
      <div class="panel">
        <div class="muted">Frame</div>
        <div class="imageWrap"><img id="frameImg"></div>
      </div>
    </section>
    <aside class="panel">
      <div class="meta" id="meta"></div>
      <h3>Speed</h3>
      <div class="buttons speed" id="speedButtons"></div>
      <h3>Type</h3>
      <div class="buttons" id="typeButtons">
        <button data-type="regulatory">Regulatory</button>
        <button data-type="school_zone">School Zone</button>
        <button data-type="advisory">Advisory</button>
        <button data-type="construction">Construction</button>
        <button data-type="not_speed_limit">Not Speed Limit</button>
      </div>
      <h3>Status</h3>
      <div class="buttons" id="statusButtons">
        <button data-status="accepted" class="primary">Accept</button>
        <button data-status="corrected">Corrected</button>
        <button data-status="ignore" class="warn">Ignore</button>
        <button data-status="needs_later">Needs Later</button>
      </div>
      <label>Ignore reason</label>
      <input id="ignoreReason" placeholder="false_positive, blurry, side_road, duplicate">
      <label>Notes</label>
      <textarea id="notes"></textarea>
      <div class="buttons">
        <button id="saveBtn" class="primary">Save</button>
        <button id="acceptPredBtn">Accept Prediction</button>
      </div>
    </aside>
  </main>
<script>
const speeds = [15,20,25,30,35,40,45,50,55,60,65,70,75];
let rows = [];
let index = 0;
let current = null;
let draft = {};

function qs(sel) { return document.querySelector(sel); }
function qsa(sel) { return Array.from(document.querySelectorAll(sel)); }

async function loadQueue() {
  const filter = qs("#filter").value;
  const res = await fetch(`/api/queue?filter=${encodeURIComponent(filter)}`);
  const data = await res.json();
  rows = data.rows;
  index = 0;
  render();
}

function setActive(selector, attr, value) {
  qsa(selector).forEach(btn => btn.classList.toggle("active", btn.dataset[attr] === String(value)));
}

function renderSpeedButtons() {
  const root = qs("#speedButtons");
  root.innerHTML = "";
  for (const speed of speeds) {
    const btn = document.createElement("button");
    btn.textContent = speed;
    btn.dataset.speed = speed;
    btn.onclick = () => {
      draft.review_speed_limit_mph = String(speed);
      setActive("#speedButtons button", "speed", speed);
    };
    root.appendChild(btn);
  }
}

function render() {
  current = rows[index] || null;
  if (!current) {
    qs("#status").textContent = "No rows";
    qs("#meta").innerHTML = "";
    qs("#cropImg").removeAttribute("src");
    qs("#frameImg").removeAttribute("src");
    return;
  }
  draft = {
    review_status: current.review_status || "",
    review_speed_limit_mph: current.review_speed_limit_mph || "",
    review_sign_type: current.review_sign_type || "",
    review_bbox: current.review_bbox || current.bbox || "",
    review_ignore_reason: current.review_ignore_reason || "",
    review_notes: current.review_notes || "",
  };
  qs("#status").textContent = `${index + 1}/${rows.length}`;
  qs("#cropImg").src = current.crop_path ? `/media/${current.record_key}/crop` : "";
  qs("#frameImg").src = `/media/${current.record_key}/frame`;
  qs("#ignoreReason").value = draft.review_ignore_reason;
  qs("#notes").value = draft.review_notes;
  setActive("#speedButtons button", "speed", draft.review_speed_limit_mph);
  setActive("#typeButtons button", "type", draft.review_sign_type);
  setActive("#statusButtons button", "status", draft.review_status);
  qs("#meta").innerHTML = [
    ["record", current.record_key],
    ["candidate", `${current.candidate_speed_limit_mph || "none"} @ ${current.candidate_confidence || ""}`],
    ["class", `${current.detector_class} (${current.proposal_confidence})`],
    ["reasons", current.review_reasons],
    ["map", `${current.map_relation} current=${current.map_current_speed_limit_mph} next=${current.map_next_speed_limit_mph} dist=${current.map_next_speed_limit_distance_m}`],
    ["reads", current.read_sources],
    ["route", current.route],
    ["time", `seg ${current.segment} @ ${current.frame_time_s}s`],
  ].map(([k,v]) => `<div><span class="muted">${k}:</span> <code>${String(v || "")}</code></div>`).join("");
}

async function save(moveNext = true) {
  if (!current) return;
  draft.review_ignore_reason = qs("#ignoreReason").value;
  draft.review_notes = qs("#notes").value;
  const payload = {record_key: current.record_key, ...draft};
  const res = await fetch("/api/review", {method: "POST", headers: {"Content-Type": "application/json"}, body: JSON.stringify(payload)});
  if (!res.ok) {
    alert(await res.text());
    return;
  }
  Object.assign(current, payload);
  if (moveNext) next();
  else render();
}

function next() { if (index < rows.length - 1) { index += 1; render(); } }
function prev() { if (index > 0) { index -= 1; render(); } }

renderSpeedButtons();
qs("#filter").onchange = loadQueue;
qs("#nextBtn").onclick = next;
qs("#prevBtn").onclick = prev;
qs("#saveBtn").onclick = () => save(true);
qs("#acceptPredBtn").onclick = () => {
  if (!current) return;
  draft.review_status = "accepted";
  draft.review_speed_limit_mph = current.candidate_speed_limit_mph || "";
  draft.review_sign_type = current.detector_class === "school_zone_speed_limit" ? "school_zone" :
    current.detector_class === "advisory_speed_limit" ? "advisory" :
    current.detector_class === "negative_empty" ? "not_speed_limit" : "regulatory";
  save(true);
};
qsa("#typeButtons button").forEach(btn => btn.onclick = () => {
  draft.review_sign_type = btn.dataset.type;
  setActive("#typeButtons button", "type", draft.review_sign_type);
});
qsa("#statusButtons button").forEach(btn => btn.onclick = () => {
  draft.review_status = btn.dataset.status;
  setActive("#statusButtons button", "status", draft.review_status);
});
document.addEventListener("keydown", ev => {
  if (ev.target.tagName === "TEXTAREA" || ev.target.tagName === "INPUT") return;
  if (ev.key === "j") next();
  if (ev.key === "k") prev();
  if (ev.key === "s") { draft.review_sign_type = "school_zone"; setActive("#typeButtons button", "type", "school_zone"); }
  if (ev.key === "r") { draft.review_sign_type = "regulatory"; setActive("#typeButtons button", "type", "regulatory"); }
  if (ev.key === "a") { draft.review_sign_type = "advisory"; setActive("#typeButtons button", "type", "advisory"); }
  if (ev.key === "0") { draft.review_status = "ignore"; draft.review_sign_type = "not_speed_limit"; setActive("#statusButtons button", "status", "ignore"); setActive("#typeButtons button", "type", "not_speed_limit"); }
  if (ev.key === "Enter") save(true);
});
loadQueue();
</script>
</body>
</html>
"""


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Serve a small browser UI for manually reviewing speed-limit queue rows.")
  parser.add_argument("--manifest", type=Path, required=True, help="manual_review_queue.csv from build_manual_review_queue.py")
  parser.add_argument("--labels-out", type=Path, help="Defaults to <manifest_dir>/manual_review_labels.csv")
  parser.add_argument("--host", default="127.0.0.1")
  parser.add_argument("--port", type=int, default=8765)
  return parser.parse_args()


def load_csv(path: Path) -> list[dict[str, str]]:
  with path.open("r", encoding="utf-8", newline="") as handle:
    return list(csv.DictReader(handle))


def load_labels(path: Path) -> dict[str, dict[str, str]]:
  if not path.is_file():
    return {}
  rows = load_csv(path)
  return {row["record_key"]: row for row in rows if row.get("record_key")}


def write_labels(path: Path, labels: dict[str, dict[str, str]]) -> None:
  path.parent.mkdir(parents=True, exist_ok=True)
  with path.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=LABEL_FIELDNAMES, extrasaction="ignore")
    writer.writeheader()
    for key in sorted(labels):
      writer.writerow(labels[key])


def merged_rows(rows: list[dict[str, str]], labels: dict[str, dict[str, str]]) -> list[dict[str, str]]:
  merged = []
  for row in rows:
    item = dict(row)
    label = labels.get(row.get("record_key", ""))
    if label:
      item.update({field: label.get(field, "") for field in QUEUE_REVIEW_FIELDS})
    merged.append(item)
  return merged


def filter_rows(rows: list[dict[str, str]], filter_name: str) -> list[dict[str, str]]:
  if filter_name == "all":
    return rows
  if filter_name == "school":
    return [row for row in rows if "school_zone" in row.get("detector_class", "") or "school_zone_candidate" in row.get("review_reasons", "")]
  if filter_name == "priority":
    return [row for row in rows if "priority_30_65" in row.get("review_reasons", "")]
  if filter_name == "disagreement":
    return [row for row in rows if "disagreement" in row.get("review_reasons", "") or "multi_value_votes" in row.get("review_reasons", "")]
  if filter_name == "negative":
    return [row for row in rows if row.get("detector_class") == "negative_empty"]
  return [row for row in rows if not row.get("review_status")]


class ReviewServer(ThreadingHTTPServer):
  def __init__(self, server_address, handler_class, manifest_path: Path, labels_path: Path):
    super().__init__(server_address, handler_class)
    self.manifest_path = manifest_path
    self.labels_path = labels_path
    self.rows = load_csv(manifest_path)
    self.row_by_key = {row["record_key"]: row for row in self.rows}
    self.labels = load_labels(labels_path)


class Handler(BaseHTTPRequestHandler):
  server: ReviewServer

  def log_message(self, format, *args):  # noqa: A003
    return

  def send_json(self, data, status=HTTPStatus.OK):
    body = json.dumps(data).encode("utf-8")
    self.send_response(status)
    self.send_header("Content-Type", "application/json")
    self.send_header("Content-Length", str(len(body)))
    self.end_headers()
    self.wfile.write(body)

  def send_text(self, text: str, status=HTTPStatus.OK, content_type="text/html; charset=utf-8"):
    body = text.encode("utf-8")
    self.send_response(status)
    self.send_header("Content-Type", content_type)
    self.send_header("Content-Length", str(len(body)))
    self.end_headers()
    self.wfile.write(body)

  def do_GET(self):  # noqa: N802
    parsed = urlparse(self.path)
    if parsed.path == "/":
      self.send_text(HTML)
      return
    if parsed.path == "/api/queue":
      params = parse_qs(parsed.query)
      filter_name = params.get("filter", ["unreviewed"])[0]
      rows = filter_rows(merged_rows(self.server.rows, self.server.labels), filter_name)
      self.send_json({"rows": rows, "count": len(rows), "reviewed": len(self.server.labels)})
      return
    if parsed.path.startswith("/media/"):
      parts = parsed.path.strip("/").split("/")
      if len(parts) != 3:
        self.send_error(HTTPStatus.NOT_FOUND)
        return
      _, record_key, kind = parts
      row = self.server.row_by_key.get(record_key)
      if row is None:
        self.send_error(HTTPStatus.NOT_FOUND)
        return
      image_path = Path(row.get("crop_path" if kind == "crop" else "frame_path", ""))
      if not image_path.is_file():
        self.send_error(HTTPStatus.NOT_FOUND)
        return
      body = image_path.read_bytes()
      self.send_response(HTTPStatus.OK)
      self.send_header("Content-Type", "image/jpeg")
      self.send_header("Content-Length", str(len(body)))
      self.end_headers()
      self.wfile.write(body)
      return
    self.send_error(HTTPStatus.NOT_FOUND)

  def do_POST(self):  # noqa: N802
    if urlparse(self.path).path != "/api/review":
      self.send_error(HTTPStatus.NOT_FOUND)
      return
    length = int(self.headers.get("Content-Length", "0"))
    try:
      payload = json.loads(self.rfile.read(length).decode("utf-8"))
    except Exception:
      self.send_error(HTTPStatus.BAD_REQUEST, "Invalid JSON")
      return
    record_key = str(payload.get("record_key") or "")
    if record_key not in self.server.row_by_key:
      self.send_error(HTTPStatus.BAD_REQUEST, "Unknown record_key")
      return
    label = {"record_key": record_key, "reviewed_at_unix": f"{time.time():.3f}"}
    for field in QUEUE_REVIEW_FIELDS:
      label[field] = str(payload.get(field) or "")
    self.server.labels[record_key] = label
    write_labels(self.server.labels_path, self.server.labels)
    self.send_json({"ok": True, "reviewed": len(self.server.labels)})


def main() -> int:
  args = parse_args()
  manifest_path = args.manifest.expanduser().resolve()
  labels_path = args.labels_out.expanduser().resolve() if args.labels_out else manifest_path.with_name("manual_review_labels.csv")
  server = ReviewServer((args.host, args.port), Handler, manifest_path, labels_path)
  print(f"Review UI: http://{args.host}:{args.port}")
  print(f"Manifest:  {manifest_path}")
  print(f"Labels:    {labels_path}")
  try:
    server.serve_forever()
  except KeyboardInterrupt:
    pass
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
