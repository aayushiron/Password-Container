#ifndef GUI_PASSWORD_CONTAINER_MAIN_H
#define GUI_PASSWORD_CONTAINER_MAIN_H

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

namespace passwordcontainer {

namespace gui {

class PasswordContainerApp : public ci::app::App {
 public:
  PasswordContainerApp();

  void draw() override;

 private:
  // Constants for the window size
  const double kWindowSize = 875;
  const double kMargin = 100;
};

}

}

#endif //GUI_PASSWORD_CONTAINER_MAIN_H
