#include "gui/window/add_account_window.h"

#include "core/util.h"

namespace passwordcontainer {

namespace gui {

namespace window {

AddAccountWindow::AddAccountWindow(PasswordContainer &container,
                                   bool &window_active)
    : container_(container), window_active_(window_active) {
}

void AddAccountWindow::DrawWindow() {
  if (window_active_) {
    // Creates the window
    ui::Begin("Add Account:");

    // Adds the text inputs for all 3 details of the new account
    ui::InputText("Account Name", &account_name_);
    ui::InputText("Username", &username_);
    ui::InputText("Password", &password_);

    // Adds a space between the slider and the inputs
    ui::Text("");

    // Creates the slider for the length of the password and the button to
    // generate a new password
    ui::SliderInt("Password Length", &generate_password_length_,
                  kGeneratePasswordMinLength, kGeneratePasswordMaxLength);
    generate_button_pressed_ = ui::Button("Generate Password");

    // Adds a space between the generate button and the confirmation button
    ui::Text("");

    // Adds an error message if the account already exists
    if (account_already_exists_) {
      ui::Text("ERROR: ACCOUNT ALREADY EXISTS");
    }

    // Adds an error message if fields are left blank
    if (invalid_details_entered_) {
      ui::Text("ERROR: INVALID DETAILS ENTERED");
    }

    // Creates buttons to add accounts and cancel the addition of an account
    add_button_pressed_ = ui::Button("Add Account");
    cancel_button_pressed_ = ui::Button("Cancel");

    // Stops the window creation
    ui::End();
  }
}

void AddAccountWindow::UpdateWindow() {
  if (window_active_) {
    if (add_button_pressed_) {
      // Sets error states to default values before processing input
      account_already_exists_ = false;
      invalid_details_entered_ = false;

      if (account_name_.empty() || username_.empty() || password_.empty()) {
        invalid_details_entered_ = true;

      } else if (container_.HasAccount(account_name_)) {
        account_already_exists_ = true;

      } else {
        // Adds the account if the inputs are valid and resets values
        container_.AddAccount(account_name_, username_, password_);
        window_active_ = false;
        ResetValuesToDefault();
      }
    }

    if (cancel_button_pressed_) {
      // Closes the window if the cancel button is pressed
      window_active_ = false;
      ResetValuesToDefault();
    }

    if (generate_button_pressed_) {
      // Sets the password field to a randomly generated password based on the
      // value of the slider.
      password_ = util::GenerateRandomPassword(generate_password_length_);
    }
  } else {
    // Makes sure values are default if the window isn't open
    ResetValuesToDefault();
  }
}

void AddAccountWindow::ResetValuesToDefault() {
  account_name_ = "";
  username_ = "";
  password_ = "";
  invalid_details_entered_ = false;
  account_already_exists_ = false;
  cancel_button_pressed_ = false;
  add_button_pressed_ = false;
}

}  // namespace window

}  // namespace gui

}  // namespace passwordcontainer