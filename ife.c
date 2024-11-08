#include <stdio.h>

/* int main(){
    float m;
    printf("Insira a nota: \n");
    scanf("%f", &m);

    if(m>=7.0){
        printf("Aprovado \n");
    }
    else{
        printf("Reprovado \n");
    }
    return 0;
} */
int main(){
    float m;
    printf("Insira a nota: \n");
    scanf("%f",&m);

    if(m>=7.0 && m<=10.0){
        printf("Aprovado");
    }
    if(m<7.0 && m>=2.4){
        printf("Exame");
    }
    if(m>10.0){
        printf("Erro valor acima do maximo");
    }
    if(m<2.4){
        printf("Reprovado");
    }
    return 0;
}