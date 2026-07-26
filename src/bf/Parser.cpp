#include "Parser.hpp"
#include "Token.hpp"

#include <optional>
#include <stdexcept>
#include <vector>

namespace bf2llvm {
Program Parser::parse() {
    return { parseBody() };
}

std::vector<Node> Parser::parseBody() {
    std::vector<Node> body{};

    // Iterate through the tokens, consuming them and building an AST
    Token token { next() };
    while (token.type != TokenType::LoopEnd && token.type != TokenType::EndOfFile) {
        switch (token.type) {
        using enum TokenType;
        case HeadIncr:
        case HeadDecr:
        case ByteIncr:
        case ByteDecr:
            body.push_back({ accumulateAction() });
            break;
        case ReadByte:
            body.push_back({ bf_node_action::Read{} });
            break;
        case ShowByte:
            body.push_back({ bf_node_action::Show{} });
            break;
        case LoopBegin:
            body.push_back({ bf_node_action::Loop{ parseBody() } });
            break;
        case LoopEnd:
            // Loop ends should be handled within the `LoopBegin` case
            throw std::runtime_error("Invalid program: Extraneous loop end");
        case Comment:
        case EndOfFile:
            break;
        }

        token = next();
    }

    return body;
}

Token Parser::next() {
    return m_cursor < m_tokens.size() - 1
        ? m_tokens[++m_cursor]
        : Token{ TokenType::EndOfFile, {} };
}

std::optional<Token> Parser::peek() {
    return m_cursor < m_tokens.size() - 1
        ? std::optional<Token>{ m_tokens[m_cursor] }
        : std::nullopt;
}

NodeAction Parser::accumulateAction() {
    if (m_cursor >= m_tokens.size())
        throw std::runtime_error("Out of bounds"); // TODO: Make better message

    Token token {m_tokens[m_cursor]};
    int n{0};

    std::optional<Token> next_token { peek() };

    while (next_token.has_value() &&
           next_token.value().type == token.type) {
      n +=
          token.type == TokenType::ByteIncr || token.type == TokenType::HeadIncr
          ? 1
          : -1;
      next(); // Consume current token & move forward
      next_token = peek();
    }

    switch (token.type) {
        using enum TokenType;
        case HeadIncr:
        case HeadDecr:
            return bf_node_action::Move{ n };
        case ByteIncr:
        case ByteDecr:
            return bf_node_action::Mutate{ n };
        default:
            // FIXME: Check before even trying to accumulate
            throw std::runtime_error("Action cannot be accumulated");
    }
}

}
