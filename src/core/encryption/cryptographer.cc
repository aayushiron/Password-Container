#include "core/encryption/cryptographer.h"

#include <string>

#include "core/util.h"

using std::string;

namespace passwordcontainer {

Cryptographer::Cryptographer(size_t offset, const std::string& key) {
  if (offset < kMinimumCharacterOffset || key.empty()) {
    throw std::invalid_argument("Invalid parameters passed in to constructor!");
  }

  character_offset_ = offset;
  key_ = key;
}

void Cryptographer::SetKey(const string& new_key) {
  if (new_key.empty()) {
    throw std::invalid_argument("Invalid parameter passed in to SetKey!");
  }

  key_ = new_key;
}

std::string Cryptographer::GetKey() const {
  return key_;
}

void Cryptographer::SetOffset(size_t offset) {
  if (offset < kMinimumCharacterOffset) {
    throw std::invalid_argument("The passed in offset is too small.");
  }

  character_offset_ = offset;
}

string Cryptographer::DecryptString(const string& str) const {
  size_t offset = CalculateRealOffset();
  string decrypted_string;

  // Loops through every encrypted character in the passed in string
  for (size_t index = 0; index < str.size();
       index += kEncryptedCharacterLength) {
    // Gets the int ASCII representation of the char
    string encrypted_char = str.substr(index, kEncryptedCharacterLength);
    int char_int_representation =
        util::ConvertStringToInt(encrypted_char) - offset;

    // Makes sure the encrypted char strings actually refers to a char
    if (!IsValidChar(char_int_representation)) {
      throw std::invalid_argument("Bad string data passed in!");
    }

    // Adds the character to the string
    decrypted_string += static_cast<char>(char_int_representation);
  }

  return decrypted_string;
}

string Cryptographer::EncryptString(const string& str) const {
  size_t offset = CalculateRealOffset();
  string encrypted_string;

  // Encrypts every character in the passed in string and returns it
  for (char c : str) {
    encrypted_string += std::to_string(static_cast<size_t>(c) + offset);
  }

  return encrypted_string;
}

size_t Cryptographer::CalculateRealOffset() const {
  // Counts the total of the ASCII value of each value in the key
  size_t key_ascii_total = 0;
  for (char c : key_) {
    key_ascii_total += c;
  }

  // Adds character_offset_ to each character and takes the average of the
  // for the calculated offset.
  return (key_ascii_total + key_.size() * character_offset_) / key_.size();
}

bool Cryptographer::IsValidChar(int int_representation) const {
  // Returns true if the passed in int represents a tab character, new line
  // character, or any character in the ASCII range of ' ' to '~'
  return int_representation == '\t' || int_representation == '\n' ||
         (int_representation >= ' ' && int_representation <= '~');
}

}  // namespace passwordcontainer