#include "db.h"
#include <stdio.h>
#include "../conf/app_config.h"

MYSQL *conectar_db(void) {
    MYSQL *conn = mysql_init(NULL);
    const AppConfig *config = app_config_get();

    if (conn == NULL) {
        fprintf(stderr, "Erro ao inicializar MySQL.\n");
        return NULL;
    }

    if (mysql_real_connect(
            conn,
            config->db_host,
            config->db_user,
            config->db_pass,
            config->db_name,
            config->db_port,
            NULL,
            0) == NULL) {
        fprintf(stderr, "Erro na conexao: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    mysql_set_character_set(conn, "utf8mb4");
    return conn;
}

void fechar_db(MYSQL *conn) {
    if (conn != NULL) {
        mysql_close(conn);
    }
}