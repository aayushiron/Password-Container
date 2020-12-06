#ifndef GUI_WINDOW_ADD_ACCOUNT_WINDOW_H
#define GUI_WINDOW_ADD_ACCOUNT_WINDOW_H

#include "core/password_container.h"
#include "gui/window/window.h"

namespace passwordcontainer {

namespace gui {

namespace window {

// This class represents a window that uses the window interface. This window
// allows a user to add their a new account to the list of all accounts that
// already are in the app. The window has a text field for the account name,
// username, and password.
class AddAccountWindow : public Window {
 public:
  // Creates a new AddAccountWindow object that represents a window for the
  // user to add accounts from. Takes a PasswordContainer and a boolean
  // called window_active that represents if the window is active or not.
  AddAccountWindow(PasswordContainer& container, bool& window_active);

  // Draws the window to add accounts if the window is to be shown and allows
  // user input.
  void DrawWindow() override;

  // Updates the window to either show an error state or add an account with the
  // specified account name, username and password to the container.
  void UpdateWindow() override;

 private:
  // The container that is having accounts added to it
  PasswordContainer& container_;

  // The boolean for whether or not the window is currently active
  bool& window_active_;
  // Booleans for invalid inputs entered
  bool account_already_exists_ = false;
  bool invalid_details_entered_ = false;
  // Booleans for the 2 buttons in the window
  bool cancel_button_pressed_ = false;
  bool add_button_pressed_ = false;

  // Strings that represent the values added to the text boxes.
  std::string account_name_;
  std::string username_;
  std::string password_;

  void ResetValuesToDefault();
};

}  // namespace window

}  // namespace gui

}  // namespace passwordcontainer

#endif  // GUI_WINDOW_ADD_ACCOUNT_WINDOW_H
