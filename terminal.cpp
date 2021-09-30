#include <iostream>
#include <cstring>
#include <unistd.h>

#define clean() printf("\033[H\033[J")

#define VERDE_CLARO "\033[1;92m"
#define AZUL_CLARO "\033[1;94m"
#define RESET "\033[0;0m"
#define VERMELHO_CLARO "\033[1;91m"

#define MAX_STRING 256

/*Inicia o terminal com uma mensagem de boas vindas*/
void IniciarTerminal(){
    clean();
    std::cout << VERMELHO_CLARO << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl << std::endl;
    std::cout << "Olá, seja bem vindo ao Terminal Prototype!" << std::endl;
    std::cout << "      Use por sua conta e risco :D" << std::endl << std::endl;
    std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << RESET << std::endl << std::endl;
    sleep(0.5);
    //clean();
}

/*Imprime o diretorio no terminal*/
void ImprimirDir(std::string user)
{
    char cwd[MAX_STRING];
    
    getcwd(cwd, sizeof(cwd));
    std::cout << VERDE_CLARO << user << ":" << RESET;
    std::cout << AZUL_CLARO << cwd << RESET;
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
        std::cout << VERMELHO_CLARO << "COMANDO INVALIDO!" << RESET << std::endl;
        break;
    }    
}

int main(){

    std::string entrada, cmd = "sair";
    std::string username = getenv("USER"); 

    IniciarTerminal();

    while (1)
    {
        ImprimirDir(username);
        std::cin >> entrada;

        if(entrada.length() == 0){
            continue;
        }

        ExecutarComando(entrada);

    }
    
    return 0;
}