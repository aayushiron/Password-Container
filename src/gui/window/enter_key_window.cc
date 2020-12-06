#include "gui/window/enter_key_window.h"

#include <fstream>

namespace passwordcontainer {

namespace gui {

namespace window {

EnterKeyWindow::EnterKeyWindow(PasswordContainer &container,
                               bool &correct_key_entered,
                               const std::string& save_location)
    : container_(container), correct_key_entered_(correct_key_entered),
      save_file_location_(save_location) {}

void EnterKeyWindow::DrawWindow() {
  if (!correct_key_entered_) {
    // Starts creating the window
    ui::Begin("Enter Key:");

    // Input text for the key
    ui::InputText("Key", &entered_key_);

    // Space between button and input text
    ui::Text("");

    // Shows error message if the wrong key was entered
    if (wrong_key_entered_) {
      ui::Text("ERROR: THE WRONG KEY HAS BEEN ENTERED!");
    }

    // Button to submit key
    continue_pressed_ = ui::Button("Continue");

    // Finishes creating the window
    ui::End();
  }
}

void EnterKeyWindow::UpdateWindow() {
  if (!correct_key_entered_) {
    // Checks if the continue button is pressed
    if (continue_pressed_) {
      try {
        // Tries to change the key
        container_.SetCryptographerKey(entered_key_);
        // Tries to load the save file into the container
        std::ifstream save_file(save_file_location_);
        save_file >> container_;

        // Sets boolean to true if there were no errors thrown when loading
        correct_key_entered_ = true;
      } catch (...) {
        // If an error was thrown, a wrong key was entered
        wrong_key_entered_ = true;
      }
    }
  }
}

}  // namespace window

}  // namespace gui

}  // namespace passwordcontainer