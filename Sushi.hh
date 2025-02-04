#pragma once
#include <vector>
#include <string>
#include <iostream>

class Sushi {
private:
    std::vector<std::string> history; // Command history stored in a vector
    static const size_t HISTORY_LENGTH;
    static const size_t MAX_LINE_INPUT; 
  bool exit_flag = false; // New attribute

public:
    Sushi() : history() {}

    static std::string read_line(std::istream &in);
   static std::string *unquote_and_dup(const char *s); // New method
  static std::string *getenv(const char *name); // New method
   void store_to_history(const std::string &line);
    bool read_config(const char *fname, bool ok_if_missing);
    void show_history();

  void re_parse(int i); // New method
  void set_exit_flag(); // New method
  bool get_exit_flag() const; // New method
  static int parse_command(const std::string command); // New method
    static const std::string DEFAULT_PROMPT;
};

#define UNUSED(expr) do { (void)(expr); } while (0)
// New declaration
extern Sushi my_shell;
