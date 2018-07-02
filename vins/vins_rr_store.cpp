#include "Vins_rr_store.h"



Vins_rr_store::Vins_rr_store()
{}


Vins_rr_store::~Vins_rr_store()
{}

void Vins_rr_store::execute(Cpu * cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("Vins_rr_store: Register doesn't exist");
    if(args[1] == 0)
        throw new std::runtime_error("Vins_rr_store: Ptr is null");
    cpu->store_value_at_address(args[1], cpu->r[args[0]]);
}

void Vins_rr_store::set_arg(uint64_t arg)
{
    if(arg_n == 2)
        throw new std::runtime_error("Vins_rp_load: Too many arguments");
    args[arg_n++] = arg;
}