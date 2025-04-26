#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int main() {
    FILE *fp;
    FILE *fp_out;
    char buffer[512]; // aumentei o buffer para mais segurança
    double tempo_total = 0;
    int qtd_pings = 0;
    time_t inicio = time(NULL);

    fp_out = fopen("saida.txt", "w");
    if (fp_out == NULL) {
        perror("Erro ao criar o arquivo de saída");
        exit(1);
    }
    int i = 0;
    while (time(NULL) - inicio < 60) {
#ifdef _WIN32
        fp = popen("ping -n 1 -w 1000 200.19.254.176", "r");
#else
        fp = popen("ping -c 1 -W 1 8.8.8.8", "r");
#endif
        if (fp == NULL) {
            perror("Erro ao executar o comando ping");
            exit(1);
        }

        
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            char *ptr = strstr(buffer, "tempo=");
            if (!ptr) {
                ptr = strstr(buffer, "time=");
            }
            if (ptr) {
                // Agora procura o número depois de "tempo=" ou "time="
                double tempo;
                // pula para depois do '='
                ptr = strchr(ptr, '=');
                if (ptr != NULL) {
                    ptr++; // anda um caractere para depois do '='
                    if (sscanf(ptr, "%lf", &tempo) == 1) {
                        tempo_total += tempo;
                        qtd_pings++;
                        i++;
                        fprintf(fp_out, "Ping: %.2f ms\n", tempo);
                        printf("%d Ping: %.2f ms\n", i, tempo);
                    }
                }
            }
        
        }
        pclose(fp);

#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }

    if (qtd_pings > 0) {
        fprintf(fp_out, "\nMedia de ping em 1 minuto: %.2f ms\n", tempo_total / qtd_pings);
        printf("\nMedia de ping em 1 minuto: %.2f ms\n", tempo_total / qtd_pings);
    } else {
        fprintf(fp_out, "\nNenhuma resposta de ping recebida.\n");
        printf("\nNenhuma resposta de ping recebida.\n");
    }

    fclose(fp_out);
    return 0;
}
