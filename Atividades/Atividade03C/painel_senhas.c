/*
 * Resposta: O menu precisa de do-while para garantir que ele seja exibido pelo 
 * menos uma vez antes de avaliar a escolha do usuário. O continue evita contar 
 * senhas negativas na opção 1 ao saltar o restante da iteração atual. Se o break 
 * fosse omitido na busca prioritária, o laço infinito continuaria executando 
 * indefinidamente após encontrar a senha ou o zero.
 */

#include <stdio.h>

int main() {
    int opcao;

    do {
        printf("===== PAINEL DE SENHAS =====\n");
        printf("1\tRegistrar lote\n");
        printf("2\tSimular chamadas\n");
        printf("3\tGrade de guiches\n");
        printf("4\tBuscar senha prioritaria\n");
        printf("0\tEncerrar\n");
        printf("Opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida\n");
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 1: {
                int senha;
                int atendidas = 0;
                int ignoradas = 0;
                int pares = 0;

                printf("Digite as senhas (0 para encerrar):\n");
                scanf("%d", &senha);

                while (senha != 0) {
                    if (senha < 0) {
                        ignoradas++;
                        scanf("%d", &senha);
                        continue;
                    }

                    atendidas++;
                    if (senha % 2 == 0) {
                        pares++;
                    }

                    scanf("%d", &senha);
                }

                printf("Atendidas: %d\n", atendidas);
                printf("Ignoradas: %d\n", ignoradas);
                printf("Pares: %d\n", pares);
                break;
            }
            case 2: {
                int inicio, fim, passo;
                printf("Inicio: ");
                scanf("%d", &inicio);
                printf("Fim: ");
                scanf("%d", &fim);
                printf("Passo: ");
                scanf("%d", &passo);

                if (passo == 0) {
                    printf("Passo invalido\n");
                } else {
                    int executou = 0;
                    printf("Chamadas:");
                    
                    if (passo > 0) {
                        for (int i = inicio; i <= fim; i += passo) {
                            printf(" %d", i);
                            executou = 1;
                        }
                    } else {
                        for (int i = inicio; i >= fim; i += passo) {
                            printf(" %d", i);
                            executou = 1;
                        }
                    }

                    if (!executou) {
                        printf(" Nenhuma chamada");
                    }
                    printf("\n");
                }
                break;
            }
            case 3: {
                int g, s;
                printf("Guiches (1 a 4): ");
                scanf("%d", &g);
                printf("Senhas por guiche (1 a 5): ");
                scanf("%d", &s);

                if (g < 1 || g > 4 || s < 1 || s > 5) {
                    printf("Grade invalida\n");
                } else {
                    for (int i = 1; i <= g; i++) {
                        printf("Guiche %d: ", i);
                        for (int j = 1; j <= s; j++) {
                            printf("%d", j);
                        }
                        printf("\n");
                    }
                }
                break;
            }
            case 4: {
                int senha;
                int lidas_antes = 0;
                int encontrada = 0;

                for (;;) {
                    printf("Senha: ");
                    scanf("%d", &senha);

                    if (senha == 0) {
                        break;
                    }

                    if (senha > 0 && senha % 10 == 0) {
                        encontrada = 1;
                        break;
                    }

                    lidas_antes++;
                }

                if (encontrada) {
                    printf("Prioritaria: %d\n", senha);
                    printf("Lidas antes: %d\n", lidas_antes);
                } else {
                    printf("Nao encontrada\n");
                    printf("Lidas: %d\n", lidas_antes);
                }
                break;
            }
            case 0:
                printf("Painel encerrado.\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}