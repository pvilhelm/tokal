#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <map>

class Vins;

class Cpu
{
public:
    Cpu();
    ~Cpu();

    void tick(void);

    static constexpr uint32_t n_regs = 15;
    static constexpr uint64_t stack_size = 1 << 20;

    uint64_t r[n_regs] = {0};
    uint32_t Z = 0; // Zero flag
    uint32_t OF = 0; //Overflow flag
    uint32_t UF = 0; // Underflow flag
    uint32_t C = 0; // Carry flag
    uint32_t N = 0; // Negative flag (less than flag)

    uint64_t INT = 0;

    uint64_t& SP = r[n_regs - 1];
    uint64_t& FP = r[n_regs - 2];
    uint64_t& IP = r[n_regs - 3];

    std::vector<std::shared_ptr<Vins>> v_vins_sptr{};
    std::vector<uint8_t> v_stack{}; 
    std::vector<uint8_t> v_heap{};

    const std::map<std::string, uint32_t> map_regname_too_num 
    {
        {"sp", n_regs - 1},
        {"fp", n_regs - 2},
        {"ip", n_regs - 3},
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
    };

};

