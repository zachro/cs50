#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Minutes: ");
    int showerLength = get_int();
    printf("Bottles: %i\n", showerLength * 12);
}