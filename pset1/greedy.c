#include <stdio.h>
#include <cs50.h>
#include <math.h>

int countCoins(int changeCents, int denomination);
int getChangeCents();


int main(void) 
{
    int changeCents = getChangeCents();
    int denominations[4] = {25, 10, 5, 1};
    int remainingChangeCents = changeCents;
    int coinCounter = 0;
    for (int i = 0; i < 4; i++) {
        int numCoins = countCoins(remainingChangeCents, denominations[i]);
        coinCounter += numCoins;
        remainingChangeCents -= numCoins * denominations[i];
    }
    printf("%i\n", coinCounter);
}

int countCoins(int changeCents, int denomination) {
    if (changeCents % denomination == 0) {
        return changeCents / denomination;
    } else {
        return (changeCents - (changeCents % denomination)) / denomination;
    }
}

int getChangeCents() {
    float change;
    do {
        printf("How much change is owed?: ");
        change = get_float();
    } while (change < 0);
    return round(change * 100);
}