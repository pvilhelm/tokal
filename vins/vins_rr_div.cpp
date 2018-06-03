#include "vins\vins_rr_div.h"

#include <stdexcept>

Vins_rr_div::Vins_rr_div()
{}


Vins_rr_div::~Vins_rr_div()
{}

void Vins_rr_div::execute(Cpu *cpu)
{
    if(args[0] >= cpu->n_regs)
        throw std::runtime_error("Vins_rr_div: Register doesn't exist");
    if(args[1] >= cpu->n_regs)
        throw std::runtime_error("Vins_rr_div: Register doesn't exist");


    uint64_t& dst = cpu->r[args[0]];
    uint64_t& src = cpu->r[args[1]];

    if(src == 0)
        throw new std::runtime_error("Vins_rr_mul: Divident is zero");

    uint64_t tmp = dst / src;

    if(tmp == 0U)
        cpu->Z = 1U;
    else
        cpu->Z = 0U;

    dst = tmp;
}

void Vins_rr_div::set_arg(uint64_t arg)
{
    if(arg_n == 2)
        throw new std::runtime_error("Vins_rr_mul: Too many arguments");
    args[arg_n++] = arg;
}