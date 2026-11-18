 /*:
 * O fall-through consciente foi mais vantajoso nos agrupamentos dos serviços (cases 1, 2 e 3; cases 4 e 5) 
 * e nos dias de expediente (cases 2, 3, 4 e 5; cases 1 e 7), além das prioridades maiúsculas/minúsculas. 
 * Ele evitou a duplicação desnecessária de código, centralizando atribuições de categoria, prazo, taxa 
 * e tipo de expediente em um único bloco central. O switch não substitui o if-else-if na classificação 
 * por faixas de renda porque o switch opera apenas sobre valores exatos e constantes discretas (int ou char), 
 * enquanto faixas de renda exigem avaliações de intervalos contínuos e comparações relacionais (ex: >= ou <=).
 */

#include <stdio.h>

int main(void) {
    int codigo_servico;
    char prioridade_char;
    int dia_semana;

    // Declaração das variáveis para armazenar as informações do relatório
    const char *nome_servico = "";
    const char *categoria = "";
    int prazo_dias = 0;
    float taxa_base = 0.0f;
    const char *status_servico = "";

    const char *nome_prioridade = "";
    int guiche = 0;
    float acrescimo = 0.0f;

    const char *nome_dia = "";
    const char *expediente = "";

    float taxa_final = 0.0f;

    // Leitura dos dados de entrada
    printf("Digite o codigo do servico (1 a 6): ");
    scanf("%d", &codigo_servico);

    printf("Digite a prioridade do atendimento (U/u, N/n, B/b): ");
    scanf(" %c", &prioridade_char);

    printf("Digite o dia da semana (1 a 7): ");
    scanf("%d", &dia_semana);

    // 1. Switch de Serviço (int com fall-through de agrupamento)
    switch (codigo_servico) {
        case 1:
            nome_servico = "Historico escolar";
            /* fall-through */
        case 2:
            switch (codigo_servico) {
                case 2: nome_servico = "Declaracao de matricula"; break;
                default: break;
            }
            /* fall-through */
        case 3:
            switch (codigo_servico) {
                case 3: nome_servico = "Declaracao de vinculo"; break;
                default: break;
            }
            categoria = "Documento simples";
            prazo_dias = 2;
            taxa_base = 15.00f;
            status_servico = "ACEITO";
            break;

        case 4:
            nome_servico = "Trancamento";
            /* fall-through */
        case 5:
            switch (codigo_servico) {
                case 5: nome_servico = "Cancelamento"; break;
                default: break;
            }
            categoria = "Interrupcao de vinculo";
            prazo_dias = 10;
            taxa_base = 0.00f;
            status_servico = "ACEITO";
            break;

        case 6:
            nome_servico = "Colacao de grau";
            categoria = "Ato solene";
            prazo_dias = 15;
            taxa_base = 80.00f;
            status_servico = "ACEITO";
            break;

        default:
            nome_servico = "Codigo invalido";
            categoria = "N/A";
            prazo_dias = 0;
            taxa_base = 0.00f;
            status_servico = "RECUSADO";
            break;
    }

    // 2. Switch de Prioridade (char com fall-through para maiúsculas e minúsculas)
    switch (prioridade_char) {
        case 'U':
        /* fall-through */
        case 'u':
            nome_prioridade = "Urgente";
            guiche = 1;
            acrescimo = 10.00f;
            break;

        case 'N':
        /* fall-through */
        case 'n':
            nome_prioridade = "Normal";
            guiche = 2;
            acrescimo = 0.00f;
            break;

        case 'B':
        /* fall-through */
        case 'b':
            nome_prioridade = "Balcao";
            guiche = 3;
            acrescimo = 0.00f;
            break;

        default:
            nome_prioridade = "Invalida";
            guiche = 0;
            acrescimo = 0.00f;
            break;
    }

    // 3. Switch do Nome do Dia (int, sem fall-through: break em todo case)
    switch (dia_semana) {
        case 1:
            nome_dia = "Domingo";
            break;
        case 2:
            nome_dia = "Segunda-feira";
            break;
        case 3:
            nome_dia = "Terca-feira";
            break;
        case 4:
            nome_dia = "Quarta-feira";
            break;
        case 5:
            nome_dia = "Quinta-feira";
            break;
        case 6:
            nome_dia = "Sexta-feira";
            break;
        case 7:
            nome_dia = "Sabado";
            break;
        default:
            nome_dia = "Dia invalido";
            break;
    }

    // 4. Switch de Expediente (int com fall-through de agrupamento)
    switch (dia_semana) {
        case 2:
        /* fall-through */
        case 3:
        /* fall-through */
        case 4:
        /* fall-through */
        case 5:
            expediente = "Pleno";
            break;

        case 6:
            expediente = "Reduzido";
            break;

        case 1:
        /* fall-through */
        case 7:
            expediente = "Fechado";
            break;

        default:
            expediente = "Dia invalido";
            break;
    }

    // Cálculo final direto (sem condicionais)
    taxa_final = taxa_base + acrescimo;

    // Saída formatada
    printf("===========================================\n");
    printf("TRIAGEM DE PROTOCOLO ACADEMICO\n");
    printf("Servico            : %s\n", nome_servico);
    printf("Categoria          : %s\n", categoria);
    printf("Prazo              : %d dias uteis\n", prazo_dias);
    printf("Taxa base          : R$ %.2f\n", taxa_base);
    printf("Prioridade         : %s\n", nome_prioridade);
    printf("Guiche             : %d\n", guiche);
    printf("Acrescimo          : R$ %.2f\n", acrescimo);
    printf("Dia                : %s\n", nome_dia);
    printf("Expediente         : %s\n", expediente);
    printf("Taxa final         : R$ %.2f\n", taxa_final);
    printf("Status do servico  : %s\n", status_servico);
    printf("===========================================\n");

    return 0;
}