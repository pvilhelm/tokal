

#include <vector>
#include <memory>
#include <string>

#include "vins\vins_all.h"

std::vector<std::shared_ptr<Vins>> parse_string(std::string s);

std::vector<std::shared_ptr<Vins>> parse_file(std::string s);

std::vector<std::string> tokenize_str(std::string s);

std::string remove_comments(std::string s);
