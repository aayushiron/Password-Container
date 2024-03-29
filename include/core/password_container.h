#ifndef CORE_PASSWORD_CONTAINER_H
#define CORE_PASSWORD_CONTAINER_H

#include <iostream>
#include <string>
#include <vector>

#include "core/encryption/cryptographer.h"

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
    // The name (what website the account is for) of the account
    std::string account_name;
    // The username and password of the account
    std::string username;
    std::string password;
  };

  // Creates a new PasswordContainer using the passed in offset and key. Throws
  // an invalid_argument exception if the offset is less than
  // kMinimumCharacterOffset or if the key is an empty string.
  PasswordContainer(size_t offset, const std::string& key);

  // Returns the vector of AccountDetails that contains information for all
  // loaded in accounts.
  std::vector<AccountDetails> GetAccounts() const;

  // Sets the key to the passed in value. Throws an invalid_argument exception
  // if the passed in key is empty.
  void SetCryptographerKey(const std::string& new_key);

  // Gets the key.
  std::string GetCryptographerKey() const;

  // Sets the character_offset to the passed in value. Throws an
  // invalid_argument exception if offset is lower than the minimum offset.
  void SetCryptographerOffset(size_t offset);

  // Adds a new account with the passed in account_name, username, and password.
  //
  // Throws an invalid_argument exception if account_name, username, or password
  // are empty. Also throws an invalid_argument exception if there is already an
  // account with account_name.
  void AddAccount(const std::string& account_name, const std::string& username,
                  const std::string& password);

  // Deletes the account with the passed in account_name.
  //
  // Throws an invalid_argument exception if there is no account with the passed
  // in account_name.
  void DeleteAccount(const std::string& account_name);

  // Modifies the account with the passed in account_name to have the passed in
  // username and password.
  //
  // Throws an invalid_argument exception if there is no account with the passed
  // in account name. Also throws the exception if the username or password is
  // empty.
  void ModifyAccount(const std::string& account_name,
                     const std::string& username, const std::string& password);

  // Returns a boolean that signifies whether there is an account with the
  // passed in account_name in the file.
  bool HasAccount(const std::string& account_name);

  // Finds the iterator that refers to the AccountDetails object is referred to
  // by the passed in account_name.
  std::vector<AccountDetails>::iterator FindAccount(
      const std::string& account_name);

  // Overloaded >> operator used to read in a file of encrypted username and
  // password data.
  //
  // Takes in an istream called input that represents the input that contains
  // data for the encrypted data. Also takes in a PasswordContainer called
  // container that is the container where the data is being loaded into.
  friend std::istream& operator>>(std::istream& input,
                                  PasswordContainer& container);

  // Overloaded << operator that is used to output a string that represents
  // encrypted password and username data.
  //
  // Takes in an ostream called output that represents the output of the
  // container. Also takes in a PasswordContainer called container that is the
  // container that is the container where data is being read from.
  friend std::ostream& operator<<(std::ostream& output,
                                  const PasswordContainer& container);

 private:
  Cryptographer cryptographer_;

  // Enum that stores values for the index value of how details are stored in
  // a file (There is the account name, then username, then password in the save
  // file).
  enum DetailIndex {
    kAccountNameIndex = 0,
    kUsernameIndex = 1,
    kPasswordIndex = 2
  };

  // Represents the number of details that are in AccountDetails (account name,
  // username, and password.
  const size_t kNumDetails = 3;

  // A vector of all accounts stored in the program
  std::vector<AccountDetails> accounts_;

  // Adds all the account data that are represented in the passed in
  // decrypted_string to the container.
  void AddAllData(const std::string& decrypted_string);

  // Adds the data for one account that is represented by the passed in
  // line_data string
  void AddOneAccountData(const std::string& line_data);

  // Returns a string representation of all the data currently in the container.
  std::string GenerateStringRepresentation() const;
};

}  // namespace passwordcontainer

#endif  // CORE_PASSWORD_CONTAINER_H
