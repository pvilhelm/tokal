#include "Vins_rl_load.h"



Vins_rl_load::Vins_rl_load()
{}


Vins_rl_load::~Vins_rl_load()
{}

void Vins_rl_load::execute(Cpu * cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rl_load: Register doesn't exist");
    cpu->r[args[0]] = args[1];
}

void Vins_rl_load::set_arg(uint64_t arg)
{
    if(arg_n == 2)
        throw new std::runtime_error("Vins_rl_load: Too many arguments");
    args[arg_n++] = arg;
}
