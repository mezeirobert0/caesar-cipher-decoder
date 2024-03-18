# Caesar's Cipher decoder

This is a console app for decoding messages that have been encoded with Caesar's Cipher. \
The program uses a brute force method, using frequency analysis, that tests all the possible displacements and returns the most likely decryption of a text.

## Pre-requisites
* C/C++ compiler (e.g. MinGW GCC, MSVC, Clang) or an IDE (e.g. Visual Studio)
* Git 

## Installation

Open the terminal, navigate to the desired location of the project using `cd` and clone the repository using the following command:

```bash
git clone https://github.com/mezeirobert0/ooplab2extra.git
```

## Running the app

### Visual Studio

Double-click on `ooplab2extra.sln` after opening the folder of the project

### Terminal

* First time: open the folder `..\ooplab2extra\ooplab2extra` in terminal (or navigate to it using `cd`) and run the following command:
```bash
gcc -o app.exe ooplab2extra.cpp functions.cpp -lstdc++
```
`-lstdc++` is optional; add it if the program doesn't compile otherwise.

* In the command line, run the program using:
```bash
.\app
```

## Using the app

While the program is running, the user is provided with 5 options to interact with the app:
```
Welcome to Caesar's Cipher application!

0. View options
1. Print frequency of letters in current text
2. Print distribution of letters in current text
3. Decode the text and print the most likely message
4. Add a new encoded message (read from keyboard)
```
The user is able to then input a number from 0 to 4:
```
Choose an option (0-5): 3
```
By default the encoded text is in the file `input.txt`. Therefore, to decode a new message, the user can either modify `input.txt`, or they can choose option `4` in order to set the encoded text to whatever they choose. \
\
Should the user enter anything except a number from 0 to 4, they are prompted with the message `Invalid option!` and are given a new chance to enter an option.

Also, when writing `close` or `exit` when asked to choose an option, the program terminates.