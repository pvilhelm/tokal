#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rr_add.h"

TEST_CASE("Test class rr_add", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};
             
            c.r[0] = 100;
            c.r[1] = 1000;
            Vins* v = new Vins_rr_add;
            v->set_arg(0);
            v->set_arg(1);

            v->execute(&c);

            REQUIRE(c.r[0] == 1100);
            REQUIRE(c.Z == 0);
            REQUIRE(c.OF == 0);

            delete v;
        }

        {
            Cpu c{};

            c.r[0] = 0xF;
            c.r[1] = 0xFFFF'FFFF'FFFF'FFF1;
            Vins* v = new Vins_rr_add;
            v->set_arg(0);
            v->set_arg(1);

            v->execute(&c);

            REQUIRE(c.r[0] == 0);
            REQUIRE(c.Z == 1);
            REQUIRE(c.OF == 1);

            delete v;
        }
        {
            Cpu c{};

            Vins* v = new Vins_rr_add;
            v->set_arg(1024);
            v->set_arg(1027);

            REQUIRE_THROWS(v->execute(&c));

            delete v;

        }
    }
}