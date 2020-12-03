#include "gui/modify_account_window.h"
#include "core/util.h"

#include <CinderImGui.h>

namespace passwordcontainer {

namespace gui {

ModifyAccountWindow::ModifyAccountWindow(PasswordContainer& container,
                                         bool& window_active,
                                         int& account_index)
    : container_(container), modify_window_active_(window_active),
      account_index_(account_index) {}

void ModifyAccountWindow::DrawModifyAccountWindow() {
  // Makes sure the modify window is supposed to be active
  if (modify_window_active_) {
    // Starts creating the new window
    ui::Begin("Modifying Account:");

    // Adds the text inputs for the new username and password
    ui::InputText("New Username", &new_username_, kGeneratePasswordMaxLength);
    ui::InputText("New Password", &new_password_, kGeneratePasswordMaxLength);

    // Adds a space between the slider and the inputs
    ui::Text("");

    // Creates the slider for the length of the password and the button to
    // generate a new password
    ui::SliderInt("Password Length", &generate_password_length_, kGeneratePasswordMinLength, kGeneratePasswordMaxLength);
    generate_button_pressed_ = ui::Button("Generate Password");

    // Adds a space
    ui::Text("");

    // Shows an error message if invalid details have been inputted
    if (invalid_details_entered_) {
      ui::Text("ERROR: INVALID INPUT ENTERED");
    }

    // Adds the button to change details and the button to cancel
    confirm_button_pressed_ = ui::Button("Change details");
    cancel_button_pressed_ = ui::Button("Cancel");

    // Finishes creating the new window
    ui::End();
  }
}

void ModifyAccountWindow::UpdateModifiedContainer() {
  if (modify_window_active_) {
    // Makes sure the account being edited doesn't exist or if
    // the cancel button is pressed.
    if (account_index_ < 0 ||
        account_index_ >= container_.GetAccounts().size() ||
        cancel_button_pressed_) {
      ResetValuesToDefault();

    } else if (confirm_button_pressed_) {
      TryChangingDetails();

    } else if (generate_button_pressed_) {
      // Sets the password field to a randomly generated password based on the
      // value of the slider.
      new_password_ = util::GenerateRandomPassword(generate_password_length_);

    } else if (window_newly_opened_) {
      // Sets the current username and password as the values in the text inputs
      // when the window is newly opened
      new_username_ = container_.GetAccounts()[account_index_].username;
      new_password_ = container_.GetAccounts()[account_index_].password;
      window_newly_opened_ = false;
    }

  } else {
    // Resets all values if the window is closed.
    ResetValuesToDefault();
  }
}

void ModifyAccountWindow::TryChangingDetails() {
  // Makes sure both the username and password are valid
  if (new_username_ != "" && new_password_ != "") {
    // Changes the details of the account being edited if the new details
    // are valid
    std::string account_name = container_.GetAccounts()[account_index_].account_name;
    container_.ModifyAccount(account_name, new_username_, new_password_);

    ResetValuesToDefault();
  } else {
    // Sets flags for the program to show an error message
    invalid_details_entered_ = true;
    confirm_button_pressed_ = false;
  }
}

void ModifyAccountWindow::ResetValuesToDefault() {
  modify_window_active_ = false;
  cancel_button_pressed_ = false;
  generate_button_pressed_ = false;
  confirm_button_pressed_ = false;
  invalid_details_entered_ = false;
  window_newly_opened_ = true;
  generate_password_length_ = kGeneratePasswordMinLength;
}

}  // namespace gui

}  // namespace passwordcontainer