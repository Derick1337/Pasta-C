#include <stdio.h>
#include <stdlib.h>

/* int main(){
    int v[5];
    v[0] = 50;
    v[1] = 40;
    v[2] = 30;
    v[3] = 20;
    v[4] = 10;

    int m = (v[0] + v[1] + v[2] + v[3] + v[4] /5 );

    printf("Resultado: %i \n", m);
}    */

int main(){

/*     int v[5] = {10,20,30,40,50}; */
    int v[5];
    int j;
    for(j=0;j<5;j++){
        printf("Insira um dado: \n");
        scanf("%d",&v[j]);
}
    int i;
    float s = 0;

    for(i=0;i<5;i++){
        s+=v[i];
    }
    printf("Resultados: %f\n",s/5);


}