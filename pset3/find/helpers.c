/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

bool binarySearch(int value, int values[], int low, int high);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // If list is empty, return false
    if (n < 1)
    {
        return false;
    }
    // Else search list
    return binarySearch(value, values, 0, n - 1);
}


bool binarySearch(int value, int values[], int low, int high)
{
    // If list exhausted, return false
    if (low > high)
    {
        return false;
    }
    
    // Set middle
    int middle = (low + high) / 2;
    
    // If middle is value, return true
    if (values[middle] == value)
    {
        return true;
    }
    // If middle too high, search first half
    else if (values[middle] > value)
    {
        return binarySearch(value, values, 0, middle - 1);
    }
    // If middle too low, search second half
    else
    {
        return binarySearch(value, values, middle + 1, high);
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int valuesCount[65536];
    // Initialize each index of valuesCount to 0
    for (int i = 0; i < 65535; i++)
    {
        valuesCount[i] = 0;
    }
    // Iterate through values[] and record counts in valuesCount
    for (int i = 0; i < n; i++)
    {
        valuesCount[values[i]]++;
    }
    // Iterate through original array and replace values in sorted order
    int valuesIndex = 0;
    for (int i = 0; i < 65535; i++)
    {
        while (valuesCount[i] > 0)
        {
            values[valuesIndex] = i;
            valuesCount[i]--;
            valuesIndex++;
        }
    }
}
