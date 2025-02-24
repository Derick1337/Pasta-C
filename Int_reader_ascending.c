#include <stdio.h>

int main() {
    int num1;


    scanf("%d", &num1);
    int num_centena = num1/100;
    int num_dezena = (num1/10) % 10;
    int num_unidade = num1%10;


    if (num_centena < num_dezena && num_dezena < num_unidade) {
        printf("ASCENDING\n");
    } else {
        printf("NOT ASCENDING\n");
    }

    return 0;
}