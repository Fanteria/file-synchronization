#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "synchronizer.hpp"

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "Program needs source and replica folder.";
    return 1;
  }
  std::string logFile = "l.log";
  std::string intervalStr = "60";
  std::string source{""};
  std::string replica{""};

  bool sourceRead = false;
  bool replicaRead = false;
  for (int i = 1; i < argc; ++i) {
    if (!std::string("-i").compare(argv[i]) ||
        !std::string("--interval").compare(argv[i])) {
      intervalStr = argv[++i];
    } else if (!std::string("-l").compare(argv[i]) ||
               !std::string("--log").compare(argv[i])) {
      logFile = argv[++i];
    } else if (!sourceRead) {
      source = argv[i];
      sourceRead = true;
    } else if (!replicaRead) {
      replica = argv[i];
      replicaRead = true;
    } else {
      std::cout << "Wrong program input." << std::endl;
      return 1;
    }
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
