#include <iostream>
#include <cstring>
#include <map>
#include <functional>

#include <unistd.h>
#include <string.h>

#include "cores.hpp"
#define MAX_STRING 512

using namespace std;

void iniciarTerminal();

void ImprimirDir(string);

void executarComando(string);

int isBlank(string);

int listarComandos(char** args);

int exitTerminal(char**);

int mudarDiretorio(char **);

int limparTerminal(char **);

void inicializarComandos();

map<string, function<int(char **)>> comandos;

int main() {
    string entrada, cmd = "exiterminal";
    string username = getenv("USER");

    inicializarComandos();
    iniciarTerminal();

    while (1) {
        ImprimirDir(username);
        getline(cin, entrada);

        if(entrada.empty() || isBlank(entrada)){        //ficou inutil com string 
            continue;
        }
        executarComando(entrada);
    }
    
    return 0;
}

/*Inicia o terminal com uma mensagem de boas vindas*/
void iniciarTerminal(){
    limparTerminal(NULL);
    cout << BIRED "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
    cout << "Olá, seja bem vindo ao Terminal Prototype!" << endl;
    cout << "      Use por sua conta e risco :D" << endl << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" COLOR_RESET << endl << endl;
    sleep(0.5);
    //limparTerminal();
}

/*Imprime o diretorio no terminal*/
void ImprimirDir(string user) {
    char cwd[MAX_STRING];
    
    getcwd(cwd, sizeof(cwd));
    cout << BIGREEN << user << "@Terminal-Prototype" COLOR_RESET ":";
    cout << BIBLUE << cwd << COLOR_RESET;
    cout << "$ ";
}

int listarComandos(char** args) {
    printf("Lista de comandos:\nexit \nhelp \ncd \nlimparTerminal \n");
    return 0;
}

void executarComando(string cmd) {
    if (comandos.find(cmd) != comandos.end()) {
        comandos.at(cmd)(nullptr);
    } else {
        cout << URED << "COMANDO INVALIDO!" << COLOR_RESET << endl;
    }
}

int exitTerminal(char** args) {
    cout << "Até logo!" << endl;
    exit(0);
}


int isBlank(string str) {
    const char * cstr = str.c_str();
    
    for(int i = 0; i < str.length(); i++) {
        if (cstr[i] != ' ')
           return 0;
    }
    return 1;
}

int limparTerminal(char **) {
    printf("\033[H\033[J");
    return 0;
}

int mudarDiretorio(char **) {
    cout << "Não implementado ainda!" << endl;
    return 0;
}

void inicializarComandos() {
    comandos.insert(pair<string, function<int(char **)>>("exit", &exitTerminal));
    comandos.insert(pair<string, function<int(char **)>>("help", &listarComandos));
    comandos.insert(pair<string, function<int(char **)>>("cd", &mudarDiretorio));
    comandos.insert(pair<string, function<int(char **)>>("clean", &limparTerminal));
}
