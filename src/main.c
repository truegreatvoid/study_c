#include <mysql/mysql.h>
#include <stdio.h>

#include "conf/platform.h"
#include "conf/app_config.h"
#include "db/db.h"
#include "services/usuario_services.h"
#include "ui/ui_menu.h"
#include "ui/ui_console.h"
#include "shared/navigation.h"

int main(void) {
    setup_platform();
    app_config_init("src/.env");

    MYSQL *conn = conectar_db();
    if (conn == NULL) {
        return 1;
    }

    const char *options[] = {
        "Cadastrar usuário",
        "Listar usuários",
        "Buscar usuário por ID",
        "Atualizar usuário",
        "Remover usuário",
        "Fechar"
    };

    while (1) {
        int escolha = ui_menu_select("VIVA SEGURA — SYSTEM", options, 6);

        if (escolha == NAV_BACK) {
            continue;
        }

        switch (escolha) {
            case 0:
                cadastrar_usuario_service(conn);
                break;
            case 1:
                listar_usuarios_service(conn);
                break;
            case 2:
                buscar_usuario_por_id_service(conn);
                break;
            case 3:
                atualizar_usuario_service(conn);
                break;
            case 4:
                deletar_usuario_service(conn);
                break;
            case 5:
                ui_clear_screen();
                fechar_db(conn);
                return 0;
        }

        printf("\nPressione ENTER para continuar...");
        fflush(stdout);
        getchar();
        ui_clear_screen();
    }
}