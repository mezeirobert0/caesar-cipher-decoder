#pragma once
using namespace std;

void readDistributionFromFile(double distribution[26]);
void readInputFromFile(string &input);
void computeFrequency(string input, int frequency[26]);
double computeChiSquared(string input, double distribution[26], int frequency[26]);
string getDecodedText(string input, double distribution[26]);