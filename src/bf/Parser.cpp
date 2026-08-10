#include "Parser.hpp"
#include "Token.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace bf2llvm {
Program Parser::parse() {
    return { parseBody() };
}

std::vector<Node> Parser::parseBody() {
    std::vector<Node> body{};

    // Iterate through the tokens, consuming them and building an AST
    Token token { m_tokens[m_cursor] };
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
            next();
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
        ? std::optional<Token>{ m_tokens[m_cursor + 1] }
        : std::nullopt;
}

NodeAction Parser::accumulateAction() {
    if (m_cursor >= m_tokens.size())
        throw std::runtime_error("Out of bounds"); // TODO: Make better message

    Token token {m_tokens[m_cursor]};
    int delta {
        token.type == TokenType::ByteIncr || token.type == TokenType::HeadIncr
            ? 1
            : -1
    };
    int n{delta};

    std::optional<Token> next_token { peek() };

    while (next_token.has_value() &&
           next_token.value().type == token.type) {
      n += delta;
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

template<class... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};

template<class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

void Program::print() const {
    std::cout << "Program {" << std::endl;
    for (const auto &n : body) {
        n.print(1);
    }
    std::cout << "}" << std::endl;
}

void Node::print(size_t level) const {
    std::string indent(level, '\t');
    std::cout << indent;

    std::visit(Overloaded{
        [](const bf_node_action::Move &a) {
            std::cout << "Move(" << a.by << ")" << std::endl;
        },
        [](const bf_node_action::Mutate &a) {
            std::cout << "Mutate(" << a.by << ")" << std::endl;
        },
        [](const bf_node_action::Show &) { std::cout << "Show" << std::endl; },
        [](const bf_node_action::Read &) { std::cout << "Read" << std::endl; },
        [level, indent](const bf_node_action::Loop &a) {
            std::cout << "Loop {" << std::endl;
            for (const auto &node : a.body) {
                node.print(level + 1);
            }
            std::cout << indent << "}" << std::endl;
        },
    }, action);
}

}
