#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Sushi.hh"

int main(int argc, char* argv[]) {
    Sushi my_shell;

    for (int i = 1; i < argc; ++i) {
        if (!my_shell.execute_script(argv[i])) {
            std::cerr << "Error executing script: " << argv[i] << std::endl;
            return EXIT_FAILURE;  // Exit immediately if a script fails
        }
    }

    return my_shell.mainloop();
}
