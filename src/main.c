#include <mysql/mysql.h>

#include "conf/app_config.h"
#include "conf/platform.h"
#include "db/db.h"
#include "modules/main_menu/main_menu.h"
#include "ui/ui_console.h"

int main(void) {
    setup_platform();
    app_config_init("src/.env");

    MYSQL *conn = conectar_db();
    if (conn == NULL) {
        return 1;
    }

    ui_clear_screen();
    main_menu_show(conn);

    ui_clear_screen();
    fechar_db(conn);
    return 0;
}