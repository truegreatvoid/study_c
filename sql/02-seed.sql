SET NAMES utf8mb4;
SET CHARACTER SET utf8mb4;

USE viva_segura;

SET @QTD_USUARIOS = 50;
SET @QTD_PROFISSIONAIS = 10;
SET @QTD_DENUNCIAS = 80;
SET @QTD_EMERGENCIAS = 40;
SET @QTD_ATENDIMENTOS = 120;
SET @QTD_SERVICOS = 12;
SET @QTD_CURSOS = 10;
SET @QTD_EMPREGOS = 15;

DROP FUNCTION IF EXISTS gerar_cpf_fake_valido;
DROP FUNCTION IF EXISTS only_digits_9;
DROP PROCEDURE IF EXISTS seed_usuarios;
DROP PROCEDURE IF EXISTS seed_profissionais;
DROP PROCEDURE IF EXISTS seed_denuncias;
DROP PROCEDURE IF EXISTS seed_emergencias;
DROP PROCEDURE IF EXISTS seed_atendimentos;
DROP PROCEDURE IF EXISTS seed_servicos;
DROP PROCEDURE IF EXISTS seed_cursos;
DROP PROCEDURE IF EXISTS seed_empregos;

DELIMITER $$

CREATE FUNCTION only_digits_9(seed_num INT)
RETURNS CHAR(9)
DETERMINISTIC
BEGIN
    RETURN LPAD(CAST((100000000 + (seed_num * 7919)) % 1000000000 AS CHAR), 9, '0');
END $$

CREATE FUNCTION gerar_cpf_fake_valido(seed_num INT)
RETURNS CHAR(11)
DETERMINISTIC
BEGIN
    DECLARE base9 CHAR(9);
    DECLARE i INT DEFAULT 1;
    DECLARE soma1 INT DEFAULT 0;
    DECLARE soma2 INT DEFAULT 0;
    DECLARE dv1 INT DEFAULT 0;
    DECLARE dv2 INT DEFAULT 0;
    DECLARE dig INT;

    SET base9 = only_digits_9(seed_num);

    IF base9 IN (
        '000000000','111111111','222222222','333333333','444444444',
        '555555555','666666666','777777777','888888888','999999999'
    ) THEN
        SET base9 = only_digits_9(seed_num + 123);
    END IF;

    SET i = 1;
    WHILE i <= 9 DO
        SET dig = CAST(SUBSTRING(base9, i, 1) AS UNSIGNED);
        SET soma1 = soma1 + (dig * (11 - i));
        SET i = i + 1;
    END WHILE;

    SET dv1 = 11 - (soma1 % 11);
    IF dv1 >= 10 THEN
        SET dv1 = 0;
    END IF;

    SET i = 1;
    WHILE i <= 9 DO
        SET dig = CAST(SUBSTRING(base9, i, 1) AS UNSIGNED);
        SET soma2 = soma2 + (dig * (12 - i));
        SET i = i + 1;
    END WHILE;

    SET soma2 = soma2 + (dv1 * 2);

    SET dv2 = 11 - (soma2 % 11);
    IF dv2 >= 10 THEN
        SET dv2 = 0;
    END IF;

    RETURN CONCAT(base9, dv1, dv2);
END $$

CREATE PROCEDURE seed_usuarios(IN qtd INT)
BEGIN
    DECLARE i INT DEFAULT 1;
    DECLARE nome_base VARCHAR(100);
    DECLARE sobrenome_base VARCHAR(100);
    DECLARE tipo_sangue VARCHAR(10);
    DECLARE alergia_base VARCHAR(255);
    DECLARE endereco_base VARCHAR(150);

    WHILE i <= qtd DO
        SET nome_base = ELT(((i - 1) % 10) + 1,
            'João', 'Maria', 'Pedro', 'Ana', 'Lucas',
            'Juliana', 'Carlos', 'Fernanda', 'Rafael', 'Camila'
        );

        SET sobrenome_base = ELT(((i - 1) % 10) + 1,
            'Silva', 'Souza', 'Oliveira', 'Santos', 'Lima',
            'Pereira', 'Costa', 'Almeida', 'Rocha', 'Barbosa'
        );

        SET tipo_sangue = ELT(((i - 1) % 8) + 1,
            'A+', 'A-', 'B+', 'B-', 'AB+', 'AB-', 'O+', 'O-'
        );

        SET alergia_base = ELT(((i - 1) % 6) + 1,
            'Nenhuma',
            'Poeira',
            'Lactose',
            'Glúten',
            'Picada de inseto',
            'Medicamento'
        );

        SET endereco_base = CONCAT(
            'Rua ',
            ELT(((i - 1) % 10) + 1,
                'das Flores', 'do Sol', 'da Paz', 'do Farol', 'das Acácias',
                'dos Navegantes', 'Boa Esperança', 'da Aurora', 'do Cajueiro', 'das Mangueiras'
            ),
            ', nº ', 100 + i,
            ', Recife - PE'
        );

        INSERT INTO usuario (
            nome,
            cpf,
            data_nascimento,
            email,
            telefone,
            endereco,
            tipo_sanguineo,
            alergias,
            nome_contato_emergencia,
            telefone_contato_emergencia
        ) VALUES (
            CONCAT(nome_base, ' ', sobrenome_base, ' ', i),
            gerar_cpf_fake_valido(i),
            DATE_SUB('2005-12-31', INTERVAL (18 + (i % 42)) YEAR) + INTERVAL (i % 365) DAY,
            CONCAT('usuario', i, '@viva-segura.local'),
            CONCAT('8199', LPAD(i, 6, '0')),
            endereco_base,
            tipo_sangue,
            alergia_base,
            CONCAT('Contato Responsável ', i),
            CONCAT('8188', LPAD(i, 6, '0'))
        );

        SET i = i + 1;
    END WHILE;
