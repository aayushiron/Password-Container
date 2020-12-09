#ifndef GUI_WINDOW_WINDOW_H
#define GUI_WINDOW_WINDOW_H

#include <CinderImGui.h>

namespace passwordcontainer {

namespace gui {

namespace window {

const int kNoAccountSelectedIndex = -1;

// Interface for all windows in the app that allows them to draw the window and
// update the window.
class Window {
 public:
  // Pure Virtual function that allows the window to be drawn in the
  // application.
  virtual void DrawWindow() = 0;

  // Pure Virtual function that allows the values in the window to be updated
  // in the application.
  virtual void UpdateWindow() = 0;
};

}  // namespace window

}  // namespace gui

}  // namespace passwordcontainer

#endif  // GUI_WINDOW_WINDOW_H
