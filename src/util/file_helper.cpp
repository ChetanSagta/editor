#include "file_helper.h"
#include <SDL2/SDL_rwops.h>
#include <spdlog/spdlog.h>
#include <string>
#include "NotImplementedYetException.h"

std::string FileHelper::read_from_file(std::string filepath) {
  SDL_RWops *file = SDL_RWFromFile(filepath.c_str(), "r+b");
  if (file == nullptr) {
    SPDLOG_INFO("File doesn't exist: Creating an empty buffer with the mentioned filename");
  }
  SPDLOG_INFO("Reading file into a buffer and showing it in the surface");
  return "";
}

void FileHelper::write_to_file(std::string) {
  throw NotImplementedYetException();
}
