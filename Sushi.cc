#include "Sushi.hh"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include <limits>
#include <algorithm> // DZ: Needed by all_of
#include <unistd.h>
#include <csignal>
#include <cstring> // DZ: Needed by strdup
#include <sys/wait.h> // DZ: Needed by waitpid

// Initialize static constants
const size_t Sushi::MAX_LINE_INPUT = 256; 
const size_t Sushi::HISTORY_LENGTH = 10;
const std::string Sushi::DEFAULT_PROMPT = "sushi> ";

std::string Sushi::read_line(std::istream &in) {
    char buffer[MAX_LINE_INPUT + 1]; 
    in.getline(buffer, MAX_LINE_INPUT/* + 1*/); // DZ: Off-by-1 error

    if (in.fail() && !in.eof()) {
        std::perror("Error reading input");
	// DZ: wrong return value
        // return nullptr;
	return "";
    }

    if (in.gcount() == MAX_LINE_INPUT && !in.eof()) {
        std::cerr << "Line too long, truncated." << std::endl;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	// DZ: Where do you truncate it?
    }

    std::string line(buffer);
    line.erase(line.find_last_not_of(" \n\r\t") + 1);

    // DZ: The first condition check is useless
    if (/*line.empty() ||*/ std::all_of(line.begin(), line.end(), isspace)) {
	// DZ: wrong return value
        // return nullptr;
	return "";
    }

    return line;
}

void Sushi::store_to_history(const std::string &line) {
    if (line.empty()) return;

    if (history.size() >= HISTORY_LENGTH) {
        history.erase(history.begin());
    }

    history.push_back(line);
}

bool Sushi::read_config(const char *fname, bool ok_if_missing) {
    std::ifstream file(fname);

    if (!file) {
      if (!ok_if_missing) {
	// DZ: Wrong use of perror
	// std::perror("Error opening config file");
	std::perror(fname);
      }
        return ok_if_missing;
    }

    std::string line;
    while (true) {
        line = read_line(file);
        if (line.empty()) {
	  // DZ: Wrong check, it leaves the file at the first blank line
	  // and ignores the rest of it; need to check for EOF
	  break;
	}
	// DZ: Must executed the command!
        store_to_history(line);
    }

    if (file.bad()) {
      // DZ: See above
        std::perror("Error reading config file");
        return false;
    }

    return true;
}

void Sushi::show_history() {
    int index = 1;
    for (const auto &entry : history) {
        std::cout << std::setw(5) << index++ << "  " << entry << std::endl;
    }
}
// DZ: Both functions implemented in the wrong file
void Sushi::set_exit_flag() {
    exit_flag = true;
}

bool Sushi::get_exit_flag() const {
    return exit_flag;
}

//---------------------------------------------------------
// New methods
int Sushi::spawn(Program *exe, bool bg)
{
    pid_t pid = fork();
    if (pid == 0) {  // Child process
        exe->execute();
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) {  // Parent process
        if (!bg) {
            int status = 0;
            waitpid(pid, &status, 0);
            assign(new std::string("?"), new std::string(std::to_string(WEXITSTATUS(status))));
        } else {
            assign(new std::string("?"), new std::string("0"));
        }
    }
    return 0;
}

void Sushi::prevent_interruption() {
    struct sigaction sa = {};
    sa.sa_handler = Sushi::refuse_to_die; // Set handler function
    sigemptyset(&sa.sa_mask); 
    sa.sa_flags = SA_RESTART /*DZ: 0 */ ;

    if (sigaction(SIGINT, &sa, nullptr) == -1) {
        std::perror("sigaction");
    }
}

void Sushi::refuse_to_die(int signo) {
  UNUSED(signo);
    std::cerr << "\nType exit to exit the shell\n";
}

int Sushi::mainloop() {
    std::string input;
    while (!get_exit_flag()) {
        std::cout << get_prompt();
        input = read_line(std::cin);

        if (input.empty()) continue;

        parse_command(input);
    }
    return 0;  // Fix: Ensure it returns int
}
std::string* Sushi::getenv(const char *name) {
    char *val = std::getenv(name);
    return val ? new std::string(val) : new std::string("");
}
void Sushi::assign(const std::string *name, const std::string *value) {
    if (setenv(name->c_str(), value->c_str(), 1) != 0) {
        // Silently fail
    }
    delete name;
    delete value;
}
std::string Sushi::get_prompt() {
    std::string* ps1 = getenv("PS1");
    std::string prompt = (ps1 && !ps1->empty()) ? *ps1 : "sushi> ";
    delete ps1;  // Prevent memory leak
    return prompt;
}
bool Sushi::execute_script(const std::string &filename) {
    std::ifstream script(filename);
    if (!script) {
        std::cerr << "Error: Cannot open script " << filename << "\n";
        return false;
    }

    std::string line;
    while (std::getline(script, line)) {
        parse_command(line);  // Assuming process_command() executes shell commands
    }

    return true;
}
char* const* Program::vector2array() {
    char** argv = new char*[args->size() + 1]; // Allocate memory
    for (size_t i = 0; i < args->size(); ++i) {
      // DZ: `char* CONST*` ensures there are no modifications. Do NOT
      // DZ: make copies without necessity
        argv[i] = strdup(args->at(i)->c_str()); // Use strdup() to avoid modifying original memory
    }
    argv[args->size()] = nullptr; // Null-terminate
    return argv;
}

void Program::free_array(char *const argv[]) {
    if (!argv) return;

    // DZ: See above
    for (size_t i = 0; argv[i] != nullptr; ++i) {
        free(argv[i]);  // Free each allocated string
    }
    delete[] argv; 
}

Program::~Program() {
  // Do not implement now
}
