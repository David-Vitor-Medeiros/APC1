/*
 * ============================================================================
 * Ao declarar char nome[50], armazenamos no máximo 49 caracteres úteis porque 
 * o último byte (índice 49) é obrigatoriamente reservado para o caractere nulo 
 * de terminação '\0', essencial para que as funções de manipulação de strings 
 * reconheçam o fim da cadeia. Em uma matriz int M[3][4], o primeiro índice (3) 
 * representa a quantidade de linhas e o segundo índice (4) representa a quantidade 
 * de colunas. A linguagem C organiza esses elementos na memória contígua em 
 * formato "linha-major" (row-major order), o que significa que os elementos 
 * de uma mesma linha são armazenados sequencialmente na memória, sendo a linha 
 * seguinte alocada logo após o término da anterior.
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>

int main() {
    int opcao;

    // Declaração das estruturas de dados conforme regras de negócio
    char alunos[5][50];                  // Opção 1: Vetor de strings para 5 alunos
    float notas_finais[5];               // Opção 2 e 4: Vetor de float de tamanho 5
    float boletim[3][4];                 // Opção 3: Matriz 3x4 (3 alunos x 4 bimestres)[cite: 2]
    
    // Variáveis auxiliares de controle
    int i, j;
    int dados_notas_preenchidos = 0;     // Flag para garantir que a Opção 2 foi executada antes da Opção 4

    do {
        // Exibição do menu interativo
        printf("\n===== SISTEMA DE GESTÃO ACADÊMICA =====\n");
        printf("1. Cadastrar Lista de Alunos (Vetor de Strings)\n");
        printf("2. Estatísticas de Desempenho (Vetor de Float)\n");
        printf("3. Matriz de Notas da Turma (Matriz Bidimensional)\n");
        printf("4. Consultar Aluno em Destaque (Pesquisa em Matriz/Vetor)\n");
        printf("0. Encerrar\n");
        printf("Opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Entrada invalida. Digite um numero inteiro.\n");
            // Limpa o buffer de entrada em caso de caractere inválido
            while (getchar() != '\n');
            continue;
        }

        // Limpa o '\n' deixado pelo scanf no buffer antes de usar fgets
        while (getchar() != '\n');

        switch (opcao) {
            case 1: {
                printf("\n--- CADASTRO DE ALUNOS ---\n");
                for (i = 0; i < 5; i++) {
                    printf("Digite o nome do aluno %d: ", i + 1);
                    if (fgets(alunos[i], sizeof(alunos[i]), stdin) != NULL) {
                        // Remove a quebra de linha (\n) capturada pelo fgets
                        alunos[i][strcspn(alunos[i], "\n")] = '\0';
                    }
                }

                printf("\nLista de Alunos Cadastrados:\n");
                for (i = 0; i < 5; i++) {
                    printf("%d. %s\n", i + 1, alunos[i]);
                }
                break;
            }

            case 2: {
                printf("\n--- ESTATÍSTICAS DE DESEMPENHO ---\n");
                float soma = 0.0, media_geral = 0.0;
                int contador_acima_media = 0;

                // Preenchimento completo do vetor de notas antes do processamento
                for (i = 0; i < 5; i++) {
                    printf("Digite a nota final do aluno %d (0 a 10): ", i + 1);
                    scanf("%f", &notas_finais[i]);
                }
                while (getchar() != '\n'); // Limpa buffer

                // Processamento dos dados
                for (i = 0; i < 5; i++) {
                    soma += notas_finais[i];
                }
                media_geral = soma / 5.0;

                for (i = 0; i < 5; i++) {
                    if (notas_finais[i] >= media_geral) {
                        contador_acima_media++;
                    }
                }

                // Exibição dos resultados
                printf("\nMédia geral da turma: %.2f\n", media_geral);
                printf("Quantidade de alunos com nota maior ou igual à média: %d\n", contador_acima_media);
                
                dados_notas_preenchidos = 1; // Marca que as notas foram preenchidas para a Opção 4
                break;
            }

            case 3: {
                printf("\n--- MATRIZ DE NOTAS DA TURMA (3 Alunos x 4 Bimestres) ---\n");
                // Preenchimento da matriz utilizando laços for aninhados
                for (i = 0; i < 3; i++) {
                    printf("--- Aluno %d ---\n", i + 1);
                    for (j = 0; j < 4; j++) {
                        printf("  Digite a nota do Bimestre %d: ", j + 1);
                        scanf("%f", &boletim[i][j]);
                    }
                }
                while (getchar() != '\n'); // Limpa buffer

                // Exibição da matriz em formato de grade/tabela com média simples por linha
                printf("\nBoletim da Turma:\n");
                printf("----------------------------------------------------\n");
                printf("Aluno     | Bim 1 | Bim 2 | Bim 3 | Bim 4 | Média Simples\n");
                printf("----------------------------------------------------\n");
                
                for (i = 0; i < 3; i++) {
                    float soma_linha = 0.0;
                    printf("Aluno %-3d |", i + 1);
                    for (j = 0; j < 4; j++) {
                        printf(" %5.1f |", boletim[i][j]);
                        soma_linha += boletim[i][j];
                    }
                    float media_aluno = soma_linha / 4.0;
                    printf("    %.2f\n", media_aluno);
                }
                printf("----------------------------------------------------\n");
                break;
            }

            case 4: {
                printf("\n--- CONSULTAR ALUNO EM DESTAQUE ---\n");
                if (!dados_notas_preenchidos) {
                    printf("[AVISO] Nenhuma nota foi cadastrada na Opção 2 ainda. Por favor, execute a Opção 2 primeiro.\n");
                    break;
                }

                float maior_nota = notas_finais[0];
                int indice_maior = 0;

                // Percorre o vetor de notas para encontrar o maior valor e o índice
                for (i = 1; i < 5; i++) {
                    if (notas_finais[i] > maior_nota) {
                        maior_nota = notas_finais[i];
                        indice_maior = i;
                    }
                }

                printf("A maior nota da turma é %.2f\n", maior_nota);
                printf("Encontrada no índice %d (correspondente ao Aluno %d).\n", indice_maior, indice_maior + 1);
                break;
            }

            case 0:
                printf("\nEncerrando o Sistema de Gestão Acadêmica. Até logo!\n");
                break;

            default:
                printf("\n[ERRO] Opção inválida! Escolha um número entre 0 e 4.\n");
        }

    } while (opcao != 0);

    return 0;
}