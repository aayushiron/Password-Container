#include "gui/account_list.h"
#include "core/util.h"

#include <CinderImGui.h>

namespace passwordcontainer {

namespace gui {

AccountList::AccountList(const PasswordContainer &container,
                         bool &modify_bool, bool &delete_bool, bool &add_bool,
                         bool &key_change_bool, int &selected_acc_ind)
    : container_(container), modify_account_pressed_(modify_bool),
      delete_account_pressed_(delete_bool), add_account_pressed_(add_bool),
      change_key_pressed_(key_change_bool), selected_account_(selected_acc_ind){}

void AccountList::DrawWindowAndUpdateValues() {
  // TODO: CHANGE TO MORE REPRESENTATIVE VALUE
  bool window_active = true;

  // Starts creating the new window
  ui::Begin("Accounts:", &window_active, ImGuiWindowFlags_MenuBar);

  DrawMenuBar();
  DrawAccountList();

  // Finishes creating the new window
  ui::End();
}

void AccountList::DrawMenuBar() {
  if (ImGui::BeginMenuBar())
  {
    // Draws sub options if the user clicked on the modify list item
    if (ImGui::BeginMenu("Modify List"))
    {
      DrawMenuSubOption(delete_account_pressed_, "Delete Account");
      DrawMenuSubOption(add_account_pressed_, "Add Account");
      DrawMenuSubOption(modify_account_pressed_, "Edit Account");

      ImGui::EndMenu();
    }

    // Draws sub options if the user clicked on the security item
    if (ImGui::BeginMenu("Security"))
    {
      DrawMenuSubOption(change_key_pressed_, "Change Key");

      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}

void AccountList::DrawMenuSubOption(bool &is_clicked, const char* option_name) {
  // Creates a submenu item and sets the boolean for the sub option if the
  // button has not already been pressed (this boolean is used in
  // other windows that will change the value to false if it is true)
  if (!is_clicked) {
    change_key_pressed_ = ImGui::MenuItem(option_name);
  } else {
    ImGui::MenuItem(option_name);
  }
}

void AccountList::DrawAccountList() {
  // Vector for all the account names in the container
  std::vector<std::string> account_names(container_.GetAccounts().size());

  // Populates the account_names array with the account names
  for (auto index = 0; index < container_.GetAccounts().size(); index++) {
    account_names[index] = (container_.GetAccounts().at(index).account_name);
  }

  // Draws a list of accounts that shows that selected_account_ account is
  // selected (the function also updates selected_account_ if the user selects
  // another value).
  ui::ListBox("Accounts", &selected_account_,
              util::ConvertStringVecToCharVec(account_names).data(),
              account_names.size());
}

}  // namespace gui

}  // namespace passwordcontainer