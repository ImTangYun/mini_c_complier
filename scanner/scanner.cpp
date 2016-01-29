//
//
//
#include "scanner.h"

Scanner::Scanner(string source_file):path_(source_file), buffer_(source_file),
    flag_(0), line_(1), eof_(false) 
{
}
void Scanner::Init()
{
    key_word_dict_["if"] = (int32_t)KEYWORD;
    key_word_dict_["else"] = (int32_t)KEYWORD;
    key_word_dict_["while"] = (int32_t)KEYWORD;
    key_word_dict_["for"] = (int32_t)KEYWORD;
    key_word_dict_["return"] = (int32_t)KEYWORD;
    key_word_dict_["continue"] = (int32_t)KEYWORD;
    key_word_dict_["do"] = (int32_t)KEYWORD;
    key_word_dict_["goto"] = (int32_t)KEYWORD;
    key_word_dict_["case"] = (int32_t)KEYWORD;
    key_word_dict_["break"] = (int32_t)KEYWORD;
    key_word_dict_["default"] = (int32_t)KEYWORD;
    key_word_dict_["switch"] = (int32_t)KEYWORD;
    key_word_dict_["enum"] = (int32_t)KEYWORD;
    key_word_dict_["extern"] = (int32_t)KEYWORD;
    key_word_dict_["sizeof"] = (int32_t)KEYWORD;
    key_word_dict_["static"] = (int32_t)KEYWORD;
    key_word_dict_["union"] = (int32_t)KEYWORD;
    key_word_dict_["usigned"] = (int32_t)KEYWORD;
    key_word_dict_["struct"] = (int32_t)KEYWORD;
    key_word_dict_["volatile"] = (int32_t)KEYWORD;
    key_word_dict_["int"] = (int32_t)KEYWORD;
    key_word_dict_["double"] = (int32_t)KEYWORD;
    key_word_dict_["float"] = (int32_t)KEYWORD;
    key_word_dict_["char"] = (int32_t)KEYWORD;
    key_word_dict_["void"] = (int32_t)KEYWORD;
    key_word_dict_["long"] = (int32_t)KEYWORD;
    key_word_dict_["short"] = (int32_t)KEYWORD;
    key_word_dict_["true"] = (int32_t)KEYWORD;
    key_word_dict_["NULL"] = (int32_t)KEYWORD;
    key_word_dict_["false"] = (int32_t)KEYWORD;
    key_word_dict_["#include"] = (int32_t)KEYWORD;
    key_word_dict_["typdef"] = (int32_t)KEYWORD;
}
void Scanner::getNextToken()
{
    if (buffer_.eof()) {
        eof_ = true;
        return;
    }
    char next_char = (flag_ == 0)?buffer_.get():tmp_;

    // skip some useless chars
    while ((next_char == ';' || next_char == ' ' || next_char == '\t' || next_char == '\n')) {
        if (next_char == '\n') ++line_;
        if (!buffer_.eof()) {
            next_char = buffer_.get();
        } else {
            eof_ = true;
            return;
        }
    }
    flag_ = 0;
    
    // words start with alphalet
    if ((next_char >= 'a' && next_char <= 'z') ||
                (next_char >= 'A' && next_char <= 'Z') || next_char == '_') {
        temp_word_ += next_char;
        charOpration();
        return;

    // delimiters
    } else if (next_char == '(' || next_char == ')' ||
            next_char == '{' || next_char == '}' ||
            next_char == '.' || next_char == '?' ||
            next_char == ',') {
        temp_word_ += next_char;
        delimiterOpration();
        temp_word_.clear();
        flag_ = 0;
        return;
    // / /= // /*...*/
    } else if (next_char == '/') {
        temp_word_ += next_char;
        if (slashOpration()) {
            getNextToken();
        }
        return;
    // number operation
    } else if (next_char >= '0' && next_char <= '9') {
        temp_word_ += next_char;
        numberOpration();
        return;
    }

    if (buffer_.eof()) {
        eof_ = true;
        return;
    }

    char next_char2 = buffer_.get();
    int32_t ret = binaryOprator(next_char, next_char2, '=', '=', (int32_t)OPRATION);
    ret = binaryOprator(next_char, next_char2, '>', '=', (int32_t)OPRATION, ret);
    ret = binaryOprator(next_char, next_char2, '<', '=', (int32_t)OPRATION, ret);
    ret = binaryOprator(next_char, next_char2, '+', '=', (int32_t)OPRATION, ret);
    ret = binaryOprator(next_char, next_char2, '-', '=', (int32_t)OPRATION, ret);
    ret = binaryOprator(next_char, next_char2, '+', '+', (int32_t)OPRATION, ret);
    ret = binaryOprator(next_char, next_char2, '-', '-', (int32_t)OPRATION, ret);
    // ret = binaryOprator(next_char, next_char2, '/', '=', (int32_t)OPRATION, ret);
    ret = binaryOprator(next_char, next_char2, '*', '=', (int32_t)OPRATION, ret);
    ret = binaryOprator(next_char, next_char2, '-', '>', (int32_t)OPRATION, ret);
    ret = binaryOprator(next_char, next_char2, ':', ':', (int32_t)OPRATION, ret);
    if (ret == 1) {
        token_.setContent(path_, line_, temp_word_, (int32_t)OPRATION);
        flag_ = 0;
    } else if (ret == 0) {
        temp_word_ += next_char;
        token_.setContent(path_, line_, temp_word_, (int32_t)UNKNOWN);
    } else {
        temp_word_ += next_char;
        token_.setContent(path_, line_, temp_word_, (int32_t)OPRATION);
        tmp_ = next_char2;
        flag_ = 1;
    }
    temp_word_.clear();
}
Token Scanner::currentToken()
{
    return token_;
}
bool Scanner::hasNext()
{
    return !buffer_.eof(); 
}
void Scanner::charOpration()
{
    while (!buffer_.eof()) {
        if (!buffer_.eof()) {
            char next_char = buffer_.get();
            if (!((next_char >= 'a' && next_char <= 'z') ||
                        (next_char >= 'A' && next_char <= 'Z') ||
                        (next_char >= '0' && next_char <= '9') ||
                        (next_char == '_')) ) {
                flag_ = 1;
                tmp_ = next_char;
                if (key_word_dict_.find(temp_word_) != key_word_dict_.end()) {
                    token_.setContent(path_, line_, temp_word_, (int32_t)KEYWORD);
                } else {
                    token_.setContent(path_, line_, temp_word_, (int32_t)IDENTIFIER);
                }
                temp_word_.clear();
                return;
            }
            temp_word_ += next_char;
        } else {
            eof_ = true;
            return;
        }
    }
}
void Scanner::delimiterOpration()
{
    token_.setContent(path_, line_, temp_word_, (int32_t)DELIMITER);
}
int32_t Scanner::binaryOprator(char next_char1, char next_char2, char first,
        char second, int32_t type, int32_t state)
{
    if (state == 1) return state;
    if (next_char1 == first) {
        if (next_char2 == second) {
            temp_word_ += next_char1;
            temp_word_ += next_char2;
            return 1;
        }
        return 2;
    }
    return state;
}
void Scanner::numberOpration()
{
    while (!buffer_.eof()) {
        char next_char = buffer_.get();
        if (next_char >= '0' && next_char <= '9') {
            temp_word_ += next_char;
        } else {
            token_.setContent(path_, line_, temp_word_, (int32_t)INTEGER);
            temp_word_.clear();
            tmp_ = next_char;
            flag_ = 1;
            return;
        }
    }
    eof_ = true;
}
bool Scanner::eof()
{
    return eof_;
}
bool Scanner::slashOpration()
{
    if (buffer_.eof()) {
        eof_ = true;
        return false;
    }
    char next_char = buffer_.get();
    if (next_char == '=') {
        temp_word_ += next_char;
        token_.setContent(path_, line_, temp_word_, (int32_t)OPRATION);
        temp_word_.clear();
    } else if (next_char == '/') {
        temp_word_.clear();
        while (!buffer_.eof() && next_char != '\n') {
            next_char = buffer_.get();
            if (next_char == '\n') ++line_;
            if (next_char == '\n') return true;
        }
        if (buffer_.eof()) {
            eof_ = true;
            return false;
        }
    } else if (next_char == '*') {
        while (!buffer_.eof()) {
            next_char = buffer_.get();
            if (next_char == '\n') ++line_;
            if (next_char == '*') {
                if (buffer_.eof()) {
                    eof_ = true;
                    return false;
                }
                next_char = buffer_.get();
                if (next_char == '/') {
                    temp_word_.clear();
                    return true;
                } else if (next_char == '\n') {
                    ++line_;
                }
            }
        }
    } else {
        token_.setContent(path_, line_, temp_word_, (int32_t)OPRATION);
        flag_ = 1;
        tmp_ = temp_word_[0];
        temp_word_.clear();
    }
    return false;
}
