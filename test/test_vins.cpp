#include "catch.hpp"
#include "Cpu.h"

#include <memory>
#include <string>
#include <type_traits>

#include "vins\vins_all.h"

using namespace std;

TEST_CASE("Test class Vins", "")
{
    SECTION("Test vin_from_name"){
        {
            string ins = "qweqwe";

            REQUIRE_THROWS(vins_util::vin_from_name(ins));
        }
        {
            string ins = "r_jmpn";

            unique_ptr<Vins> uptr_vin = vins_util::vin_from_name(ins);
            Vins_r_jmpn vin_ans;

            REQUIRE(typeid(*uptr_vin).name() == typeid(vin_ans).name());
        }
        {
            string ins = "r_jmpz";

            unique_ptr<Vins> uptr_vin = vins_util::vin_from_name(ins);
            Vins_r_jmpz vin_ans;

            REQUIRE(typeid(*uptr_vin).name() == typeid(vin_ans).name());
        }
        {
            string ins = "rr_mul";

            unique_ptr<Vins> uptr_vin = vins_util::vin_from_name(ins);
            Vins_rr_mul vin_ans;

            REQUIRE(typeid(*uptr_vin).name() == typeid(vin_ans).name());
        }

    }
}