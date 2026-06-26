import sys
import os
import pyray as rl

# Add selfdrive's parent to path to support openpilot imports
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from selfdrive.ui.layouts.settings.starpilot.scribble import draw_custom_icon

def main():
    rl.init_window(200, 200, "Icon Render")
    rl.set_target_fps(60)

    # Run for a few frames to make sure rendering is ready
    for _ in range(10):
        rl.begin_drawing()
        rl.clear_background(rl.Color(15, 12, 30, 255)) # Dark background matching Driving Model tile

        # Draw aicar icon centered
        # x_c and y_c will be at x + 30*s, y + 30*s.
        # Let's draw it at x=70, y=70, scale s=1.0. Centered at 100, 100.
        draw_custom_icon("aicar", 70.0, 70.0, 1.0, rl.WHITE)

        rl.end_drawing()

    rl.take_screenshot("scratch/aicar_preview.png")
    rl.close_window()
    print("Screenshot saved to scratch/aicar_preview.png")

if __name__ == "__main__":
    main()
