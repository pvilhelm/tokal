#include "vins/vins_r_jmpp.h"

#include <stdexcept>

Vins_r_jmpp::Vins_r_jmpp()
{}


Vins_r_jmpp::~Vins_r_jmpp()
{}

void Vins_r_jmpp::execute(Cpu *cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_r_jmpp: Register doesn't exist");

    uint64_t& dst = cpu->r[args[0]]; 

    if(cpu->Z == 0 && cpu->N == 0)
        cpu->IP = dst;
}

void Vins_r_jmpp::set_arg(uint64_t arg)
{
    if(arg_n == 1)
        throw new std::runtime_error("Vins_r_jmpp: Too many arguments");
    args[arg_n++] = arg;
}