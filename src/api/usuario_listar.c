#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

#include "../shared/usuario_lista.h"

int api_listar_usuarios(MYSQL *conn, UsuarioLista *lista) {
    const char *query =
        "SELECT id, nome, cpf, data_nascimento, email, telefone, endereco, "
        "tipo_sanguineo, alergias, nome_contato_emergencia, telefone_contato_emergencia "
        "FROM usuario ORDER BY id DESC";

    if (lista == NULL) {
        return 0;
    }

    lista->total = 0;

    if (mysql_query(conn, query) != 0) {
        return 0;
    }

    MYSQL_RES *resultado = mysql_store_result(conn);
    if (resultado == NULL) {
        return 0;
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(resultado)) != NULL) {
        if (lista->total >= USUARIO_LISTA_MAX) {
            break;
        }

        int i = lista->total;
        lista->ids[i] = row[0] ? atoi(row[0]) : 0;

        memset(&lista->itens[i], 0, sizeof(lista->itens[i]));

        snprintf(lista->itens[i].nome, sizeof(lista->itens[i].nome), "%s", row[1] ? row[1] : "");
        snprintf(lista->itens[i].cpf, sizeof(lista->itens[i].cpf), "%s", row[2] ? row[2] : "");
        snprintf(
            lista->itens[i].data_nascimento,
            sizeof(lista->itens[i].data_nascimento),
            "%s",
            row[3] ? row[3] : ""
        );
        snprintf(lista->itens[i].email, sizeof(lista->itens[i].email), "%s", row[4] ? row[4] : "");
        snprintf(lista->itens[i].telefone, sizeof(lista->itens[i].telefone), "%s", row[5] ? row[5] : "");
        snprintf(lista->itens[i].endereco, sizeof(lista->itens[i].endereco), "%s", row[6] ? row[6] : "");
        snprintf(
            lista->itens[i].tipo_sanguineo,
            sizeof(lista->itens[i].tipo_sanguineo),
            "%s",
            row[7] ? row[7] : ""
        );
        snprintf(lista->itens[i].alergias, sizeof(lista->itens[i].alergias), "%s", row[8] ? row[8] : "");
        snprintf(
            lista->itens[i].nome_contato_emergencia,
            sizeof(lista->itens[i].nome_contato_emergencia),
            "%s",
            row[9] ? row[9] : ""
        );
        snprintf(
            lista->itens[i].telefone_contato_emergencia,
            sizeof(lista->itens[i].telefone_contato_emergencia),
            "%s",
            row[10] ? row[10] : ""
        );

        lista->total++;
    }

    mysql_free_result(resultado);
    return 1;
}