#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

// TODO implement the fonctions sanitize, caesar et send here

void run_encoder(bool rightShift, int shift, string fileName) {
	string ENCODED = ""; //encoded char will stay here
	string YOUR_MESSAGE;
	string filename; //remember there is a difference between fileName and fileName
	if (fileName[0]=='/') filename = fileName.substr(1,fileName.length()); // removes the / before the tmp/f105 instead of /tmp/f105
	else filename = fileName; //use // to comment the previous line and remove the else if you got no probs
	ofstream file (filename, ios_base::app);

    if (file.is_open ()) {
        while (1) { // main loop start here
            cout << "Your message: "; 
            cin >> YOUR_MESSAGE;
            for(int i=0; i<YOUR_MESSAGE.length();i++) { //for loop for encoding
                char xc, c = YOUR_MESSAGE.at(i);
                if(rightShift) xc = toupper(c)-shift; //add or substract by the shift G|D
                else xc = toupper(c)+shift;
                if (xc<65) xc = xc+26; //add if the value if below 65 (A)
                if (xc>90) xc = xc-26; //subtract if the value if above 90 (Z)
                ENCODED = ENCODED + xc; //adds chars to string
            }
            cout << "Sending message: " << ENCODED << endl; //writing on consol
            file << ENCODED << endl; //writhing on file
            ENCODED = ""; //resetting when a line is over
        }
        file.close (); //closing file when done
    }
    else cerr << "Unable to open file" << filename << endl;
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

    run_encoder(rightShift, shift, filename); //calling my function

    return 0;
}
