#include "catch.hpp"
#include "Cpu.h"

#include <memory>

#include "vins\vins_all.h"


TEST_CASE("Test class Cpu","")
{
    SECTION("Test load_value_at_address")
    {
        {
            Cpu cpu{};
            uint64_t i = 0xF00;
            REQUIRE(cpu.load_value_at_address((uint64_t)&i) == 0xF00);
            cpu.store_value_at_address((uint64_t)&i, 0xBAA);
            REQUIRE(cpu.load_value_at_address((uint64_t)&i) == 0xBAA);
        }
    }
    SECTION("Test ref")
    {
        Cpu c{};

        c.r[c.n_regs - 2] = 1;
        REQUIRE(c.FP == 1);

    }

    SECTION("Test execute some vins")
    {
        {
            Cpu c{};

            std::shared_ptr<Vins> v = std::make_shared<Vins_rl_add>();
            v->set_arg(0);
            v->set_arg(1);
            c.v_vins_sptr.push_back(v);
            c.tick();
            REQUIRE(c.r[0] == 1);
            REQUIRE(c.IP == 1);

        }
    }

    SECTION("Test some more")
    {
        {
            Cpu c{};

            std::shared_ptr<Vins> v = std::make_shared<Vins_rl_add>();
            v->set_arg(0);
            v->set_arg(1);
            c.v_vins_sptr.push_back(v);
            c.tick();
            REQUIRE(c.r[0] == 1);
            REQUIRE(c.IP == 1);
            v = std::make_shared<Vins_rl_load>();
            v->set_arg(0);
            v->set_arg(1);
            c.v_vins_sptr.push_back(v);

            v = std::make_shared<Vins_rl_load>();
            v->set_arg(1);
            v->set_arg(2);
            c.v_vins_sptr.push_back(v);


            v = std::make_shared<Vins_rr_add>();
            v->set_arg(0);
            v->set_arg(1);
            c.v_vins_sptr.push_back(v);

            c.tick(); c.tick(); c.tick();
            REQUIRE(c.r[0] == 3);
            REQUIRE(c.Z == 0);
        }
    }
}