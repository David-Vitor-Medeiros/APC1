#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX 30

enum StatusAluno {
    REPROVADO = 0,
    RECUPERACAO = 1,
    APROVADO = 2
};

struct Aluno {
    int matricula;
    char nome[41];
    float a1;
    float a2;
    float media;
    enum StatusAluno status;
};

const char* statusParaString(enum StatusAluno status) {
    switch (status) {
        case APROVADO: return "APROVADO";
        case RECUPERACAO: return "RECUPERACAO";
        case REPROVADO: return "REPROVADO";
        default: return "DESCONHECIDO";
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    struct Aluno turma[MAX];
    int totalAlunos = 0;
    int opcao;

    do {
        printf("\n=== MINI CADASTRO DE TURMAS ===\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Listar alunos\n");
        printf("3. Buscar por matricula\n");
        printf("4. Buscar por trecho do nome\n");
        printf("5. Estatisticas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (opcao) {
            case 1: {
                if (totalAlunos >= MAX) {
                    printf("\nErro: Capacidade maxima de %d alunos atingida!\n", MAX);
                    break;
                }

                struct Aluno novoAluno;

                printf("\n--- Cadastrar Aluno ---\n");
                printf("Matricula: ");
                scanf("%d", &novoAluno.matricula);
                while (getchar() != '\n');

                int matriculaExiste = 0;
                for (int i = 0; i < totalAlunos; i++) {
                    if (turma[i].matricula == novoAluno.matricula) {
                        matriculaExiste = 1;
                        break;
                    }
                }

                if (matriculaExiste) {
                    printf("Erro: Ja existe um aluno cadastrado com esta matricula!\n");
                    break;
                }

                printf("Nome (max 40 caracteres): ");
                fgets(novoAluno.nome, sizeof(novoAluno.nome), stdin);
                novoAluno.nome[strcspn(novoAluno.nome, "\n")] = '\0';

                printf("Nota A1: ");
                scanf("%f", &novoAluno.a1);
                while (getchar() != '\n');

                printf("Nota A2: ");
                scanf("%f", &novoAluno.a2);
                while (getchar() != '\n');

                novoAluno.media = (0.4f * novoAluno.a1) + (0.6f * novoAluno.a2);

                if (novoAluno.media >= 5.0f) {
                    novoAluno.status = APROVADO;
                } else if (novoAluno.media >= 3.0f) {
                    novoAluno.status = RECUPERACAO;
                } else {
                    novoAluno.status = REPROVADO;
                }

                turma[totalAlunos] = novoAluno;
                totalAlunos++;

                printf("\nSucesso: Aluno cadastrado com sucesso!\n");
                break;
            }
            case 2: {
                if (totalAlunos == 0) {
                    printf("\nNenhum aluno cadastrado na turma.\n");
                    break;
                }

                printf("\n--- Lista de Alunos ---\n");
                printf("%-10s | %-40s | %-5s | %-5s | %-6s | %s\n", "Matricula", "Nome", "A1", "A2", "Media", "Status");
                printf("------------------------------------------------------------------------------------\n");
                for (int i = 0; i < totalAlunos; i++) {
                    printf("%-10d | %-40s | %5.2f | %5.2f | %6.2f | %s\n",
                           turma[i].matricula,
                           turma[i].nome,
                           turma[i].a1,
                           turma[i].a2,
                           turma[i].media,
                           statusParaString(turma[i].status));
                }
                break;
            }
            case 3: {
                if (totalAlunos == 0) {
                    printf("\nNenhum aluno cadastrado para buscar.\n");
                    break;
                }

                int buscaMatricula;
                printf("\n--- Buscar por Matricula ---\n");
                printf("Digite a matricula: ");
                scanf("%d", &buscaMatricula);
                while (getchar() != '\n');

                int encontrado = -1;
                for (int i = 0; i < totalAlunos; i++) {
                    if (turma[i].matricula == buscaMatricula) {
                        encontrado = i;
                        break;
                    }
                }

                if (encontrado != -1) {
                    printf("\nAluno encontrado:\n");
                    printf("Matricula: %d\n", turma[encontrado].matricula);
                    printf("Nome: %s\n", turma[encontrado].nome);
                    printf("A1: %.2f | A2: %.2f | Media: %.2f\n", turma[encontrado].a1, turma[encontrado].a2, turma[encontrado].media);
                    printf("Status: %s\n", statusParaString(turma[encontrado].status));
                } else {
                    printf("\nnao encontrado\n");
                }
                break;
            }
            case 4: {
                if (totalAlunos == 0) {
                    printf("\nNenhum aluno cadastrado para buscar.\n");
                    break;
                }

                char trecho[41];
                printf("\n--- Buscar por Trecho do Nome ---\n");
                printf("Digite o trecho do nome: ");
                fgets(trecho, sizeof(trecho), stdin);
                trecho[strcspn(trecho, "\n")] = '\0';

                int contadorResultados = 0;
                printf("\nResultados da busca:\n");
                for (int i = 0; i < totalAlunos; i++) {
                    if (strstr(turma[i].nome, trecho) != NULL) {
                        printf("- [%d] %s | Media: %.2f | Status: %s\n",
                               turma[i].matricula, turma[i].nome, turma[i].media, statusParaString(turma[i].status));
                        contadorResultados++;
                    }
                }

                if (contadorResultados == 0) {
                    printf("Nenhum aluno encontrado com esse trecho de nome.\n");
                }
                break;
            }
            case 5: {
                if (totalAlunos == 0) {
                    printf("\nNenhum aluno cadastrado para gerar estatisticas.\n");
                    break;
                }

                int qtdAprovados = 0;
                int qtdRecuperacao = 0;
                int qtdReprovados = 0;
                float somaMedias = 0.0f;

                for (int i = 0; i < totalAlunos; i++) {
                    somaMedias += turma[i].media;
                    if (turma[i].status == APROVADO) {
                        qtdAprovados++;
                    } else if (turma[i].status == RECUPERACAO) {
                        qtdRecuperacao++;
                    } else if (turma[i].status == REPROVADO) {
                        qtdReprovados++;
                    }
                }

                float mediaGeral = somaMedias / totalAlunos;

                printf("\n--- Estatisticas da Turma ---\n");
                printf("Total de alunos cadastrados: %d / %d\n", totalAlunos, MAX);
                printf("Aprovados: %d\n", qtdAprovados);
                printf("Em Recuperacao: %d\n", qtdRecuperacao);
                printf("Reprovados: %d\n", qtdReprovados);
                printf("Media geral da turma: %.2f\n", mediaGeral);
                break;
            }
            case 0:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Escolha uma opcao entre 0 e 5.\n");
        }
    } while (opcao != 0);

    return 0;
}