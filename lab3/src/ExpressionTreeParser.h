#pragma once

#include "Token.h"
#include "common_inc.h"
#include "stack.hpp"

struct Node
{
    Token token;
    std::string identifier;
    Node *left, *right;
};

class ExpressionTreeParser
{
public:
    ExpressionTreeParser(size_t stackSize);
    ~ExpressionTreeParser();

    void parseFromString(const std::string& input);

    void printTree(std::ostream& output);

private:
    Node* parseExpression(std::istream& input);

    static Node* createNode(const Token token, Node* left, Node* right, std::string identifier = "");

    static void traverseNodes(std::ostream& output,
        const std::string& padding,
        const std::string& pointer,
        Node*& ptr,
        bool hasRightSibling);

    static void freeTree(Node*& ptr);

    Stack<Node*> nodes;
    Node* root = nullptr;
};
