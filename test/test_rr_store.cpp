#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rr_store.h"

TEST_CASE("Test class vins_rr_store", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};

            uint64_t target = 1001;

            Vins *v = new Vins_rr_store;
            c.r[0] = 0xDEAD;
            v->set_arg(0);
            v->set_arg((uint64_t)&target);

            v->execute(&c);

            REQUIRE(target == 0xDEAD);

            delete v;
        }
    }
}