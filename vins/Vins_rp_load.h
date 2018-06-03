#pragma once

#include "vins\Vins.h"

class Vins_rp_load :
    public Vins
{
public:
    Vins_rp_load();
    ~Vins_rp_load();

    void execute(Cpu *cpu) override;

    void set_arg(uint64_t arg) override;
    uint32_t n_args(void) const override { return 2; }

private:
    uint32_t arg_n = 0;
    uint64_t args[2] = {0};
};

