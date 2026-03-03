#include <stdio.h>

// Definindo uma enumeração para representar os dias da semana
enum DiasDaSemana {
    DOMINGO,
    SEGUNDA,
    TERCA,
    QUARTA,
    QUINTA,
    SEXTA,
    SABADO
};

int main() {
    // Declarando uma variável do tipo enum DiasDaSemana
    enum DiasDaSemana dia = QUARTA;

    // Exibindo o dia da semana
    switch (dia) {
        case DOMINGO:
            printf("Domingo\n");
            break;
        case SEGUNDA:
            printf("Segunda-feira\n");
            break;
        case TERCA:
            printf("Terça-feira\n");
            break;
        case QUARTA:
            printf("Quarta-feira\n");
            break;
        case QUINTA:
            printf("Quinta-feira\n");
            break;
        case SEXTA:
            printf("Sexta-feira\n");
            break;
        case SABADO:
            printf("Sábado\n");
            break;
        default:
            printf("Dia inválido\n");
    }

    return 0;
}
