CC = gcc
CFLAGS = -Wall -Wextra -g -Isrc
LDFLAGS = -lmysqlclient

TARGET = bin/main
PATH_TO_MYSQL = docker/mysql/docker-compose.yaml

SRC = \
	src/main.c \
	src/conf/env.c \
	src/conf/app_config.c \
	src/conf/platform.c \
	src/ui/ui_theme.c \
	src/ui/ui_console.c \
	src/ui/ui_table.c \
	src/ui/ui_loading.c \
	src/ui/ui_menu.c \
	src/db/db.c \
	src/api/usuario_cadastrar.c \
	src/api/usuario_listar.c \
	src/api/usuario_buscar_por_id.c \
	src/api/usuario_atualizar.c \
	src/api/usuario_deletar.c \
	src/services/usuario_cadastrar_service.c \
	src/services/usuario_listar_service.c \
	src/services/usuario_buscar_por_id_service.c \
	src/services/usuario_atualizar_service.c \
	src/services/usuario_deletar_service.c \
	src/modules/main_menu/main_menu.c \
	src/modules/usuarios/usuarios_menu.c \
	src/modules/exemplo_2/exemplo_2_menu.c

all: build run

build:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: clean build
	./$(TARGET)

clean:
	rm -rf bin/main

db-up:
	docker compose -f $(PATH_TO_MYSQL) up -d

db-down:
	docker compose -f $(PATH_TO_MYSQL) down

db-reset:
	docker compose -f $(PATH_TO_MYSQL) down -v
	docker compose -f $(PATH_TO_MYSQL) up -d

db-logs:
	docker compose -f $(PATH_TO_MYSQL) logs -f mysql

db-wait:
	until docker exec docker_mysql mysqladmin ping -h 127.0.0.1 -uapp -papp --silent; do \
		echo "Aguardando MySQL subir..."; \
		sleep 2; \
	done

dev: db-up db-wait build run

rebuild: db-reset clean build run
