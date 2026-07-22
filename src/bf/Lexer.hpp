#pragma once

#include "Token.hpp"

namespace bf2llvm {

class Lexer {
    public:
        /**
         * @brief Creates a new instance of a Brainfuck Lexer.
         *
         * @param source View of the BF source code that will be tokenized.
         */
        Lexer(std::string_view source) : m_source(source), m_cursor(0) {}

        /**
         * @brief Gets the next token, if available.
         *
         * @return Token Current `Token` if there is one, else an EOF Token to
         * imply that we are OOB.
         */
        Token nextToken();

    private:
        /**
         * @brief Checks if current character is a Brainfuck command.
         *
         * The current character is defined as `m_source[m_cursor]`.
         *
         * @return bool Whether the current character is defined as a command.
         */
        inline bool isCommand();

        /**
         * @brief Moves the cursor forward past whitespace.
         */
        void skipWhitespace();

    private:
        /// Source code that will be tokenized.
        std::string_view m_source;
        /// Pointer to the character being evaluated by the `Lexer`.
        size_t m_cursor;
};

}
