#include <mysql/mysql.h>

#include "../shared/usuario_lista.h"
#include "../ui/ui_table.h"
#include "../ui/ui_theme.h"

int api_listar_usuarios(MYSQL *conn, UsuarioLista *lista);

void listar_usuarios_service(MYSQL *conn) {
    UsuarioLista lista = {0};

    ui_print_primary("\n=== LISTAGEM DE USUÁRIOS ===\n");

    if (!api_listar_usuarios(conn, &lista)) {
        ui_print_error("Falha ao listar usuários.\n");
        return;
    }

    if (lista.total == 0) {
        ui_print_warning("Nenhum usuário cadastrado.\n");
        return;
    }

    ui_render_usuario_table(&lista);
}