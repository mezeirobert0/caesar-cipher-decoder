#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "functions.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// Function for reading the distribution of letters in an alphabet, from the file distribution.txt
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

// Function for reading the encoded message, from the file input.txt
void readInputFromFile(string &input)
{
    input = "";
    ifstream fin("input.txt");
    char c;
    while (fin.get(c))
        input += c;
    fin.close();
}

// Function for computing the frequency of each letter in the current message
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

// function for computing the chi squared distance between the distribution of letters in the aplhabet
// and the current frequency of letters in the current message
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

// Function that successfully decodes Caesar's cipher
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

// Functions for printing to console the options available to the end user
void print_options()
{
    string options[5];
    options[0] = "0. View options";
    options[1] = "1. Print frequency of letters in current text";
    options[2] = "2. Print distribution of letters in current text";
    options[3] = "3. Decode the text and print the most likely message";
    options[4] = "4. Add a new encoded message(read from keyboard)";

    for (string option : options)
        cout << option << '\n';
    cout << '\n';
}

// Function that enables the user to interact with the functions the program provides
void run_console()
{
    double distribution[26];
    int frequency[26];

    string text;
    string decodedText;

    bool computedFrequency = false;
    bool decoded = false;

    readDistributionFromFile(distribution);
    readInputFromFile(text);

    cout << "Welcome to Caesar's Cipher application!\n\n";

    print_options();
    while (true)
    {
        string opt;
        cout << "Choose an option (0-5): ";
        cin >> opt; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards the rest of the line 
        cout << '\n';

        if (opt == "0")
            print_options();

        else if (opt == "1")
        {
            if (!computedFrequency)
            {
                computeFrequency(text, frequency);
                computedFrequency = true;
            }

            cout << "Frequency of letters in text:\n";
            for (short i = 0; i < 26; i++)
                cout << (char)(i + 65) << ' ' << frequency[i] << '\n';

            cout << '\n';
        }

        else if (opt == "2")
        {
            if (!computedFrequency)
            {
                computeFrequency(text, frequency);
                computedFrequency = true;
            }

            int numberOfLetters = text.size();
            for (char ch : text)
                if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')))
                    numberOfLetters--;


            cout << "Distribution of letters in text (%):\n";
            for (short i = 0; i < 26; i++)
                cout << (char)(i + 65) << ' ' << fixed << setprecision(2) << frequency[i] * 100.0 / numberOfLetters << '\n';

            cout << '\n';
        }

        else if (opt == "3")
        {
            if (!computedFrequency)
            {
                computeFrequency(text, frequency);
                computedFrequency = true;
            }

            if (!decoded)
            {
                decodedText = getDecodedText(text, distribution);
                decoded = true;
            }

            cout << "Decoded text:\n" << decodedText << "\n\n";
        }

        else if (opt == "4")
        {
            computedFrequency = false;
            decoded = false;

            cout << "Enter the encoded message (no enters):\n";
            getline(cin, text);
            cout << '\n';
        }

        else if (opt == "exit" || opt == "close")
            break;

        else cout << "Invalid option!\n\n";
    }
}