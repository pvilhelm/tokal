#pragma once
#include "Vins.h"
class Vins_rl_load :
    public Vins
{
public:
    Vins_rl_load();
    ~Vins_rl_load();

    void execute(Cpu *cpu) override;

    void set_arg(uint64_t arg) override;
    uint32_t n_args(void) const override { return 2; }

private:
    uint32_t arg_n = 0;
    uint64_t args[2] = {0};
};

