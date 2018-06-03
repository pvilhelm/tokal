#include "assembly.h"

#include <set>
#include <stdexcept> 
#include <limits>
#include <memory>

using namespace std;

assembly::assembly()
{}


assembly::~assembly()
{}

void assembly::parse_string(string s)
{
    string s_program = assembly_util::remove_comments(s);
    vector<string> v_tokens = assembly_util::tokenize_string(s_program);

    for(auto &it = v_tokens.cbegin(); it < v_tokens.cend(); it++) {
        //check if primitive
        if(set_primitives.find(*it) != set_primitives.cend()) {
            ps_handle_primitive(it, v_tokens.cend());
        } else if(vins_util::set_of_instruction_names.find(*it) != vins_util::set_of_instruction_names.cend()) {
            ps_handle_vins(it, v_tokens.cend());
        }
    }
}

void assembly::ps_handle_vins(vector<string>::const_iterator &it, vector<string>::const_iterator end)
{
    string s_type = *it++;
    //Now we need to check how many arguments the vin have
    shared_ptr<Vins> sptr_vin = vins_util::vin_from_name(s_type);
    uint32_t n_args = sptr_vin->n_args();
    if(it + n_args == end)
        throw runtime_error("Parse error. Too few tokens for virtual instruction");

    // At this point of the assembly all syntactic sugar should be nice uint64:s :D
    for(int i = 0; i < n_args; i++) {
        uint64_t value = stoull(*it++,0,0);
        sptr_vin->set_arg(value);
    }

    //this should be a new line token
    string nl = *it++;
    if(nl != "\n")
        throw runtime_error("No new line at end of virtual instruction line");

    this->v_instructions.push_back(sptr_vin);

}

void assembly::ps_handle_primitive(vector<string>::const_iterator &it, vector<string>::const_iterator end)
{
    if(it + 3 == end)
        throw runtime_error("Parse error. Too few tokens for primitive");

    string s_type = *it++; //the type of the primitive
    string name = *it++;
    string value = *it++;

    //this need to be a new line
    string nl = *it++;
    if(nl != "\n")
        throw runtime_error("Parse error. No new line after primitive");

    uint64_t adress = v_cdata.size();
    //check if we should pad to "natural" boundary
    if(s_type == "s8" || s_type == "u8")
        ;
    else if(s_type == "s16" || s_type == "u16") {
        uint64_t mod = adress % 2;
        if(mod){
            v_cdata.push_back(0);
            adress = v_cdata.size();
        }
    } else if(s_type == "s32" || s_type == "u32" || s_type == "single") {
        uint64_t mod = adress % 4;
        if(mod){
            for(int i = 0; i < 4 - mod; i++){
                v_cdata.push_back(0);
            }
            adress = v_cdata.size();
        }
    } else if(s_type == "s64" || s_type == "u64" || s_type == "double") {
        uint64_t mod = adress % 8;
        if(mod) {
            for(int i = 0; i < 8 - mod; i++) {
                v_cdata.push_back(0);
            }
            adress = v_cdata.size();
        }
    } else {
        throw runtime_error("bugg: " + s_type);
    }

    auto pair = map_symbol_to_adress.emplace(name, adress);
    if(!pair.second)
        throw runtime_error("Symbol already defined!");

    //parse the value
    if(s_type == "u8") {
        unsigned long v = std::stoul(value, 0, 0);
        if(v & ~0xFF)
            throw runtime_error("Value to large for u8: ");
        v_cdata.push_back((uint8_t)v);
    } else if(s_type == "s8") {
        signed long v = std::stol(value, 0, 0);
        if(v < -128 || v > 127)
            throw runtime_error("Value to large for s8: ");
        v_cdata.push_back((int8_t)v);
    } else if(s_type == "s16") {
        signed long v = std::stol(value, 0, 0);
        if(v < numeric_limits<int16_t>::min() || v > numeric_limits<int16_t>::max())
            throw runtime_error("Value to large for s16: " + v);
        v_cdata.push_back((uint8_t)(uint16_t)v);
        v_cdata.push_back((uint8_t)((uint16_t)v >> 8U));
    } else if(s_type == "u16") {
        unsigned long v = std::stoul(value, 0, 0);
        if(v > numeric_limits<uint16_t>::max())
            throw runtime_error("Value to large for u16");
        v_cdata.push_back((uint8_t)v);
        v_cdata.push_back((uint8_t)(v >> 8U));
    } else if(s_type == "s32") {
        signed long long v = std::stoll(value, 0, 0);
        if(v < numeric_limits<int32_t>::min() || v > numeric_limits<int32_t>::max())
            throw runtime_error("Value to large for s32: ");
        v_cdata.push_back((uint8_t)(uint32_t)v);
        v_cdata.push_back((uint8_t)((uint32_t)v >> 8U));
        v_cdata.push_back((uint8_t)((uint32_t)v >> 16U));
        v_cdata.push_back((uint8_t)((uint32_t)v >> 24U));
    } else if(s_type == "u32") {
        unsigned long long v = std::stoull(value, 0, 0);
        if(v > numeric_limits<uint32_t>::max())
            throw runtime_error("Value to large for u32: ");
        v_cdata.push_back((uint8_t)v);
        v_cdata.push_back((uint8_t)(v >> 8U));
        v_cdata.push_back((uint8_t)(v >> 16U));
        v_cdata.push_back((uint8_t)(v >> 24U));
    } else if(s_type == "u64") {
        unsigned long long v = std::stoull(value, 0, 0);
        v_cdata.push_back((uint8_t)v);
        v_cdata.push_back((uint8_t)(v >> 8U));
        v_cdata.push_back((uint8_t)(v >> 16U));
        v_cdata.push_back((uint8_t)(v >> 24U));
        v_cdata.push_back((uint8_t)(v >> 32U));
        v_cdata.push_back((uint8_t)(v >> 40U));
        v_cdata.push_back((uint8_t)(v >> 48U));
        v_cdata.push_back((uint8_t)(v >> 56U));
    } else if(s_type == "s64") {
        signed long long v = std::stoll(value, 0, 0);
        v_cdata.push_back((uint8_t)(uint64_t)v);
        v_cdata.push_back((uint8_t)((uint64_t)v >> 8U));
        v_cdata.push_back((uint8_t)((uint64_t)v >> 16U));
        v_cdata.push_back((uint8_t)((uint64_t)v >> 24U));
        v_cdata.push_back((uint8_t)((uint64_t)v >> 32U));
        v_cdata.push_back((uint8_t)((uint64_t)v >> 40U));
        v_cdata.push_back((uint8_t)((uint64_t)v >> 48U));
        v_cdata.push_back((uint8_t)((uint64_t)v >> 56U));
    } else if(s_type == "single") {
        float vf = std::stof(value, 0);
        uint32_t v = *(uint32_t*)&vf;
        v_cdata.push_back((uint8_t)v);
        v_cdata.push_back((uint8_t)(v >> 8U));
        v_cdata.push_back((uint8_t)(v >> 16U));
        v_cdata.push_back((uint8_t)(v >> 24U));
    } else if(s_type == "double") {
        double vf = std::stod(value, 0);
        uint64_t v = *(uint64_t*)&vf;
        v_cdata.push_back((uint8_t)v);
        v_cdata.push_back((uint8_t)(v >> 8U));
        v_cdata.push_back((uint8_t)(v >> 16U));
        v_cdata.push_back((uint8_t)(v >> 24U));
        v_cdata.push_back((uint8_t)(v >> 32U));
        v_cdata.push_back((uint8_t)(v >> 40U));
        v_cdata.push_back((uint8_t)(v >> 48U));
        v_cdata.push_back((uint8_t)(v >> 56U));
    }
}

