#include <stdio.h>

void hanoi(int n, char from, char aux, char to) {
    if (n == 0)
        return;

    hanoi(n - 1, from, to, aux);
    printf("Move disk %d from %c to %c\n", n, from, to);
    hanoi(n - 1, aux, from, to);
}

int main() {
    int n;

    printf("Number of disks: ");
    scanf("%d", &n);

    hanoi(n, 'A', 'B', 'C');

    return 0;
}

