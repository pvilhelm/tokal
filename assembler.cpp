#include <set>
#include <sstream>

#include "assembler.h"

std::vector<std::shared_ptr<Vins>> parse_string(std::string s)
{
    return std::vector<std::shared_ptr<Vins>>();
}

std::vector<std::shared_ptr<Vins>> parse_file(std::string s)
{
    return std::vector<std::shared_ptr<Vins>>();
}



std::vector<std::string> tokenize_str(std::string s)
{
    
    return std::vector<std::string>();
}

/* Remove comments and "," etc */
std::string remove_comments(std::string s)
{
    std::stringstream ss;

    std::string tmp;

    bool in_comment = false;
    bool in_string = false; 
    bool escaped = false;
    
    for(int i = 0; i < s.length;i++) {
        char c = s[i];
        switch(c) {
            case '\\':
                if(!in_string)
                    throw std::runtime_error("Parse error. Invalid \\ at position " + i);
                if(escaped) escaped = false;
                else escaped = true;
            case '"':
                if(in_string) in_string = false;
                else in_string = true;
                break;
            case '#':
                if(!in_string) {
                    in_comment = true;
                }
                break;
            case '\n':
                if(in_comment) in_comment = false;
                break;
        }
    }

    return std::string();
}
