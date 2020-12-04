#ifndef GUI_MODIFY_ACCOUNT_WINDOW_H
#define GUI_MODIFY_ACCOUNT_WINDOW_H

#include <string>

#include "core/password_container.h"
#include "gui/window/window.h"

namespace passwordcontainer {

namespace gui {

namespace window {

// This class represents the window where account details can be modified. The
// window has two text input fields so that users can input their new username
// and password. There is also a slider that allows you to generate a password
// and a button to start the generation, and a button to change the details and
// cancel the modification. Finally, an error message shows up if invalid
// details are entered.
class ModifyAccountWindow : public Window {
 public:
  // Creates a new Modify Window object with the passed in container and the
  // boolean that represents whether the window should be shown or not. Also
  // takes in an int that represents the account_index of the account being
  // modified.
  ModifyAccountWindow(PasswordContainer& container, bool& window_active,
                      int& account_index);

  // Draws the window to modify the account that is currently selected in the
  // container and updates the new_username and new_password parameters.
  void DrawWindow() override;

  // Updates the details of the account if the confirm button is pressed and
  // the typed in information is accurate, and makes the window disappear if the
  // cancel button is pressed.
  void UpdateWindow() override;

 private:
  // Boolean that tracks whether a window was newly opened
  bool window_newly_opened_;
  // Boolean that signifies whether the details entered in are invalid (Shows
  // error message)
  bool invalid_details_entered_;
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
  int& account_index_;

  // Strings that represent the new username and password
  std::string new_username_;
  std::string new_password_;

  // Tries to change the details for the selected account, but sets flags for
  // showing an error message when an invalid input is entered.
  void TryChangingDetails();

  // Resets all the booleans and private variables to their default values for
  // use the next time the window is opened.
  void ResetValuesToDefault();
};

}

}

}

#endif  // GUI_MODIFY_ACCOUNT_WINDOW_H
