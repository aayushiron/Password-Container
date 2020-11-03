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
  * Add Command line support to save passwords to a file
  * Generate passwords that can be size customizable
- Week 3
  * Create a graphical interface using a UI CinderBlock like 
  [CIUI](https://www.syedrezaali.com/cinderui/)
- Stretch Goals:
  * Use full RSA encryption to protect the contents of the password files
  * Encrypt the full state of the application so nobody can hook onto the memory of the 
    app to steal password data