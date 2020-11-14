#ifndef GUI_PASSWORD_CONTAINER_MAIN_H
#define GUI_PASSWORD_CONTAINER_MAIN_H

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <CinderImGui.h>

namespace passwordcontainer {

namespace gui {

class PasswordContainerApp : public ci::app::App {
 public:
  PasswordContainerApp();

  void setup() override;
  void draw() override;
  void update() override;

 private:
  // Boolean to check if the button has been pressed
  bool button_pressed_;

  // The number of times the button has been pressed
  size_t counter_;

  // Constants for the window size
  const double kWindowSize = 300;
};

}  // namespace gui

}  // namespace passwordcontainer

#endif //GUI_PASSWORD_CONTAINER_MAIN_H
