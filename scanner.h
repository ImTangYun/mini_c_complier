//
//
//
#ifndef _SCANNER_H_
#define _SCANNER_H_
#include <string>
#include <unordered_map>
#include <fstream>
#include "token.h"

using namespace std;
class Scanner
{
    public:
        Scanner(string source_file);
        void Init();
        void getNextToken();
        Token currentToken();
        bool hasNext();
        bool eof();
    private:
        ifstream buffer_; 
        unordered_map<string, int32_t> key_word_dict_;
        string temp_word_;
        Token token_;
        string path_;
        int32_t line_;
        int32_t flag_;
        char tmp_;
        bool eof_;

    private:
        void charOpration();
        void delimiterOpration();
        void numberOpration();
        int32_t binaryOprator(char next_char1, char next_char2, char first,
                char second, int32_t type, int32_t state = 0);
};
#endif
