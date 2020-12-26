#include "gui/window/change_key_window.h"

namespace passwordcontainer {

namespace gui {

namespace window {

ChangeKeyWindow::ChangeKeyWindow(PasswordContainer& container,
                                 bool& window_active)
    : container_(container), window_active_(window_active) {
}

void ChangeKeyWindow::DrawWindow() {
  if (window_active_) {
    // Starts the window
    ui::Begin("Change Key:");

    // Creates the input field for the new key
    ui::InputText("New Key", &new_key_);

    // Space between text and button
    ui::Text("");

    // Shows error message if an invalid key is entered
    if (invalid_key_entered_) {
      ui::Text("ERROR : INVALID KEY ENTERED!");
    }

    // Buttons for changing the key and cancelling
    change_key_pressed_ = ui::Button("Change Key");
    cancel_button_pressed_ = ui::Button("Cancel");

    // Ends the window
    ui::End();
  }
}

void ChangeKeyWindow::UpdateWindow() {
  if (window_active_) {
    if (change_key_pressed_) {
      // Checks if the entered key is invalid
      if (new_key_.empty()) {
        invalid_key_entered_ = true;

      } else {
        // Sets the container key to the new key if it isn't valid and closes
        // window
        container_.SetCryptographerKey(new_key_);
        window_active_ = false;
        ResetValuesToDefault();
      }
    }

    // Closes window if the cancel button is pressed
    if (cancel_button_pressed_) {
      window_active_ = false;
      ResetValuesToDefault();
    }
  } else {
    // Makes sure all values are at default when the window is closed
    ResetValuesToDefault();
  }
}

void ChangeKeyWindow::ResetValuesToDefault() {
  invalid_key_entered_ = false;
  change_key_pressed_ = false;
  cancel_button_pressed_ = false;
  new_key_ = "";
}

}  // namespace window

}  // namespace gui

}  // namespace passwordcontainer