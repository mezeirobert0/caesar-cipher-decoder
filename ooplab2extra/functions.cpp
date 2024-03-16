#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "functions.h"
#include <string>
using namespace std;

void readDistributionFromFile(double distribution[26])
{
    ifstream fin("distribution.txt");
    for (short i = 0; i < 26; i++)
    {
        char letter;
        fin >> letter;
        fin >> distribution[(int)letter - 65];
    }
    fin.close();
}

void readInputFromFile(string &input)
{
    input = "";
    ifstream fin("input.txt");
    char c;
    while (fin.get(c))
        input += c;
    fin.close();
}

void computeFrequency(string input, int frequency[26])
{
    // A - 65, a - 97
    for (short i = 0; i < 26; i++)
        frequency[i] = 0;
    
    for (char &c : input)
    {
        if (c >= 'A' && c <= 'Z')
            frequency[(int)c - 65]++;
        else if (c >= 'a' && c <= 'z')
            frequency[(int)c - 97]++;
    }
}

double computeChiSquared(string input, double distribution[26], int frequency[26])
{
    int inputLen = input.size();
    double result = 0;
    for (short i = 0; i < 26; i++)
    {
        double expected = distribution[i] * inputLen;
        result += (expected - frequency[i]) * (expected - frequency[i]) / expected;
    }

    return result;
}

string getDecodedText(string input, double distribution[26])
{
    int currentFrequency[26];
    computeFrequency(input, currentFrequency);

    double minChiSquared = computeChiSquared(input, distribution, currentFrequency);
    string bestDecodedText = input;
    
    
    for (int step = 0; step < 25; step++)
    {
        for (char& c : input)
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
            {
                if (c == 'A')
                    c = 'Z';

                else if (c == 'a')
                    c = 'z';

                else c--;
            }

        computeFrequency(input, currentFrequency);

        double currentChiSquared = computeChiSquared(input, distribution, currentFrequency);

        if (minChiSquared == -1 || currentChiSquared < minChiSquared)
        {
            minChiSquared = currentChiSquared;
            bestDecodedText = input;
        }
        
    }

    return bestDecodedText;
}