#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 50

// Estrutura de um nó da árvore de Huffman
struct MinHNode {
    char item;                  // Caractere armazenado no nó
    unsigned freq;              // Frequência do caractere
    struct MinHNode *left, *right; // Ponteiros para subárvores esquerda e direita
};

// Estrutura da min-heap usada na construção da árvore
struct MinHeap {
    unsigned size;             // Tamanho atual da heap
    unsigned capacity;         // Capacidade máxima da heap
    struct MinHNode **array;   // Array de ponteiros para nós da heap
};

// Cria um novo nó com caractere e frequência
struct MinHNode *newNode(char item, unsigned freq) {
    struct MinHNode *temp = (struct MinHNode *)malloc(sizeof(struct MinHNode));
    temp->left = temp->right = NULL;
    temp->item = item;
    temp->freq = freq;
    return temp;
}

// Cria uma nova min-heap com capacidade dada
struct MinHeap *createMinH(unsigned capacity) {
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHNode **)malloc(capacity * sizeof(struct MinHNode *));
    return minHeap;
}

// Troca dois ponteiros de nós
void swapMinHNode(struct MinHNode **a, struct MinHNode **b) {
    struct MinHNode *t = *a;
    *a = *b;
    *b = t;
}

// Mantém a propriedade de min-heap recursivamente
void minHeapify(struct MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < (int)minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < (int)minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Verifica se a heap tem apenas um elemento
int checkSizeOne(struct MinHeap *minHeap) {
    return (minHeap->size == 1);
}

// Remove o nó com menor frequência da heap
struct MinHNode *extractMin(struct MinHeap *minHeap) {
    struct MinHNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Insere um novo nó na heap
void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    // Move o novo nó até a posição correta
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Constroi a min-heap a partir dos nós existentes
void buildMinHeap(struct MinHeap *minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Verifica se o nó é uma folha (sem filhos)
int isLeaf(struct MinHNode *root) {
    return !(root->left) && !(root->right);
}

// Cria heap e insere nós com caracteres e suas frequências
struct MinHeap *createAndBuildMinHeap(char item[], int freq[], int size) {
    struct MinHeap *minHeap = createMinH(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(item[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// Constrói a árvore de Huffman
struct MinHNode *buildHuffmanTree(char item[], int freq[], int size) {
    struct MinHNode *left, *right, *top;
    struct MinHeap *minHeap = createAndBuildMinHeap(item, freq, size);

    while (!checkSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// Armazena os códigos de Huffman em uma tabela
void storeCodes(struct MinHNode *root, int arr[], int top, char *charCodes[]) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, charCodes);
    }
    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, charCodes);
    }
    if (isLeaf(root)) {
        // Se não houve nenhum bit atribuído, ou seja, só um caractere na árvore
        if (top == 0) {
            char *code = (char *)malloc(2); // Espaço para "0" + '\0'
            code[0] = '0';
            code[1] = '\0';
            charCodes[(unsigned char)root->item] = code;
        } else {
            char *code = (char *)malloc(top + 1);
            for (int i = 0; i < top; ++i)
                code[i] = arr[i] + '0';
            code[top] = '\0';
            charCodes[(unsigned char)root->item] = code;
        }
    }
    
}

int main() {
    char input[1000];
    int freq[256] = {0};
    char *charCodes[256] = {NULL};

    printf("Digite uma frase: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove '\n' do final

    // Conta a frequência de cada caractere na entrada
    for (int i = 0; input[i] != '\0'; i++) {
        freq[(unsigned char)input[i]]++;
    }

    // Prepara arrays de caracteres únicos e suas frequências
    char uniqueChars[256];
    int uniqueFreqs[256];
    int n = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            uniqueChars[n] = (char)i;
            uniqueFreqs[n] = freq[i];
            n++;
        }
    }

    // Constrói a árvore de Huffman
    struct MinHNode *root = buildHuffmanTree(uniqueChars, uniqueFreqs, n);

    // Armazena os códigos em tabela
    int arr[MAX_TREE_HT];
    storeCodes(root, arr, 0, charCodes);

    // Imprime a tabela de códigos
    printf("\nChar | Huffman Code\n");
    printf("--------------------\n");
    for (int i = 0; i < n; i++) {
        char c = uniqueChars[i];
        printf("  %c   | %s\n", c, charCodes[(unsigned char)c]);
    }
    

    // Imprime a string codificada
    printf("\nFrase codificada (Huffman):\n");
    for (int i = 0; input[i] != '\0'; i++) {
        printf("%s", charCodes[(unsigned char)input[i]]);
    }
    printf("\n");

    // Libera a memória alocada para os códigos
    for (int i = 0; i < 256; i++) {
        if (charCodes[i]) {
            free(charCodes[i]);
        }
    }

    return 0;
}