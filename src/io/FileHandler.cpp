#include "FileHandler.hpp"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

namespace bf2llvm {
    std::string read_file(const std::filesystem::path &path) {
        std::ifstream file { path, std::ios::binary };
        if (!file)
            throw std::runtime_error("Failed to open file");

        file.seekg(0, std::ios::end);

        std::string content(file.tellg(), '\0');

        file.seekg(0);
        file.read(content.data(), content.size());

        if (!file && !file.eof())
            throw std::runtime_error("Could not read file");

        return content;
    }
}
