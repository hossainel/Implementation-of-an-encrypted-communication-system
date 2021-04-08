#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

//please comment the line number 15 and 16 if you get error on send function
using namespace std;

// TODO implement the fonctions sanitize, caesar et send here

//This function is responsible for writing a message on a file.
void send(string fileName, string ENCODED_MESSAGE) {
	string filename = fileName; //remember there is a difference between fileName and fileName
	//Comment the following two line if you get errors on writing files
	if (fileName[0]=='/') filename = fileName.substr(1,fileName.length()); // removes the / before the tmp/f105 instead of /tmp/f105
	else filename = fileName; //use // to comment the previous line and remove the else if you got no probs
	ofstream file (filename, ios_base::app);
    if (file.is_open ()) {
        file << ENCODED_MESSAGE << endl; //writhing on file
        file.close (); //closing file when done
    }
    else cerr << "Unable to open file" << filename << endl;
}

//This function takes a message, in clear text, and the shift information as
//a parameter and returns the encrypted version of the message.
string caesar(bool rightShift, int shift, string MESSAGE) {
	string ENCODED = ""; //encoded char will stay here

    for(int i=0; i<MESSAGE.length();i++) { //for loop for encoding
        char c = MESSAGE.at(i);
        if(rightShift) c = c-shift; //add or subtract by the shift G|D
        else c = c+shift;
        if (c<65) c = c+26; //add if the value if below 65 (A)
        if (c>90) c = c-26; //subtract if the value if above 90 (Z)
        ENCODED = ENCODED + c; //adds chars to string
    }
    return ENCODED;
}

//This function takes a message as a parameter and takes care of cleaning it.
//A cleaned message is a message that only contains uppercase alphabetic characters.
//In case a lowercase letter is entered, the function must transform it into uppercase
//using the toupper function.
void sanitize(bool rightShift, int shift, string fileName) {
	string YOUR_MESSAGE, ENCODED;
	char c;
    while (1) { // main loop start here
        cout << "Your message: ";
        cin >> YOUR_MESSAGE; //gets the message
        string temp="";
        //for loop for make a cleaned message that only contains uppercase alphabetic characters.

        for (int i = 0; i < YOUR_MESSAGE.size(); ++i) {
            if (YOUR_MESSAGE[i] >= 'A' && YOUR_MESSAGE[i] <= 'Z') {
                temp = temp + YOUR_MESSAGE[i];
            }
            else if (YOUR_MESSAGE[i] >= 'a' && YOUR_MESSAGE[i] <= 'z') {
                c = toupper(YOUR_MESSAGE[i]); //the toupper function that transform everything into uppercase
                temp = temp + c;
            }
        }
        YOUR_MESSAGE = temp;
        temp = "";
        ENCODED = caesar(rightShift, shift, YOUR_MESSAGE); //calls the Caesar function to get encoded value
        cout << "Sending message: " << ENCODED << endl; //writing on console
        send(fileName, ENCODED); //calls send function to write the file
    }
}


int main(int argc, char *argv[]) {
    // The arguments to provide: G|D n fichier
    if (argc < 4) {
        cout << "Utilization: ./send G|D shift file. " << endl;
        return 1;
    }
    if (strcmp(argv[1], "G") != 0 && strcmp(argv[1], "D") != 0){
        cout << " The first argument must be G ou D, " << argv[1] << " is incorrect." << endl;
        return 1;
    }
    bool rightShift = strcmp(argv[1], "D") == 0;
    // atoi: conversion of a string to an integer
    int shift = atoi(argv[2]);
    string filename = argv[3];
    // TODO your program begins here
    cout << " Encrypted communication with Ceasar " << argv[1] <<  " " << shift <<" via " << filename << endl;

    sanitize(rightShift, shift, filename); //calling sanitize function

    return 0;
}
