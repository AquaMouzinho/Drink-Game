#ifndef XICARA_HPP
#define XICARA_HPP

#include "Copo.hpp"

class Xicara : public Copo {
public:
    Xicara(const ObjetoDeJogo &obj, double limiteIdeal = 200) : Copo(obj, limiteIdeal, 375.0) {}
    virtual ~Xicara(){}

    virtual void preencher(double vazao);
};

#endif 