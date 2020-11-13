#ifndef CORE_PASSWORD_CONTAINER_H
#define CORE_PASSWORD_CONTAINER_H

#include <iostream>
#include <vector>

namespace passwordcontainer {

// The class that contains all the data for the username and passwords. Can read
// and write encrypted data.
//
// The encryption used in this container utilizes a key that has the int values
// of all characters in it plus a specified offset averaged to find a newly
// calculated offset. That is then used to encrypt a  string by adding the
// calculated offset to each character in the data or decrypt the data by
// subtracting the offset from each character.
class PasswordContainer {
 public:
  // A Struct that contains the final details of the accounts for the program to
  // use.
  struct AccountDetails {
    // Simple constructor that defines the account name, username and password
    // of the account this object represents.
    AccountDetails(std::string acc_name,
                   std::string user,
                   std::string pass)
        : name(acc_name), username(user), password(pass) {}

    // The name (what website the account is for) of the account
    std::string name;
    // The username and password of the account
    std::string username;
    std::string password;
  };

  // Creates a new PasswordContainer using the passed in offset and key. Throws
  // an invalid_argument exception if the offset is less than
  // minimum_character_offset_ or if the key is an empty string.
  PasswordContainer(size_t offset, std::string key);

  // Returns the vector of AccountDetails that contains information for all
  // loaded in accounts.
  std::vector<AccountDetails> GetAccounts() const;

  // Sets the key to the passed in value
  void SetKey(const std::string& new_key);

  // Overloaded >> operator used to read in a file of encrypted username and
  // password data.
  //
  // Takes in an istream called input that represents the input that contains
  // data for the encrypted data. Also takes in a PasswordContainer called
  // container that is the container where the data is being loaded into.
  friend std::istream &operator>>(std::istream& input,
                                  PasswordContainer& container);

  // Overloaded << operator that is used to output a string that represents
  // encrypted password and username data.
  //
  // Takes in an ostream called output that represents the output of the
  // container. Also takes in a PasswordContainer called container that is the
  // container that is the container where data is being read from.
  friend std::ostream &operator<<(std::ostream& output,
                                  PasswordContainer& container);

 private:
  const size_t minimum_character_offset_ = 100;

  // The initial offset used to calculate the final offset. Must be at least
  // minimum_character_offset_.
  size_t character_offset_;

  // The key used to generate a new offset to decrypt/encrypt the data
  std::string key_;

  // A vector of all accounts stored in the program
  std::vector<AccountDetails> accounts_;

  // Encrypts the string that is passed in using the character_offset_ and key_.
  std::string EncryptString(const std::string& str);

  // Decrypts the string that is passed in using the character_offset_ and key_.
  std::string DecryptString(const std::string& str);
};

}  // namespace passwordcontainer

#endif  // CORE_PASSWORD_CONTAINER_H
