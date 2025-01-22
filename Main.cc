#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Sushi.hh"

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    Sushi shell;

    // Get the $HOME environment variable
    const char *home = std::getenv("HOME");
    if (!home) {
        std::cerr << "Error: HOME environment variable not set" << std::endl;
        return EXIT_FAILURE;
    }

    // Read configuration file from $HOME/sushi.conf
    std::string config_path = std::string(home) + "/sushi.conf";
    if (!shell.read_config(config_path.c_str(), true)) {
        return EXIT_FAILURE;
    }

    // Main loop
    std::string command;
    while (true) {
        // Display prompt and read command
        std::cout << Sushi::DEFAULT_PROMPT;
        command = shell.read_line(std::cin);

        if (!command.empty()) {
            shell.store_to_history(command);
        }

        // Display history
        shell.show_history();

        // Exit if the command is "exit"
        if (command == "exit") {
            break;
        }
    }

    return EXIT_SUCCESS;
}
