#include "synchronizer.hpp"

namespace fs = std::filesystem;
using std::invalid_argument;
using std::queue, std::set;
using std::string;

void Synchronizer::copyFile(const fs::path &path) {
  string rPath = replicaPath(path);
  if (fs::copy_file(path, rPath, fs::copy_options::update_existing)) {
    logger.log(rPath, Logger::COPY);
  }
}

void Synchronizer::copyDir(const fs::path &dir) {
  string rDir = replicaPath(dir);
  if (fs::exists(rDir))
    return;
  logger.log(rDir, Logger::CREATE);
  fs::create_directory(rDir);
}

string Synchronizer::replicaPath(const std::filesystem::path &path) {
  return path.string().replace(0, source.string().size(), replica.string());
}

Synchronizer::Synchronizer(const string &_source, const string &_replica,
                           const string &_logFile)
    : source(_source), replica(_replica), logger(_logFile) {
  if (!fs::exists(source))
    throw invalid_argument("Source folder must exist.");

  if (!fs::exists(replica))
    throw invalid_argument("Replica folder must exist.");

  if (!fs::is_directory(source))
    throw invalid_argument("Source must be directory.");

  if (!fs::is_directory(replica))
    throw invalid_argument("Replica must be directory.");
}

void Synchronizer::sync() {
  set<string> rFiles{};
  set<string> rDirs{};
  for (const auto &entry : fs::recursive_directory_iterator(replica)) {
    if (entry.is_directory())
      rDirs.insert(entry.path().string());
    else
      rFiles.insert(entry.path().string());
  }

  queue<fs::path> dirs{};
  dirs.push(source);

  fs::path dir;
  while (!dirs.empty()) {
    dir = dirs.front();
    for (const auto &entry : fs::directory_iterator(dir)) {
      if (entry.is_directory()) {
        copyDir(entry.path());
        dirs.push(entry);
        rDirs.erase(replicaPath(entry.path()));
      } else {
        copyFile(entry.path());
        rFiles.erase(replicaPath(entry.path()));
      }
    }
    dirs.pop();
  }

  for (const auto &entry : rFiles)
    fs::remove(entry);
  for (const auto &entry : rDirs)
    fs::remove(entry);
}
