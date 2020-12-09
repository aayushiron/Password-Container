#ifndef GUI_WINDOW_CHANGE_KEY_WINDOW_H
#define GUI_WINDOW_CHANGE_KEY_WINDOW_H

#include "core/password_container.h"
#include "gui/window/window.h"

namespace passwordcontainer {

namespace gui {

namespace window {

// This class is an implementation of the Window interface. This window allows
// the encryption key of the container to be changed to better encrypt the file.
// The user can input a new key and change it. The window doesn't allow empty
// keys.
class ChangeKeyWindow : public Window {
 public:
  // Creates a new ChangeKeyWindow object with the passed in container and
  // boolean that represents whether the window should be open or not.
  ChangeKeyWindow(PasswordContainer& container, bool& window_active);

  // Draws the window and allows editing of the key.
  void DrawWindow() override;

  // Updates the window parameters and the container if necessary
  void UpdateWindow() override;

 private:
  // The container which is having its key changed
  PasswordContainer& container_;

  // Checks if the window should currently be active
  bool& window_active_;
  // Checks if invalid input was entered
  bool invalid_key_entered_ = false;
  // Booleans to see if any buttons were pressed
  bool change_key_pressed_ = false;
  bool cancel_button_pressed_ = false;

  // The new key that the user inputs
  std::string new_key_;

  // Resets all values back to their default states (used when closing window or
  // reopening the window).
  void ResetValuesToDefault();
};

}  // namespace window

}  // namespace gui

}  // namespace passwordcontainer

#endif  // GUI_WINDOW_CHANGE_KEY_WINDOW_H
