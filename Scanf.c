#include <stdio.h>
#include <stdlib.h>
/*
int main(){
        int idade = 0;
        printf("Valor incial da idade : %d.\n", idade);

        printf("Digite uma idade: \n");
        scanf("%d", &idade);

        printf("Idade informada: %d.\n", idade);
    return 0;
} */
/* int main(){
    int idade = 0;
    int ano = 1945;

    printf("Diite uma idade e ano: \n");
    scanf("%d %d",&idade, &ano);
    printf("Idade informada: %d.\n", idade);
    printf("Ano informado: %d.\n", ano);


    return 0;
} */
int main(){
    float peso = 0.0;
    int idade = 0;
    printf("Digite uma idade: \n");
    scanf("%d", &idade);
    printf("Digite seu peso: \n");
    scanf("%f", &peso);

    printf("Sua idade eh %d e seu peso eh %.3f", idade, peso);
}