#include "ExpressionTreeParser.h"

ExpressionTreeParser::ExpressionTreeParser(size_t stackSize)
    : nodes(Stack<Node*>(stackSize))
{
}

ExpressionTreeParser::~ExpressionTreeParser()
{
    ExpressionTreeParser::freeTree(root);
}

void ExpressionTreeParser::parseFromString(const std::string& input)
{
    std::stringstream inputStream(input);
    try
    {
        root = parseExpression(inputStream);
    }
    catch (std::out_of_range& e)
    {
        throw std::logic_error("invalid expression");
    }
}

void ExpressionTreeParser::printTree(std::ostream& output)
{
    if (root == nullptr)
    {
        return;
    }

    output << tokenToString(root->token, root->identifier);

    std::string pointerRight = "└──";
    std::string pointerLeft = root->right != nullptr ? "├──" : "└──";

    ExpressionTreeParser::traverseNodes(output, "", pointerLeft, root->left, root->right != nullptr);
    ExpressionTreeParser::traverseNodes(output, "", pointerRight, root->right, false);
    output << std::endl;
}

Node* ExpressionTreeParser::parseExpression(std::istream& input)
{
    nodes.flush();
    char ch;
    std::string identifier;
    Node *node1, *node2, *newNode;

    while (input.get(ch))
    {

        switch (ch)
        {
        case '+':
            node2 = nodes.pop();
            node1 = nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::PLUS, node1, node2);
            nodes.push(newNode);
            break;

        case '-':
            node2 = nodes.pop();
            node1 = nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::MINUS, node1, node2);
            nodes.push(newNode);
            break;

        case '*':
            node2 = nodes.pop();
            node1 = nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::MUL, node1, node2);
            nodes.push(newNode);
            break;

        case '/':
            node2 = nodes.pop();
            node1 = nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::DIV, node1, node2);
            nodes.push(newNode);
            break;

        case '^':
            node2 = nodes.pop();
            node1 = nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::POW, node1, node2);
            nodes.push(newNode);
            break;

        case '~':
            node1 = nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::UMINUS, node1, nullptr);
            nodes.push(newNode);
            break;

        case '#':
            node1 = nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::UPLUS, node1, nullptr);
            nodes.push(newNode);
            break;

        default:
            if (std::isalpha(ch))
            {
                identifier = std::string(1, ch);
                while (input.get(ch) && std::isalnum(ch))
                {
                    identifier += ch;
                }
                input.putback(ch);
                newNode = ExpressionTreeParser::createNode(Token::IDENTIFIER, nullptr, nullptr, identifier);
                nodes.push(newNode);
            }
            break;
        }
    }

    return nodes.pop();
}

Node* ExpressionTreeParser::createNode(const Token token, Node* left, Node* right, std::string identifier)
{
    Node* node = new Node;
    node->token = token;
    node->left = left;
    node->right = right;
    node->identifier = identifier;
    return node;
}

void ExpressionTreeParser::traverseNodes(std::ostream& output,
    const std::string& padding,
    const std::string& pointer,
    Node*& ptr,
    bool hasRightSibling)
{
    if (ptr != nullptr)
    {
        output << std::endl
               << padding << pointer << tokenToString(ptr->token, ptr->identifier);

        std::string newPadding = padding;
        if (hasRightSibling)
        {
            newPadding += "│  ";
        }
        else
        {
            newPadding += "   ";
        }

        std::string pointerRight = "└──";
        std::string pointerLeft = ptr->right != nullptr ? "├──" : "└──";

        traverseNodes(output, newPadding, pointerLeft, ptr->left, ptr->right != nullptr);
        traverseNodes(output, newPadding, pointerRight, ptr->right, false);
    }
}

void ExpressionTreeParser::freeTree(Node*& ptr)
{
    if (ptr != nullptr)
    {
        freeTree(ptr->left);
        freeTree(ptr->right);
        delete ptr;
        ptr = nullptr;
    }
}
