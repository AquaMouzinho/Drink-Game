#include "Xicara.hpp"

void Xicara::preencher(double vazao){
    qtdAtual+= vazao;
    double qtdPorB = limiteMaximo/(this->getSprite()->getLargura() * this->getSprite()->getAltura());
    int i = ((qtdAtual*this->getSprite()->getAltura())/limiteMaximo);
    //int j = ((qtdAtual/qtdPorB)-((i+1)*5));
    
    this->getSprite()->putAt(Sprite("src/xicara/xicara_"+std::to_string(i)+".img"),0,0);
    this->update();
}
