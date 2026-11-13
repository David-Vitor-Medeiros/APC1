/*
 * O operador ternario foi mais vantajoso no calculo do bonus de pontualidade
 * por permitir uma atribuicao condicional simples e direta em uma unica linha.
 * Já o if aninhado tornou-se indispensavel na analise do desconto base, pois a
 * verificacao da media academica depende estritamente do contexto da faixa
 * social previamente classificada, tornando inviavel resolver a regra de negocio
 * com apenas uma estrutura condicional simples sem duplicar codigos ou condicoes.
 */

#include <stdio.h>

int main() {
    char nome[100];
    int idade;
    float renda, media;
    char pontual;

    // Leitura de dados conforme especificação
    printf("Digite o nome completo do aluno: ");
    fgets(nome, sizeof(nome), stdin);

    // Remoção manual da quebra de linha do fgets sem bibliotecas externas
    int i = 0;
    while (nome[i] != '\0') {
        if (nome[i] == '\n') {
            nome[i] = '\0';
            break;
        }
        i++;
    }

    printf("Digite a idade do aluno: ");
    scanf("%d", &idade);

    printf("Digite a renda familiar mensal (R$): ");
    scanf("%f", &renda);

    printf("Digite a media academica (0.0 a 10.0): ");
    scanf("%f", &media);

    printf("Status de pontualidade no pagamento (S/N): ");
    scanf(" %c", &pontual);

    // 1. Validação de Entrada (if / if-else)
    if (idade < 16 || renda <= 0) {
        printf("\nErro: Idade invalida ou renda nula/negativa. Analise encerrada.\n");
        return 1;
    }

    char *faixa;
    float descontoBase = 0.0f;

    // 2. Classificação da Faixa Social (if-else-if)
    // 3. Análise de Desconto Acadêmico (if Aninhado)
    if (renda <= 2000.0f) {
        faixa = "Faixa A";
        if (media >= 8.5f) {
            descontoBase = 50.0f;
        } else {
            descontoBase = 30.0f;
        }
    } else if (renda <= 5000.0f) {
        faixa = "Faixa B";
        if (media >= 9.0f) {
            descontoBase = 25.0f;
        } else {
            descontoBase = 10.0f;
        }
    } else {
        faixa = "Faixa C";
        if (media >= 9.5f) {
            descontoBase = 10.0f;
        } else {
            descontoBase = 0.0f;
        }
    }

    // 4. Bônus de Pontualidade (Operador Ternário ?:)
    float bonusPontual = (pontual == 'S' || pontual == 's') ? 5.0f : 0.0f;

    // 5. Cálculo Final
    float descontoTotal = descontoBase + bonusPontual;

    // Exibição formatada estritamente conforme o exemplo das instruções
    printf("\n========================================\n");
    printf("    SISTEMA DE AVALIAÇÃO DE DESCONTO    \n");
    printf("========================================\n");
    printf("Aluno         : %s\n", nome);
    printf("Faixa Social  : %s\n", faixa);
    printf("Média         : %.2f\n", media);
    printf("Desconto Base : %.1f%%\n", descontoBase);
    printf("Bônus Pontual : %.1f%%\n", bonusPontual);
    printf("----------------------------------------\n");
    printf("Desconto Total: %.1f%%\n", descontoTotal);
    
    if (descontoTotal > 0.0f) {
        printf("Status        : APROVADO PARA BOLSA\n");
    } else {
        printf("Status        : NAO ELEGIVEL PARA BOLSA\n");
    }
    printf("========================================\n");

    return 0;
}