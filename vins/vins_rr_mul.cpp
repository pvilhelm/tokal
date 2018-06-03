#include "vins/Vins_rr_mul.h"

#include <stdexcept>

Vins_rr_mul::Vins_rr_mul()
{}


Vins_rr_mul::~Vins_rr_mul()
{}

void Vins_rr_mul::execute(Cpu *cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rr_mul: Register doesn't exist");
    if(args[1] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rr_mul: Register doesn't exist");

    uint64_t& dst = cpu->r[args[0]];
    uint64_t& src = cpu->r[args[1]];
 
    uint64_t tmp = dst * src;

    if(dst != 0U && tmp / dst != src)
        cpu->OF = 1;
    else
        cpu->OF = 0;
    
    if(tmp == 0U)
        cpu->Z = 1U;
    else
        cpu->Z = 0U;

    dst = tmp;
}

void Vins_rr_mul::set_arg(uint64_t arg)
{
    if(arg_n == 2)
        throw new std::runtime_error("Vins_rr_mul: Too many arguments");
    args[arg_n++] = arg;
}