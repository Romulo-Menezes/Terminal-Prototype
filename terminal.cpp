#include <iostream>
#include <sstream>
#include <cstring>
#include <map>
#include <functional>
#include <vector>

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "cores.hpp"
#define MAX_STRING 512

using namespace std;

void iniciarTerminal();

void ImprimirDir(string);

bool executarComandoEmbutido(string);

int isBlank(string);

int listarComandos(char** args);

int exitTerminal(char**);

int mudarDiretorio(char **);

int limparTerminal(char **);

void inicializarComandos();

map<string, function<int(char **)>> comandos;

void executarComandoDoSistema(string, char **);

void executarComando(string);

vector<string> split(const string&, const string&) ;

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
    cout << "Lista de comandos:" << endl;
    for(map<string, function<int(char **)>>::iterator entry = comandos.begin(); entry != comandos.end(); ++entry) {
        cout << entry->first << endl;
    }
    return 0;
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

void executarComando(string entrada) {
    if(!executarComandoEmbutido(entrada)) {
        vector<string> raw_text = split(entrada, " ");
        vector<char*> pointerVec(raw_text.size() + 1);
        for(unsigned i = 0; i < raw_text.size(); ++i) {
            pointerVec[i] = raw_text[i].data();
        }
        pointerVec[raw_text.size()] = NULL;
        char** args = pointerVec.data();
        executarComandoDoSistema(raw_text[0], args);
    }
}

bool executarComandoEmbutido(string cmd) {
    if (comandos.find(cmd) != comandos.end()) {
        comandos.at(cmd)(nullptr);
        return true;
    } else {
        // cout << URED << "COMANDO INVALIDO!" << COLOR_RESET << endl;
        return false;
    }
}

void executarComandoDoSistema(string comando, char ** argumentos){
    pid_t pid = fork();

    if (pid == -1) {
        printf("\nFalha na criação de um processo filho.");
        exit(1);
    } else if (pid == 0) {
        if (execvp(comando.c_str(), argumentos) < 0) {
            printf("\nXiii, consigo executar esse comando ai não...\n");
        }

        exit(0);
    } else {
        wait(NULL);
        return;
    }
}

vector<string> split(const string& str, const string& delim) {
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}