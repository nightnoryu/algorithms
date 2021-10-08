#pragma once

#include "Token.h"
#include "stack.hpp"

struct Node
{
    Token token;
    int number;
    Node *left, *right;
};

void printTree(std::ostream& output, Node*& ptr);
void freeTree(Node*& ptr);

class ExpressionTreeParser
{
public:
    ExpressionTreeParser(size_t stackSize);

    Node* parseFromString(const std::string& input);

    Node* parseFromStream(std::istream& input);

private:
    Stack<Node*> m_nodes;
};
