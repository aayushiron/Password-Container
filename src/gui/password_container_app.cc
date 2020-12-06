#include "gui/password_container_app.h"

#include <fstream>

namespace passwordcontainer {

namespace gui {

PasswordContainerApp::PasswordContainerApp() :
      container_(kDefaultOffset, kDefaultKey),
      account_list_(container_, is_file_decrypted_, is_modification_requested_,
                    is_addition_requested_, is_key_change_requested_,
                    selected_item_, kSaveFileLocation),
      modify_account_window_(container_, is_modification_requested_,
                             selected_item_),
      account_details_window_(container_, selected_item_),
      add_account_window_(container_, is_addition_requested_),
      change_key_window_(container_, is_key_change_requested_),
      enter_key_window_(container_, is_file_decrypted_, kSaveFileLocation) {
  ci::app::setWindowSize((int)kWindowSize, (int)kWindowSize);
}

void PasswordContainerApp::setup() {
  ui::initialize();

  // Creates a new input stream to see if the file at kSaveFileLocation exists
  std::ifstream input_file(kSaveFileLocation);
  if (!input_file.is_open()) {
    // Creates a new file at kSaveFileLocation if no file already exists there
    std::ofstream output_file(kSaveFileLocation);
    output_file.close();

    // Makes sure the window to enter the key doesn't show up
    is_file_decrypted_ = true;
  }
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