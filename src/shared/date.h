#ifndef DATE_H
#define DATE_H

#include <stdio.h>
#include <string.h>
#include "io.h"

static inline int converter_data_para_mysql(
    const char *origem,
    char *destino,
    size_t tamanho_destino
) {
    int dia, mes, ano;

    if (sscanf(origem, "%2d-%2d-%4d", &dia, &mes, &ano) != 3) {
        return 0;
    }

    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900 || ano > 2100) {
        return 0;
    }

    snprintf(destino, tamanho_destino, "%04d-%02d-%02d", ano, mes, dia);
    return 1;
}

static inline int converter_data_para_exibicao(
    const char *origem,
    char *destino,
    size_t tamanho_destino
) {
    int ano, mes, dia;

    if (sscanf(origem, "%4d-%2d-%2d", &ano, &mes, &dia) != 3) {
        return 0;
    }

    snprintf(destino, tamanho_destino, "%02d-%02d-%04d", dia, mes, ano);
    return 1;
}

static inline int ler_data_usuario(
    const char *mensagem,
    char *destino_mysql,
    size_t tamanho_destino
) {
    char entrada[16];

    while (1) {
        if (ler_linha_obrigatoria(mensagem, entrada, sizeof(entrada)) == NAV_BACK) {
            return NAV_BACK;
        }

        if (converter_data_para_mysql(entrada, destino_mysql, tamanho_destino)) {
            return 0;
        }

        printf("Data inválida. Use o formato dd-mm-aaaa.\n");
    }
}

#endif