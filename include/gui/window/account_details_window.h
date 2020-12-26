#ifndef GUI_ACCOUNT_DETAILS_WINDOW_H
#define GUI_ACCOUNT_DETAILS_WINDOW_H

#include <string>

#include "core/password_container.h"
#include "gui/window/window.h"

namespace passwordcontainer {

namespace gui {

namespace window {

// This class is an implementation of the Window interface that shows the
// details of the account that is currently selected. This window has two
// uneditable text fields for the username and passwords so that the user can
// select the text. There is also a button that allows the user to copy the
// password to the clipboard.
class AccountDetailsWindow : public Window {
 public:
  // Creates a new AccountDetailsWindow that is getting data from the passed in
  // container and is getting data from the account at the passed in
  // account_index in the container.
  AccountDetailsWindow(const PasswordContainer& container, int& account_index);

  // Draws the window and all fields based on the state of all the variables.
  // Doesn't draw the window if no account is currently selected.
  void DrawWindow() override;

  // Updates the state of all variables in the window based on the current
  // account_index_ and whether buttons were pressed.
  void UpdateWindow() override;

 private:
  // The container used to store all the account data
  const PasswordContainer& container_;

  // The index of the current account
  int& account_index_;

  // Booleans for whether the window is open or if the copy button is pressed
  bool window_open_ = false;
  bool copy_password_pressed_ = false;

  // The account name, username, and password that are in the account at
  // account_index
  std::string account_name_;
  std::string username_;
  std::string password_;
};

}  // namespace window

}  // namespace gui

}  // namespace passwordcontainer

#endif  // GUI_ACCOUNT_DETAILS_WINDOW_H
