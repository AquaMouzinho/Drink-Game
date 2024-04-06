#include "FaseMenu.hpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>

void FaseMenu::init(){
    objs.push_back(new ObjetoDeJogo("OPMenu1", TextSprite("NOVO JOGO"), 20, 70));
    objs.push_back(new ObjetoDeJogo("OPMenu2", TextSprite("SAIR"), 23, 70));
    objs.push_back(new ObjetoDeJogo("Seletor", TextSprite("→ "), 20, 65));
    pSel = objs.back();
    std::cout.flush();
    op = Fase::OP_1;
    gameState = Fase::PLAYING;
    tela = Fase::PLAYING;
    menu_thread_ = thread(&FaseMenu::runPlayerChannel, ref(*this));
}

unsigned FaseMenu::run(SpriteBuffer &screen){
    tela = Fase::PLAYING;

    system("clear");
    this->draw(screen);
    this->show(screen);

    while(true){
        //entrada = getchar();
        if(isKeyPressed()){
            keyPressed = false;
            //std::cout << "apertou" << entrada << std::endl;
            if(entrada == 'q') {gameState=Fase::LEVEL_COMPLETE; break;}
            else if(entrada == 'w'){
                op = Fase::OP_1 + (op - Fase::OP_1 +1) % 2;

                pSel->moveTo(20 + (op - Fase::OP_1) * 2, 65);
            }else if(entrada == 's'){
                op = Fase::OP_1 + (2 + ((op - Fase::OP_1) -1)) % 2;

                pSel->moveTo(20 + (op - Fase::OP_1) * 3, 65);
            }else if(entrada == 'f'){
                if(op == Fase::OP_2){
                    gameState = Fase::LEVEL_COMPLETE;
                }
                tela = Fase::PAUSED;
                return op;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        system("clear");
        this->update();
        this->draw(screen);
        this->show(screen);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    gameState = Fase::LEVEL_COMPLETE;
    //closeThreads();
    return Fase::END_GAME;
}

void FaseMenu::closeThreads(){
    std::cout << "Pressione qualquer tecla para confirmar..." << std::endl;
    menu_thread_.join();
}

void FaseMenu::runPlayerChannel(FaseMenu &menu) {
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

    while(menu.gameState != Fase::LEVEL_COMPLETE){
        if(menu.tela == Fase::PLAYING){
            menu.entrada = getchar();

            menu.keyPressed = true;
        }else{
            menu.keyPressed = false;
        }
    }
    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
}
