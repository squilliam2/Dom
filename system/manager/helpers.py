import os

def unblock_stdout() -> None:
  import errno
  import fcntl
  import signal
  import sys

  # get a non-blocking stdout
  child_pid, child_pty = os.forkpty()
  if child_pid != 0:  # parent

    # child is in its own process group, manually pass kill signals
    signal.signal(signal.SIGINT, lambda signum, frame: os.kill(child_pid, signal.SIGINT))
    signal.signal(signal.SIGTERM, lambda signum, frame: os.kill(child_pid, signal.SIGTERM))

    fcntl.fcntl(sys.stdout, fcntl.F_SETFL, fcntl.fcntl(sys.stdout, fcntl.F_GETFL) | os.O_NONBLOCK)

    while True:
      try:
        dat = os.read(child_pty, 4096)
      except OSError as e:
        if e.errno == errno.EIO:
          break
        continue

      if not dat:
        break

      try:
        sys.stdout.write(dat.decode('utf8'))
      except (OSError, UnicodeDecodeError):
        pass

    # os.wait() returns a tuple with the pid and a 16 bit value
    # whose low byte is the signal number and whose high byte is the exit status
    exit_status = os.wait()[1] >> 8
    os._exit(exit_status)


def write_onroad_params(started, params):
  params.put_bool("IsOnroad", started)
  params.put_bool("IsOffroad", not started)


def save_bootlog():
  import threading

  def fn():
    import pathlib
    import shutil
    import subprocess
    import tempfile

    from openpilot.common.basedir import BASEDIR
    from openpilot.common.params import Params

    tmpdir = tempfile.mkdtemp()
    env = os.environ.copy()
    env['PARAMS_COPY_PATH'] = tmpdir

    try:
      params = Params()
      params_dirname = pathlib.Path(params.get_param_path()).name
      params_dir = os.path.join(tmpdir, params_dirname)
      shutil.copytree(params.get_param_path(), params_dir, dirs_exist_ok=True)
      subprocess.call("./bootlog", cwd=os.path.join(BASEDIR, "system/loggerd"), env=env)
    finally:
      shutil.rmtree(tmpdir, ignore_errors=True)

  t = threading.Thread(target=fn)
  t.daemon = True
  t.start()
