#include "bf/Lexer.hpp"
#include "bf/Parser.hpp"
#include "bf/Token.hpp"
#include "io/FileHandler.hpp"

#include <filesystem>
#include <iostream>
#include <vector>

constexpr char INPUT_FILENAME[] { "../hello-world-commented.bf" };

int main() {
    // Read the input file
    // TODO: Make this program take an arg for the input file
    auto input_content = bf2llvm::read_file(std::filesystem::path{INPUT_FILENAME});

    bf2llvm::Lexer lexer { {input_content} };

    std::vector<bf2llvm::Token> tokens;

    do {
        tokens.push_back(lexer.nextToken());
    } while (tokens.size() > 0 && tokens.back().type != bf2llvm::TokenType::EndOfFile);

    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        std::cout << *it << std::endl;
    }

    bf2llvm::Parser parser { tokens };

    return 0;
}
