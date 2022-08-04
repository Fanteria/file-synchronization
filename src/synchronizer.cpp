#include "synchronizer.hpp"

namespace fs = std::filesystem;
using std::cout, std::endl; // TODO remove after testing
using std::queue;
using std::string;

void Synchronizer::copyFile(const fs::path &path) { cout << path << endl; }

Synchronizer::Synchronizer(const string &_source, const string &_replica,
                           const string &_logFile)
    : source(_source), replica(_replica), logger(_logFile) {
  if (!(fs::exists(source) && fs::exists(replica))) {
    // TODO
  }
  if (!(fs::is_directory(source) && fs::is_directory(replica))) {
    // TODO
  }
}

bool Synchronizer::run() {
  queue<fs::path> dirs{};
  dirs.push(source);

  fs::path dir;
  while (!dirs.empty()) {
    dir = dirs.front();
    for (const auto &entry : fs::directory_iterator(dir)) {
      if (entry.is_directory()) {
        dirs.push(entry);
      } else {
        copyFile(entry.path());
      }
    }
    dirs.pop();
  }
  return false;
}
