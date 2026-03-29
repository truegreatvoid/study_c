#include <mysql/mysql.h>
#include <stdio.h>

#include "../shared/usuario.h"

int api_atualizar_usuario(MYSQL *conn, int id, const Usuario *u) {
    char query[2048];

    snprintf(
        query,
        sizeof(query),
        "UPDATE usuario SET "
        "nome='%s', "
        "cpf='%s', "
        "data_nascimento='%s', "
        "email='%s', "
        "telefone='%s', "
        "endereco='%s', "
        "tipo_sanguineo='%s', "
        "alergias='%s', "
        "nome_contato_emergencia='%s', "
        "telefone_contato_emergencia='%s' "
        "WHERE id=%d",
        u->nome,
        u->cpf,
        u->data_nascimento,
        u->email,
        u->telefone,
        u->endereco,
        u->tipo_sanguineo,
        u->alergias,
        u->nome_contato_emergencia,
        u->telefone_contato_emergencia,
        id
    );

    if (mysql_query(conn, query) != 0) {
        return 0;
    }

    return 1;
}