END $$

CREATE PROCEDURE seed_profissionais(IN qtd INT)
BEGIN
    DECLARE i INT DEFAULT 1;
    DECLARE especialidade_base VARCHAR(100);
    DECLARE nome_base VARCHAR(100);

    WHILE i <= qtd DO
        SET nome_base = ELT(((i - 1) % 10) + 1,
            'Carlos Mendes', 'Paula Lima', 'Renato Alves', 'Patrícia Gomes', 'Eduardo Nunes',
            'Bruna Castro', 'Felipe Tavares', 'Larissa Melo', 'Ricardo Martins', 'Aline Duarte'
        );

        SET especialidade_base = ELT(((i - 1) % 8) + 1,
            'Médico',
            'Enfermeiro(a)',
            'Psicólogo(a)',
            'Assistente Social',
            'Socorrista',
            'Técnico de Enfermagem',
            'Advogado(a)',
            'Orientador(a)'
        );

        INSERT INTO profissional (
            nome,
            sexo,
            data_nascimento,
            especialidade,
            telefone,
            email
        ) VALUES (
            CONCAT(nome_base, ' ', i),
            ELT(((i - 1) % 2) + 1, 'M', 'F'),
            DATE_SUB('1998-12-31', INTERVAL (22 + (i % 28)) YEAR) + INTERVAL (i % 365) DAY,
            especialidade_base,
            CONCAT('8177', LPAD(i, 6, '0')),
            CONCAT('profissional', i, '@viva-segura.local')
        );

        SET i = i + 1;
    END WHILE;
END $$

CREATE PROCEDURE seed_denuncias(IN qtd INT)
BEGIN
    DECLARE i INT DEFAULT 1;
    DECLARE max_usuario INT DEFAULT 0;

    SELECT COALESCE(MAX(id), 0) INTO max_usuario FROM usuario;

    WHILE i <= qtd DO
        INSERT INTO denuncia (
            descricao,
            data_denuncia,
            horario,
            usuario_id
        ) VALUES (
            CONCAT(
                ELT(((i - 1) % 6) + 1,
                    'Relato de violência doméstica',
                    'Denúncia de assédio em via pública',
                    'Ocorrência de ameaça verbal',
                    'Pedido de ajuda após perseguição',
                    'Relato de agressão física',
                    'Denúncia de comportamento suspeito'
                ),
                ' - registro ', i
            ),
            DATE_SUB(CURDATE(), INTERVAL (i % 180) DAY),
            MAKETIME(8 + (i % 10), (i * 7) % 60, 0),
            ((i - 1) % max_usuario) + 1
        );

        SET i = i + 1;
    END WHILE;
END $$

CREATE PROCEDURE seed_emergencias(IN qtd INT)
BEGIN
    DECLARE i INT DEFAULT 1;
    DECLARE max_usuario INT DEFAULT 0;

    SELECT COALESCE(MAX(id), 0) INTO max_usuario FROM usuario;

    WHILE i <= qtd DO
        INSERT INTO emergencia (
            local_emergencia,
            descricao,
            horario,
            data_emergencia,
            usuario_id
        ) VALUES (
            CONCAT(
                ELT(((i - 1) % 8) + 1,
                    'Av. Boa Viagem',
                    'Centro do Recife',
                    'Praça do Derby',
                    'Terminal Integrado',
                    'Hospital da Restauração',
                    'Rua da Aurora',
                    'Shopping Recife',
                    'UFPE'
                ),
                ' - ponto ', i
            ),
            ELT(((i - 1) % 6) + 1,
                'Acidente de trânsito com vítima',
                'Solicitação de apoio imediato',
                'Pessoa passando mal no local',
                'Ocorrência com risco iminente',
                'Necessidade de atendimento urgente',
                'Situação crítica reportada por morador'
            ),
            MAKETIME(6 + (i % 14), (i * 11) % 60, 0),
            DATE_SUB(CURDATE(), INTERVAL (i % 120) DAY),
            ((i - 1) % max_usuario) + 1
        );

        SET i = i + 1;
    END WHILE;
END $$

