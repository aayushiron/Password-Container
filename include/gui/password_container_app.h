#ifndef GUI_PASSWORD_CONTAINER_MAIN_H
#define GUI_PASSWORD_CONTAINER_MAIN_H

#include <CinderImGui.h>
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <string>

#include "core/password_container.h"
#include "gui/account_list.h"

namespace passwordcontainer {

namespace gui {

class PasswordContainerApp : public ci::app::App {
 public:
  PasswordContainerApp();

  // Overridden Cinder methods to setup the app, draw the window, and updating
  // values.
  void setup() override;
  void draw() override;
  void update() override;

 private:
  // The container used to store account information
  PasswordContainer container_;

  // The account list object used as the main window
  AccountList account_list_;

  // Booleans to track the action the user expects to be executed
  bool is_modification_requested_;
  bool is_addition_requested_;
  bool is_deletion_requested_;
  bool is_container_loaded_;
  bool is_key_change_requested_;

  // The index of the selected item in the list of accounts. Defaults to a value
  // where there is no account selected.
  int selected_item_ = kNoAccountSelectedIndex;

  // Constants for the window size
  const double kWindowSize = 600;
};

}  // namespace gui

}  // namespace passwordcontainer

#endif  // GUI_PASSWORD_CONTAINER_MAIN_H
