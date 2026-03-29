#include "exemplo_2_menu.h"

#include <stdio.h>

#include "../../ui/ui_console.h"
#include "../../ui/ui_theme.h"

void exemplo_2_menu_show(void) {
    ui_clear_screen();

    ui_print_primary("=== MÓDULO EXEMPLO 2 ===\n");
    ui_print_success("Módulo em desenvolvimento.\n");

    printf("\nPressione ENTER para voltar...");
    fflush(stdout);
    getchar();

    ui_clear_screen();
}