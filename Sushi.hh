#pragma once
#include <vector>
#include <string>
#include <iostream>

class Sushi {
private:
    std::vector<std::string> history; // Command history stored in a vector
    static const size_t HISTORY_LENGTH;
    static const size_t MAX_LINE_INPUT; 

public:
    Sushi() : history() {}

    std::string read_line(std::istream &in);
    void store_to_history(const std::string &line);
    bool read_config(const char *fname, bool ok_if_missing);
    void show_history();

    static const std::string DEFAULT_PROMPT;
};

#define UNUSED(expr) do { (void)(expr); } while (0)
