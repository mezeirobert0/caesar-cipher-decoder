#include <iostream>
#include "functions.h"
using namespace std;

int main()
{
    double distribution[26];
    readDistributionFromFile(distribution);

    char text[1001];
    readInputFromFile(text);

    int frequency[26];
    computeFrequency(text, frequency);

    return 0;
}
