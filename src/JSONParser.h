#include "JSONNode.h"
#include "Token.h"
#include <memory>

class JSONParser
{
    std::fstream file;
    std::shared_ptr<JSON::JSONNode> root;
    std::shared_ptr<JSON::JSONNode> current;
    Tokenizer tokenizer;

public:
    JSONParser(const std::string filename) : tokenizer(filename) {}
    void parse();
    std::shared_ptr<JSON::JSONNode> parseObject();
    std::shared_ptr<JSON::JSONNode> parseString();
    std::shared_ptr<JSON::JSONNode> parseNumber();
    std::shared_ptr<JSON::JSONNode> parseList();
    std::shared_ptr<JSON::JSONNode> parseBoolean();
    std::shared_ptr<JSON::JSONNode> parseNull();
};
