#include "ExpressionTreeParser.h"

ExpressionTreeParser::ExpressionTreeParser(size_t stackSize)
    : m_nodes(Stack<Node*>(stackSize))
{
}

ExpressionTreeParser::~ExpressionTreeParser()
{
    ExpressionTreeParser::freeTree(m_root);
}

void ExpressionTreeParser::parseFromString(const std::string& input)
{
    std::stringstream inputStream(input);
    try
    {
        m_root = parseExpression(inputStream);
    }
    catch (std::out_of_range& e)
    {
        throw std::logic_error("invalid expression");
    }
}

void ExpressionTreeParser::printTree(std::ostream& output)
{
    if (m_root == nullptr)
    {
        return;
    }

    output << tokenToString(m_root->token, m_root->number);

    std::string pointerRight = "└──";
    std::string pointerLeft = m_root->right != nullptr ? "├──" : "└──";

    ExpressionTreeParser::traverseNodes(output, "", pointerLeft, m_root->left, m_root->right != nullptr);
    ExpressionTreeParser::traverseNodes(output, "", pointerRight, m_root->right, false);
    output << std::endl;
}

Node* ExpressionTreeParser::parseExpression(std::istream& input)
{
    m_nodes.flush();
    char ch;
    int number;
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
            input >> number;
            newNode = ExpressionTreeParser::createNode(Token::NUMBER, nullptr, nullptr, number);
            m_nodes.push(newNode);
            break;

        case '+':
            node2 = m_nodes.pop();
            node1 = m_nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::PLUS, node1, node2);
            m_nodes.push(newNode);
            break;

        case '-':
            if (std::isdigit(input.peek()))
            {
                input.putback(ch);
                input >> number;
                newNode = ExpressionTreeParser::createNode(Token::NUMBER, nullptr, nullptr, number);
                m_nodes.push(newNode);
                break;
            }
            node2 = m_nodes.pop();
            node1 = m_nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::MINUS, node1, node2);
            m_nodes.push(newNode);
            break;

        case '*':
            node2 = m_nodes.pop();
            node1 = m_nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::MUL, node1, node2);
            m_nodes.push(newNode);
            break;

        case '/':
            node2 = m_nodes.pop();
            node1 = m_nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::DIV, node1, node2);
            m_nodes.push(newNode);
            break;

        case '^':
            node2 = m_nodes.pop();
            node1 = m_nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::POW, node1, node2);
            m_nodes.push(newNode);
            break;

        case '~':
            node1 = m_nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::UMINUS, node1, nullptr);
            m_nodes.push(newNode);
            break;

        case '#':
            node1 = m_nodes.pop();
            newNode = ExpressionTreeParser::createNode(Token::UPLUS, node1, nullptr);
            m_nodes.push(newNode);
            break;

        default:
            break;
        }
    }

    return m_nodes.pop();
}

Node* ExpressionTreeParser::createNode(const Token token, Node* left, Node* right, int number)
{
    Node* node = new Node;
    node->token = token;
    node->left = left;
    node->right = right;
    node->number = number;
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
