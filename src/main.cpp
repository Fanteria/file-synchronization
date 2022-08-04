#include <iostream> // TODO delete after testing
#include <string>

#include "synchronizer.hpp"

int main(int argc, char **args) {
  if (argc != 3) {
    std::cout << "Program needs two arguments. Source and replica folder.\n";
    return 1;
  }
  Synchronizer synchronizer(args[1], args[2]);
  synchronizer.run();
  return 0;
}
