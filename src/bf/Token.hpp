#pragma once

#include <ostream>
#include <string_view>


namespace bf2llvm {

/**
 * @brief Brainfuck commands and other utility token types.
 *
 * @see https://en.wikipedia.org/wiki/Brainfuck#Language_design
 */
enum class TokenType {
    // BF commands:
    HeadIncr,
    HeadDecr,
    ByteIncr,
    ByteDecr,
    ReadByte,
    ShowByte,
    LoopBegin,
    LoopEnd,

    // Extras / Utility Types:
    Comment,     // Denotes a comment (char not from above commands)
    EndOfFile, // Denotes the end of a file / input source
};

std::ostream &operator<<(std::ostream &os, TokenType tt);


/**
 * @brief Stores information about a token.
 */
struct Token {
    /// The type of this token.
    TokenType type;
    /// The value, if any (empty S_V otherwise), that this token holds.
    std::string_view value;
};

std::ostream &operator<<(std::ostream &os, const Token& tok);

}
