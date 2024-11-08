#include <stdio.h>
#include <stdlib.h>

/* int main(){

    char s[10];
    printf("Voce esta usando o scanf padrao digite sua frase: \n");
    scanf("%s",s);
    fflush(stdin);

    printf("Resultado %s\n\n",s);

    printf("Digite algo scanf condicionado: \n");
    scanf("%9[^\n]s",s);
    printf("Resultado %s\n\n",s);
} */
int main(){

    char s[10];
    printf("Coloque sua frase \n");
    fgets(s,10,stdin);
    fflush(stdin);/*
    printf("%s",s); */
    puts("Resultado:");
    puts(s);
    puts("");
} 