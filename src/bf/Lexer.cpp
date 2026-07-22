#include "Lexer.hpp"
#include "Token.hpp"
namespace bf2llvm {

Token Lexer::nextToken() {
    using enum TokenType;
    // Advance to next character
    skipWhitespace();

    // If we're attempting to read OOB, assume that we are at EOF
    if (m_cursor >= m_source.size()) {
        return {EndOfFile, {}};
    }

    // Get the token that's under the cursor
    size_t curr_pos {m_cursor};
    switch (m_source[m_cursor]) {
        case '>':
            m_cursor++;
            return {HeadIncr, m_source.substr(curr_pos, 1)};
        case '<':
            m_cursor++;
            return {HeadDecr, m_source.substr(curr_pos, 1)};
        case '+':
            m_cursor++;
            return {ByteIncr, m_source.substr(curr_pos, 1)};
        case '-':
            m_cursor++;
            return {ByteDecr, m_source.substr(curr_pos, 1)};
        case '.':
            m_cursor++;
            return {ShowByte, m_source.substr(curr_pos, 1)};
        case ',':
            m_cursor++;
            return {ReadByte, m_source.substr(curr_pos, 1)};
        case '[':
            m_cursor++;
            return {LoopBegin, m_source.substr(curr_pos, 1)};
        case ']':
            m_cursor++;
            return {LoopEnd, m_source.substr(curr_pos, 1)};
        default:
            // Chars not in above are considered comments, return entire comment
            size_t comment_start {curr_pos};
            size_t length {0};
            while (m_cursor < m_source.size() && !isCommand()) {
                m_cursor++;
                length++;
            }
            return {Comment, m_source.substr(comment_start, length)};
    }
}

inline bool Lexer::isCommand() {
    constexpr char commands[] {'>', '<', '+', '-', '.', ',', '[', ']'};
    char curr {m_source[m_cursor]};
    for (char cmd : commands) {
        if (curr == cmd) return true;
    }
    return false;
}

void Lexer::skipWhitespace() {
    while (m_cursor < m_source.size() && std::isspace(m_source[m_cursor])) {
        m_cursor++;
    }
}
}
