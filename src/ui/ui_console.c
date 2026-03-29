#include "ui_console.h"
#include "ui_theme.h"
#include "../conf/app_config.h"
#include <stdio.h>

void ui_clear_screen(void) {
    printf("\033[2J\033[H");
}

void ui_render_header(void) {
    const AppConfig *config = app_config_get();

    ui_print_primary("\n=====================================\n");
    printf("         %s\n", config->app_name);
    ui_print_primary("=====================================\n");
}

void ui_render_menu(void) {
    ui_render_header();
    printf("[1] Cadastrar usuário\n");
    printf("[2] Listar usuários\n");
    printf("[3] Buscar usuário por ID\n");
    printf("[4] Atualizar usuário\n");
    printf("[5] Remover usuário\n");
    printf("[0] Sair\n");
    ui_print_primary("=====================================\n");
    printf("Escolha uma opção: ");
}