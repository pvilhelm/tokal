#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rr_div.h"

TEST_CASE("Test class vins_rr_div", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};

            c.r[0] = 1000;
            c.r[1] = 1000;
            Vins* v = new Vins_rr_div;
            v->set_arg(0);
            v->set_arg(1);

            v->execute(&c);

            REQUIRE(c.r[0] == 1);
            REQUIRE(c.Z == 0);
            REQUIRE(c.OF == 0);

            delete v;
        }
        {
            Cpu c{};

            c.r[0] = 1000;
            c.r[1] = 0;
            Vins* v = new Vins_rr_div;
            v->set_arg(0);
            v->set_arg(1);

            REQUIRE_THROWS(v->execute(&c));

            delete v;
        }
    }
}