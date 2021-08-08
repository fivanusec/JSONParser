#pragma once

#include <memory>
#include <map>
#include <vector>

namespace JSON
{
    class JSONNode;
    using JSONObject = std::map<std::string, std::shared_ptr<JSONNode>>;
    using JSONList = std::vector<std::shared_ptr<JSONNode>>;

    class JSONNode
    {
        enum class Type
        {
            OBJECT,
            LIST,
            STRING,
            NUMBER,
            BOOLEAN,
            NULL_TYPE
        };

        union Values
        {
            JSONObject *object;
            JSONList *list;
            std::string *s;
            float fValue;
            bool bValue;
        } values;

        Type type;

    public:
        JSONNode() {}
        JSONNode(Type t) { type = t; }

        auto getObject()
        {
            if (type == Type::OBJECT)
            {
                return *values.object;
            }
            throw std::logic_error("Improper return");
        }
        auto getList()
        {
            if (type == Type::LIST)
            {
                return *values.list;
            }
            throw std::logic_error("Improper return");
        }
        auto getString()
        {
            if (type == Type::STRING)
            {
                return *values.s;
            }
            throw std::logic_error("Improper return");
        }
        auto getFloat()
        {
            if (type == Type::NUMBER)
            {
                return values.fValue;
            }
            throw std::logic_error("Improper return");
        }

        void setObject(JSONObject *object)
        {
            this->values.object = object;
            type = Type::OBJECT;
        }

        void setString(std::string *s)
        {
            this->values.s = s;
            type = Type::STRING;
        }
        void setNumber(float f)
        {
            this->values.fValue = f;
            type = Type::NUMBER;
        }
        void setList(JSONList *list)
        {
            this->values.list = list;
            type = Type::LIST;
        }

        void setBoolean(bool v)
        {
            this->values.bValue = v;
            type = Type::BOOLEAN;
        }

        void setNull()
        {
            type = Type::NULL_TYPE;
        }

        std::string toString(int indentationLevel);
        void print_node(int indentationLevel);
    };
}