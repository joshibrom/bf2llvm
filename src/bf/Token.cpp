#include "Token.hpp"

#include <cctype>
#include <ostream>
#include <string_view>


namespace bf2llvm {

std::ostream &operator<<(std::ostream &os, TokenType tt) {
    using enum TokenType;

    switch (tt) {
        case HeadIncr:
            return os << "HEAD_INCR";
        case HeadDecr:
            return os << "HEAD_DECR";
        case ByteIncr:
            return os << "BYTE_INCR";
        case ByteDecr:
            return os << "BYTE_DECR";
        case ShowByte:
            return os << "SHOW_BYTE";
        case ReadByte:
            return os << "READ_BYTE";
        case LoopBegin:
            return os << "LOOP_BEG";
        case LoopEnd:
            return os << "LOOP_END";
        case Comment:
            return os << "COMMENT";
        case EndOfFile:
            return os << "END_OF_FILE";
    };
}

std::ostream &operator<<(std::ostream &os, const Token &tok) {
    return os << "Token{ .type=" << tok.type << ", .value='" << tok.value << "' }";
}

}
