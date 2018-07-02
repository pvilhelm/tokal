#include "catch.hpp"

#include <string>
#include <vector>
#include <type_traits>

#include "assembly.h"
#include "vins\vins_all.h"
#include "Cpu.h"

using namespace std;

TEST_CASE("Test assembly")
{
    SECTION("Test tokenize_string")
    {
        {
            string test_string = "tokenize me plz";
            auto v_ans = assembly_util::tokenize_string(test_string);

            vector<string> key = {"tokenize","me","plz"};

            REQUIRE(key == v_ans);
            
        }
        {
            string test_string = "tokenize me plz\nand me too! 201";
            auto v_ans = assembly_util::tokenize_string(test_string);

            vector<string> key = {"tokenize","me","plz","\n","and","me", "too!", "201"};

            REQUIRE(key == v_ans);
        }

        {
            string test_string = "tokenize me plz\\\nand me too! 201";
            auto v_ans = assembly_util::tokenize_string(test_string);

            vector<string> key = {"tokenize","me","plz\\\n","and","me", "too!", "201"};

            REQUIRE(key == v_ans);
        }
        {
            string test_string = "\tI\thate\ttabs";
            auto v_ans = assembly_util::tokenize_string(test_string);

            vector<string> key = {"I","hate","tabs"};

            REQUIRE(key == v_ans);
        }
        {
            string test_string = "  a      b                c    \t   \t d";
            auto v_ans = assembly_util::tokenize_string(test_string);

            vector<string> key = {"a","b","c","d"};

            REQUIRE(key == v_ans);
        }
    }

    SECTION("remove_comments")
    {
        {
            string test_string = "code #comments";
            string key = "code ";
            string ans = assembly_util::remove_comments(test_string);

            REQUIRE(key == ans);
        }
        {
            string test_string = "code #comments\nmore code#some comments";
            string key = "code \nmore code";
            string ans = assembly_util::remove_comments(test_string);

            REQUIRE(key == ans);
        }
        {
            string test_string = "code #comments\nmore code \"#not comment\"#comment";
            string key = "code \nmore code \"#not comment\"";
            string ans = assembly_util::remove_comments(test_string);

            REQUIRE(key == ans);
        }
        {
            string test_string = "\\#comm\\ent\n\"test\"";
            string key = "\\\n\"test\"";
            string ans = assembly_util::remove_comments(test_string);

            REQUIRE(key == ans);
        }
        {
            string test_string = "a#comment#commentinacomment\nb";
            string key = "a\nb";
            string ans = assembly_util::remove_comments(test_string);

            REQUIRE(key == ans);
        }
    }

    SECTION("Test assigning ps_handle_primitive")
    {
        {
            vector<string> v{"u8","test","8","\n"};

            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == 8);
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
        {
            vector<string> v{"u16","test","0XFFAA","\n"};

            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == 0xAA);
            REQUIRE(ass.v_cdata[1] == 0xFF);
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
        {
            vector<string> v{"u32","test","0XFFAABBCC","\n"};

            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == 0xcc);
            REQUIRE(ass.v_cdata[1] == 0xBB); 
            REQUIRE(ass.v_cdata[2] == 0xAA);
            REQUIRE(ass.v_cdata[3] == 0xFF);
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
        {
            vector<string> v{"u64","test","0X44332211FFAABBCC","\n"};

            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == 0xcc);
            REQUIRE(ass.v_cdata[1] == 0xBB);
            REQUIRE(ass.v_cdata[2] == 0xAA);
            REQUIRE(ass.v_cdata[3] == 0xFF);
            REQUIRE(ass.v_cdata[4] == 0x11);
            REQUIRE(ass.v_cdata[5] == 0x22);
            REQUIRE(ass.v_cdata[6] == 0x33);
            REQUIRE(ass.v_cdata[7] == 0x44);
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
        {
            vector<string> v{"s8","test","8","\n"};

            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == 8);
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
        {
            vector<string> v{"s16","test","-86","\n"};

            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == 0xAA);
            REQUIRE(ass.v_cdata[1] == 0xFF);
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
        {
            vector<string> v{"s32","test","-1122902","\n"};

            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == 0xAA);
            REQUIRE(ass.v_cdata[1] == 0xDD);
            REQUIRE(ass.v_cdata[2] == 0xEE);
            REQUIRE(ass.v_cdata[3] == 0xFF);
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
        {
            vector<string> v{"s64","test","-4822678189205112","\n"};

            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == 0x88);
            REQUIRE(ass.v_cdata[1] == 0x99);
            REQUIRE(ass.v_cdata[2] == 0xAA);
            REQUIRE(ass.v_cdata[3] == 0xBB);
            REQUIRE(ass.v_cdata[4] == 0xCC);
            REQUIRE(ass.v_cdata[5] == 0xDD);
            REQUIRE(ass.v_cdata[6] == 0xEE);
            REQUIRE(ass.v_cdata[7] == 0xFF);
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
        {
            vector<string> v{"double","test","0.73","\n"};

            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == 0x5c);
            REQUIRE(ass.v_cdata[1] == 0x8f);
            REQUIRE(ass.v_cdata[2] == 0xc2);
            REQUIRE(ass.v_cdata[3] == 0xf5);
            REQUIRE(ass.v_cdata[4] == 0x28);
            REQUIRE(ass.v_cdata[5] == 0x5c);
            REQUIRE(ass.v_cdata[6] == 0xe7);
            REQUIRE(ass.v_cdata[7] == 0x3f);
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
        {
            vector<string> v{"single","test","0.73","\n"};

            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == 0x48);
            REQUIRE(ass.v_cdata[1] == 0xe1);
            REQUIRE(ass.v_cdata[2] == 0x3a);
            REQUIRE(ass.v_cdata[3] == 0x3f);
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
        {
            vector<string> v{"single","test","inf","\n"};

            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == 0x00);
            REQUIRE(ass.v_cdata[1] == 0x00);
            REQUIRE(ass.v_cdata[2] == 0x80);
            REQUIRE(ass.v_cdata[3] == 0x7f);
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
        {
            vector<string> v{"double","test","inf","\n"};
            double inf = numeric_limits<double>::infinity();
            uint64_t iinf = *(uint64_t*)&inf;
            assembly ass;

            ass.ps_handle_primitive(v.cbegin(), v.cend());

            REQUIRE(ass.map_symbol_to_offset_adress.find("test") != ass.map_symbol_to_offset_adress.cend());
            REQUIRE(ass.v_cdata[0] == ((uint8_t)iinf));
            REQUIRE(ass.v_cdata[1] == ((uint8_t)(iinf >> 8)));
            REQUIRE(ass.v_cdata[2] == ((uint8_t)(iinf >> 16)));
            REQUIRE(ass.v_cdata[3] == ((uint8_t)(iinf >> 24)));
            REQUIRE(ass.v_cdata[4] == ((uint8_t)(iinf >> 32)));
            REQUIRE(ass.v_cdata[5] == ((uint8_t)(iinf >> 40)));
            REQUIRE(ass.v_cdata[6] == ((uint8_t)(iinf >> 48)));
            REQUIRE(ass.v_cdata[7] == ((uint8_t)(iinf >> 56)));
            REQUIRE(ass.map_symbol_to_offset_adress.find("test") == ass.map_symbol_to_offset_adress.cbegin());
        }
    }

    SECTION("Test throws ps_handle_primitive")
    {
        {
            vector<string> v{"u8","test","256","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"u8","test","-1","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"u16","test","65536","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"s8","test","128","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"s8","test","-129","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"s16","test","-32769","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"s16","test","32768","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"s32","test","2147483648","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"s32","test","-2147483649","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"u32","test","-2147483649","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"u32","test","4294967296","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"u64","test","18446744073709551616","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"s64","test","9223372036854775808","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
        {
            vector<string> v{"s64","test","-9223372036854775809","\n"};

            assembly ass;

            REQUIRE_THROWS(ass.ps_handle_primitive(v.cbegin(), v.cend()));
        }
    }

    SECTION("Test padding ps_handle_primitive")
    {
        {
            vector<string> v{"u8","test","255","\n", "u16", "test2","0x2211","\n"};

            assembly ass;
            auto &it = v.cbegin();
            ass.ps_handle_primitive(it, v.cend());
            ass.ps_handle_primitive(++it, v.cend());

            REQUIRE(ass.v_cdata[0] == 255);
            REQUIRE(ass.v_cdata[2] == 0x11);
            REQUIRE(ass.v_cdata[3] == 0x22);
        }
        {
            vector<string> v{"u8","test","255","\n", "u32", "test4","0x44332211","\n"};

            assembly ass;
            auto &it = v.cbegin();
            ass.ps_handle_primitive(it, v.cend());
            ass.ps_handle_primitive(++it, v.cend());

            REQUIRE(ass.v_cdata[0] == 255);
            REQUIRE(ass.v_cdata[4] == 0x11);
            REQUIRE(ass.v_cdata[5] == 0x22);
            REQUIRE(ass.v_cdata[6] == 0x33);
            REQUIRE(ass.v_cdata[7] == 0x44);
        }
        {
            vector<string> v{"s8","test","127","\n", "s32", "test4","1144201745","\n"};

            assembly ass;
            auto &it = v.cbegin();
            ass.ps_handle_primitive(it, v.cend());
            ass.ps_handle_primitive(++it, v.cend());

            REQUIRE(ass.v_cdata[0] == 127);
            REQUIRE(ass.v_cdata[4] == 0x11);
            REQUIRE(ass.v_cdata[5] == 0x22);
            REQUIRE(ass.v_cdata[6] == 0x33);
            REQUIRE(ass.v_cdata[7] == 0x44);
        }
        {
            vector<string> v{"u8","test","255","\n", "u64", "test4","0x8877665544332211","\n"};

            assembly ass;
            auto &it = v.cbegin();
            ass.ps_handle_primitive(it, v.cend());
            ass.ps_handle_primitive(++it, v.cend());

            REQUIRE(ass.v_cdata[0] == 255);
            REQUIRE(ass.v_cdata[8] == 0x11);
            REQUIRE(ass.v_cdata[9] == 0x22);
            REQUIRE(ass.v_cdata[10] == 0x33);
            REQUIRE(ass.v_cdata[11] == 0x44);
            REQUIRE(ass.v_cdata[12] == 0x55);
            REQUIRE(ass.v_cdata[13] == 0x66);
            REQUIRE(ass.v_cdata[14] == 0x77);
            REQUIRE(ass.v_cdata[15] == 0x88);
        }
        {
            vector<string> v{"u8","test","255","\n", "s64", "test4","-8613303245920329199","\n"};

            assembly ass;
            auto &it = v.cbegin();
            ass.ps_handle_primitive(it, v.cend());
            ass.ps_handle_primitive(++it, v.cend());

            REQUIRE(ass.v_cdata[0] == 255);
            REQUIRE(ass.v_cdata[8] == 0x11);
            REQUIRE(ass.v_cdata[9] == 0x22);
            REQUIRE(ass.v_cdata[10] == 0x33);
            REQUIRE(ass.v_cdata[11] == 0x44);
            REQUIRE(ass.v_cdata[12] == 0x55);
            REQUIRE(ass.v_cdata[13] == 0x66);
            REQUIRE(ass.v_cdata[14] == 0x77);
            REQUIRE(ass.v_cdata[15] == 0x88);
        }
        {
            vector<string> v{"s8","test","127","\n", "s32", "test","1144201745","\n"};

            assembly ass;
            auto &it = v.cbegin();
            ass.ps_handle_primitive(it, v.cend());
            REQUIRE_THROWS(ass.ps_handle_primitive(it, v.cend()));       
        }
    }

    SECTION("Test assigning ps_handle_vins")
    {
        {
            vector<string> s_test = {"rl_add","0","2","\n"}; //add 2 to register 0
            Vins_rl_add ans_type;
            assembly ass;

            Cpu cpu;

            ass.ps_handle_vins(s_test.cbegin(), s_test.cend());
            
            REQUIRE(typeid(*ass.v_instructions[0]).name() == typeid(ans_type).name());
            ass.v_instructions[0]->execute(&cpu);
            REQUIRE(cpu.r[0] == 2);
        }
    }

    SECTION("Test parse string with primitives")
    {
        {
            string program = "u8 u 3\nu8 i 3\nrl_add 0 i\n";
            Vins_rl_add ans_type;
            assembly ass;

            ass.parse_string(program);
            REQUIRE(typeid(*ass.v_instructions[0]).name() == typeid(ans_type).name());
            REQUIRE(ass.map_symbol_to_address.find("i")->first == "i");
            REQUIRE(ass.map_symbol_to_address.find("i")->second == 1 + (uint64_t)&ass.v_cdata[0]);

        }
    }

    SECTION("Test parse string with primitives and label")
    {
        {
            string program = "u8 u 3\nu8 i 3\nrl_add 0 i\n:label\nrp_load 0 label\n";
            Vins_rl_add ans_type;
            assembly ass;

            ass.parse_string(program);
            REQUIRE(typeid(*ass.v_instructions[0]).name() == typeid(ans_type).name());
            REQUIRE(ass.map_symbol_to_address.find("i")->first == "i");
            REQUIRE(ass.map_symbol_to_address.find("i")->second == (uint64_t)&ass.v_cdata[0] + 1);
            REQUIRE(ass.map_symbol_to_address.find("label")->first == "label");
            REQUIRE(ass.map_symbol_to_address.find("label")->second == 1);
        }
    }

    SECTION("Test parse string with primitives and label")
    {
        {
            string file_path = "C:/repos/tokal/test/test_tasm/test0.tasm";

            assembly ass = assembly::assembly_from_file(file_path);

            REQUIRE(ass.v_instructions.size() == 3);
            REQUIRE(ass.v_cdata.size() == 8);

            Cpu cpu;

            for(auto ins : ass.v_instructions) {
                ins->execute(&cpu);
            }

            REQUIRE(cpu.r[0] == 6);
        }
        {
            string file_path = "C:/repos/tokal/test/test_tasm/test1.tasm";

            assembly ass = assembly::assembly_from_file(file_path);
            
            //REQUIRE(ass.v_instructions.size() == 5);
            //REQUIRE(ass.v_cdata.size() == 0);

            Cpu cpu;

            cpu.setup_assembly(ass);
            cpu.run_program();


            REQUIRE(cpu.r[0] == 255);
        }
        {
            string file_path = "C:/repos/tokal/test/test_tasm/test2.tasm";

            assembly ass = assembly::assembly_from_file(file_path);

            Cpu cpu;

            cpu.setup_assembly(ass);
            cpu.run_program();


            REQUIRE(cpu.r[0] == 12);
            REQUIRE(cpu.r[1] == 20);
        }
        {
            string file_path = "C:/repos/tokal/test/test_tasm/test3.tasm";

            assembly ass = assembly::assembly_from_file(file_path);

            Cpu cpu;

            cpu.setup_assembly(ass);

            cpu.v_stack[0] = 2;
            cpu.v_stack[8] = 3;
            cpu.SP = (uint64_t)&cpu.v_stack[0] + 16;
            cpu.run_program();


            REQUIRE(cpu.r[0] == 8);
        }
    }
}