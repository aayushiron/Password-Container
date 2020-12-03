#ifndef GUI_MODIFY_ACCOUNT_WINDOW_H
#define GUI_MODIFY_ACCOUNT_WINDOW_H

#include <string>

#include "core/password_container.h"

namespace passwordcontainer {

namespace gui {

class ModifyAccountWindow {
 public:
  // Creates a new Modify Window object with the passed in container and the
  // boolean that represents whether the window should be shown or not. Also
  // takes in an int that represents the account_index of the account being
  // modified.
  ModifyAccountWindow(PasswordContainer& container, bool& window_active,
                      int account_index);

  // Draws the window to modify the account that is currently selected in the
  // container and updates the new_username and new_password parameters.
  void DrawModifyAccountWindow();

  // Updates the details of the account if the confirm button is pressed and
  // the typed in information is accurate, and makes the window disappear if the
  // cancel button is pressed.
  void UpdateModifiedContainer();

 private:
  // Tracks the state of the confirm button in the window
  bool confirm_button_pressed_;
  // Tracks the state of the cancel button in the window
  bool cancel_button_pressed_;
  // Tracks the state of the generate password button in the window
  bool generate_button_pressed_;
  // Boolean that signifies whether the modify window is active.
  bool& modify_window_active_;

  // The container that contains the accounts to be modified
  PasswordContainer& container_;

  // Constants for the minimum and maximum length of the generated password
  const int kGeneratePasswordMinLength = 8;
  const int kGeneratePasswordMaxLength = 32;
  // The length of the random password to be generated
  int generate_password_length_ = kGeneratePasswordMinLength;

  // The index of the account that is having its details modified.
  int account_index_;

  // Strings that represent the new username and password
  std::string new_username_;
  std::string new_password_;
};

}

}

#endif  // GUI_MODIFY_ACCOUNT_WINDOW_H
