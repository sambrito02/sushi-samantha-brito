#include "Sushi.hh"
#include <string>
#include <iostream>

// DZ: You implemented only 2 special characters out of 11 required
std::string *Sushi::unquote_and_dup(const char* s)
{
    std::string* result = new std::string();

    for (size_t i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '\\' && s[i + 1] != '\0') {  // Check for escape sequences
            ++i;
            switch (s[i]) {
                case 'n': result->push_back('\n'); break;
                case 't': result->push_back('\t'); break;
                case 'r': result->push_back('\r'); break;
                case 'b': result->push_back('\b'); break;
                case 'f': result->push_back('\f'); break;
                case 'v': result->push_back('\v'); break;
                case 'a': result->push_back('\a'); break;
                case 'e': result->push_back('\033'); break;  // Escape character
                case '\\': result->push_back('\\'); break;
                case '\"': result->push_back('\"'); break;
                case '\'': result->push_back('\''); break;
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
int Sushi::parse_command(const std::string command) {
    std::istringstream iss(command);
    std::string first;
    iss >> first;

    // Handle environment variable assignment
    if (first.find('=') != std::string::npos) {
        size_t pos = first.find('=');
        std::string name = first.substr(0, pos);
        std::string value = first.substr(pos + 1);
        putenv(new std::string(name), new std::string(value));
        return 0;
    }
    // Handle built-in commands (like `exit`)
    else if (first == "exit") {
        exit(0);
    }
    // Execute external commands
    else {
        bool bg = (command.back() == '&');
        std::string actual_command = command;
        if (bg) actual_command.pop_back();  // Remove '&' from command
        
        Program *exe = new Program(new std::vector<std::string*>({new std::string(actual_command)}));
        Sushi().spawn(exe, bg);
        delete exe;
    }
    return 0;
}

//---------------------------------------------------------------
// Implement the function
std::string *Sushi::getenv(const char* s) 
{
    char *val = std::getenv(name);
    return (val != nullptr) ? new std::string(val) : new std::string("");
}

// Implement the function
void Sushi::putenv(const std::string* name, const std::string* value)
{
  if (setenv(name->c_str(), value->c_str(), 1) != 0) {
        std::cerr << "Failed to set environment variable: " << *name << std::endl;
    }
    delete name;
    delete value;
}

//---------------------------------------------------------------
// Do not modify this function
void yyerror(const char* s) {
  std::cerr << "Parse error: " << s << std::endl;
}


