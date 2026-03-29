#include "ui_table.h"

#include <stdio.h>
#include <string.h>

#include "../shared/date.h"
#include "ui_theme.h"

#define DETAIL_TOTAL_WIDTH 78
#define DETAIL_INNER_WIDTH 74
#define DETAIL_LABEL_WIDTH 20
#define DETAIL_VALUE_WIDTH 50

#define COL_ID_MIN 2
#define COL_NOME_MIN 4
#define COL_CPF_MIN 3
#define COL_NASC_MIN 10
#define COL_EMAIL_MIN 5
#define COL_TEL_MIN 8

#define COL_ID_MAX 6
#define COL_NOME_MAX 32
#define COL_CPF_MAX 14
#define COL_NASC_MAX 10
#define COL_EMAIL_MAX 29
#define COL_TEL_MAX 15

static size_t max_size(size_t a, size_t b) {
    return a > b ? a : b;
}

static size_t min_size(size_t a, size_t b) {
    return a < b ? a : b;
}

static void fit_text(const char *src, char *dest, size_t dest_size, size_t visible_width) {
    size_t len;

    if (dest_size == 0) {
        return;
    }

    if (src == NULL) {
        dest[0] = '\0';
        return;
    }

    len = strlen(src);

    if (len <= visible_width) {
        snprintf(dest, dest_size, "%s", src);
        return;
    }

    if (visible_width <= 3) {
        snprintf(dest, dest_size, "%.*s", (int) visible_width, src);
        return;
    }

    snprintf(dest, dest_size, "%.*s...", (int) (visible_width - 3), src);
}

static void print_separator(
    size_t id_w,
    size_t nome_w,
    size_t cpf_w,
    size_t nasc_w,
    size_t email_w,
    size_t tel_w
) {
    ui_print_primary("+");
    for (size_t i = 0; i < id_w + 2; i++) ui_print_primary("-");
    ui_print_primary("+");
    for (size_t i = 0; i < nome_w + 2; i++) ui_print_primary("-");
    ui_print_primary("+");
    for (size_t i = 0; i < cpf_w + 2; i++) ui_print_primary("-");
    ui_print_primary("+");
    for (size_t i = 0; i < nasc_w + 2; i++) ui_print_primary("-");
    ui_print_primary("+");
    for (size_t i = 0; i < email_w + 2; i++) ui_print_primary("-");
    ui_print_primary("+");
    for (size_t i = 0; i < tel_w + 2; i++) ui_print_primary("-");
    ui_print_primary("+\n");
}

void ui_render_usuario_table(const UsuarioLista *lista) {
    size_t id_w = strlen("ID");
    size_t nome_w = strlen("Nome");
    size_t cpf_w = strlen("CPF");
    size_t nasc_w = strlen("Nascimento");
    size_t email_w = strlen("Email");
    size_t tel_w = strlen("Telefone");

    if (lista == NULL) {
        return;
    }

    for (int i = 0; i < lista->total; i++) {
        char id_text[32];
        char data_exibicao[16] = "";

        snprintf(id_text, sizeof(id_text), "%d", lista->ids[i]);

        id_w = max_size(id_w, strlen(id_text));
        nome_w = max_size(nome_w, strlen(lista->itens[i].nome));
        cpf_w = max_size(cpf_w, strlen(lista->itens[i].cpf));
        email_w = max_size(email_w, strlen(lista->itens[i].email));
        tel_w = max_size(tel_w, strlen(lista->itens[i].telefone));

        if (lista->itens[i].data_nascimento[0] != '\0' &&
            converter_data_para_exibicao(
                lista->itens[i].data_nascimento,
                data_exibicao,
                sizeof(data_exibicao)
            )) {
            nasc_w = max_size(nasc_w, strlen(data_exibicao));
        }
    }

    id_w = min_size(max_size(id_w, COL_ID_MIN), COL_ID_MAX);
    nome_w = min_size(max_size(nome_w, COL_NOME_MIN), COL_NOME_MAX);
    cpf_w = min_size(max_size(cpf_w, COL_CPF_MIN), COL_CPF_MAX);
    nasc_w = min_size(max_size(nasc_w, COL_NASC_MIN), COL_NASC_MAX);
    email_w = min_size(max_size(email_w, COL_EMAIL_MIN), COL_EMAIL_MAX);
    tel_w = min_size(max_size(tel_w, COL_TEL_MIN), COL_TEL_MAX);

    ui_print_primary("");
    print_separator(id_w, nome_w, cpf_w, nasc_w, email_w, tel_w);

    ui_print_primary("|");
    printf(" %-*s ", (int) id_w, "ID");
    ui_print_primary("|");
    printf(" %-*s ", (int) nome_w, "Nome");
    ui_print_primary("|");
    printf(" %-*s ", (int) cpf_w, "CPF");
    ui_print_primary("|");
    printf(" %-*s ", (int) nasc_w, "Nascimento");
    ui_print_primary("|");
    printf(" %-*s ", (int) email_w, "Email");
    ui_print_primary("|");
    printf(" %-*s ", (int) tel_w, "Telefone");
    ui_print_primary("|\n");

    ui_print_primary("");
    print_separator(id_w, nome_w, cpf_w, nasc_w, email_w, tel_w);

    for (int i = 0; i < lista->total; i++) {
        char id_text[32];
        char nome[256];
        char cpf[64];
        char nascimento[32] = "";
        char email[256];
        char telefone[128];

        snprintf(id_text, sizeof(id_text), "%d", lista->ids[i]);

        fit_text(lista->itens[i].nome, nome, sizeof(nome), nome_w);
        fit_text(lista->itens[i].cpf, cpf, sizeof(cpf), cpf_w);
        fit_text(lista->itens[i].email, email, sizeof(email), email_w);
        fit_text(lista->itens[i].telefone, telefone, sizeof(telefone), tel_w);

        if (lista->itens[i].data_nascimento[0] != '\0' &&
            converter_data_para_exibicao(
                lista->itens[i].data_nascimento,
                nascimento,
                sizeof(nascimento)
            )) {
            char data_ajustada[32];
            fit_text(nascimento, data_ajustada, sizeof(data_ajustada), nasc_w);
            snprintf(nascimento, sizeof(nascimento), "%s", data_ajustada);
        } else {
            nascimento[0] = '\0';
        }

        ui_print_primary("|");
        printf(" %-*.*s ", (int) id_w, (int) id_w, id_text);
        ui_print_primary("|");
        printf(" %-*.*s ", (int) nome_w, (int) nome_w, nome);
        ui_print_primary("|");
        printf(" %-*.*s ", (int) cpf_w, (int) cpf_w, cpf);
        ui_print_primary("|");
        printf(" %-*.*s ", (int) nasc_w, (int) nasc_w, nascimento);
        ui_print_primary("|");
        printf(" %-*.*s ", (int) email_w, (int) email_w, email);
        ui_print_primary("|");
        printf(" %-*.*s ", (int) tel_w, (int) tel_w, telefone);
        ui_print_primary("|\n");
    }

    ui_print_primary("");
    print_separator(id_w, nome_w, cpf_w, nasc_w, email_w, tel_w);
    printf("Total de registros: %d\n", lista->total);
}

