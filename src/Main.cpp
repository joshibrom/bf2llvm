#include "bf/Lexer.hpp"
#include "bf/Token.hpp"

#include <iostream>
#include <vector>

int main() {
    bf2llvm::Lexer lexer { {"[->+<] And some test comment"} };

    std::vector<bf2llvm::Token> tokens;

    do {
        tokens.push_back(lexer.nextToken());
    } while (tokens.size() > 0 && tokens.back().type != bf2llvm::TokenType::EndOfFile);

    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        std::cout << *it << std::endl;
    }

    return 0;
}
