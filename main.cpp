#include "MiniGame.hpp"
#include <string>
#include <iostream>
using std::string, std::cout, std::endl;

/*
unsigned int contaCaracteres(const string &s){
    unsigned int charCount = 0;

    unsigned int strLen = s.length();
    unsigned int u = 0;
    const char *c_str = s.c_str();
    while(u < strLen)
    {
        u += mblen(&c_str[u], strLen - u);
        charCount += 1;
    }

    return charCount;
}

std::string particionaString(const std::string &s, unsigned int inicio, unsigned int fim){
    //int inicio => numero do "indice" do caractere de inicio da nova string (incluso)
    //int inicio => numero do "indice" caractere que encerra a nova string (não-incluso)
    string novastr = "";

    unsigned int charCount = 0;
    unsigned int strLen = s.length();
    unsigned int u = 0, previous_u = u;
    const char *c_str = s.c_str();

    //faz u chegar no inicio da particao da string
    while(charCount < inicio)
    {
        u += mblen(&c_str[u], strLen - u);
        previous_u = u;
        charCount++;
    }
    //vai de onde u parou até o fim
    while(charCount < fim)
    {
        u += mblen(&c_str[u], strLen - u);
        for(int i = previous_u; i < u; i++){
            novastr += s[i];
        }
        previous_u = u;
        //cout << charCount << " nova_str: " << novastr << endl;
        charCount++;
    }


    //cout << "String atualmente :" << novastr.c_str() <<"fim"<<endl;
    return novastr;
}
*/

/*
void loadFromFile(std::ifstream &fsprt){
    if (!fsprt.is_open())
	{	
		std::cout << "Erro ao ler arquivo..." << std::endl;
		return;
	}
	
	int largura = 0, tam = 0, altura = 0;
	std::string tmp;
	
	while(getline(fsprt,tmp))
	{
		cout << (tmp) << endl;
		tam = contaCaracteres(tmp);
		if (tam > largura)
			largura = tam;
		
	}
	
}
*/

/* TESTE PARTICIONAR STRING UTF-8
    setlocale(LC_ALL, "en_US.utf8");
    string ex("████████████████████████████████████████████████████████████████████ḅḐ                          ḋḐ██████████████████████████████████████████████████████████████");
    string ex2("VASMOS TESTAR");

    int c = 75;
    int cont2 = contaCaracteres(ex2);
    
    string resultado = particionaString(ex, 0, c)+ex2+particionaString(ex, (c+cont2), contaCaracteres(ex));
    cout <<"resultado:" << resultado << "fim" <<endl;

*/

int main(void){
    
   MiniGame::run();

    return 0;
}