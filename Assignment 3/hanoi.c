#include <stdio.h>


void hanoi(int n, int from, int aux, int target) {
    if (n==0) {
        return;
    }

    hanoi(n-1, from, target, aux);
    printf("Move disk ");
    printf("%d", n);
    printf(" from tower ");
    printf("%d", from);
    printf(" to tower ");
    printf("%d", target);
    printf("\n");
    hanoi(n-1, aux, target, from);
}

int main() {
    printf("Hanoi with 3 disks, moving from tower 1 to 3: \n");
    hanoi(3, 1, 2, 3);

    printf("Hanoi with 5 disks: \n");
    hanoi(5, 1, 2, 3);
}