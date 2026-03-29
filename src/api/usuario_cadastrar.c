#include <mysql/mysql.h>
#include <stdio.h>

#include "../shared/usuario.h"

int api_cadastrar_usuario(MYSQL *conn, const Usuario *u) {
    char query[2048];

    snprintf(
        query,
        sizeof(query),
        "INSERT INTO usuario ("
        "nome, cpf, data_nascimento, email, telefone, endereco, "
        "tipo_sanguineo, alergias, nome_contato_emergencia, telefone_contato_emergencia"
        ") VALUES ("
        "'%s', '%s', '%s', '%s', '%s', '%s', "
        "'%s', '%s', '%s', '%s'"
        ")",
        u->nome,
        u->cpf,
        u->data_nascimento,
        u->email,
        u->telefone,
        u->endereco,
        u->tipo_sanguineo,
        u->alergias,
        u->nome_contato_emergencia,
        u->telefone_contato_emergencia
    );

    if (mysql_query(conn, query) != 0) {
        return 0;
    }

    return 1;
}