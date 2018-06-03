#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rp_add.h"

TEST_CASE("Test class rp_add", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};

            uint64_t term = 1000;
            c.r[0] = 100;

            Vins* v = new vins_rp_add;
            v->set_arg(0);
            v->set_arg((uint64_t)&term);

            v->execute(&c);

            REQUIRE(c.r[0] == 1100);
            REQUIRE(c.Z == 0);
            REQUIRE(c.OF == 0);

            delete v;
        }

        {
            Cpu c{};

            uint64_t term = 0xFFFF'FFFF'FFFF'FFF1;
            c.r[0] = 0xF;

            Vins* v = new vins_rp_add;
            v->set_arg(0);
            v->set_arg((uint64_t)&term);

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

            Vins* v = new vins_rp_add;
            v->set_arg(1024);
            v->set_arg((uint64_t)&term);

            REQUIRE_THROWS(v->execute(&c));

            delete v;
        }
        {
            Cpu c{};

            uint64_t term = 0xFFFF'FFFF'FFFF'FFF1;
            c.r[0] = 0xF;

            Vins* v = new vins_rp_add;
            v->set_arg(1024);
            v->set_arg(0);

            REQUIRE_THROWS(v->execute(&c));

            delete v;
        }
    }
}