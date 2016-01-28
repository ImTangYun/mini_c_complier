//
//
//
//
#include <stdio.h>
#include "token.h"

string get_type_str(int32_t type)
{
    switch (type) {
        case (int32_t)KEYWORD:
            return "KEYWORD";
        case (int32_t)CHAR:
            return "CHAR";
        case (int32_t)OPRATION:
            return "OPRATION";
        case (int32_t)DELIMITER:
            return "DELIMITER";
        case (int32_t)INTEGER:
            return "INTEGER";
        case (int32_t)IDENTIFIER:
            return "IDENTIFIER";
        case (int32_t)STRING:
            return "STRING";
        case (int32_t)UNKNOWN:
            return "UNKNOWN";
        case (int32_t)END_OF_FILE:
            return "END_OF_FILE";
        default:
            return "ERROR";
    }
}
void Token::setLocation(const string &path, const int line)
{
}
void Token::setWord(const string& word)
{
}
void Token::setType(TYPE type)
{
}
void Token::setContent(const string &path, const int line,
        const string& word, int32_t type)
{
    location_.path_ = path;
    location_.line_ = line;
    word_ = word;
    type_ = type;
}
void Token::dump()
{
    printf("%s:%d   %s  %s\n", location_.path_.c_str(), location_.line_, 
            word_.c_str(), get_type_str(type_).c_str());
}
