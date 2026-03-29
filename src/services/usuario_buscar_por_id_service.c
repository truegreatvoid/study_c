#include <mysql/mysql.h>
#include <stdio.h>

#include "../shared/io.h"
#include "../shared/usuario.h"
#include "../ui/ui_table.h"
#include "../ui/ui_theme.h"

int api_buscar_usuario_por_id(MYSQL *conn, int id, Usuario *u);

void buscar_usuario_por_id_service(MYSQL *conn) {
    int id;
    int status;
    Usuario u = {0};

    ui_print_primary("\n=== BUSCAR USUÁRIO POR ID ===\n");

    printf("Digite o ID: ");
    scanf("%d", &id);
    limpar_buffer();

    status = api_buscar_usuario_por_id(conn, id, &u);

    if (status < 0) {
        ui_print_error("Falha ao buscar usuário.\n");
        return;
    }

    if (status == 0) {
        ui_print_warning("Nenhum usuário encontrado para o ID informado.\n");
        return;
    }

    ui_render_usuario_detalhe(id, &u);
}