#include <iostream>
#include <cstring>

#include <unistd.h>
#include <string.h>

#include "cores.hpp"

#define clean() printf("\033[H\033[J")
#define MAX_STRING 512

/*Inicia o terminal com uma mensagem de boas vindas*/
void IniciarTerminal(){
    clean();
    std::cout << BIRED "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl << std::endl;
    std::cout << "Olá, seja bem vindo ao Terminal Prototype!" << std::endl;
    std::cout << "      Use por sua conta e risco :D" << std::endl << std::endl;
    std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" COLOR_RESET << std::endl << std::endl;
    sleep(0.5);
    //clean();
}

/*Imprime o diretorio no terminal*/
void ImprimirDir(std::string user)
{
    char cwd[MAX_STRING];
    
    getcwd(cwd, sizeof(cwd));
    std::cout << BIGREEN << user << "@Terminal-Prototype" COLOR_RESET ":";
    std::cout << BIBLUE << cwd << COLOR_RESET;
    std::cout << "$ ";
}

void ListaDeComandos(){
    printf("Lista de comandos:\nexit \nhelp \ncd \nclean \n");
}

void ExecutarComando(std::string cmd){
    int numeroDeComandos = 4, varSwitch = -1;
    std::string *listaDeComandos = new std::string[numeroDeComandos];

    listaDeComandos[0] = "exit";
    listaDeComandos[1] = "help";
    listaDeComandos[2] = "cd";
    listaDeComandos[3] = "clean";

    for(int i = 0; i < numeroDeComandos; i++){
        if(listaDeComandos[i].compare(cmd) == 0){
            varSwitch = i + 1;
            break;
        }
    }

    switch (varSwitch)
    {
    case 1:
        std::cout << "Até logo!" << std::endl;
        exit(0);
    case 2:
        ListaDeComandos();
        break;
    case 3:
        std::cout << "Não implementado ainda!" << std::endl;
        break;
    case 4:
        clean();
        break;

    default:
        std::cout << URED << "COMANDO INVALIDO!" << COLOR_RESET << std::endl;
        break;
    }    
}

int isBlank(std::string str) {
    const char * cstr = str.c_str();
    
    for(int i = 0; i < str.length(); i++) {
        if (cstr[i] != ' ')
           return 0;
    }
    return 1;
}

int main(){

    std::string entrada, cmd = "sair";
    std::string username = getenv("USER"); 

    IniciarTerminal();

    while (1)
    {
        ImprimirDir(username);
        getline(std::cin, entrada);

        if(entrada.empty() || isBlank(entrada)){        //ficou inutil com string 
            continue;
        }

        ExecutarComando(entrada);

    }
    
    return 0;
}