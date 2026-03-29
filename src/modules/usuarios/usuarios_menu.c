#include "usuarios_menu.h"

#include <stdio.h>

#include "../../services/usuario_services.h"
#include "../../shared/navigation.h"
#include "../../ui/ui_console.h"
#include "../../ui/ui_menu.h"

void usuarios_menu_show(MYSQL *conn) {
    const char *options[] = {
        "Cadastrar usuário",
        "Listar usuários",
        "Buscar usuário por ID",
        "Atualizar usuário",
        "Remover usuário",
        "Voltar"
    };

    while (1) {
        int escolha = ui_menu_select("Módulo de Usuários", options, 6);

        if (escolha == NAV_BACK || escolha == 5) {
            return;
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
        }

        printf("\nPressione ENTER para continuar...");
        fflush(stdout);
        getchar();
        ui_clear_screen();
    }
}