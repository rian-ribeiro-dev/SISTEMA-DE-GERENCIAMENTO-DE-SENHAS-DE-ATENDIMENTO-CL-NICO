#ifndef OPERACOES_H
#define OPERACOES_H

#define MAX 100

typedef struct {
    char codigo[6];
    int categoria;
} Senha;

void cadastrarPaciente(void);
void gerarSenha(int categoria);
int classificar(char genero, int idade, int gestante, int lactante, int especial, int obeso);
void consultarProxima(void);
void chamarPaciente(void);
void mostrarAtendimento(void);
void finalizarAtendimento(void);
void mostrarPainel(void);

#endif
