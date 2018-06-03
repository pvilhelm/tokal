#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rl_load.h"

TEST_CASE("Test class vins_rl_load", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};
            
            uint64_t literal = 1001;

            Vins *v = new Vins_rl_load;
            v->set_arg(0);
            v->set_arg(literal);

            v->execute(&c);

            REQUIRE(c.r[0] == 1001);

            delete v;
        }
    }
}