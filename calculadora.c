#include <stdio.h>

int lerNumeroValido(float *numero) {
    int retorno;

    retorno = scanf("%f", numero);

    if (retorno != 1) {
        while (getchar() != '\n');
        return 0;
    }

    return 1;
}

int operadorValido(char operador) {
    if (operador == '+' || operador == '-' || operador == '*' || operador == '/') {
        return 1;
    }

    return 0;
}

int opcaoValida(int opcao) {
    if (opcao == 1 || opcao == 2) {
        return 1;
    }

    return 0;
}

int main() {
    float num1, num2, resultado;
    char operador;
    int opcao;

    do {
        printf("\n=== CALCULADORA ===\n");

        printf("Digite o primeiro numero: ");
        while (!lerNumeroValido(&num1)) {
            printf("Numero invalido! Digite novamente: ");
        }

        printf("Digite o operador (+, -, *, /): ");
        scanf(" %c", &operador);

        while (!operadorValido(operador)) {
            printf("Operador invalido! Digite novamente (+, -, *, /): ");
            scanf(" %c", &operador);
        }

        printf("Digite o segundo numero: ");
        while (!lerNumeroValido(&num2)) {
            printf("Numero invalido! Digite novamente: ");
        }

        if (operador == '/' && num2 == 0) {
            printf("Erro: divisao por zero nao e permitida!\n");
        } else {
            switch (operador) {
                case '+':
                    resultado = num1 + num2;
                    break;
                case '-':
                    resultado = num1 - num2;
                    break;
                case '*':
                    resultado = num1 * num2;
                    break;
                case '/':
                    resultado = num1 / num2;
                    break;
            }

            printf("Resultado: %.2f\n", resultado);
        }

        printf("\nDigite 1 para sair ou 2 para fazer uma nova operacao: ");
        while (scanf("%d", &opcao) != 1 || !opcaoValida(opcao)) {
            while (getchar() != '\n');
            printf("Opcao invalida! Digite 1 para sair ou 2 para continuar: ");
        }

    } while (opcao == 2);

    printf("\nPrograma encerrado.\n");

    return 0;
}