#pragma once

#include "vins\Vins.h"

class Vins_rr_store :
    public Vins
{
public:
    Vins_rr_store();
    ~Vins_rr_store();

    void execute(Cpu *cpu) override;

    void set_arg(uint64_t arg) override;
    uint32_t n_args(void) const override { return 2; }

private:
    uint32_t arg_n = 0;
    uint64_t args[2] = {0};
};

