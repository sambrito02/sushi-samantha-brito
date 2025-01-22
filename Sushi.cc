#include "Sushi.hh"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include <limits>

// Initialize static constants
const size_t Sushi::MAX_LINE_INPUT = 256; 
const size_t Sushi::HISTORY_LENGTH = 10;
const std::string Sushi::DEFAULT_PROMPT = "sushi> ";

std::string Sushi::read_line(std::istream &in) {
    char buffer[MAX_LINE_INPUT + 1]; 
    in.getline(buffer, MAX_LINE_INPUT + 1);

    if (in.fail() && !in.eof()) {
        std::perror("Error reading input");
        return nullptr;
    }

    if (in.gcount() == MAX_LINE_INPUT && !in.eof()) {
        std::cerr << "Line too long, truncated." << std::endl;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string line(buffer);
    line.erase(line.find_last_not_of(" \n\r\t") + 1);

    if (line.empty() || std::all_of(line.begin(), line.end(), isspace)) {
        return nullptr;
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
        if (!ok_if_missing) std::perror("Error opening config file");
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
