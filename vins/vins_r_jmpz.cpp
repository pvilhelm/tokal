#include "vins/vins_r_jmpz.h"

#include <stdexcept>

Vins_r_jmpz::Vins_r_jmpz()
{}


Vins_r_jmpz::~Vins_r_jmpz()
{}

void Vins_r_jmpz::execute(Cpu *cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_r_jmpz: Register doesn't exist");

    uint64_t& dst = cpu->r[args[0]]; 

    if(cpu->Z == 1)
        cpu->IP = dst;
}

void Vins_r_jmpz::set_arg(uint64_t arg)
{
    if(arg_n == 1)
        throw new std::runtime_error("Vins_r_jmpz: Too many arguments");
    args[arg_n++] = arg;
}