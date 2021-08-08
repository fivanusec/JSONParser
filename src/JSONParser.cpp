#include "JSONParser.h"

void JSONParser::parse()
{
    std::string key = "";

    while (tokenizer.hasMoreTokens())
    {
        Token token;
        try
        {
            token = tokenizer.getToken();
            std::cout << token.toString() << std::endl;

            switch (token.type)
            {
            case TOKEN::CURLY_OPEN:
            {
                std::shared_ptr<JSON::JSONNode> parsedObject = parseObject();
                parsedObject->print_node(0);
                if (!root)
                {
                    root = parsedObject;
                }
                break;
            }
            case TOKEN::ARRAY_OPEN:
            {
                std::shared_ptr<JSON::JSONNode> parsedList = parseList();
                parsedList->print_node(0);
                if (!root)
                {
                    root = parsedList;
                }
                break;
            }

            case TOKEN::STRING:
            {
                tokenizer.rollBackToken();
                std::shared_ptr<JSON::JSONNode> parsedString = parseString();
                parsedString->print_node(0);
                if (!root)
                {
                    root = parsedString;
                }
                break;
            }
            case TOKEN::NUMBER:
            {
                tokenizer.rollBackToken();
                std::shared_ptr<JSON::JSONNode> parsedNumber = parseNumber();
                parsedNumber->print_node(0);
                if (!root)
                {
                    root = parsedNumber;
                }
                break;
            }

            case TOKEN::BOOLEAN:
            {
                tokenizer.rollBackToken();
                std::shared_ptr<JSON::JSONNode> parsedBoolean = parseBoolean();
                break;
            }
            }
        }
        catch (std::logic_error e)
        {
            break;
        }
    }
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseObject()
{
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    JSON::JSONObject *keyObjectMap = new JSON::JSONObject();
    bool hasCompleted = false;
    while (!hasCompleted)
    {
        if (tokenizer.hasMoreTokens())
        {
            Token nextToken = tokenizer.getToken();
            std::string key = nextToken.value;
            std::cout << key << std::endl;
            tokenizer.getToken();
            nextToken = tokenizer.getToken();
            std::shared_ptr<JSON::JSONNode> node;

            switch (nextToken.type)
            {
            case TOKEN::STRING:
            {
                tokenizer.rollBackToken();
                (*keyObjectMap)[key] = parseString();
                break;
            }
            case TOKEN::ARRAY_OPEN:
            {
                (*keyObjectMap)[key] = parseList();
                break;
            }
            case TOKEN::NUMBER:
            {
                tokenizer.rollBackToken();
                (*keyObjectMap)[key] = parseNumber();
                break;
            }
            case TOKEN::CURLY_OPEN:
            {
                (*keyObjectMap)[key] = parseObject();
                break;
            }
            case TOKEN::BOOLEAN:
            {
                tokenizer.rollBackToken();
                (*keyObjectMap)[key] = parseBoolean();
                break;
            }
            case TOKEN::NULL_TYPE:
            {
                (*keyObjectMap)[key] = parseNull();
                break;
            }
            }
            nextToken = tokenizer.getToken();
            if (nextToken.type == TOKEN::CURLY_CLOSE)
            {
                hasCompleted = true;
                break;
            }
        }
        else
        {
            throw std::logic_error("No more tokens");
        }
    }
    node->setObject(keyObjectMap);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseString()
{
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    Token token = tokenizer.getToken();
    std::string *sValue = new std::string(token.value);
    node->setString(sValue);
    return node;
}
std::shared_ptr<JSON::JSONNode> JSONParser::parseNumber()
{
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    Token nextToken = tokenizer.getToken();
    std::string value = nextToken.value;
    float fValue = std::stof(value);
    node->setNumber(fValue);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseList()
{
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    JSON::JSONList *list =
        new JSON::JSONList();
    bool hasCompleted = false;
    while (!hasCompleted)
    {
        if (!tokenizer.hasMoreTokens())
        {
            throw std::logic_error("No more tokens");
        }
        else
        {
            Token nextToken = tokenizer.getToken();
            std::shared_ptr<JSON::JSONNode> node;
            switch (nextToken.type)
            {
            case TOKEN::ARRAY_OPEN:
            {
                node = parseList();
                break;
            }
            case TOKEN::CURLY_OPEN:
            {
                node = parseObject();
                break;
            }
            case TOKEN::STRING:
            {
                tokenizer.rollBackToken();
                node = parseString();
                break;
            }
            case TOKEN::NUMBER:
            {
                tokenizer.rollBackToken();
                node = parseNumber();
                break;
            }
            case TOKEN::BOOLEAN:
            {
                tokenizer.rollBackToken();
                node = parseBoolean();
                break;
            }
            case TOKEN::NULL_TYPE:
            {
                node = parseNull();
                break;
            }
            }
            list->push_back(node);
            nextToken = tokenizer.getToken();
            if (nextToken.type == TOKEN::ARRAY_CLOSE)
            {
                hasCompleted = true;
            }
        }
    }
    node->setList(list);
    return node;
}
std::shared_ptr<JSON::JSONNode> JSONParser::parseBoolean()
{
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    Token nextToken = tokenizer.getToken();
    node->setBoolean(nextToken.value == "True" ? true : false);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseNull()
{
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    node->setNull();
    return node;
}