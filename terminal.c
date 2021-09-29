#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define clear() printf("\033[H\033[J")

#define ANSI_VERDE_CLARO "\033[1;92m"
#define ANSI_AZUL_CLARO "\033[1;94m"
#define ANSI_RESET "\033[0;0m"
#define ANSI_VERMELHO_CLARO "\033[1;91m"

#define MAX_STRING 500

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


int main(){

    char strDeEntrada[MAX_STRING], cmd[] = "sair";
    char *username;
    username = getenv("USER"); 

    IniciarTerminal();

    while (1)
    {
        ImprimirDir(username);
        scanf("%s", strDeEntrada);

        if(strcmp(strDeEntrada, cmd) == 0)
            exit(0);

    }
    
    return 0;
}