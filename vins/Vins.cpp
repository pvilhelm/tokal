#include "Vins.h"

#include <memory>
#include <exception>

#include "vins\vins_all.h"

Vins::Vins()
{}

std::unique_ptr<Vins> vins_util::vin_from_name(const std::string name)
{
    if(name == "r_jmpn") {
        return std::make_unique<Vins_r_jmpn>();
    } else if(name == "r_jmpz") {
        return std::make_unique<Vins_r_jmpz>();
    } else if(name == "rl_add") {
        return std::make_unique<Vins_rl_add>();
    } else if(name == "rl_load") {
        return std::make_unique<Vins_rl_load>();
    } else if(name == "rp_load") {
        return std::make_unique<Vins_rp_load>();
    } else if(name == "rr_add") {
        return std::make_unique<Vins_rr_add>();
    } else if(name == "rr_cmp") {
        return std::make_unique<Vins_rr_cmp>();
    } else if(name == "rr_div") {
        return std::make_unique<Vins_rr_div>();
    } else if(name == "rr_mul") {
        return std::make_unique<Vins_rr_mul>();
    } else if(name == "rr_sub") {
        return std::make_unique<Vins_rr_mul>();
    }

    throw std::runtime_error("Not a valid instruction");
}
