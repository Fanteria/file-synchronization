#include "logger.hpp"

using std::string;

Logger::Logger(const string &fileName) { file.open(fileName); }

Logger::~Logger() {
  if (file.is_open())
    file.close();
}

void Logger::log(const string &message) {
  if (file.is_open()) {
    file << message + "\n";
  }
}

void Logger::log(const std::string &filename, Logger::Type type) {
  log("File " + filename + " " + types[type] + ".");
}
