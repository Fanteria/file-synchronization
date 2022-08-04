#include "logger.hpp"

using std::cout;
using std::string;

Logger::Logger(const string &fileName, bool console) : console(console) {
  file.open(fileName);
}

Logger::~Logger() {
  if (file.is_open())
    file.close();
}

void Logger::log(const string &message) {
  if (console)
    cout << message << "\n";
  if (file.is_open())
    file << message << "\n";
}

void Logger::log(const std::string &filename, Logger::Type type) {
  log("File " + filename + " " + types[type] + ".");
}
