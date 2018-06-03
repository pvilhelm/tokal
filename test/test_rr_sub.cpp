#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rr_sub.h"

TEST_CASE("Test class vins_rr_sub", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};

            c.r[0] = 100;
            c.r[1] = 100;
            Vins* v = new Vins_rr_sub;
            v->set_arg(0);
            v->set_arg(1);

            v->execute(&c);

            REQUIRE(c.r[0] == 0);
            REQUIRE(c.Z == 1);
            REQUIRE(c.UF == 0);

            delete v;
        }

        {
            Cpu c{};

            c.r[0] = 0xF;
            c.r[1] = 0xFFFF'FFFF'FFFF'FFFF;
            Vins* v = new Vins_rr_sub;
            v->set_arg(0);
            v->set_arg(1);

            v->execute(&c);

            REQUIRE(c.r[0] == 0x10);
            REQUIRE(c.Z == 0);
            REQUIRE(c.UF == 1);

            delete v;
        }
        {
            Cpu c{};

            Vins* v = new Vins_rr_sub;
            v->set_arg(1024);
            v->set_arg(1027);
            REQUIRE_THROWS(v->execute(&c));

            delete v;

        }
    }
}