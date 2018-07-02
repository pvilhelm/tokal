#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rr_load.h"

TEST_CASE("Test class vins_rr_load", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};

            uint64_t literal = 1001;

            Vins *v = new Vins_rr_load;
            v->set_arg(0);
            v->set_arg(1);

            c.r[0] = 0;
            c.r[1] = (uint64_t)&literal;

            v->execute(&c);

            REQUIRE(c.r[0] == 1001);

            delete v;
        }
    }
}