#include <mysql/mysql.h>

#include "../shared/date.h"
#include "../shared/io.h"
#include "../shared/navigation.h"
#include "../shared/usuario.h"
#include "../ui/ui_loading.h"
#include "../ui/ui_theme.h"

int api_cadastrar_usuario(MYSQL *conn, const Usuario *u);

void cadastrar_usuario_service(MYSQL *conn) {
    Usuario u = {0};

    ui_print_primary("\n=== NOVO USUÁRIO ===\n");
    ui_print_warning("Pressione ESC para voltar.\n\n");

    if (ler_linha_obrigatoria("Nome: ", u.nome, sizeof(u.nome)) == NAV_BACK) {
        ui_print_warning("Cadastro cancelado.\n");
        return;
    }

    if (ler_linha_obrigatoria("CPF (somente números): ", u.cpf, sizeof(u.cpf)) == NAV_BACK) {
        ui_print_warning("Cadastro cancelado.\n");
        return;
    }

    if (ler_data_usuario(
            "Data de nascimento (dd-mm-aaaa): ",
            u.data_nascimento,
            sizeof(u.data_nascimento)
        ) == NAV_BACK) {
        ui_print_warning("Cadastro cancelado.\n");
        return;
    }

    if (ler_linha_obrigatoria("Email: ", u.email, sizeof(u.email)) == NAV_BACK) {
        ui_print_warning("Cadastro cancelado.\n");
        return;
    }

    if (ler_linha_obrigatoria("Telefone: ", u.telefone, sizeof(u.telefone)) == NAV_BACK) {
        ui_print_warning("Cadastro cancelado.\n");
        return;
    }

    if (ler_linha_obrigatoria("Endereço: ", u.endereco, sizeof(u.endereco)) == NAV_BACK) {
        ui_print_warning("Cadastro cancelado.\n");
        return;
    }

    if (ler_linha_opcional("Tipo sanguíneo: ", u.tipo_sanguineo, sizeof(u.tipo_sanguineo)) == NAV_BACK) {
        ui_print_warning("Cadastro cancelado.\n");
        return;
    }

    if (ler_linha_opcional("Alergias: ", u.alergias, sizeof(u.alergias)) == NAV_BACK) {
        ui_print_warning("Cadastro cancelado.\n");
        return;
    }

    if (ler_linha_opcional(
            "Nome do contato de emergência: ",
            u.nome_contato_emergencia,
            sizeof(u.nome_contato_emergencia)
        ) == NAV_BACK) {
        ui_print_warning("Cadastro cancelado.\n");
        return;
    }

    if (ler_linha_opcional(
            "Telefone do contato de emergência: ",
            u.telefone_contato_emergencia,
            sizeof(u.telefone_contato_emergencia)
        ) == NAV_BACK) {
        ui_print_warning("Cadastro cancelado.\n");
        return;
    }

    ui_loading("Processando cadastro", 10, 70);

    if (api_cadastrar_usuario(conn, &u)) {
        ui_print_success("Usuário cadastrado com sucesso.\n");
    } else {
        ui_print_error("Falha ao cadastrar usuário.\n");
    }
}