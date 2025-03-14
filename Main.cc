#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Sushi.hh"

// Declare a global Sushi object
Sushi my_shell; 

int main(int argc, char* argv[]) {
  // Use argc and argv!
  
  // Move this into the constructor
  //-------------------------------------------
  Sushi::prevent_interruption();
  

    // Get the $HOME environment variable
    const char* home = std::getenv("HOME");
    // DZ: No need to exit because "ok if missing"
    if (!home) {
        std::cerr << "Error: HOME environment variable not set" << std::endl;
        return EXIT_FAILURE;
    }

    // Read configuration file from $HOME/sushi.conf
    std::string config_path = std::string(home) + "/sushi.conf";
    if (!my_shell.read_config(config_path.c_str(), true)) {
        return EXIT_FAILURE;
    }

   //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  // Move this into the main loop method
  //-------------------------------------------
   // Main loop
    std::string command;
    while (!my_shell.get_exit_flag()) {
        // Display prompt and read command
        std::cout << Sushi::DEFAULT_PROMPT;
        command = my_shell.read_line(std::cin);

        // DZ: store_to_history performs this check
        if (command.empty()) {
            continue;
        }

        // Parse the command; store it in history only if it's valid
        if (my_shell.parse_command(command) == 0) {  // 0 means no syntax error
            my_shell.store_to_history(command);
        }

        // Display history (optional — uncomment if needed)
        // my_shell.show_history();

	// DZ: The parser taes care of this
        // Exit if the command is "exit"
	/*
        if (command == "exit") {
            my_shell.set_exit_flag();  // Set the flag to exit the loop
        }
	*/
    }
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  my_shell.mainloop();

    // DZ: Unneeded message
    // std::cout << "Exit\n";
    return EXIT_SUCCESS;
}

