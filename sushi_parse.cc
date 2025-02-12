#include "Sushi.hh"
#include <string>
#include <iostream>

std::string *Sushi::unquote_and_dup(const char* s)
{
	std::string* result = new std::string();

	    for (size_t i = 0; s[i] != '\0'; ++i) {
	        if (s[i] == '\\' && s[i + 1] != '\0') {  // Check for escape sequences
	            ++i;
	            switch (s[i]) {
	                case 'n': result->push_back('\n'); break;
	                case 't': result->push_back('\t'); break;
	                case '\\': result->push_back('\\'); break;
	                default:  // Unknown escape, keep it as-is
	                    result->push_back('\\');
	                    result->push_back(s[i]);
	                    break;
	            }
	        } else {
	            result->push_back(s[i]);
	        }
	    }

	    return result;
	}

void Sushi::re_parse(int i) {
	if (i <= 0 || i > static_cast<int>(history.size())) {
	        std::cerr << "Error: !" << i << ": event not found\n";
	        return;
	    }

	    const std::string& command = history[i - 1];
	    if (parse_command(command) != 0) {
	        history.push_back(command);
	    }
	}
//int Sushi::parse_command(const std::string command) {
    // Simulate syntax error detection for demonstration purposes
  //  if (command.find("||") != std::string::npos || command.find("&&") != std::string::npos || 
    //    command.find(">>") != std::string::npos || command.find("<>") != std::string::npos) {
      //  std::cerr << "Syntax error: " << command << "\n";
       // return 1;  // Return non-zero for syntax errors
    //}

    // No syntax error detected
    //std::cout << "Parsing command: " << command << "\n";
    //return 0;
//}

void Sushi::set_exit_flag() {
    exit_flag = true;
}

bool Sushi::get_exit_flag() const {
    return exit_flag;
}

//---------------------------------------------------------------
// Do not modify this function YET
std::string *Sushi::getenv(const char* s) 
{
  return new std::string(s); // Must be changed - eventually
}

//---------------------------------------------------------------
// Do not modify this function
void yyerror(const char* s) {
  std::cerr << "Parse error: " << s << std::endl;
}


