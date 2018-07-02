#include "Vins_rr_load.h"

Vins_rr_load::Vins_rr_load()
{}


Vins_rr_load::~Vins_rr_load()
{}

void Vins_rr_load::execute(Cpu * cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rr_load: Register doesn't exist");
    if(cpu->r[args[1]] == 0)
        throw std::runtime_error("Vins_rr_load: Null ptr");

    cpu->r[args[0]] = *(uint64_t*)cpu->r[args[1]];
}

void Vins_rr_load::set_arg(uint64_t arg)
{
    if(arg_n == 2)
        throw new std::runtime_error("Vins_rr_load: Too many arguments");
    args[arg_n++] = arg;
}
