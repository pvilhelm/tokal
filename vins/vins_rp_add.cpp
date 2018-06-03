#include "vins/vins_rp_add.h"

#include <stdexcept>

vins_rp_add::vins_rp_add()
{}


vins_rp_add::~vins_rp_add()
{}

void vins_rp_add::execute(Cpu *cpu)
{
    if(args[0] >= cpu->n_regs)
        throw new std::runtime_error("vins_rp_add: Register doesn't exist");

    uint64_t& dst = cpu->r[args[0]];
    uint64_t *src = (uint64_t*)args[1];

    if(src == 0)
        throw new std::runtime_error("vins_rp_add: Src pointer is null");

    uint64_t tmp = dst + *src;

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

void vins_rp_add::set_arg(uint64_t arg)
{
    if(arg_n == 2)
        throw new std::runtime_error("vins_rp_add: Too many arguments");
    args[arg_n++] = arg;
}

 