#include <exception>

#include "Cpu.h"
#include "vins\vins_all.h"
#include "assembly.h"

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

void Cpu::setup_assembly(assembly &ass)
{
    clear_flags();
    clear_registers();

    v_vins_sptr = ass.v_instructions;
    v_stack = std::vector<uint8_t>(stack_size);
    for(int i = 0; i < stack_size; i++)
        v_stack.push_back(0);
    this->SP = (uint64_t)&v_stack[0];
}

void Cpu::run_program()
{
    run_program(-1);
}

void Cpu::run_program(int32_t n)
{
    if(n < 0){
        while(IP < v_vins_sptr.size()) {
            this->tick();
        }
    } else {
        for(int i = 0; IP < v_vins_sptr.size() && i < n; i++) {
            this->tick();
        }
    }
}

void Cpu::clear_flags(void)
{
    Z = 0; // Zero flag
    OF = 0; //Overflow flag
    UF = 0; // Underflow flag
    C = 0; // Carry flag
    N = 0; // Negative flag (less than flag)
    INT = 0;
}

void Cpu::clear_registers(void)
{
    for(auto &rr : r) {
        rr = 0;
    }
}

uint64_t Cpu::load_value_at_address(uint64_t ptr) const
{
    return *(uint64_t*)ptr;
}

void Cpu::store_value_at_address(uint64_t ptr, uint64_t value) const
{
    *(uint64_t*)ptr = value;
    return;
}
