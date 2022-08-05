#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "synchronizer.hpp"

int main(int argc, char **argv) {
  const std::string helpText =
      "Program for synchronize folders:\n"
      "Usage: file-synchronization  SOURCE REPLICA [OPTION] ...\n"
      "SOURCE is path to source directory.\n"
      "REPLICA is path to replica directory.\n\n"
      "Options:\n"
      " -i, --interval\tPositive integer of iteration time in seconds.\n"
      " -l, --log\tName of file for logging.";
  std::string logFile = "l.log";
  std::string intervalStr = "60";
  std::string source{""};
  std::string replica{""};

  bool sourceRead = false;
  bool replicaRead = false;
  for (int i = 1; i < argc; ++i) {
    if (!std::string("-h").compare(argv[i]) ||
        !std::string("--help").compare(argv[i])) {
      std::cout << helpText << std::endl;
      return 0;
    }
    if (!std::string("-i").compare(argv[i]) ||
        !std::string("--interval").compare(argv[i]))
      intervalStr = argv[++i];
    else if (!std::string("-l").compare(argv[i]) ||
             !std::string("--log").compare(argv[i]))
      logFile = argv[++i];
    else if (!sourceRead) {
      source = argv[i];
      sourceRead = true;
    } else if (!replicaRead) {
      replica = argv[i];
      replicaRead = true;
    } else {
      std::cout << "Wrong program input." << std::endl;
      std::cout << helpText << std::endl;
      return 1;
    }
  }
  if (!(sourceRead && replicaRead)) {
    std::cout << "Program needs source and replica folder.";
    return 1;
  }

  int interval;
  try {
    interval = std::stoi(intervalStr);
  } catch (const std::invalid_argument &e) {
    std::cout << "Interval muset be number." << std::endl;
    return 1;
  }
  if (interval <= 0) {
    std::cout << "Interval must be greater than zero." << std::endl;
    return 1;
  }

  try {
    Synchronizer synchronizer{source, replica, logFile};
    while (true) {
      synchronizer.sync();
      sleep(interval);
    }
  } catch (const std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}
