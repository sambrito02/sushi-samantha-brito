#include "Sushi.hh"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include <limits>
#include <algorithm> // DZ: Needed by all_of

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

void Sushi::set_exit_flag()
{
  // To be implemented
}

bool Sushi::get_exit_flag() const
{
  return false; // To be fixed
}
