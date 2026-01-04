#include <stdio.h>

typedef struct {
    int row;
    int col;
    int value;
} Term;

int main() {
    int r, c;
    int matrix[50][50];
    Term sparse[250];
    int i, j;
    int k = 0;

    printf("Rows, Cols: ");
    scanf("%d %d", &r, &c);

    printf("Enter matrix:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (matrix[i][j] != 0) {
                sparse[k].row = i;
                sparse[k].col = j;
                sparse[k].value = matrix[i][j];
                k++;
            }
        }
    }

    printf("\nSparse (row col value):\n");
    for (i = 0; i < k; i++) {
        printf("%d %d %d\n", sparse[i].row, sparse[i].col, sparse[i].value);
    }

    return 0;
}

