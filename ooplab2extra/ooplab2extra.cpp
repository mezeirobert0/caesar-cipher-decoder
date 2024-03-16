#include <iostream>
#include "functions.h"
using namespace std;

int main()
{
    double distribution[26];
    readDistributionFromFile(distribution);

    string text;
    readInputFromFile(text);

    cout << getDecodedText(text, distribution) << '\n';

    return 0;
}
