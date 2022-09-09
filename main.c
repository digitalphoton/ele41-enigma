#include <stdio.h>
#include <stdlib.h>

// Structs --------------------------------------------------------------

typedef struct contato{

    int ida;
    int volta;
    struct contato * proximo;
}Contato;

typedef struct rotor{

    int offset;
    Contato * entrada;
    Contato * saida;
}Rotor;

typedef enum fases{
    IDA,    // 0
    VOLTA   // 1
}Fases;

// Funções --------------------------------------------------------------

// retorna um ponteiro pra um rotor vazio, sem offset

Rotor * iniciaRotor(){

    Rotor * novo = (Rotor*)malloc(sizeof(Rotor));
    novo -> offset = 0;
    novo -> entrada = NULL;
    novo -> saida = NULL;

    return novo;
}

int adiciona_contato(Rotor * rotor, int indice_ida, int indice_volta){

    int resultado = 0;

    Contato * novo = (Contato*)malloc(sizeof(Contato));
    novo -> ida = indice_ida;
    novo -> volta = indice_volta;
    novo -> proximo = NULL;

    if(rotor -> entrada == NULL){

        rotor -> entrada = novo;
        rotor -> saida = novo;
        novo -> proximo = NULL;
    }
    else{

        rotor -> saida -> proximo = novo;
        rotor -> saida = novo;
        novo -> proximo = NULL;
    }

    return resultado;
}

// dado um índice (input) e uma fase, retorna um índice de output, que será usado no próximo rotor
int processa(Rotor * rotor, Fases fase, int input){

    int output;
    int cont = 0;

    Contato * aux = rotor -> entrada;
    while(cont != input){
        aux = aux -> proximo;
        cont++;
    }

    if(fase == IDA){
        output = aux -> ida;
    }
    else{
        output = aux -> volta;
    }
    return output;
}

// ----------------------------------------------------------------------------

int main(){

    //------------------------------------
    Rotor * rotor1 = iniciaRotor();

    adiciona_contato(rotor1, 1, 1);
    adiciona_contato(rotor1, 0, 0);
    adiciona_contato(rotor1, 2, 2);
    adiciona_contato(rotor1, 3, 3);
    //------------------------------------
    Rotor * rotor2 = iniciaRotor();

    adiciona_contato(rotor2, 2, 3);
    adiciona_contato(rotor2, 1, 1);
    adiciona_contato(rotor2, 3, 0);
    adiciona_contato(rotor2, 0, 2);
    //------------------------------------

    Rotor * espelho = iniciaRotor();

    adiciona_contato(espelho, 3, 0);
    adiciona_contato(espelho, 2, 1);
    adiciona_contato(espelho, 1, 2);
    adiciona_contato(espelho, 0, 3);
    //------------------------------------

    int resultado = processa(rotor1, IDA, 1);
    resultado = processa(rotor2, IDA, resultado);
    resultado = processa(espelho, IDA, resultado);

    resultado = processa(espelho, VOLTA, resultado);
    resultado = processa(rotor2, VOLTA, resultado);
    resultado = processa(rotor1, VOLTA, resultado);

    return 0;
}
