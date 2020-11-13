#include "gui/password_container_app.h"

namespace passwordcontainer {

namespace gui {

PasswordContainerApp::PasswordContainerApp() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void PasswordContainerApp::draw() {
  ci::Color8u background_color("black");
  ci::gl::clear(background_color);
}

}

}