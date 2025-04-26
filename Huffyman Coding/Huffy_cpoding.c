#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 50

typedef struct HuffmanNode {
    char item;
    int freq;          
    struct HuffmanNode *left, *right;
} HuffmanNode;

HuffmanNode* newNode(char item, int freq) {
    HuffmanNode *node = (HuffmanNode*) malloc(sizeof(HuffmanNode));
    node->item = item;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

int FindMinIndex(HuffmanNode* nodes[], int count) {
    int minIndex = 0;
    for (int i = 1; i < count; i++) {
        if (nodes[i]->freq < nodes[minIndex]->freq) {
            minIndex = i;
        }
    }
    return minIndex;
}

void RemoveAt(HuffmanNode* nodes[], int *count, int index) {
    for (int i = index; i < (*count) - 1; i++) {
        nodes[i] = nodes[i + 1];
    }
    (*count)--;
}

void GenerateCodes(HuffmanNode *node, char code[], int top, char codes[256][MAX_TREE_HT + 1]) {
    if (!node)
        return;
    
    if (node->left) {
        code[top] = '0';
        GenerateCodes(node->left, code, top + 1, codes);
    }
    
    if (node->right) {
        code[top] = '1';
        GenerateCodes(node->right, code, top + 1, codes);
    }

    if (node->left == NULL && node->right == NULL) {
        code[top] = '\0'; 
        
        strcpy(codes[(int)node->item], code);
    }
}

int main() {
    char input[1024];
    printf("Digite uma string para codificação Huffman:\n");
    if (!fgets(input, sizeof(input), stdin)) {
        printf("Erro na leitura da entrada.\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    int len = strlen(input);
    
    
    int charFrequencies[256] = {0};
    for (int i = 0; i < len; i++) {
        unsigned char ch = input[i];
        charFrequencies[ch]++;
    }
    
    
    HuffmanNode *nodes[256];
    int nodeCount = 0;
    for (int i = 0; i < 256; i++) {
        if (charFrequencies[i] > 0) {
            nodes[nodeCount++] = newNode((char)i, charFrequencies[i]);
        }
    }
    

    while (nodeCount > 1) {
        int minIndex1 = FindMinIndex(nodes, nodeCount);
        HuffmanNode *leftNode = nodes[minIndex1];
        RemoveAt(nodes, &nodeCount, minIndex1);
        
        int minIndex2 = FindMinIndex(nodes, nodeCount);
        HuffmanNode *rightNode = nodes[minIndex2];
        RemoveAt(nodes, &nodeCount, minIndex2);
        
        
        HuffmanNode *newInternalNode = newNode('$', leftNode->freq + rightNode->freq);
        newInternalNode->left = leftNode;
        newInternalNode->right = rightNode;
        
        
        nodes[nodeCount++] = newInternalNode;
    }
    
    HuffmanNode *huffmanTree = nodes[0];
    

    char codes[256][MAX_TREE_HT + 1] = {{0}};
    char codeBuffer[MAX_TREE_HT + 1];
    
    
    if (huffmanTree->left == NULL && huffmanTree->right == NULL) {
        strcpy(codes[(int)huffmanTree->item], "0");
    } else {
        GenerateCodes(huffmanTree, codeBuffer, 0, codes);
    }
    
    
    printf("\nChar | Huffman Code\n");
    printf("--------------------\n");
    for (int i = 0; i < 256; i++) {
        if (codes[i][0] != '\0') {
            printf("  %c  |  %s\n", i, codes[i]);
        }
    }
    
    
    printf("\nString codificada:\n");
    for (int i = 0; i < len; i++) {
        printf("%s", codes[(int)input[i]]);
    }
    printf("\n");
    
    
    return 0;
}
