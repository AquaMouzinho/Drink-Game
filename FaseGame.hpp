#ifndef FASEGAME_HPP
#define FASEGAME_HPP

#include "ASCII_Engine/Fase.hpp"
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include "ASCII_Engine/SpriteBuffer.hpp"
#include "Copo.hpp"

#include <thread>
#include <chrono>
using std::thread;

class FaseGame : public Fase {
public:
    FaseGame(std::string name, const Sprite &bkg) : Fase(name, bkg), keyPressed(false) {};
    virtual ~FaseGame() {}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    bool isKeyPressed() const { return keyPressed; }

    
private:
    Copo* copoAtual;
    SpriteBase *txtMlIdeal, *txtMlMaximo, *txtMlAtual, *txtTempo, *txtCopos, *spriteCopo, *spriteNPC, *spriteTorneira;
    ObjetoDeJogo *display;
    unsigned gameState;

    char entrada;
    bool keyPressed;
    thread input_thread_;
    
    void closePlayerChannel();
    static void runPlayerChannel(FaseGame &);
    Copo *gerarCopo();
    void aleatorizarNPC(SpriteBase *);
};

#endif