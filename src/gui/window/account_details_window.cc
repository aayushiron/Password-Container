#include "gui/window/account_details_window.h"

#include <CinderImGui.h>

#include <string>

#include "core/util.h"

namespace passwordcontainer {

namespace gui {

namespace window {

AccountDetailsWindow::AccountDetailsWindow(const PasswordContainer& container,
                                           int& account_index)
    : container_(container),
      account_index_(account_index) {}

void AccountDetailsWindow::DrawWindow() {
  if (window_open_) {
    // Starts creating the new window
    ui::Begin("Account Details:");

    // Adds text for the account name
    ui::Text(("Account:  " + account_name_).c_str());

    // Creates two un-editable text boxes so users can copy data
    ui::InputText("Username", &username_, ImGuiInputTextFlags_ReadOnly);
    ui::InputText("Password", &password_, ImGuiInputTextFlags_ReadOnly);

    // Adds a space
    ui::Text("");

    // Sets the flag to copy the password to the clipboard based on whether the
    // button was pressed
    copy_password_pressed_ = ui::Button("Copy Password");

    ui::End();
  }
}

void AccountDetailsWindow::UpdateWindow() {
  // Makes sure that the current index is a valid account in the container
  if (account_index_ >= 0 || account_index_ < container_.GetAccounts().size()) {
    window_open_ = true;

    // Updates all the variables to hold the correct data
    account_name_ = container_.GetAccounts()[account_index_].account_name;
    username_ = container_.GetAccounts()[account_index_].username;
    password_ = container_.GetAccounts()[account_index_].password;

    // Copies the password to the clipboard if the button is pressed
    if (copy_password_pressed_) {
      util::CopyToClipboard(password_);
    }
  } else {
    // Makes sure the button for copying isn't clicked and the window is closed
    window_open_ = false;
    copy_password_pressed_ = false;
  }
}

}

}

}