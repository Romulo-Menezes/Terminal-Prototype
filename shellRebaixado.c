/* Comandos para compilar e executar gcc shell.c -lreadline     ./a.out */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAXCOM 1000 /* Número máximo de letras suportadas */
#define MAXLIST 100 /* Número máximo de comandos a serem suportados */
#define MAXSIZE 1024 
#define clear() printf("\033[H\033[J")

void init_shell(){
    
    clear();
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\n\n\t      BOM DIA      ");
    printf("\n\n\t     BOA TARDE");
    printf("\n\n\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

    char *usuario = getenv("USER");

    printf("\n\nUsuario: %s \n\n", usuario);
}

/* Pegar entrada */
int pegarEntrada (char* entrada){

    char *linha;

    linha = readline("\n>>> "); /* Imprime um prompt e, em seguida, lê e retorna uma única linha de texto do usuário */

    /* Se o usuário escreveu alguma coisa eu salvo a linha, copio para a entrada e retorno */
    if (strlen(linha) > 0)
    {
        add_history(linha); /* Salva a linha que o usuário digitou em uma lista de histórico, assim elas poderão ser reutilizadas futuramente */
        strcpy(entrada, linha);
        return 0;
    }

    return 1;
}

/* Seção de ajuda */
void mostrarAjuda(){
    
    puts("\nLista de Comandos suportados:"
        "\n-> cd"
        "\n-> ls"
        "\n-> exit"
        "\n-> todos outros comandos gerais disponíveis no UNIX shell \n");
}

/* Mostrar diretório atual */
void motrarDiretorio() {

    char diretorioAtual[MAXSIZE];                   
    getcwd(diretorioAtual, sizeof(diretorioAtual)); /* Pega o nome do caminho do diretório de trabalho atual */
    printf("\nDiretorio Atual: %s", diretorioAtual);
}

/* Executando comandos */
void executarComandos(char **listaDePalavras){

    /* Criando um filho para eu poder executar um comando (que é um programa) enquanto continuo a rodar esse processo */
    pid_t pid = fork();

    if (pid == -1)
    {
        printf("\nFalha na criação de um processo filho.");
        exit(1);
    }

    /* Executando os programas de fora do shell */
    else if (pid == 0)
    {
        /*  O primeiro argumento é o arquivo que você deseja executar (é rapaz, os comandos são programas externos), e o segundo
        *   argumento é uma matriz de strings terminadas em nulo que representam os argumentos apropriados para o arquivo.
        */
        if (execvp(listaDePalavras[0], listaDePalavras) < 0)
            printf("\nXiii, consigo executar esse comando ai não...\n");

        exit(0);
    }

    /* Esperando a execução do programa terminar */
    else
    {
        /* Esperando o processo do filho terminar */
        wait(NULL);
        return;
    }
}

/*  strsep() leva dois argumentos - O primeiro argumento é usado para passar o endereço da cadeia de caracteres que precisa ser pesquisada. 
*   O segundo parâmetro especifica um conjunto de caracteres delimitadores, que marcam o início e o fim dos tokens extraídos. 
*   Quando o primeiro token é encontrado, o primeiro argumento é modificado para armazenar o ponteiro para o próximo delimitador encontrado.
*
*   OBS.: Observe que os caracteres delimitadores são descartados nas strings de token extraídas. 
*
*   Exemplo: se eu tenho aaa --bbb-ccc e meu delimitador é " -" quando eu usar token = strsep(&string, " -"), o que estará dentro do token é 
*   "aaa" e o que sobrará na string é "bbb-ccc".
*/

/* Separando as palavras usando como delimitador o espaço */
void separarPalavras(char *entrada, char **listaDePalavras){

    for (int i = 0; i < MAXLIST; i++)
    {
        listaDePalavras[i] = strsep(&entrada, " "); /* Guardando no vetor de char cada palavra que for achada */

        if (listaDePalavras[i] == NULL) /* Se parou de achar palavras para o loop */
            break;

        if (strlen(listaDePalavras[i]) == 0) /* Se o tamanho da minha palavra na minha posição atual for 0 eu volto uma posição antes de continuar o processo */
            i--;
    }
}

/* Executar comandos internos do sistema, que fazem parte do próprio shell */
int comandosEmbutidos(char** comando){

    int numeroDeComandos = 3, varSwitch = 0;
    char *listaDeComandos[numeroDeComandos];
    char *username;

    listaDeComandos[0] = "exit";
    listaDeComandos[1] = "cd";
    listaDeComandos[2] = "help";

    for (int i = 0; i < numeroDeComandos; i++)
    {
        /* Checando se o comando dado é igual ao comando da posição atual da lista */
        if (strcmp(comando[0], listaDeComandos[i]) == 0)
        {
            varSwitch = i + 1; /* Se o comando for diferente eu aumento um no incrementador, indo assim para meu próximo comando da lista */
            break;
        }
    }

    switch (varSwitch)
    {
        case 1:
            printf("\nAdeus meu bom amigo!\n");
        exit(0);

        case 2:
            chdir(comando[1]); /* Muda o diretório atual para o diretório salvo na posição 1 do vetor de palavras */
        return 1;

        case 3:
            mostrarAjuda();
        return 1;

    default:
            break;
    }

    return 0;
}

/* Analisa a entrada e chama as funções que precisam ser chamadas*/
int analisarEntrada(char *entrada, char **listaDePalavras){

    /* Pega a linha inteira e tranforma em uma lista com as palavras */
    separarPalavras(entrada, listaDePalavras);

    /* Se o meu comando dado for algum comando interno eu executo o comando interno pela outra função e retorno para a main */
    if (comandosEmbutidos(listaDePalavras))
        return 0;

    return 1;
}

int main(){

    char entrada[MAXCOM], *listaDePalavras[MAXLIST];
    int execFlag = 0;
    
    init_shell();

    while (1)
    {
        /* Mostrando diretório */
        motrarDiretorio();

        /* Pega a entrada do usuário */
        if (pegarEntrada(entrada))
            continue;

        /* Analisa a entrada para descobrir se é um comando embutido ou uma chamada de outro programa, se for um comando embutido 
         * ele vai executar o comando e retornar 0. Se for um comando simples ele irá retornar 1 */
        execFlag = analisarEntrada(entrada, listaDePalavras);

        /* Executa os comandos simples (programa externo) que não contenham a " | " */
        if (execFlag == 1)
            executarComandos(listaDePalavras);
    }

    return 0;
}
