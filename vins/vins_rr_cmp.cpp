#include "vins/Vins_rr_cmp.h"

#include <stdexcept>

Vins_rr_cmp::Vins_rr_cmp()
{}


Vins_rr_cmp::~Vins_rr_cmp()
{}

void Vins_rr_cmp::execute(Cpu *cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rr_cmp: Register doesn't exist");
    if(args[1] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rr_cmp: Register doesn't exist");

    uint64_t& dst = cpu->r[args[0]];
    uint64_t& src = cpu->r[args[1]];

    if(dst == src) {
        cpu->Z = 1;
        cpu->N = 0;
    } else if(src > dst) {
        cpu->Z = 0;
        cpu->N = 0;
    } else {
        cpu->Z = 0;
        cpu->N = 1;
    }
}

void Vins_rr_cmp::set_arg(uint64_t arg)
{
    if(arg_n == 2)
        throw new std::runtime_error("Vins_rl_add: Too many arguments");
    args[arg_n++] = arg;
}