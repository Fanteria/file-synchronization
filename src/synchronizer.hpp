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

  /**
   * @brief Copy file if source is newer than replica
   *
   * @param path is path of file
   */
  void copyFile(const std::filesystem::path &path);

  /**
   * @brief Copy dir to replica folder if not exists.
   *
   * @param dir is path of directory
   */
  void copyDir(const std::filesystem::path &dir);

  /**
   * @brief Create path to file in replica folder.
   *
   * @param path is path to file in source folder
   */
  inline std::string replicaPath(const std::filesystem::path &path);

public:
  /**
   * @brief Constructor for synchronizer.
   *
   * @param source is path to source directory
   * @param replica is path to replica directory
   * @param logFile is name of file for logging, default "log.log"
   */
  Synchronizer(const std::string &source, const std::string &replica,
               const std::string &logFile = "log.log");

  void sync();
};
