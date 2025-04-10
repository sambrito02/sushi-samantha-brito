#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Sushi.hh"
<<<<<<< HEAD
=======

// DZ: Must be a global variable
>>>>>>> 1d1493f3da590886c512a1eb44288044ef1622ce
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

    return my_shell.mainloop();
}
