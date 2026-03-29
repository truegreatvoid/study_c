#ifndef USUARIO_SERVICES_H
#define USUARIO_SERVICES_H

#include <mysql/mysql.h>

void cadastrar_usuario_service(MYSQL *conn);
void listar_usuarios_service(MYSQL *conn);
void buscar_usuario_por_id_service(MYSQL *conn);
void atualizar_usuario_service(MYSQL *conn);
void deletar_usuario_service(MYSQL *conn);

#endif