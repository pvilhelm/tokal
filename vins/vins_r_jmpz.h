#pragma once
#include "Vins.h"
class Vins_r_jmpz :
    public Vins
{
public:
    Vins_r_jmpz();
    ~Vins_r_jmpz();

    void execute(Cpu *cpu) override;

    void set_arg(uint64_t arg) override;
    uint32_t n_args(void) const override { return 1; }

private:
    uint32_t arg_n = 0;
    uint64_t args[1] = {0};

};

