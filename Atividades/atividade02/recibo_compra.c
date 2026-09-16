/*
 * O scanf("%s") para de ler no primeiro espaco em branco, entao um
 * nome como "Maria Silva Souza" seria cortado em "Maria". Alem disso,
 * scanf("%s") nao limita o tamanho da entrada, podendo causar overflow
 * de buffer. Por isso, uso fgets() para ler o nome do cliente e do
 * produto, pois ele le a linha inteira (com espacos) e recebe o
 * tamanho do buffer como limite. Depois removo o '\n' que o fgets
 * deixa, e limpo o buffer apos os scanf de int/float para nao
 * bagunçar as leituras seguintes.
 */

#include <stdio.h>
#include <string.h>

/* Remove o '\n' final que o fgets deixa na string, se existir */
void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/* Limpa o restante do buffer de entrada até o próximo '\n' (ou EOF) */
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta */
    }
}

int main(void) {
    char nome_cliente[100];
    char nome_produto[100];
    int codigo_produto;
    int quantidade;
    float preco_unitario;
    char categoria;
    float total;

    /* Nome completo do cliente (com espacos) */
    printf("Nome completo do cliente: ");
    fgets(nome_cliente, sizeof(nome_cliente), stdin);
    remove_newline(nome_cliente);

    /* Codigo do produto (inteiro) */
    printf("Codigo do produto: ");
    scanf("%d", &codigo_produto);
    limpar_buffer(); /* limpa o '\n' deixado pelo scanf antes do proximo fgets */

    /* Nome do produto (pode ter espacos) */
    printf("Nome do produto: ");
    fgets(nome_produto, sizeof(nome_produto), stdin);
    remove_newline(nome_produto);

    /* Quantidade (inteiro > 0) */
    do {
        printf("Quantidade (> 0): ");
        scanf("%d", &quantidade);
        limpar_buffer();
        if (quantidade <= 0) {
            printf("Quantidade invalida! Digite um valor maior que zero.\n");
        }
    } while (quantidade <= 0);

    /* Preco unitario (float) */
    printf("Preco unitario: ");
    scanf("%f", &preco_unitario);
    limpar_buffer();

    /* Categoria (A, B ou C) - lida com cuidado apos numeros/strings */
    printf("Categoria (A/B/C): ");
    scanf(" %c", &categoria); /* o espaco antes de %c descarta espacos/\n pendentes */
    limpar_buffer();

    /* Calculo do total */
    total = quantidade * preco_unitario;

    /* Impressao do recibo formatado */
    printf("\n========================================\n");
    printf("           RECIBO DE COMPRA\n");
    printf("========================================\n");
    printf("%-10s: %s\n", "Cliente", nome_cliente);
    printf("%-10s: %s\n", "Produto", nome_produto);
    printf("%-10s: %d\n", "Codigo", codigo_produto);
    printf("%-10s: %c\n", "Categoria", categoria);
    printf("%-10s: %d\n", "Qtd", quantidade);
    printf("%-10s: R$ %.2f\n", "Unitario", preco_unitario);
    printf("%-10s: R$ %.2f\n", "Total", total);
    printf("========================================\n");

    return 0;
}