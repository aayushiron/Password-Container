#include "gui/window/account_list_window.h"

#include <fstream>

#include "core/util.h"

namespace passwordcontainer {

namespace gui {

namespace window {

AccountListWindow::AccountListWindow(PasswordContainer& container,
                                     bool& window_open, bool& modify_bool,
                                     bool& add_bool, bool& key_change_bool,
                                     int& selected_acc_ind,
                                     const std::string& save_location)
    : container_(container),
      modify_account_pressed_(modify_bool),
      add_account_pressed_(add_bool),
      change_key_pressed_(key_change_bool),
      selected_account_(selected_acc_ind),
      window_open_(window_open),
      save_file_location_(save_location) {
}

void AccountListWindow::DrawWindow() {
  if (window_open_) {
    // Starts creating the new window (false as second parameter to get rid of x
    // button at top right of window).
    ui::Begin("Accounts:", false, ImGuiWindowFlags_MenuBar);

    DrawMenuBar();
    DrawAccountList();

    // Finishes creating the new window
    ui::End();
  }
}

void AccountListWindow::UpdateWindow() {
  if (window_open_) {
    if (delete_account_pressed_) {
      // Makes sure that a valid account is selected
      if (selected_account_ >= 0 &&
          selected_account_ < container_.GetAccounts().size()) {
        // Deletes the account
        container_.DeleteAccount(
            container_.GetAccounts()[selected_account_].account_name);

        // Makes sure no account is selected if the index is invalid after
        // deletion
        if (selected_account_ >= container_.GetAccounts().size()) {
          selected_account_ = kNoAccountSelectedIndex;
        }

        // resets the boolean to check if the delete button is pressed
        delete_account_pressed_ = false;
      }
    }

    if (save_pressed_) {
      // Writes the data in the container to the file
      std::ofstream file_output(save_file_location_);
      file_output << container_;
      file_output.close();
    }
  }
}

void AccountListWindow::DrawMenuBar() {
  if (ImGui::BeginMenuBar()) {
    // Draws sub options if the user clicked on the modify list item
    if (ImGui::BeginMenu("Modify List")) {
      DrawMenuSubOption(delete_account_pressed_, "Delete Account");
      DrawMenuSubOption(add_account_pressed_, "Add Account");
      DrawMenuSubOption(modify_account_pressed_, "Edit Account");

      ImGui::EndMenu();
    }

    // Draws sub options if the user clicked on the file item
    if (ImGui::BeginMenu("File")) {
      DrawMenuSubOption(change_key_pressed_, "Change Key");
      DrawMenuSubOption(save_pressed_, "Save");

      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}

void AccountListWindow::DrawMenuSubOption(bool& is_clicked,
                                          const char* option_name) {
  // Creates a submenu item and sets the boolean for the sub option if the
  // button has not already been pressed (this boolean is used in
  // other windows that will change the value to false if it is true)
  if (!is_clicked) {
    is_clicked = ImGui::MenuItem(option_name);
  } else {
    ImGui::MenuItem(option_name);
  }
}

void AccountListWindow::DrawAccountList() {
  // Vector for all the account names in the container
  std::vector<std::string> account_names(container_.GetAccounts().size());

  // Populates the account_names array with the account names
  for (auto index = 0; index < container_.GetAccounts().size(); index++) {
    account_names[index] = (container_.GetAccounts().at(index).account_name);
  }

  // Stores the selected index before the user makes any changes
  int original_index = selected_account_;

  // Draws a list of accounts that shows that selected_account_ account is
  // selected (the function also updates selected_account_ if the user selects
  // another value).
  ui::ListBox("Accounts", &selected_account_,
              util::ConvertStringVecToCharVec(account_names).data(),
              account_names.size());

  // If the account selected changes, close all windows that relate to the
  // previously selected account.
  if (original_index != selected_account_) {
    modify_account_pressed_ = false;
    delete_account_pressed_ = false;
  }
}

}  // namespace window

}  // namespace gui

}  // namespace passwordcontainer