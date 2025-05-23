#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Sushi.hh"

// DZ: Must be initialized befor used in `my_shell`
const std::string Sushi::DEFAULT_CONFIG = ".sushirc";
const std::string Sushi::DEFAULT_PROMPT = "sushi> ";

// DZ: Must be a global variable
Sushi my_shell;
int main(int argc, char* argv[]) {
  //Sushi my_shell;

    for (int i = 1; i < argc; ++i) {
      my_shell.read_config(argv[i], false);
      // DZ: Wrong function
      //if (!my_shell.execute_script(argv[i])) {
	  // DZ: Already reported
	  // std::cerr << "Error executing script: " << argv[i] << std::endl;
      //return EXIT_FAILURE;  // Exit immediately if a script fails
      //}
    }

    my_shell.mainloop();
    return 0; 
}
