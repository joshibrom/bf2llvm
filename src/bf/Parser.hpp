#pragma once

#include "Token.hpp"

#include <cstddef>
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
    struct Mutate { std::size_t by; };
    struct Move   { std::size_t by; };
    struct Read   {};
    struct Show   {};
    struct Loop   { std::vector<Node> body; };
}

struct Node {
  std::variant < bf_node_action::Mutate, bf_node_action::Move,
                 bf_node_action::Read, bf_node_action::Show,
                 bf_node_action::Loop> action;
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
        Parser(std::span<const Token> tokens) : m_tokens(tokens) {}

    private:
        std::span<const Token> m_tokens;
};

}
