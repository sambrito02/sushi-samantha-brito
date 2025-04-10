#include "Sushi.hh"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include <limits>
#include <algorithm>
#include <unistd.h>
#include <csignal>
#include <cstring>
#include <sys/wait.h>

// Initialize static constants
const size_t Sushi::MAX_LINE_INPUT = 256;
const size_t Sushi::HISTORY_LENGTH = 10;
const std::string Sushi::DEFAULT_PROMPT = "sushi> ";

std::string Sushi::read_line(std::istream &in) {
    char buffer[MAX_LINE_INPUT + 1];
    in.getline(buffer, MAX_LINE_INPUT);

    if (in.fail() && !in.eof()) {
        std::perror("Error reading input");
        return "";
    }

    if (in.gcount() == MAX_LINE_INPUT && !in.eof()) {
        std::cerr << "Line too long, truncated." << std::endl;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string line(buffer);
    line.erase(line.find_last_not_of(" \n\r\t") + 1);

    if (std::all_of(line.begin(), line.end(), isspace)) {
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
        if (!ok_if_missing) std::perror(fname);
        return ok_if_missing;
    }

    std::string line;
    while (true) {
        line = read_line(file);
        if (line.empty()) break;
        store_to_history(line);
    }

    if (file.bad()) {
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

void Sushi::set_exit_flag() {
    exit_flag = true;
}

bool Sushi::get_exit_flag() const {
    return exit_flag;
}

int Sushi::spawn(Program *exe, bool bg) {
    if (exe->pipe == nullptr) {
        pid_t pid = fork();
        if (pid == 0) {
<<<<<<< HEAD
            exe->execute();
=======
	  // DZ: No such function
            exe->execute();  // Run the command
>>>>>>> 1d1493f3da590886c512a1eb44288044ef1622ce
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            if (!bg) {
                int status = 0;
                waitpid(pid, &status, 0);
                putenv/*assign*/(new std::string("?"), new std::string(std::to_string(WEXITSTATUS(status))));
            } else {
	      putenv/*assign*/(new std::string("?"), new std::string("0"));
            }
            return 0;
        } else {
            perror("fork");
            return -1;
        }
    }

    std::vector<Program*> commands;
    for (Program* p = exe; p != nullptr; p = p->pipe) {
        commands.push_back(p);
    }

    int num_cmds = commands.size();
    int pipes[2];
    int prev_read = -1;
    std::vector<pid_t> pids;

    for (int i = 0; i < num_cmds; ++i) {
        if (i < num_cmds - 1 && pipe(pipes) == -1) {
            perror("pipe");
            return -1;
        }

        pid_t pid = fork();
        if (pid == 0) {
            if (prev_read != -1) {
                dup2(prev_read, STDIN_FILENO);
                close(prev_read);
            }

            if (i < num_cmds - 1) {
                close(pipes[0]);
                dup2(pipes[1], STDOUT_FILENO);
                close(pipes[1]);
            }

            commands[i]->execute();
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            pids.push_back(pid);
            if (prev_read != -1) close(prev_read);
            if (i < num_cmds - 1) {
                close(pipes[1]);
                prev_read = pipes[0];
            }
        } else {
            perror("fork");
            return -1;
        }
    }

    if (!bg) {
        int status = 0;
        for (pid_t pid : pids) {
            waitpid(pid, &status, 0);
        }
        putenv/*assign*/(new std::string("?"), new std::string(std::to_string(WEXITSTATUS(status))));
    } else {
      putenv/*assign*/(new std::string("?"), new std::string("0"));
    }

    return 0;
}

void Sushi::prevent_interruption() {
    struct sigaction sa = {};
    sa.sa_handler = Sushi::refuse_to_die;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
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
<<<<<<< HEAD
    return 0;
}


=======
    return 0;  // Fix: Ensure it returns int
}

// DZ: Duplicate definition
/*
std::string* Sushi::getenv(const char *name) {
    char *val = std::getenv(name);
    return val ? new std::string(val) : new std::string("");
}
*/

//DZ: Wrong function name
/*
>>>>>>> 1d1493f3da590886c512a1eb44288044ef1622ce
void Sushi::assign(const std::string *name, const std::string *value) {
    if (setenv(name->c_str(), value->c_str(), 1) != 0) {
        // silently ignore
    }
    delete name;
    delete value;
<<<<<<< HEAD
}

std::string Sushi::get_prompt() {
    std::string* ps1 = getenv("PS1");
    std::string prompt = (ps1 && !ps1->empty()) ? *ps1 : "sushi> ";
    delete ps1;
    return prompt;
}

=======
    }
*/

std::string Sushi::get_prompt() {
    std::string* ps1 = getenv("PS1");
    std::string prompt = (ps1 && !ps1->empty()) ? *ps1 : DEFAULT_PROMPT/*"sushi> "*/;
    delete ps1;  // Prevent memory leak
    return prompt;
}
// DZ: Not needed
/*
>>>>>>> 1d1493f3da590886c512a1eb44288044ef1622ce
bool Sushi::execute_script(const std::string &filename) {
    std::ifstream script(filename);
    if (!script) {
        std::cerr << "Error: Cannot open script " << filename << "\n";
        return false;
    }

    std::string line;
    while (std::getline(script, line)) {
        parse_command(line);
    }

    return true;
}
<<<<<<< HEAD

=======
*/
>>>>>>> 1d1493f3da590886c512a1eb44288044ef1622ce
char* const* Program::vector2array() {
    char** argv = new char*[args->size() + 1];
    for (size_t i = 0; i < args->size(); ++i) {
        argv[i] = strdup(args->at(i)->c_str());
    }
    argv[args->size()] = nullptr;
    return argv;
}

void Program::free_array(char *const argv[]) {
    if (!argv) return;
    for (size_t i = 0; argv[i] != nullptr; ++i) {
        free(argv[i]);
    }
    delete[] argv;
}
/*int Sushi::parse_command(const std::string command) {
    std::istringstream iss(command);
    std::string first;
    iss >> first;
 
    // Handle environment variable assignment
    if (first.find('=') != std::string::npos) {
        size_t pos = first.find('=');
        std::string name = first.substr(0, pos);
        std::string value = first.substr(pos + 1);
        setenv(name.c_str(), value.c_str(), 1); // updated to use standard setenv
        return 0;
    }               

    // Handle built-in command
    if (first == "exit") {
        exit_flag = true; // assuming exit_flag is a member of Sushi
        return 0;
    }
    
    // Execute external command
    bool bg = (!command.empty() && command.back() == '&');
    std::string actual_command = command;
    if (bg) actual_command.pop_back(); // Remove '&'

    // Split the command into tokens
    std::istringstream cmd_iss(actual_command);  
    std::string token;
    auto args = new std::vector<std::string*>();
    while (cmd_iss >> token) {
        args->push_back(new std::string(token));
    }    
    
    Program* exe = new Program(args);
    spawn(exe, bg); // use current Sushi instance
    delete exe;
    
    return 0;
}*/
Program::~Program() {
}

void Program::execute() {
    char* const* argv = vector2array();
    execvp(argv[0], const_cast<char* const*>(argv));
    perror("execvp");
    free_array(argv);
    exit(EXIT_FAILURE);
}

