For my final project, I want to create an app that can store and read passwords 
from an encrypted file. The app should also be able to generate its own passwords
that can be used in most sites, and should allow storing of passwords from the command
line.

I want to do this project because I always struggle with creating new passwords for 
different websites, and if I create a new password just for one site, I usually never 
remember it after a while. I don't feel comfortable giving my personal information to 
services such as lastpass, so I want to code my own implementation of the app.

My time line is as follows:
- Week 1
  * Load in a file that contains decrypted passwords
  * Save the passwords to an encrypted file
  * Create encryption and decryption methods to secure passwords
- Week 2
  * Add Command line support to save passwords to a file and to get data from a file
  * Generate passwords that can be size customizable
  * Doesn't allow password file to be read or written to unless a password is inputted
- Week 3
  * Create a graphical interface using a UI CinderBlock like 
  [CIUI](https://www.syedrezaali.com/cinderui/)
    * Has a list of all the different accounts that have their passwords stored in the file
    * Allows editing of account name and password
    * Has UI Element such as a slider to generate a password of a certain size
    * Can delete or add new passwords to the list of passwords currently available
    * Has Button to copy text to clipboard
    * Allows account to be deleted
    * Password does not show until a show password button is pressed
    * Doesn't allow any access until a password is entered
- Stretch Goals:
  * Use full RSA encryption to protect the contents of the password files
  * Encrypt the full state of the application so nobody can hook onto the memory of the 
    app to steal password data