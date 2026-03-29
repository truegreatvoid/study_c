#ifndef DB_H
#define DB_H

#include <mysql/mysql.h>

MYSQL *conectar_db(void);
void fechar_db(MYSQL *conn);

#endif