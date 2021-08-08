#include <iostream>
#include "JSONNode.h"

std::string JSON::JSONNode::toString(int indentationLevel)
{
    std::string spaceString = std::string(indentationLevel, ' ');
    //sstreams
    std::string outputString = "";
    // std::cout < type << std::endl;
    switch (type)
    {
    case Type::STRING:
    {
        outputString += spaceString + *values.s;
        break;
    }
    case Type::NUMBER:
    {
        outputString += spaceString + std::to_string(values.fValue);
        break;
    }
    case Type::BOOLEAN:
    {
        outputString += spaceString + (values.bValue ? "true" : "false");
        break;
    }
    case Type::NULL_TYPE:
    {
        outputString += spaceString + "null";
        break;
    }
    case Type::LIST:
    {
        std::cout << "[";
        int index = 0;
        for (auto node : (*values.list))
        {
            outputString += node->toString(indentationLevel + 1);
            if (index < (*values.list).size() - 1)
            {
                outputString += spaceString + ", ";
            }
            index++;
        }
        outputString += spaceString + "]\n";
        break;
    }
    case Type::OBJECT:
    {
        outputString += "{\n";
        for (JSONObject::iterator i = (*values.object).begin();
             i != (*values.object).end(); i++)
        {
            outputString += spaceString + i->first + ":";
            outputString += i->second->toString(indentationLevel + 1);
            JSONObject::iterator next = i;
            next++;
            if ((next) != (*values.object).end())
            {
                outputString += spaceString + ",";
            }
            outputString += spaceString + "\n";
        }
        outputString += "}\n";
        return outputString;
    }
    }
}

void JSON::JSONNode::print_node(int indentationLevel)
{
    std::cout << toString(indentationLevel);
}