static void print_detail_border(void) {
    ui_print_primary("+----------------------------------------------------------------------------+\n");
}

static void print_detail_title(const char *title) {
    char title_fit[DETAIL_INNER_WIDTH + 1];
    char title_block[DETAIL_INNER_WIDTH + 3];

    fit_text(title ? title : "", title_fit, sizeof(title_fit), DETAIL_INNER_WIDTH);
    snprintf(title_block, sizeof(title_block), " %-*s ", DETAIL_INNER_WIDTH, title_fit);

    ui_print_primary("|");
    ui_print_success(title_block);
    ui_print_primary("|\n");
}

static void print_detail_row(const char *label, const char *value) {
    char label_fit[DETAIL_LABEL_WIDTH + 1];
    char value_fit[DETAIL_VALUE_WIDTH + 1];
    char label_block[DETAIL_LABEL_WIDTH + 1];
    char value_block[DETAIL_VALUE_WIDTH + 1];

    fit_text(label ? label : "", label_fit, sizeof(label_fit), DETAIL_LABEL_WIDTH);
    fit_text(value ? value : "", value_fit, sizeof(value_fit), DETAIL_VALUE_WIDTH);

    snprintf(label_block, sizeof(label_block), "%-*s", DETAIL_LABEL_WIDTH, label_fit);
    snprintf(value_block, sizeof(value_block), "%-*s", DETAIL_VALUE_WIDTH, value_fit);

    ui_print_primary("| ");
    ui_print_warning(label_block);
    printf(" : ");
    printf("%s", value_block);
    ui_print_primary(" |\n");
}

void ui_render_usuario_detalhe(int id, const Usuario *usuario) {
    char id_text[32];
    char data_exibicao[16] = "";

    if (usuario == NULL) {
        return;
    }

    snprintf(id_text, sizeof(id_text), "%d", id);

    if (usuario->data_nascimento[0] != '\0') {
        if (!converter_data_para_exibicao(
                usuario->data_nascimento,
                data_exibicao,
                sizeof(data_exibicao))) {
            data_exibicao[0] = '\0';
        }
    }

    print_detail_border();
    print_detail_title("USUÁRIO ENCONTRADO");
    print_detail_border();

    print_detail_row("ID", id_text);
    print_detail_row("Nome", usuario->nome);
    print_detail_row("CPF", usuario->cpf);
    print_detail_row("Nascimento", data_exibicao);
    print_detail_row("Email", usuario->email);
    print_detail_row("Telefone", usuario->telefone);
    print_detail_row("Endereço", usuario->endereco);
    print_detail_row("Tipo sanguíneo", usuario->tipo_sanguineo);
    print_detail_row("Alergias", usuario->alergias);
    print_detail_row("Contato emergência", usuario->nome_contato_emergencia);
    print_detail_row("Telefone emergência", usuario->telefone_contato_emergencia);

    print_detail_border();
}