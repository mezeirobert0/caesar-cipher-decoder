#pragma once
using namespace std;

void readDistributionFromFile(double arr[26]);
void readInputFromFile(char input[1001]);
void computeFrequency(char input[1001], int arr[26]);
double computeChiSquared(int inputLen, double distribution[26], int frequency[26]);
void getDecodedText(char input[1001], double distribution[26]);