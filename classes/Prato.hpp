#ifndef PRATO_HPP
#define PRATO_HPP

#include "Copo.hpp"

class Prato : public Copo {
public:
    Prato(const ObjetoDeJogo &obj, double limiteIdeal = 100) : Copo(obj, limiteIdeal, 180.0) {}
    virtual ~Prato(){}

    virtual void preencher(double vazao);
};
#endif 