#pragma once

#include "Token.hpp"

#include <cstddef>
#include <optional>
#include <span>
#include <variant>
#include <vector>

namespace bf2llvm {

/**
 * @brief Stores a standard action node of the AST.
 */
struct Node;

/**
 * @brief Diffrent supported actions that a `Node` may perform.
 */
namespace bf_node_action {
    struct Mutate { int by; };
    struct Move   { int by; };
    struct Read   {};
    struct Show   {};
    struct Loop   { std::vector<Node> body; };
}

using NodeAction = std::variant < bf_node_action::Mutate, bf_node_action::Move,
                                  bf_node_action::Read, bf_node_action::Show,
                                  bf_node_action::Loop>;

struct Node {
    NodeAction action;
};

/**
 * @brief Parent AST node for a BF program.
 */
struct Program {
    std::vector<Node> body;
};


/**
 * @brief Handles parsing a stream of `Token`s into an AST.
 */
class Parser {
    public:
        Parser(std::span<const Token> tokens) : m_tokens(tokens), m_cursor(0) {}

        /**
        * @brief Parses tokens into a `Program`.
        *
        * @return AST representation of the source program.
        */
        Program parse();

    private:
        /**
        * @brief Parses tokens into a collection of body actions.
        *
        * @return Collection of AST nodes acting as the body of a program or loop.
        */
        std::vector<Node> parseBody();

        /**
        * @brief Gets the next `Token`, moving the cursor forward.
        *
        * @return The next token in the input collection of tokens.
        */
        Token next();

        /**
        * @brief Checks if there is another token, returning it if so.
        *
        * @return Optionally, the next `Token` if there is another token in the source collection.
        */
        std::optional<Token> peek();

        /**
        * @brief Accumulates accumulatable actions into a single `NodeAction`.
        *
        * @return A single, accumulated `NodeAction` for nodes which can be
        * accumulated, else a `std::runtime_error` is thrown.
        */
        NodeAction accumulateAction();

    private:
        std::span<const Token> m_tokens;
        std::size_t m_cursor;
};

}
