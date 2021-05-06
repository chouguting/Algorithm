#include <string.h>
#include <malloc.h>
#include"stdio.h"


typedef struct {
    int value;
    int nextX;
    int nextY;
} element;
element **theMatrix;

void LCS(char *str1, char *str2) {
    int height = strlen(str1);
    int width = strlen(str2);
    theMatrix = (element **) malloc(sizeof(element *) * (height + 1));
    for (int i = 0; i <= height; i++) {
        theMatrix[i] = (element *) malloc(sizeof(element) * (width + 1));
        element temp = {0, i, 0};
        theMatrix[i][0] = temp;
    }
    for (int i = 0; i <= width; i++) {
        element temp = {0, 0, i};
        theMatrix[0][i] = temp;
    }
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                element temp = {theMatrix[i - 1][j - 1].value + 1, i - 1, j - 1};
                theMatrix[i][j] = temp;
            } else if (theMatrix[i - 1][j].value >= theMatrix[i][j - 1].value) {
                element temp = {theMatrix[i - 1][j].value, i - 1, j};
                theMatrix[i][j] = temp;
            } else {
                element temp = {theMatrix[i][j - 1].value, i, j - 1};
                theMatrix[i][j] = temp;
            }
        }
    }
}

void printLCS(int *counter, int i, int j) {
    if (i == 0 || j == 0)return;
    if (theMatrix[i][j].nextX == i - 1 && theMatrix[i][j].nextY == j - 1) {
        printLCS(counter, i - 1, j - 1);
        *counter += 1;
    } else if (theMatrix[i][j].nextX == i - 1) {
        printLCS(counter, i - 1, j);
    } else {
        printLCS(counter, i, j - 1);
    }
}


int main() {
    char str1[20001];
    char str2[20001];

    scanf("%s", str1);
    scanf("%s", str2);
    LCS(str1, str2);
    int counter = 0;
    printLCS(&counter, strlen(str1), strlen(str2));
    printf("%d\n", counter);
    return 0;
}