CREATE PROCEDURE seed_atendimentos(IN qtd INT)
BEGIN
    DECLARE i INT DEFAULT 1;
    DECLARE max_usuario INT DEFAULT 0;
    DECLARE max_profissional INT DEFAULT 0;

    SELECT COALESCE(MAX(id), 0) INTO max_usuario FROM usuario;
    SELECT COALESCE(MAX(id), 0) INTO max_profissional FROM profissional;

    WHILE i <= qtd DO
        INSERT INTO atendimento (
            data_atendimento,
            horario,
            protocolo,
            observacoes,
            usuario_id,
            profissional_id
        ) VALUES (
            DATE_SUB(CURDATE(), INTERVAL (i % 150) DAY),
            MAKETIME(7 + (i % 11), (i * 13) % 60, 0),
            CONCAT('PROTO-', LPAD(i, 6, '0')),
            ELT(((i - 1) % 5) + 1,
                'Atendimento inicial realizado com orientações.',
                'Usuário encaminhado para acompanhamento.',
                'Ocorrência registrada e monitorada.',
                'Atendimento finalizado sem intercorrências.',
                'Caso mantido em observação.'
            ),
            ((i - 1) % max_usuario) + 1,
            ((i - 1) % max_profissional) + 1
        );

        SET i = i + 1;
    END WHILE;
END $$

CREATE PROCEDURE seed_servicos(IN qtd INT)
BEGIN
    DECLARE i INT DEFAULT 1;

    WHILE i <= qtd DO
        INSERT INTO servico (
            nome,
            descricao,
            tipo
        ) VALUES (
            CONCAT(
                ELT(((i - 1) % 6) + 1,
                    'Acolhimento',
                    'Atendimento Psicossocial',
                    'Orientação Jurídica',
                    'Atendimento Médico',
                    'Proteção Emergencial',
                    'Encaminhamento Social'
                ),
                ' ',
                i
            ),
            CONCAT('Descrição do serviço número ', i, '.'),
            ELT(((i - 1) % 4) + 1,
                'Saúde',
                'Segurança',
                'Assistência',
                'Jurídico'
            )
        );

        SET i = i + 1;
    END WHILE;
END $$

CREATE PROCEDURE seed_cursos(IN qtd INT)
BEGIN
    DECLARE i INT DEFAULT 1;

    WHILE i <= qtd DO
        INSERT INTO curso (
            nome,
            descricao,
            tipo
        ) VALUES (
            CONCAT(
                ELT(((i - 1) % 6) + 1,
                    'Primeiros Socorros',
                    'Defesa Pessoal',
                    'Rede de Apoio',
                    'Direitos da Mulher',
                    'Prevenção de Violência',
                    'Acolhimento Comunitário'
                ),
                ' ',
                i
            ),
            CONCAT('Curso demonstrativo número ', i, '.'),
            ELT(((i - 1) % 4) + 1,
                'Saúde',
                'Segurança',
                'Educação',
                'Social'
            )
        );

        SET i = i + 1;
    END WHILE;
END $$

CREATE PROCEDURE seed_empregos(IN qtd INT)
BEGIN
    DECLARE i INT DEFAULT 1;

    WHILE i <= qtd DO
        INSERT INTO emprego (
            cargo,
            setor,
            descricao,
            requisitos
        ) VALUES (
            CONCAT(
                ELT(((i - 1) % 8) + 1,
                    'Auxiliar Administrativo',
                    'Recepcionista',
                    'Vigilante',
                    'Assistente Social',
                    'Cuidador(a)',
                    'Atendente',
                    'Técnico de Apoio',
                    'Analista Operacional'
                ),
                ' ',
                i
            ),
            ELT(((i - 1) % 5) + 1,
                'Administrativo',
                'Segurança',
                'Saúde',
                'Assistência',
                'Operações'
            ),
            CONCAT('Vaga gerada automaticamente para testes - registro ', i, '.'),
            ELT(((i - 1) % 5) + 1,
                'Ensino médio completo',
                'Experiência com atendimento ao público',
                'Curso técnico na área',
                'Boa comunicação e organização',
                'Disponibilidade de horário'
            )
        );

        SET i = i + 1;
    END WHILE;
END $$

DELIMITER ;

CALL seed_usuarios(@QTD_USUARIOS);
CALL seed_profissionais(@QTD_PROFISSIONAIS);
CALL seed_denuncias(@QTD_DENUNCIAS);
CALL seed_emergencias(@QTD_EMERGENCIAS);
CALL seed_atendimentos(@QTD_ATENDIMENTOS);
CALL seed_servicos(@QTD_SERVICOS);
CALL seed_cursos(@QTD_CURSOS);
CALL seed_empregos(@QTD_EMPREGOS);

DROP PROCEDURE IF EXISTS seed_usuarios;
DROP PROCEDURE IF EXISTS seed_profissionais;
DROP PROCEDURE IF EXISTS seed_denuncias;
DROP PROCEDURE IF EXISTS seed_emergencias;
DROP PROCEDURE IF EXISTS seed_atendimentos;
DROP PROCEDURE IF EXISTS seed_servicos;
DROP PROCEDURE IF EXISTS seed_cursos;
DROP PROCEDURE IF EXISTS seed_empregos;

DROP FUNCTION IF EXISTS gerar_cpf_fake_valido;
DROP FUNCTION IF EXISTS only_digits_9;