#include "main_menu.h"

#include "../../shared/navigation.h"
#include "../../ui/ui_menu.h"
#include "../usuarios/usuarios_menu.h"
#include "../exemplo_2/exemplo_2_menu.h"

int main_menu_show(MYSQL *conn) {
    const char *options[] = {
        "Usuários",
        "Exemplo 2",
        "Fechar"
    };

    while (1) {
        int escolha = ui_menu_select("VIVA SEGURA — SYSTEM", options, 3);

        if (escolha == NAV_BACK) {
            continue;
        }

        switch (escolha) {
            case 0:
                usuarios_menu_show(conn);
                break;
            case 1:
                exemplo_2_menu_show();
                break;
            case 2:
                return 0;
        }
    }
}