#ifndef CORE_CRYPTOGRAPHER_H
#define CORE_CRYPTOGRAPHER_H

#include <iostream>

namespace passwordcontainer {

class Cryptographer {
 public:
  Cryptographer(size_t offset, const std::string& key);

  // Encrypts the string that is passed in using the character_offset_ and key_.
  std::string EncryptString(const std::string& str) const;

  // Decrypts the string that is passed in using the character_offset_ and key_.
  std::string DecryptString(const std::string& str) const;

  // Sets the key to the passed in value. Throws an invalid_argument exception
  // if the passed in key is empty.
  void SetKey(const std::string& new_key);

  // Gets the key.
  std::string GetKey() const;

  // Sets the character_offset to the passed in value. Throws an
  // invalid_argument exception if offset is lower than the minimum offset.
  void SetOffset(size_t offset);

 private:
  const size_t kMinimumCharacterOffset = 100;

  // The length that 1 encrypted character has in a file
  const size_t kEncryptedCharacterLength = 3;

  // The initial offset used to calculate the final offset. Must be at least
  // kMinimumCharacterOffset.
  size_t character_offset_;

  // The key used to generate a new offset to decrypt/encrypt the data
  std::string key_;

  // Calculates the real offset that is used for encryption using the current
  // character_offset_ and key_.
  size_t CalculateRealOffset() const;

  // Finds out whether the passed in int represents a valid char or not
  bool IsValidChar(int int_representation) const;
};

}  // namespace passwordcontainer

#endif  // CORE_CRYPTOGRAPHER_H
