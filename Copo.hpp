#ifndef COPO_HPP
#define COPO_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Copo : public ObjetoDeJogo {
public:
    Copo(const ObjetoDeJogo &obj, double lI = 400.0, double lM = 500.0) : ObjetoDeJogo(obj), limiteMaximo(lM), limiteIdeal(lI), qtdAtual(0) {} 
    virtual ~Copo() {}

    virtual void update() { ObjetoDeJogo::update(); }

    virtual void preencher(double vazao);
    
    double getLimiteMaximo() const {return limiteMaximo;}
    double getLimiteIdeal() const {return limiteIdeal;}
    double getQtdAtual() const {return qtdAtual;}
    
protected:
    double limiteMaximo, limiteIdeal, qtdAtual;
};

#endif