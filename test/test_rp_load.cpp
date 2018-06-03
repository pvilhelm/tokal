#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rp_load.h"

TEST_CASE("Test class vins_rp_load", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};

            uint64_t literal = 1001;

            Vins *v = new Vins_rp_load;
            v->set_arg(0);
            v->set_arg((uint64_t)&literal);

            v->execute(&c);

            REQUIRE(c.r[0] == 1001);

            delete v;
        }
        {
            Cpu c{};

            Vins *v = new Vins_rp_load;
            v->set_arg(0);
            v->set_arg((uint64_t)0);

            REQUIRE_THROWS(v->execute(&c));

            delete v;
        }
    }
}