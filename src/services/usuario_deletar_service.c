#include <mysql/mysql.h>
#include <stdio.h>

#include "../shared/io.h"
#include "../ui/ui_theme.h"

int api_deletar_usuario(MYSQL *conn, int id, int *linhas_afetadas);

void deletar_usuario_service(MYSQL *conn) {
    int id;
    int linhas_afetadas = 0;

    ui_print_primary("\n=== REMOVER USUÁRIO ===\n");

    printf("Digite o ID para remover: ");
    scanf("%d", &id);
    limpar_buffer();

    if (!api_deletar_usuario(conn, id, &linhas_afetadas)) {
        ui_print_error("Falha ao remover usuário.\n");
        return;
    }

    if (linhas_afetadas == 0) {
        ui_print_warning("Nenhum registro removido. Verifique se o ID existe.\n");
        return;
    }

    ui_print_success("Usuário removido com sucesso.\n");
}