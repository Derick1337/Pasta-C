#include <stdio.h>

// Função que multiplica dois números usando apenas somas
int multiplicar_com_soma(int a, int b) {
    int resultado = 0;
    for (int i = 0; i < b; i++) {
        resultado += a;
    }
    return resultado;
}

int main() {
    int n;
    printf("Digite um número inteiro positivo: ");
    scanf("%d", &n);

    int fatorial = 1;

    for (int i = 2; i <= n; i++) {
        fatorial = multiplicar_com_soma(fatorial, i);
    }

    printf("Fatorial de %d (usando apenas somas) = %d\n", n, fatorial);

    return 0;
}
