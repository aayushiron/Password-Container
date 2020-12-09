#ifndef GUI_WINDOW_ENTER_KEY_WINDOW_H
#define GUI_WINDOW_ENTER_KEY_WINDOW_H

#include "core/password_container.h"
#include "gui/window/window.h"

namespace passwordcontainer {

namespace gui {

namespace window {

// Class that is an implementation of the Window interface. This window shows up
// before all other windows and doesn't allow the user farther until they input
// the correct key. The window is very simple and only has a text box and a
// continue button.
class EnterKeyWindow : public Window {
 public:
  // Creates a new window to enter the key using the passed in container that
  // represents the container the data is getting loaded into and a boolean
  // representing the correct key being entered. Also takes in a string that
  // represents the location of the save file.
  EnterKeyWindow(PasswordContainer& container, bool& correct_key_entered,
                 const std::string& save_location);

  // Draws and updates the values of the window
  void DrawWindow() override;
  void UpdateWindow() override;

 private:
  // The container the data is being loaded into
  PasswordContainer& container_;

  // Boolean that checks if the correct key was entered
  bool& correct_key_entered_;
  // Boolean that checks if an error message is to be shown
  bool wrong_key_entered_ = false;
  // Boolean that checks if the continue button was pressed
  bool continue_pressed_ = false;

  // The key that is being entered
  std::string entered_key_;
  // The location of the save file
  std::string save_file_location_;
};

}  // namespace window

}  // namespace gui

}  // namespace passwordcontainer

#endif  // GUI_WINDOW_ENTER_KEY_WINDOW_H
