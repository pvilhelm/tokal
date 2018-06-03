#include <exception>

#include "Cpu.h"
#include "vins\vins_all.h"

Cpu::Cpu()
{}


Cpu::~Cpu()
{}

void Cpu::tick(void)
{
    if(this->IP >= this->v_vins_sptr.size())
        throw std::runtime_error("No more instructions to fetch");
    /* If a "interrupt" is set go to the interrupt vector, which conveniently is 0 */
    if(this->INT != 0)
        this->IP = 0;

    auto v_uptr = this->v_vins_sptr[this->IP++];
    v_uptr->execute(this);
}
