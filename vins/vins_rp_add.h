#pragma once
#include "Vins.h"
class vins_rp_add :
    public Vins
{
public:
    vins_rp_add();
    ~vins_rp_add();

    void execute(Cpu *cpu) override;

    void set_arg(uint64_t arg) override;

private:
    uint32_t arg_n = 0;
    uint64_t args[2] = {0};

};

