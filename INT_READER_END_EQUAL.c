#include <stdio.h>
#include <stdlib.h>

int main() {
    int num1, num2;
    scanf("%d", &num1);
    scanf("%d", &num2);

    if (num1 == num2) {
        printf("EQUAL\n");
    } else {
        printf("NOT EQUAL\n");
    }

    return 0;
}