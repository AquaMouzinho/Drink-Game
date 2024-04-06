#include "FaseGame.hpp"
#include "Xicara.hpp"
#include "Jarra.hpp"
#include "Prato.hpp"
#include <termios.h>
#include <unistd.h>
using std::ref;

#define TIME 60000

void FaseGame::init() {
    objs.push_back(new ObjetoDeJogo("balaoIdeal", Sprite("src/balao.img"),20,69));

    objs.push_back(new ObjetoDeJogo("npc",Sprite("src/personagens/personagem_0.img"),24,52));
    spriteNPC = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("torneira", Sprite("src/torneira/torneira_0.img"),11,103));
    spriteTorneira = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("txtTempo", TextSprite("60s"),9,56));
    txtTempo = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("txtCopos", TextSprite("00"),9,73));
    txtCopos = objs.back()->getSprite();

    copoAtual = gerarCopo();
    objs.push_back(copoAtual);
    spriteCopo = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("txtMLAtual", TextSprite("0000"),34,101));
    txtMlAtual = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("txtMLIdeal", TextSprite(std::to_string(copoAtual->getLimiteIdeal()).substr(0,4)+"ML"),22,72));
    txtMlIdeal = objs.back()->getSprite();
    
    objs.push_back(new ObjetoDeJogo("txtMLMaximo", TextSprite(std::to_string(copoAtual->getLimiteMaximo()).substr(0,4)),34,106));
    txtMlMaximo = objs.back()->getSprite();

    // objs.push_back(new ObjetoDeJogo("displayEncerrado", Sprite("src/display_encerrado.img"),15,46));
    // display = objs.back();
    // display->desativarObj();

    gameState = Fase::PLAYING;
    input_thread_ = thread(&FaseGame::runPlayerChannel, ref(*this));
}

unsigned FaseGame::run(SpriteBuffer &screen){
    int tempoAtual = 0, coposPreenchidos = 0;
    bool isTransbordou = false;
    while(tempoAtual < TIME || keyPressed){

        if(isKeyPressed()){
            keyPressed = false;
            switch (entrada)
            {
                case 'q':
                    gameState = Fase::LEVEL_COMPLETE;
                    closePlayerChannel();
                    return Fase::MENU;
                case 'f':
                    {
                        std::cout << "apertou" << entrada <<std::endl;
                        isTransbordou = false;
                        spriteTorneira->putAt(Sprite("src/torneira/torneira_1.img"),0,0);
                        spriteTorneira->update();

                        while(!isKeyPressed() && !isTransbordou){
                            if(copoAtual->getQtdAtual() < copoAtual->getLimiteMaximo()){
                                copoAtual->preencher(10);
                                txtMlAtual->putAt(TextSprite(std::to_string(copoAtual->getQtdAtual()).substr(0,4)), 0,0);

                                tempoAtual+=100;
                                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                            }else{
                                isTransbordou = true;
                                
                                system("clear");
                                this->update();
                                this->draw(screen);
                                this->show(screen);

                                tempoAtual+=100;
                                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                                break;
                            }
                            txtTempo->putAt(TextSprite((((TIME - tempoAtual) > 10000) ? std::to_string(TIME - tempoAtual).substr(0,2) : "0"+std::to_string(TIME - tempoAtual).substr(0,1))+"s"),0,0);
                            
                            system("clear");
                            this->update();
                            this->draw(screen);
                            this->show(screen);
                        }
                        
                        keyPressed = false;
                        spriteTorneira->putAt(Sprite("src/torneira/torneira_0.img"),0,0);
                        spriteTorneira->update();
                        if(!isTransbordou)
                            coposPreenchidos++;
                        
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        for(int z = 0; z < 15; z++){
                            copoAtual->moveLeft();
                            system("clear");
                            this->update();
                            this->draw(screen);
                            this->show(screen);
                            std::this_thread::sleep_for(std::chrono::milliseconds(75));

                        }
                        std::this_thread::sleep_for(std::chrono::seconds(1));

                        Copo *tmp = copoAtual;
                        tmp->desativarObj();
                        copoAtual = gerarCopo();
                        objs.push_back(copoAtual);
                        spriteCopo = objs.back()->getSprite();
                        txtMlIdeal->putAt(TextSprite(std::to_string(copoAtual->getLimiteIdeal()).substr(0,4)+"ML"),0,0);
                        txtMlAtual->putAt(TextSprite(std::to_string(copoAtual->getQtdAtual()).substr(0,4)), 0,0);
                        txtMlMaximo->putAt(TextSprite(std::to_string(copoAtual->getLimiteMaximo()).substr(0,4)), 0,0);
                        aleatorizarNPC(spriteNPC);
                        objs.remove(tmp);
                        delete tmp;
                        txtCopos->putAt(TextSprite((coposPreenchidos>9 ? std::to_string(coposPreenchidos): "0"+std::to_string(coposPreenchidos))),0,0);
                    }
                    break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }else{
            tempoAtual += 300;
            txtTempo->putAt(TextSprite((((TIME - tempoAtual) > 10000) ? std::to_string(TIME - tempoAtual).substr(0,2) : "0"+std::to_string(TIME - tempoAtual).substr(0,1))+"s"),0,0);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        
        system("clear");
        this->update();
        this->draw(screen);
        this->show(screen);
    }
    gameState = Fase::LEVEL_COMPLETE;
    // display->ativarObj();
    // display->update();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    system("clear");
    this->update();
    this->draw(screen);
    this->show(screen);
    closePlayerChannel();
    return Fase::MENU;
}

void FaseGame::aleatorizarNPC(SpriteBase *s){
    srandom(time(NULL));
    unsigned numNPC = 0 + rand()%5;
    s->putAt(Sprite("src/personagens/personagem_"+std::to_string(numNPC)+".img"), 0, 0);
    s->update();
}

Copo* FaseGame::gerarCopo(){
    Copo *c;
    srandom(time(NULL));
    unsigned tipoCopo = 1+ rand()%4;
    switch (tipoCopo)
    {
        case 1:
            c = (new Prato(ObjetoDeJogo("Prato",Sprite("src/prato/prato_0.img"),28, 100), 50.0 + rand()%100));
            break;
        case 2:
            c = (new Xicara(ObjetoDeJogo("Xicara",Sprite("src/xicara/xicara_0.img"),26, 100), 100.0 + rand()%250));
            break;
    // case 3:
    //     c = (new Jarra(ObjetoDeJogo("Jarra",Sprite("src/jarra/jarra_0.img"),21, 100), 800.0 + rand()%1100));
    //     break;
        default:
            c = (new Copo(ObjetoDeJogo("Copo",Sprite("src/copo/copo_0.img"),24, 100), 100.0 + rand()%350));
            break;
    }
    return c;
}

void FaseGame::closePlayerChannel(){
    std::cout << "Partida encerrada! Pressione qualquer tecla para retornar ao menu..." << std::endl;
    input_thread_.join();
}

void FaseGame::runPlayerChannel(FaseGame &game) {
    struct termios old_tio, new_tio;
    unsigned char c;

    /* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO,&old_tio);

    /* we want to keep the old setting to restore them a the end */
    new_tio=old_tio;

    /* disable canonical mode (buffered i/o) and local echo */
    new_tio.c_lflag &=(~ICANON & ~ECHO);

    /* set the new settings immediately */
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

    while(game.gameState != Fase::LEVEL_COMPLETE){
        game.entrada = getchar();

        game.keyPressed = true;
    }
    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
}
