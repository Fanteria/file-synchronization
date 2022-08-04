#include <iostream> // TODO delete after testing
#include <string>

#include "synchronizer.hpp"

int main(int argc, char **args) {
  if (argc != 5) {
    std::cout << "Program needs four arguments. Source and replica folder, "
                 "name of log file and interval for synchronization.\n";
    return 1;
  }
  Synchronizer synchronizer(args[1], args[2], args[3]);

  synchronizer.sync();
  return 0;
}