string assembly_util::remove_comments(string s)
{
    string ans;
    bool is_in_comment = false;
    bool is_in_quote = false;
    bool is_escaped = false;

    for(auto it = s.cbegin(); it < s.cend(); it++) {
        if(*it == '#') {
            if(!is_in_quote) {
                is_in_comment = true;
            } else {//is_in_comment
                ans += *it;
            }
        } else if(*it == '\"') {
            if(!is_in_comment) {
                if(is_in_quote) {
                    if(!is_escaped) {
                        is_in_quote = false;
                    }
                } else {// !is_in_quote
                    is_in_quote = true;
                }
                ans += *it;
            }
            is_escaped = false;
        } else if(*it == '\\') {
            if(!is_in_comment) {
                if(is_escaped) {
                    is_escaped = false;
                } else { // !is_escaped
                    is_escaped = true;
                }
                ans += *it;
            }
        } else if(*it == '\n') {
            is_escaped = false;
            if(!is_in_quote) {
                if(is_in_comment) {
                    is_in_comment = false;
                }
                ans += *it;
            } else {
                ans += *it;
            }
        } else if(!is_in_comment) {
            ans += *it;
        }
    }
    return ans;
}

/* Tokenize the string */
vector<string> assembly_util::tokenize_string(string s)
{
    
    bool is_in_quote = false;
    bool is_escaped = false;
    string tmp;

    vector<string> ans;

    for(char c : s) {
        
        if(c == '\"') {
            if(!is_escaped) {
                tmp += c;
                is_in_quote = false;
            } else {
                tmp += c;
                is_escaped = false; 
            }   
        } else if(c == '\\') {
            if(is_escaped) {
                is_escaped = false;
            } else {
                is_escaped = true;
            }
            tmp += c;
        } else if(c == ' ') {
            if(!is_in_quote){
                if(tmp.length() > 0){
                    ans.push_back(tmp);
                    tmp = "";
                }
            } else {
                tmp +=c;
            }
        } else if(c == '\t') {
            if(!is_in_quote) {
                if(tmp.length() > 0) {
                    ans.push_back(tmp);
                    tmp = "";
                }
            } else {
                tmp += " ";
            }
        } else if(c == '\n') {
            if(is_escaped && !is_in_quote) {
                tmp += c;
                ans.push_back(tmp);
                tmp = "";
                is_escaped = false;
            } else if(is_escaped) {
                tmp += c;
            } else {
                ans.push_back(tmp);
                tmp = "";
                tmp += c;
                ans.push_back(tmp);
                tmp = "";
            }
        } else {
            tmp += c;
        }  
    }
    if(tmp.length() != 0)
        ans.push_back(tmp);

    return ans;
}
