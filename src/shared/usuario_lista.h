#ifndef USUARIO_LISTA_H
#define USUARIO_LISTA_H

#include "usuario.h"

#define USUARIO_LISTA_MAX 100

typedef struct {
    Usuario itens[USUARIO_LISTA_MAX];
    int ids[USUARIO_LISTA_MAX];
    int total;
} UsuarioLista;

#endif