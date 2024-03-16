#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "functions.h"
#include <cstring>
using namespace std;

void readDistributionFromFile(double arr[26])
{
    ifstream fin("distribution.txt");
    for (short i = 0; i < 26; i++)
    {
        char letter;
        fin >> letter;
        fin >> arr[(int)letter - 65];
    }
    fin.close();
}

void readInputFromFile(char input[1001])
{
    ifstream fin("input.txt");
    fin.getline(input, 1001);
    fin.close();
}

void computeFrequency(char input[1001], int arr[26])
{
    // A - 65, a - 97
    for (short i = 0; i < 26; i++)
        arr[i] = 0;
    
    for (short i = 0; input[i] != '\0'; i++)
    {
        if (input[i] >= 'A' && input[i] <= 'Z')
            arr[(int)input[i] - 65]++;
        else if (input[i] >= 'a' && input[i] <= 'z')
            arr[(int)input[i] - 97]++;
    }
}

double computeChiSquared(int inputLen, double distribution[26], int frequency[26])
{
    double result = 0;
    for (short i = 0; i < 26; i++)
    {
        double expected = distribution[i] * inputLen;
        result += (expected - frequency[i]) * (expected - frequency[i]) / expected;
    }

    return result;
}

void getDecodedText(char input[1001], double distribution[26])
{
    char bestDecodedText[1001];
    double minChiSquared = -1;
    int inputLen = strlen(input);

    for (int step = 0; step < 25; step++)
    {
        for (int i = 0; input[i] != '\0'; i++)
            if ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z'))
            {
                if (input[i] == 'A')
                    input[i] = 'Z';

                else if (input[i] == 'a')
                    input[i] = 'z';

                else input[i]--;
            }

        int currentFrequency[26];
        computeFrequency(input, currentFrequency);

        double currentChiSquared = computeChiSquared(inputLen, distribution, currentFrequency);

        if (minChiSquared == -1 || currentChiSquared < minChiSquared)
        {
            minChiSquared = currentChiSquared;
            strcpy(bestDecodedText, input);
        }
        
    }

    strcpy(input, bestDecodedText);
}