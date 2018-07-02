#include "vins_rr_band.h"

Vins_rr_band::Vins_rr_band()
{}


Vins_rr_band::~Vins_rr_band()
{}

void Vins_rr_band::execute(Cpu * cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rr_band: Register doesn't exist");
    if(args[1] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rr_band: Register doesn't exist");

    cpu->r[args[0]] &= cpu->r[args[1]];
}

void Vins_rr_band::set_arg(uint64_t arg)
{
    if(arg_n == 2)
        throw new std::runtime_error("Vins_rr_load: Too many arguments");
    args[arg_n++] = arg;
}
