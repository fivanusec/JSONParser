#include <fstream>
#include <vector>
#include <map>
#include <stdexcept>
#include <stack>
#include <iostream>

enum class TOKEN
{
    CURLY_OPEN,
    CURLY_CLOSE,
    COLON,
    STRING,
    NUMBER,
    ARRAY_OPEN,
    ARRAY_CLOSE,
    COMMA,
    BOOLEAN,
    NULL_TYPE
};

struct Token
{
    std::string value;
    TOKEN type;

    std::string toString();
};

class Tokenizer
{
    std::fstream file;
    size_t prevPos;

public:
    Tokenizer(std::string fileName);
    auto getWithoutWhiteSpace() -> char;
    auto getToken() -> Token;
    auto hasMoreTokens() -> bool;
    void rollBackToken();
};