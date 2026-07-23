#pragma once

#include <filesystem>
#include <string>

namespace bf2llvm {

/**
 * @brief Reads an input file to a string.
 *
 * @param path Path to the input file.
 *
 * @throws If the input file cannot be open / read.
 */
std::string read_file(const std::filesystem::path &path);

}
