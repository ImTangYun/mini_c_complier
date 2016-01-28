//
//
//
#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <stdint.h>
#include <string>

using std::string;

enum TYPE
{
    KEYWORD = 0,
    OPRATION,
    DELIMITER,
    INTEGER,
    IDENTIFIER,
    CHAR,
    STRING,
    UNKNOWN,
    END_OF_FILE
};

string get_type_str(int32_t type);

struct Location
{
    Location():line_(1){}
    string path_;
    int32_t line_;
};

class Token
{
    public:
        void setLocation(const string &path, const int32_t line);
        void setWord(const string& word);
        void setType(TYPE type);
        void setContent(const string &path, const int32_t line,
                const string& word, int32_t type);
        void dump();
    private:
        Location location_;
        string word_;
        int32_t type_;
};
#endif
