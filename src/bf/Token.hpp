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
    HEAD_INCR,
    HEAD_DECR,
    BYTE_INCR,
    BYTE_DECR,
    READ_BYTE,
    SHOW_BYTE,
    LOOP_BEG,
    LOOP_END,

    // Extras / Utility Types:
    COMMENT,     // Denotes a comment (char not from above commands)
    END_OF_FILE, // Denotes the end of a file / input source
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
