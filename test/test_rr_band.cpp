#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rr_band.h"

TEST_CASE("Test class vins_rr_band", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};
             
            Vins *v = new Vins_rr_band;
            v->set_arg(0);
            v->set_arg(1);

            c.r[0] = 0x8899aabbccddeeff;
            c.r[1] = 0xF0F0F0F0F0F0F0F0;
            uint64_t ans = 0x8090a0b0c0d0e0f0;
            v->execute(&c);

            REQUIRE(c.r[0] == ans);

            delete v;
        }
    }
}