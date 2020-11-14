#include "gui/password_container_app.h"

#include <iostream>

namespace passwordcontainer {

namespace gui {

PasswordContainerApp::PasswordContainerApp() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
  button_pressed_ = false;
  counter_ = 0;
}

void PasswordContainerApp::setup() {
  ui::initialize();
}

void PasswordContainerApp::draw() {
  bool my_tool_active = true;
  ui::Begin("Counter App", &my_tool_active, ImGuiWindowFlags_MenuBar);

  // Clears the background of the cinder app
  ci::Color8u background_color("black");
  ci::gl::clear(background_color);

  // Adds the counter text and button
  std::string counter_text = "Counter: " + std::to_string(counter_);
  ui::Text("%s", counter_text.c_str());
  button_pressed_ = ui::Button( "Add 1" );
  ui::End();
}

void PasswordContainerApp::update() {
  if (button_pressed_) {
    counter_++;
    button_pressed_ = false;
  }
}

}  // namespace gui

}  // namespace passwordcontainer