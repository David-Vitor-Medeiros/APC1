#include <stdio.h>

// Definição das constantes de preço
#define PRECO_REFEICAO 12.50
#define PRECO_CAFE 4.00

int main() {
    // Declaração de variáveis
    int qtd_refeicoes = 0;
    int qtd_cafes = 0;
    float valor_disponivel = 0.0f;
    float gasto_refeicoes = 0.0f;
    float gasto_cafes = 0.0f;
    float gasto_total = 0.0f;
    float saldo_restante = 0.0f;
    float percentual_usado = 0.0f;

    // Leitura dos dados de entrada
    printf("Quantidade de refeicoes: ");
    scanf("%d", &qtd_refeicoes);

    printf("Quantidade de cafes: ");
    scanf("%d", &qtd_cafes);

    printf("Valor disponivel no cartao: ");
    scanf("%f", &valor_disponivel);

    // Processamento dos gastos e saldo
    gasto_refeicoes = qtd_refeicoes * PRECO_REFEICAO;
    gasto_cafes = qtd_cafes * PRECO_CAFE;
    gasto_total = gasto_refeicoes + gasto_cafes;
    saldo_restante = valor_disponivel - gasto_total;

    // Exibição do relatório de custos
    printf("\nGasto refeicoes: %.2f\n", gasto_refeicoes);
    printf("Gasto cafes: %.2f\n", gasto_cafes);
    printf("Gasto total: %.2f\n", gasto_total);
    printf("Saldo restante: %.2f\n", saldo_restante);

    // --- DESAFIO OPCIONAL (+0,3 bônus) ---
    if (valor_disponivel > 0) {
        percentual_usado = (gasto_total / valor_disponivel) * 100.0f;
        printf("Percentual do cartao utilizado: %.2f%%\n", percentual_usado);
    }

    if (saldo_restante < 0) {
        printf("[AVISO] Saldo insuficiente! Voce ultrapassou o limite do cartao.\n");
    }

    return 0;
}