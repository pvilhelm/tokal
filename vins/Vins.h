#pragma once

#include "Cpu.h"
#include <string>
#include <memory>

#include <set>

class Vins
{
public:
    Vins();
    virtual ~Vins() = default;

    virtual void execute(Cpu *cpu) = 0;

    virtual void set_arg(uint64_t lit) = 0;

    virtual uint32_t n_args(void) const = 0;

};


namespace vins_util{
    std::unique_ptr<Vins> vin_from_name(const std::string name);

    const std::set<std::string> set_of_instruction_names =
    {
        "r_jmpn",
        "r_jmpz",
        "r_jmpp",
        "rl_add",
        "rl_load",
        "rp_load",
        "rr_add",
        "rr_cmp",
        "rr_div",
        "rr_mul",
        "rr_sub",
        "rr_store",
        "rr_load",
        "rr_band",
    };
}

