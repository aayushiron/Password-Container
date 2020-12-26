# Password Container
A simple password container that can be used to hold your passwords and can also be used to generate
passwords. Currently includes both a command line interface and a GUI.

![](https://i.imgur.com/urjdfNt.png)

![](https://i.imgur.com/9heXJjx.png)

## Dependencies
* Can only be run using windows
* Microsoft Visual Studio Build tools 2015
* [Cinder v0.9.2](https://libcinder.org/download)
  * The Cinderblock [Cinder-ImGui](https://github.com/aayushiron/Cinder-ImGui)
* Clion

### Build Instructions (Windows only)
1) Download Cinder and extract it into a folder
2) Open the folder in Clion and click the build button
3) Navigate to the folder called `blocks` from the root cinder folder
4) Clone `Cinder-ImGui` into this folder
5) Go back to the root cinder folder
6) Create a new folder called `my-projects` and clone this repository in it
7) Open this repository in clion
8) To run the gui, run the `password-container-app` configuration and to run the cli, run the
   `password-container-cli` configuration (Make sure you add command line arguments to the cli
   configuration)

## Usage
The command Line interface of the password container needs two command line arguments when it is
being run. The first is the location of the save file used to store the data in the password 
container, and the second argument is the key used to decrypt this save file.

The GUI has a default save file location as a constant in the code in 
`include/gui/password_container_app.h`. If this file doesn't exist, it
creates the file and starts adding data to it. If this file does not exist, it uses the default
key also found in the same file. Other than this file, the gui needs nothing else to run.

## CLI Commands
| Command           | Action                                               |
|-------------------|------------------------------------------------------|
|`add`              | Adds an account to the container                     |
|`delete`           | Deletes an account from the container                |
|`modify`           | Modifies an account in the container                 |
|`list accounts`    | Lists all accounts in the container                  |
|`show details`     | Shows the details of the specified account           |
|`generate password`| Generates a random password with the passed in length|
|`change key`       | Changes the key used for encryption and decryption   |
|`save`             | Saves the data to the file and encrypts it           |
|`quit`             | Quits the cli                                        |