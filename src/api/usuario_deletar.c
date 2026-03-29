#include <mysql/mysql.h>
#include <stdio.h>

int api_deletar_usuario(MYSQL *conn, int id, int *linhas_afetadas) {
    char query[256];

    if (linhas_afetadas != NULL) {
        *linhas_afetadas = 0;
    }

    snprintf(query, sizeof(query), "DELETE FROM usuario WHERE id = %d", id);

    if (mysql_query(conn, query) != 0) {
        return 0;
    }

    if (linhas_afetadas != NULL) {
        *linhas_afetadas = (int) mysql_affected_rows(conn);
    }

    return 1;
}