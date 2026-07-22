#include "Token.hpp"

#include <cctype>
#include <ostream>
#include <string_view>


namespace bf2llvm {

std::ostream &operator<<(std::ostream &os, TokenType tt) {
    switch (tt) {
        case TokenType::HEAD_INCR:
            return os << "TokenType::HEAD_INCR";
        case TokenType::HEAD_DECR:
            return os << "TokenType::HEAD_DECR";
        case TokenType::BYTE_INCR:
            return os << "TokenType::BYTE_INCR";
        case TokenType::BYTE_DECR:
            return os << "TokenType::BYTE_DECR";
        case TokenType::SHOW_BYTE:
            return os << "TokenType::SHOW_BYTE";
        case TokenType::READ_BYTE:
            return os << "TokenType::READ_BYTE";
        case TokenType::LOOP_BEG:
            return os << "TokenType::LOOP_BEG";
        case TokenType::LOOP_END:
            return os << "TokenType::LOOP_END";
        case TokenType::COMMENT:
            return os << "TokenType::COMMENT";
        case TokenType::END_OF_FILE:
            return os << "TokenType::END_OF_FILE";
    };
}

std::ostream &operator<<(std::ostream &os, const Token &tok) {
    return os << "Token{ .type=" << tok.type << ", .value='" << tok.value << "' }";
}

}
