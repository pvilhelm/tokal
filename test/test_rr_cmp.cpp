#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rr_cmp.h"

TEST_CASE("Test class vins_rr_cmp", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};
            c.r[0] = 1;
            c.r[1] = 1;

            Vins *v = new Vins_rr_cmp;

            v->set_arg(0);
            v->set_arg(1);
            v->execute(&c);

            REQUIRE(c.Z == 1);
            REQUIRE(c.N == 0);

            delete v;
        }
        {
            Cpu c{};
            c.r[0] = 1;
            c.r[1] = 0;

            Vins *v = new Vins_rr_cmp;

            v->set_arg(0);
            v->set_arg(1);
            v->execute(&c);

            REQUIRE(c.Z == 0);
            REQUIRE(c.N == 1);

            delete v;
        }
        {
            Cpu c{};
            c.r[0] = 1;
            c.r[1] = 2;

            Vins *v = new Vins_rr_cmp;

            v->set_arg(0);
            v->set_arg(1);
            v->execute(&c);

            REQUIRE(c.Z == 0);
            REQUIRE(c.N == 0);

            delete v;
        }
    }
}