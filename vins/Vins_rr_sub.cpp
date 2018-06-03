#include "vins/Vins_rr_sub.h"

#include <stdexcept>

Vins_rr_sub::Vins_rr_sub()
{}


Vins_rr_sub::~Vins_rr_sub()
{}

void Vins_rr_sub::execute(Cpu *cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rr_sub: Register doesn't exist");
    if(args[1] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rr_sub: Register doesn't exist");

    uint64_t& dst = cpu->r[args[0]];
    uint64_t& src = cpu->r[args[1]];


    uint64_t tmp = dst - src;

    if(tmp > dst)
        cpu->UF = 1U;
    else
        cpu->UF = 0U;
    if(tmp == 0U)
        cpu->Z = 1U;
    else
        cpu->Z = 0U;

    dst = tmp;
}

void Vins_rr_sub::set_arg(uint64_t arg)
{
    if(arg_n == 2)
        throw new std::runtime_error("Vins_rr_sub: Too many arguments");
    args[arg_n++] = arg;
}