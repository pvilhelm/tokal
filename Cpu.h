#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <map>
 

class assembly;
class Vins;


namespace cpu_util {
    constexpr uint32_t n_regs = 15;
    constexpr uint64_t stack_size = 1 << 20;

    const std::map<std::string, uint32_t> map_regname_too_num
    {
        {"sp", n_regs - 1},
        {"fp", n_regs - 2},
        {"ip", n_regs - 3},
        {"bp", n_regs - 4},
        {"r0", 0},
        {"r1", 1},
        {"r2", 2},
        {"r3", 3},
        {"r4", 4},
        {"r5", 5},
        {"r6", 6},
        {"r7", 7},
        {"r8", 8},
        {"r9", 9},
        {"r11", 11},
        {"r12", 12},
        {"r13", 13},
        {"r14", 14},
        {"SP", n_regs - 1},
        {"FP", n_regs - 2},
        {"IP", n_regs - 3},
        {"BP", n_regs - 4},
        {"R0", 0},
        {"R1", 1},
        {"R2", 2},
        {"R3", 3},
        {"R4", 4},
        {"R5", 5},
        {"R6", 6},
        {"R7", 7},
        {"R8", 8},
        {"R9", 9},
        {"R11", 11},
        {"R12", 12},
        {"R13", 13},
        {"R14", 14},
    };
}

class Cpu
{
public:
    Cpu();
    ~Cpu();

    void tick(void);
    void setup_assembly(assembly &ass);
    void run_program();
    void run_program(int32_t n);

    const uint32_t n_regs = cpu_util::n_regs;
    const uint64_t stack_size = cpu_util::stack_size;

    uint64_t r[cpu_util::n_regs] = {0};
    uint32_t Z = 0; // Zero flag
    uint32_t OF = 0; //Overflow flag
    uint32_t UF = 0; // Underflow flag
    uint32_t C = 0; // Carry flag
    uint32_t N = 0; // Negative flag (less than flag)
    uint32_t INT = 0;

    void clear_flags(void);
    void clear_registers(void);

    uint64_t& SP = r[cpu_util::n_regs - 1];
    uint64_t& FP = r[cpu_util::n_regs - 2];
    uint64_t& IP = r[cpu_util::n_regs - 3];
    uint64_t& BP = r[cpu_util::n_regs - 4];

    std::vector<std::shared_ptr<Vins>> v_vins_sptr{};
    std::vector<uint8_t> v_stack;

    uint64_t load_value_at_address(uint64_t ptr) const;
    void store_value_at_address(uint64_t ptr, uint64_t value) const;

    
};
