#include "Lexer.hpp"
namespace bf2llvm {

Token Lexer::nextToken() {
    // Advance to next character
    skipWhitespace();

    // If we're attempting to read OOB, assume that we are at EOF
    if (m_cursor >= m_source.size()) {
        return {TokenType::END_OF_FILE, {}};
    }

    // Get the token that's under the cursor
    size_t curr_pos {m_cursor};
    switch (m_source[m_cursor]) {
        case '>':
            m_cursor++;
            return {TokenType::HEAD_INCR, m_source.substr(curr_pos, 1)};
        case '<':
            m_cursor++;
            return {TokenType::HEAD_DECR, m_source.substr(curr_pos, 1)};
        case '+':
            m_cursor++;
            return {TokenType::BYTE_INCR, m_source.substr(curr_pos, 1)};
        case '-':
            m_cursor++;
            return {TokenType::BYTE_DECR, m_source.substr(curr_pos, 1)};
        case '.':
            m_cursor++;
            return {TokenType::SHOW_BYTE, m_source.substr(curr_pos, 1)};
        case ',':
            m_cursor++;
            return {TokenType::READ_BYTE, m_source.substr(curr_pos, 1)};
        case '[':
            m_cursor++;
            return {TokenType::LOOP_BEG, m_source.substr(curr_pos, 1)};
        case ']':
            m_cursor++;
            return {TokenType::LOOP_END, m_source.substr(curr_pos, 1)};
        default:
            // Chars not in above are considered comments, return entire comment
            size_t comment_start {curr_pos};
            size_t length {0};
            while (m_cursor < m_source.size() && !isCommand()) {
                m_cursor++;
                length++;
            }
            return {TokenType::COMMENT, m_source.substr(comment_start, length)};
    }
}

inline bool Lexer::isCommand() {
    switch (m_source[m_cursor]) {
        case '>':
        case '<':
        case '+':
        case '-':
        case '.':
        case ',':
        case '[':
        case ']':
            return true;
        default:
            return false;
    }
}

void Lexer::skipWhitespace() {
    while (m_cursor < m_source.size() && std::isspace(m_source[m_cursor])) {
        m_cursor++;
    }
}
}
