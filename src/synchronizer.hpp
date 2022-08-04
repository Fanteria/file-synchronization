#include <filesystem>
#include <iostream> // TODO remove after testing
#include <queue>
#include <string>

#include "logger.hpp"

class Synchronizer {
protected:
  std::filesystem::path source;
  std::filesystem::path replica;
  Logger logger;

  void copyFile(const std::filesystem::path &path);

public:
  Synchronizer(const std::string &source, const std::string &replica,
               const std::string &logFile = "log.log");

  bool run();
};
