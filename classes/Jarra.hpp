#ifndef JARRA_HPP
#define JARRA_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include "Copo.hpp"

class Jarra : public Copo {
public:
    Jarra(const ObjetoDeJogo &obj, double limiteIdeal = 1000.0) : Copo(obj, limiteIdeal, 2000.0) {}
    virtual ~Jarra(){}

};

#endif 