#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

#include "../shared/usuario.h"

int api_buscar_usuario_por_id(MYSQL *conn, int id, Usuario *u) {
    char query[512];

    snprintf(
        query,
        sizeof(query),
        "SELECT nome, cpf, data_nascimento, email, telefone, endereco, "
        "tipo_sanguineo, alergias, nome_contato_emergencia, telefone_contato_emergencia "
        "FROM usuario WHERE id = %d",
        id
    );

    if (mysql_query(conn, query) != 0) {
        return -1;
    }

    MYSQL_RES *resultado = mysql_store_result(conn);
    if (resultado == NULL) {
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(resultado);

    if (row == NULL) {
        mysql_free_result(resultado);
        return 0;
    }

    memset(u, 0, sizeof(*u));

    snprintf(u->nome, sizeof(u->nome), "%s", row[0] ? row[0] : "");
    snprintf(u->cpf, sizeof(u->cpf), "%s", row[1] ? row[1] : "");
    snprintf(u->data_nascimento, sizeof(u->data_nascimento), "%s", row[2] ? row[2] : "");
    snprintf(u->email, sizeof(u->email), "%s", row[3] ? row[3] : "");
    snprintf(u->telefone, sizeof(u->telefone), "%s", row[4] ? row[4] : "");
    snprintf(u->endereco, sizeof(u->endereco), "%s", row[5] ? row[5] : "");
    snprintf(u->tipo_sanguineo, sizeof(u->tipo_sanguineo), "%s", row[6] ? row[6] : "");
    snprintf(u->alergias, sizeof(u->alergias), "%s", row[7] ? row[7] : "");
    snprintf(
        u->nome_contato_emergencia,
        sizeof(u->nome_contato_emergencia),
        "%s",
        row[8] ? row[8] : ""
    );
    snprintf(
        u->telefone_contato_emergencia,
        sizeof(u->telefone_contato_emergencia),
        "%s",
        row[9] ? row[9] : ""
    );

    mysql_free_result(resultado);
    return 1;
}