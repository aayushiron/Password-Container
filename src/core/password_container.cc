#include "core/password_container.h"
#include <sstream>

namespace passwordcontainer {

PasswordContainer::PasswordContainer(size_t offset, const std::string& key) {
  if (offset < kMinimumCharacterOffset || key.empty()) {
    throw std::invalid_argument("Invalid parameters passed in to constructor!");
  }

  character_offset_ = offset;
  key_ = key;
}

std::vector<PasswordContainer::AccountDetails> PasswordContainer::GetAccounts() const {
  return accounts_;
}

void PasswordContainer::SetKey(const std::string& new_key) {
  if (new_key.empty()) {
    throw std::invalid_argument("Invalid parameter passed in to SetKey!");
  }

  key_ = new_key;
}

std::istream &operator>>(std::istream& input, PasswordContainer& container) {
  // Code to get all data from the input file found here:
  // https://stackoverflow.com/questions/3203452/how-to-read-entire-stream-into-a-stdstring
  std::string encrypted_string(std::istreambuf_iterator<char>(input), {});
  std::string decrypted_string = container.DecryptString(encrypted_string);

  container.AddAllData(decrypted_string);

  return input;
}

std::ostream &operator<<(std::ostream& output, const PasswordContainer& container) {
  std::string data_representation = container.GenerateStringRepresentation();
  output << container.EncryptString(data_representation);

  return output;
}

std::string PasswordContainer::DecryptString(const std::string& str) const {
  size_t offset = CalculateRealOffset();
  std::string decrypted_string;

  // Loops through every encrypted character in the passed in string
  for (size_t index = 0; index < str.size(); index += kEncryptedCharacterLength) {
    // Gets the int ASCII representation of the char
    std::string encrypted_char = str.substr(index, kEncryptedCharacterLength);
    int char_int_representation = ConvertStringToInt(encrypted_char) - offset;

    // Makes sure the encrypted char strings actually refers to a char
    if (!IsValidChar(char_int_representation)) {
      throw std::invalid_argument("Bad string data passed in!");
    }

    // Adds the character to the string
    decrypted_string += static_cast<char>(char_int_representation);
  }

  return decrypted_string;
}

std::string PasswordContainer::EncryptString(const std::string& str) const {
  size_t offset = CalculateRealOffset();
  std::string encrypted_string;

  // Encrypts every character in the passed in string and returns it
  for (char c : str) {
    encrypted_string += std::to_string(static_cast<size_t>(c) + offset);
  }

  return encrypted_string;
}

std::string PasswordContainer::GenerateStringRepresentation() const {
  std::string string_representation;

  // Loops through all accounts and adds their details to the final string
  for (const AccountDetails& account : accounts_) {
    string_representation += account.name + '\t' +
                             account.username + '\t' +
                             account.password + '\n';
  }

  // Removes the trailing \n character from the string
  if (string_representation.size() != 0) {
    string_representation.pop_back();
  }

  return string_representation;
}

void PasswordContainer::AddAllData(const std::string& decrypted_string) {
  std::stringstream decrypted_stream(decrypted_string);
  std::string current_line;

  // Loops through all lines and adds the data from all of them
  while (getline(decrypted_stream, current_line, '\n')) {
    AddOneAccountData(current_line);
  }
}

void PasswordContainer::AddOneAccountData(const std::string& line_data) {
  std::string current_detail;
  std::stringstream line_stream(line_data);
  AccountDetails current_account; // Creates a new AccountDetails object

  // Loops through all data in the current line
  for (size_t detail_index = 0; detail_index < kNumDetails; detail_index++) {
    // Throws an error if data is missing
    if (!getline(line_stream, current_detail, '\t')) {
      throw std::invalid_argument("Bad data passed in!");
    }

    // Adds the information to the AccountDetails based on what detail the
    // program currently is on
    switch (detail_index) {
      case 0:
        current_account.name = current_detail;
        break;
      case 1:
        current_account.username = current_detail;
        break;
      case 2:
        current_account.password = current_detail;
        break;
    }
  }

  accounts_.push_back(current_account);
}

size_t PasswordContainer::CalculateRealOffset() const {
  // Counts the total of the ASCII value of each value in the key
  size_t key_ascii_total = 0;
  for (char c : key_) {
    key_ascii_total += c;
  }

  // Adds character_offset_ to each character and takes the average of the
  // for the calculated offset.
  return (key_ascii_total + key_.size() * character_offset_) / key_.size();
}

bool PasswordContainer::IsValidChar(int int_representation) const {
  // Returns true if the passed in int represents a tab character, new line
  // character, or any character in the ASCII range of ' ' to '~'
  return int_representation == '\t' || int_representation == '\n' ||
         (int_representation >= ' ' && int_representation <= '~');
}

int PasswordContainer::ConvertStringToInt(
    const std::string& to_convert) const {
  // Creates a new string stream and puts the passed in string into the string
  // stream
  std::stringstream string_stream;
  string_stream << to_convert;

  // Makes sure that the passed in string can be converted to an int
  int asInt;
  if (!(string_stream >> asInt)) {
    throw std::invalid_argument("Cannot convert\"" + to_convert + "\"to int.");
  }

  return asInt;
}

}  // namespace passwordcontainer