#include "gui/password_container_app.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "core/util.h"

namespace passwordcontainer {

namespace gui {

PasswordContainerApp::PasswordContainerApp() : container_(100, "CorrectKey"),
      account_list_(container_, is_modification_requested_,
                    is_deletion_requested_, is_addition_requested_,
                    is_key_change_requested_, selected_item_) {
  ci::app::setWindowSize((int)kWindowSize, (int)kWindowSize);

  // Loads in the data for the container from the specified file.
  // TODO: CREATE WAY FOR USER TO SPECIFY FILE TO BE LOADED IN
  std::ifstream file("../../../tests/resources/Data.pwords");
  file >> container_;
}

void PasswordContainerApp::setup() {
  ui::initialize();
}

void PasswordContainerApp::draw() {
  // Clears the background of the cinder app
  ci::Color8u background_color("black");
  ci::gl::clear(background_color);

  account_list_.DrawWindowAndUpdateValues();
}

void PasswordContainerApp::update() {

}

}  // namespace gui

}  // namespace passwordcontainer