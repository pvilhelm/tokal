#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rl_add.h"

TEST_CASE("Test class rl_add", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};

            c.r[0] = 100;

            Vins* v = new Vins_rl_add;
            v->set_arg(0);
            v->set_arg(10);

            v->execute(&c);

            REQUIRE(c.r[0] == 110);
            REQUIRE(c.Z == 0);
            REQUIRE(c.OF == 0);

            delete v;
        }

        {
            Cpu c{};

            uint64_t term = 0xFFFF'FFFF'FFFF'FFF1;
            c.r[0] = 0xF;

            Vins* v = new Vins_rl_add;
            v->set_arg(0);
            v->set_arg(term);

            v->execute(&c);

            REQUIRE(c.r[0] == 0);
            REQUIRE(c.Z == 1);
            REQUIRE(c.OF == 1);

            delete v;
        }
        {
            Cpu c{};

            uint64_t term = 0xFFFF'FFFF'FFFF'FFF1;
            c.r[0] = 0xF;

            Vins* v = new Vins_rl_add;
            v->set_arg(1024);
            v->set_arg(term);

            REQUIRE_THROWS(v->execute(&c));

            delete v;
        }
    }
}