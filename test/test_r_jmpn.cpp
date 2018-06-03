#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_r_jmpn.h"

TEST_CASE("Test class vins_r_jmpn", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};


            Vins *v = new Vins_r_jmpn;

            c.N = 1;
            c.r[10] = 10;
            v->set_arg(10);
            v->execute(&c);

            REQUIRE(c.IP == 10);

            delete v;
        }
        {
            Cpu c{};


            Vins *v = new Vins_r_jmpn;

            c.N = 0;
            c.r[10] = 10;
            v->set_arg(10);
            v->execute(&c);

            REQUIRE(c.IP == 0);

            delete v;
        }
    }
}