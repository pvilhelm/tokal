#include "Vins_rp_load.h"



Vins_rp_load::Vins_rp_load()
{}


Vins_rp_load::~Vins_rp_load()
{}

void Vins_rp_load::execute(Cpu * cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rp_load: Register doesn't exist");
    if(args[1] == 0)
        throw new std::runtime_error("Vins_rp_load: Ptr is null");
    cpu->r[args[0]] = *(uint64_t*)args[1];
}

void Vins_rp_load::set_arg(uint64_t arg)
{
    if(arg_n == 2)
        throw new std::runtime_error("Vins_rp_load: Too many arguments");
    args[arg_n++] = arg;
}