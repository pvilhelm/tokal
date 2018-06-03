#include "vins/Vins_rl_add.h"

#include <stdexcept>

Vins_rl_add::Vins_rl_add()
{}


Vins_rl_add::~Vins_rl_add()
{}

void Vins_rl_add::execute(Cpu *cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rl_add: Register doesn't exist");
    
    uint64_t& dst = cpu->r[args[0]];
    uint64_t& src = args[1];
     

    uint64_t tmp = dst + src;

    if(tmp < dst)
        cpu->OF = 1U;
    else
        cpu->OF = 0U;
    if(tmp == 0U)
        cpu->Z = 1U;
    else
        cpu->Z = 0U;

    dst = tmp;
}

void Vins_rl_add::set_arg(uint64_t arg)
{
    if(arg_n == 2)
        throw new std::runtime_error("Vins_rl_add: Too many arguments");
    args[arg_n++] = arg;
}