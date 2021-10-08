#include "ExpressionTreeParser.h"

ExpressionTreeParser::ExpressionTreeParser(size_t stackSize)
    : m_nodes(Stack<Node*>(stackSize))
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

    output << tokenToString(root->token, root->number);

    std::string pointerRight = "└──";
    std::string pointerLeft = root->right != nullptr ? "├──" : "└──";

    ExpressionTreeParser::traverseNodes(output, "", pointerLeft, root->left, root->right != nullptr);
    ExpressionTreeParser::traverseNodes(output, "", pointerRight, root->right, false);
}

Node* ExpressionTreeParser::parseExpression(std::istream& input)
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

void ExpressionTreeParser::traverseNodes(std::ostream& output,
    const std::string& padding,
    const std::string& pointer,
    Node*& ptr,
    bool hasRightSibling)
{
    if (ptr != nullptr)
    {
        output << std::endl
               << padding << pointer << tokenToString(ptr->token, ptr->number);

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
