#include <iostream>

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define clear() printf("\033[H\033[J")

#define ANSI_VERDE_CLARO "\033[1;92m"
#define ANSI_AZUL_CLARO "\033[1;94m"
#define ANSI_RESET "\033[0;0m"
#define ANSI_VERMELHO_CLARO "\033[1;91m"

#define MAX_STRING 256

/*Inicia o terminal com uma mensagem de boas vindas*/
void IniciarTerminal(){
    clear();
    printf( ANSI_VERMELHO_CLARO "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    printf("Olá, seja bem vindo ao Terminal Prototype!\n");
    printf("      Use por sua conta e risco :D\n\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n" ANSI_RESET );
    sleep(2);
    clear();
}

/*Imprime o diretorio no terminal*/
void ImprimirDir(char *user)
{
    char cwd[MAX_STRING];
    
    getcwd(cwd, sizeof(cwd));
    printf( ANSI_VERDE_CLARO "%s:" ANSI_RESET, user);
    printf( ANSI_AZUL_CLARO "%s" ANSI_RESET, cwd );
    printf("$ ");
}

void ListaDeComandos(){
    printf("Lista de comandos:\nexit \nhelp \ncd \n");
}

void ExecutarComando(char *cmd){
    int numeroDeComandos = 3, varSwitch = -1;
    char *listaDeComandos[numeroDeComandos];

    listaDeComandos[0] = "exit";
    listaDeComandos[1] = "help";
    listaDeComandos[2] = "cd";

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

    default:
        printf(ANSI_VERMELHO_CLARO "COMANDO INVALIDO!\n" ANSI_RESET);
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