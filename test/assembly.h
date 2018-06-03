#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <set>
#include <map>
#include <memory>

#include "vins\Vins.h"

class assembly
{
public:
    assembly();
    ~assembly();

    std::vector<std::shared_ptr<Vins>> v_instructions;
    std::vector<uint8_t> v_cdata;
    std::map<std::string, uint64_t> map_symbol_to_adress;

    std::string string_serialize();
    std::vector<uint8_t> bin_serialize();

    void parse_string(std::string s);
    void ps_handle_primitive(std::vector<std::string>::const_iterator &it, std::vector<std::string>::const_iterator end);
    void ps_handle_vins(std::vector<std::string>::const_iterator &it, std::vector<std::string>::const_iterator end);

    const std::set<std::string> set_primitives = {"u8, u16, u32, u64, s8, s16, s32, s64, single, double"};
};

namespace assembly_util {
    std::string remove_comments(std::string s);
    std::vector<std::string> tokenize_string(std::string s);
}
