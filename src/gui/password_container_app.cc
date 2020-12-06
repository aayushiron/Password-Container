#include "gui/password_container_app.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "core/util.h"

namespace passwordcontainer {

namespace gui {

PasswordContainerApp::PasswordContainerApp() : container_(100, "CorrectKey"),
      account_list_(container_, is_file_decrypted_, is_modification_requested_,
                    is_deletion_requested_, is_addition_requested_,
                    is_key_change_requested_, selected_item_),
      modify_account_window_(container_, is_modification_requested_,
                             selected_item_),
      account_details_window_(container_, selected_item_),
      add_account_window_(container_, is_addition_requested_),
      change_key_window_(container_, is_key_change_requested_),
      enter_key_window_(container_, is_file_decrypted_) {
  ci::app::setWindowSize((int)kWindowSize, (int)kWindowSize);
}

void PasswordContainerApp::setup() {
  ui::initialize();
}

void PasswordContainerApp::draw() {
  // Clears the background of the cinder app
  ci::Color8u background_color("black");
  ci::gl::clear(background_color);

  enter_key_window_.DrawWindow();
  account_list_.DrawWindow();
  modify_account_window_.DrawWindow();
  account_details_window_.DrawWindow();
  add_account_window_.DrawWindow();
  change_key_window_.DrawWindow();
}

void PasswordContainerApp::update() {
  // Updates the state of all windows
  enter_key_window_.UpdateWindow();
  account_list_.UpdateWindow();
  modify_account_window_.UpdateWindow();
  account_details_window_.UpdateWindow();
  add_account_window_.UpdateWindow();
  change_key_window_.UpdateWindow();
}

}  // namespace gui

}  // namespace passwordcontainer