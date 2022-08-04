#include <chrono>
#include <filesystem>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>

#include "logger.hpp"

class Synchronizer {
protected:
  std::filesystem::path source;
  std::filesystem::path replica;
  Logger logger;

  void copyFile(const std::filesystem::path &path);

  void copyDir(const std::filesystem::path &dir);

  inline std::string replicaPath(const std::filesystem::path &path);

public:
  Synchronizer(const std::string &source, const std::string &replica,
               const std::string &logFile = "log.log");

  void sync();
};
