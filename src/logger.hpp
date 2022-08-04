#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <fstream>
#include <iostream>
#include <string>

class Logger {
protected:
  const std::string types[3] = {"created", "copied", "removed"};
  const bool console;
  std::ofstream file;

public:
  enum Type { CREATE, COPY, REMOVE };

  /*
   * @brief Constructor for logger.
   *
   * @param name of file for loggeing
   */
  Logger(const std::string &fileName = "log.log", bool console = true);

  /*
   * @brief Destructor for logger.
   */
  ~Logger();

  /*
   * @brief Disable copy constructor for logger.
   */
  Logger(const Logger &) = delete;

  /*
   * @brief Disable assign operator for logger.
   */
  Logger &operator=(const Logger &) = delete;

  /**
   * @brief Log message to log file.
   *
   * @param message for log
   */
  void log(const std::string &message);

  /**
   * @brief Log message to log file.
   *
   * @param filename message for log
   * @param type of logging
   */
  void log(const std::string &filename, Type type);
};

#endif // LOGGER_H_INCLUDED
