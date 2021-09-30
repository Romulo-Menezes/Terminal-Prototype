#include <iostream>

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define clean() printf("\033[H\033[J")

#define VERDE_CLARO "\033[1;92m"
#define AZUL_CLARO "\033[1;94m"
#define RESET "\033[0;0m"
#define VERMELHO_CLARO "\033[1;91m"

#define MAX_STRING 256

/*Inicia o terminal com uma mensagem de boas vindas*/
void IniciarTerminal(){
    clean();
    printf( VERMELHO_CLARO "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    printf("Olá, seja bem vindo ao Terminal Prototype!\n");
    printf("      Use por sua conta e risco :D\n\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n" RESET );
    sleep(2);
    //clean();
}

/*Imprime o diretorio no terminal*/
void ImprimirDir(char *user)
{
    char cwd[MAX_STRING];
    
    getcwd(cwd, sizeof(cwd));
    printf( VERDE_CLARO "%s:"RESET, user);
    printf( AZUL_CLARO "%s" RESET, cwd );
    printf("$ ");
}

void ListaDeComandos(){
    printf("Lista de comandos:\nexit \nhelp \ncd \nclean \n");
}

void ExecutarComando(char *cmd){
    int numeroDeComandos = 4, varSwitch = -1;
    char *listaDeComandos[numeroDeComandos];

    listaDeComandos[0] = "exit";
    listaDeComandos[1] = "help";
    listaDeComandos[2] = "cd";
    listaDeComandos[3] = "clean";

    for(int i = 0; i < numeroDeComandos; i++){
        if(strcmp(cmd, listaDeComandos[i]) == 0){
            varSwitch = i + 1;
            break;
        }
    }

    switch (varSwitch)
    {
    case 1:
        printf("Até logo!\n");
        exit(0);
    case 2:
        ListaDeComandos();
        break;
    case 3:
        printf("Não implementado ainda!\n");
        break;
    case 4:
        clean();
        break;

    default:
        printf(VERMELHO_CLARO "COMANDO INVALIDO!\n" RESET);
        break;
    }

    
}

int main(){

    char strDeEntrada[MAX_STRING], cmd[] = "sair";
    char *username;
    username = getenv("USER"); 

    IniciarTerminal();

    while (1)
    {
        ImprimirDir(username);
        std::cin.getline(strDeEntrada, MAX_STRING);

        if(strlen(strDeEntrada) == 0){
            continue;
        }

        ExecutarComando(strDeEntrada);            

    }
    
    return 0;
}