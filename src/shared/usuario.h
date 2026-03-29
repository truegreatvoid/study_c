#ifndef USUARIO_H
#define USUARIO_H

typedef struct {
    char nome[100];
    char cpf[12];
    char data_nascimento[11];
    char email[100];
    char telefone[21];
    char endereco[151];
    char tipo_sanguineo[11];
    char alergias[256];
    char nome_contato_emergencia[100];
    char telefone_contato_emergencia[21];
} Usuario;

#endif