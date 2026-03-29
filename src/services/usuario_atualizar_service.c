#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

#include "../shared/date.h"
#include "../shared/io.h"
#include "../shared/navigation.h"
#include "../shared/usuario.h"
#include "../ui/ui_theme.h"

int api_buscar_usuario_por_id(MYSQL *conn, int id, Usuario *u);
int api_atualizar_usuario(MYSQL *conn, int id, const Usuario *u);

static int editar_campo_texto(
    const char *label,
    char *destino,
    size_t tamanho
) {
    char entrada[256];
    char mensagem[300];

    snprintf(mensagem, sizeof(mensagem), "%s [%s]: ", label, destino);

    if (ler_linha_opcional(mensagem, entrada, sizeof(entrada)) == NAV_BACK) {
        return NAV_BACK;
    }

    if (entrada[0] != '\0') {
        snprintf(destino, tamanho, "%s", entrada);
    }

    return 0;
}

static int editar_campo_data(
    const char *label,
    char *destino_mysql,
    size_t tamanho
) {
    char entrada[32];
    char mensagem[128];
    char data_exibicao[16] = "";

    if (destino_mysql[0] != '\0') {
        if (!converter_data_para_exibicao(destino_mysql, data_exibicao, sizeof(data_exibicao))) {
            data_exibicao[0] = '\0';
        }
    }

    snprintf(
        mensagem,
        sizeof(mensagem),
        "%s [%s]: ",
        label,
        data_exibicao[0] != '\0' ? data_exibicao : ""
    );

    if (ler_linha_opcional(mensagem, entrada, sizeof(entrada)) == NAV_BACK) {
        return NAV_BACK;
    }

    if (entrada[0] == '\0') {
        return 0;
    }

    while (!converter_data_para_mysql(entrada, destino_mysql, tamanho)) {
        ui_print_error("Data inválida. Use o formato dd-mm-aaaa.\n");

        if (ler_linha_opcional(mensagem, entrada, sizeof(entrada)) == NAV_BACK) {
            return NAV_BACK;
        }

        if (entrada[0] == '\0') {
            return 0;
        }
    }

    return 0;
}

void atualizar_usuario_service(MYSQL *conn) {
    int id;
    int status;
    Usuario u = {0};

    ui_print_primary("\n=== ATUALIZAR USUÁRIO ===\n");

    printf("Digite o ID para atualizar: ");
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

    ui_print_warning("Pressione ENTER para manter o valor atual.\n");
    ui_print_warning("Pressione ESC para cancelar.\n\n");

    if (editar_campo_texto("Nome", u.nome, sizeof(u.nome)) == NAV_BACK) {
        ui_print_warning("Atualização cancelada.\n");
        return;
    }

    if (editar_campo_texto("CPF (somente números)", u.cpf, sizeof(u.cpf)) == NAV_BACK) {
        ui_print_warning("Atualização cancelada.\n");
        return;
    }

    if (editar_campo_data("Data de nascimento (dd-mm-aaaa)", u.data_nascimento, sizeof(u.data_nascimento)) == NAV_BACK) {
        ui_print_warning("Atualização cancelada.\n");
        return;
    }

    if (editar_campo_texto("Email", u.email, sizeof(u.email)) == NAV_BACK) {
        ui_print_warning("Atualização cancelada.\n");
        return;
    }

    if (editar_campo_texto("Telefone", u.telefone, sizeof(u.telefone)) == NAV_BACK) {
        ui_print_warning("Atualização cancelada.\n");
        return;
    }

    if (editar_campo_texto("Endereço", u.endereco, sizeof(u.endereco)) == NAV_BACK) {
        ui_print_warning("Atualização cancelada.\n");
        return;
    }

    if (editar_campo_texto("Tipo sanguíneo", u.tipo_sanguineo, sizeof(u.tipo_sanguineo)) == NAV_BACK) {
        ui_print_warning("Atualização cancelada.\n");
        return;
    }

    if (editar_campo_texto("Alergias", u.alergias, sizeof(u.alergias)) == NAV_BACK) {
        ui_print_warning("Atualização cancelada.\n");
        return;
    }

    if (editar_campo_texto(
            "Nome do contato de emergência",
            u.nome_contato_emergencia,
            sizeof(u.nome_contato_emergencia)
        ) == NAV_BACK) {
        ui_print_warning("Atualização cancelada.\n");
        return;
    }

    if (editar_campo_texto(
            "Telefone do contato de emergência",
            u.telefone_contato_emergencia,
            sizeof(u.telefone_contato_emergencia)
        ) == NAV_BACK) {
        ui_print_warning("Atualização cancelada.\n");
        return;
    }

    if (api_atualizar_usuario(conn, id, &u)) {
        ui_print_success("Usuário atualizado com sucesso.\n");
    } else {
        ui_print_error("Falha ao atualizar usuário.\n");
    }
}