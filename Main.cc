#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Sushi.hh"

Sushi my_shell; // New global var

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    // DZ: Moved to globals (not an error)
    // Sushi shell;

    // Get the $HOME environment variable
    const char *home = std::getenv("HOME");
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

    // Main loop
    std::string command;
    while (true) {
        // Display prompt and read command
        std::cout << Sushi::DEFAULT_PROMPT;
        command = my_shell.read_line(std::cin);

	// DZ: store_to_history performs this check
        //if (!command.empty()) {
            my_shell.store_to_history(command);
	    //}

        // Display history
        my_shell.show_history();

        // Exit if the command is "exit"
        if (command == "exit") {
            break;
        }
    }

    return EXIT_SUCCESS;
}
