#include "ExpressionTreeParser.h"

void printTree(std::ostream& output, Node*& ptr)
{
    if (ptr != nullptr)
    {
        printTree(output, ptr->left);
        output << tokenToString(ptr->token, ptr->number);
        printTree(output, ptr->right);
    }
}

void freeTree(Node*& ptr)
{
    if (ptr != nullptr)
    {
        freeTree(ptr->left);
        freeTree(ptr->right);
        delete ptr;
        ptr = nullptr;
    }
}

ExpressionTreeParser::ExpressionTreeParser(size_t stackSize)
    : m_nodes(Stack<Node*>(stackSize))
{
}

Node* ExpressionTreeParser::parseFromString(const std::string& input)
{
    std::stringstream inputStream(input);
    return parseFromStream(inputStream);
}

Node* ExpressionTreeParser::parseFromStream(std::istream& input)
{
    m_nodes.flush();
    char ch;
    Node *node1, *node2, *newNode;

    while (input.get(ch))
    {

        switch (ch)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            input.putback(ch);
            newNode = new Node;
            newNode->token = Token::NUMBER;
            input >> newNode->number;
            newNode->left = newNode->right = nullptr;
            m_nodes.push(newNode);
            break;

        case '+':
            node2 = m_nodes.pop();
            node1 = m_nodes.pop();
            newNode = new Node;
            newNode->token = Token::PLUS;
            newNode->left = node1;
            newNode->right = node2;
            m_nodes.push(newNode);
            break;

        case '-':
            if (std::isdigit(input.peek()))
            {
                input.putback(ch);
                newNode = new Node;
                newNode->token = Token::NUMBER;
                input >> newNode->number;
                newNode->left = newNode->right = nullptr;
                m_nodes.push(newNode);
                break;
            }
            node2 = m_nodes.pop();
            node1 = m_nodes.pop();
            newNode = new Node;
            newNode->token = Token::MINUS;
            newNode->left = node1;
            newNode->right = node2;
            m_nodes.push(newNode);
            break;

        case '*':
            node2 = m_nodes.pop();
            node1 = m_nodes.pop();
            newNode = new Node;
            newNode->token = Token::MUL;
            newNode->left = node1;
            newNode->right = node2;
            m_nodes.push(newNode);
            break;

        case '/':
            node2 = m_nodes.pop();
            node1 = m_nodes.pop();
            newNode = new Node;
            newNode->token = Token::DIV;
            newNode->left = node1;
            newNode->right = node2;
            m_nodes.push(newNode);
            break;

        case '^':
            node2 = m_nodes.pop();
            node1 = m_nodes.pop();
            newNode = new Node;
            newNode->token = Token::POW;
            newNode->left = node1;
            newNode->right = node2;
            m_nodes.push(newNode);
            break;

        default:
            break;
        }
    }

    return m_nodes.pop();
}
