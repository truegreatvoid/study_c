#ifndef UI_TABLE_H
#define UI_TABLE_H

#include "../shared/usuario.h"
#include "../shared/usuario_lista.h"

void ui_render_usuario_table(const UsuarioLista *lista);
void ui_render_usuario_detalhe(int id, const Usuario *usuario);

#endif