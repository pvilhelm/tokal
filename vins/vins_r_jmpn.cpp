#include "vins/vins_r_jmpn.h"

#include <stdexcept>

Vins_r_jmpn::Vins_r_jmpn()
{}


Vins_r_jmpn::~Vins_r_jmpn()
{}

void Vins_r_jmpn::execute(Cpu *cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_r_jmpz: Register doesn't exist");

    uint64_t& dst = cpu->r[args[0]];

    if(cpu->N == 1)
        cpu->IP = dst;
}

void Vins_r_jmpn::set_arg(uint64_t arg)
{
    if(arg_n == 1)
        throw new std::runtime_error("Vins_r_jmpz: Too many arguments");
    args[arg_n++] = arg;
}