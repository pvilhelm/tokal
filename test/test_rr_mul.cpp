#include "catch.hpp"
#include "Cpu.h"
#include "vins\vins_rr_mul.h"

TEST_CASE("Test class vins_rr_mul", "")
{
    SECTION("Test")
    {
        {
            Cpu c{};

            c.r[0] = 1000;
            c.r[1] = 1000;
            Vins* v = new Vins_rr_mul;
            v->set_arg(0);
            v->set_arg(1);

            v->execute(&c);

            REQUIRE(c.r[0] == 1000000);
            REQUIRE(c.Z == 0);
            REQUIRE(c.OF == 0);

            delete v;
        }
        {
            Cpu c{};

            c.r[0] = 1000;
            c.r[1] = 0;
            Vins* v = new Vins_rr_mul;
            v->set_arg(0);
            v->set_arg(1);

            v->execute(&c);

            REQUIRE(c.r[0] == 0);
            REQUIRE(c.Z == 1);
            REQUIRE(c.OF == 0);

            delete v;
        }
        {
            Cpu c{};

            c.r[0] = 1 << 64;
            c.r[1] = 2;
            Vins* v = new Vins_rr_mul;
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

            c.r[0] = 1 << 33;
            c.r[1] = 1 << 32;
            Vins* v = new Vins_rr_mul;
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

            c.r[0] = 0;
            c.r[1] = 0;
            Vins* v = new Vins_rr_mul;
            v->set_arg(0);
            v->set_arg(1);

            v->execute(&c);

            REQUIRE(c.r[0] == 0);
            REQUIRE(c.Z == 1);
            REQUIRE(c.OF == 0);

            delete v;
        }
    }
}