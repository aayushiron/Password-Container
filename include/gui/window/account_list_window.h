#ifndef GUI_ACCOUNT_LIST_H
#define GUI_ACCOUNT_LIST_H

#include "core/password_container.h"
#include "gui/window/window.h"

namespace passwordcontainer {

namespace gui {

namespace window {

// This class represents the main window of the gui. The main window has a menu
// bar that allows you to modify the accounts, delete the accounts, add
// accounts, and the change the key for the encryption. It also has a list of
// Account names that is the main interface for indicating the selected account.
class AccountListWindow : public Window {
 public:
  // Creates a new AccountListWindow object using the passed in container, booleans,
  // and the current selected account index. Assumes that all values are valid
  // when creating objects.
  AccountListWindow(PasswordContainer& container_, bool& modify_bool,
                    bool& delete_bool, bool& add_bool, bool& key_change_bool,
                    int& selected_acc_ind);

  // Draws the window with the menu bar and a list of all accounts. Updates the
  // values of all booleans and integers that might be used by other windows.
  void DrawWindow() override;

  // Deletes the selected account if the delete option is pressed in the menu
  // bar
  void UpdateWindow() override;

 private:
  // The password container where all of the account information is found.
  PasswordContainer& container_;

  // Booleans that represents whether a certain button is pressed in the menu
  // bar
  bool& modify_account_pressed_;
  bool& delete_account_pressed_;
  bool& add_account_pressed_;
  bool& change_key_pressed_;

  // The index of the account that is currently selected in the list
  int& selected_account_;

  // Draws the menu bar and updates all variables that relate to the menu bar.
  void DrawMenuBar();

  // Draws a sub option in the menu that uses the passed in is_clicked boolean
  // to check whether the option has been clicked. Uses the passed in
  // option_name as the name of the option in the menu. The menu does not update
  // the boolean if is_clicked is true.
  void DrawMenuSubOption(bool& is_clicked, const char* option_name);

  // Draws the Account list and updates all variables that relate to the
  // account list.
  void DrawAccountList();
};

}

}  // namespace gui

}  // namespace passwordcontainer

#endif  // GUI_ACCOUNT_LIST_H
