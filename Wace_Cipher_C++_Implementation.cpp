////// Wave Cipher - Full - C++ Code Implementation //////

#include <iostream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

int main() {

    cout << "----------------------WELCOME----------------------\n\n";

    int enc_or_dec_choice;
    cout << "Enter 1 for encryption. \nEnter 2 for decryption. \n>";
    cin >> enc_or_dec_choice;

    switch (enc_or_dec_choice) {

    case 1: {
        cout << "\n[You have chosen 1 for encryption]\n\n";

        string k, pt, dhKey, pass;
        cout << "Enter a random keyword: ";
        cin >> k;
        cout << "Enter Diffie-Hellman secret number: ";
        cin >> dhKey;
        cout << "Enter the plaintext: ";
        getline(cin >> ws, pt);

        pass = k + dhKey;

        /////////////////////// GENERATING A BINARY TRANSPOSITION KEY ///////////////////////

        // The binary sum will be stored in this variable
        bitset<12> binary_sum;

        for (char c : pass) {
            // Convert the characters of the key into binary
            bitset<12> binary(c);
            // Add the binary codes of every character with each other
            binary_sum = binary_sum.to_ulong() + binary.to_ulong();
        }

        // Defining transposition key
        string tk = binary_sum.to_string();

        //cout << "\nTransposition key: " << tk;

        // Extend or shorten the key based on the plaintext length
        string etk = tk;
        if (tk.length() > 1) {
            etk = tk + tk.substr(1, pt.length() % tk.length() - 1);
        }

        //////////////////////// TEXT SUBSTITUTION ////////////////////////////

        // Initialize the ciphertext
        string ct = "";

        // Loop through the plaintext characters
        for (int i = 0; i < pt.length(); i++) {
            // Get the ASCII value of the current character in the key
            int passASCII = int(pass[i % pass.length()]);
            // Get the ASCII value of the current character in the plaintext
            int ptASCII = int(pt[i]);
            // Add the ASCII values of the plaintext and key characters
            int ctASCII = ((ptASCII + passASCII) % 95) + 32;
            // Convert the result back into a character and add it to the ciphertext
            ct += char(ctASCII);
        }

        //cout << "\nSubstitut ciphertext: " << ct;

        ////////////////////////// TEXT TRANSPOSITION //////////////////////////////

        // push the the ciphertext characters in two separate vector arrays based on the extended key. key value 1 means character will to section1 and key value 0 means character will go to section2
        vector<char> s1, s2;
        int counter = 0;
        for (int i = 0; i < pt.length(); ++i) {
            switch (etk[counter++ % etk.length()]) {
            case '1':
                s1.push_back(ct[i]);
                break;
            case '0':
                s2.push_back(ct[i]);
                break;
            default:
                cout << "Error in the transposition key";
                return 0;
            }
        }



        // Print the characters from section1 and section2 respectively
        string tct;
        cout << "\nCiphertext: ";
        for (char c1 : s1) cout << c1;
        for (char c2 : s2) cout << c2;

        cout << endl;

        break;
    }

    case 2: {
        cout << "\n[You have chosen 2 for decryption]\n\n";

        string k, ct, dhKey, pass;
        cout << "Enter the keyword: ";
        cin >> k;
        cout << "Enter Diffie-Hellman secret number: ";
        cin >> dhKey;
        cout << "Enter the ciphertext: ";
        getline(cin >> ws, ct);

        pass = k + dhKey;

        /////////////////////// GENERATING A BINARY TRANSPOSITION KEY ///////////////////////

        // The binary sum will be stored in this variable
        bitset<12> binary_sum;

        for (char c : pass) {
            // Convert the characters of the key into binary
            bitset<12> binary(c);
            // Add the binary codes of every character with each other
            binary_sum = binary_sum.to_ulong() + binary.to_ulong();
        }

        // Defining transposition key
        string tk = binary_sum.to_string();

        //cout << "\nTransposition key: " << tk;

        // Extend or shorten the key based on the plaintext length
        string etk = tk;
        if (tk.length() > 1) {
            etk = tk + tk.substr(1, ct.length() % tk.length() - 1);
        }

        ////////////////////// REVERSE CIPHERTEXT TRANSPOSITION ////////////////////////

        // Generate two number series in the two vector arrays, section1 and section2. The number series will be generated based on the binary values in the extended key.
        vector<int> s1, s2;
        int counter = 0;
        for (int i = 0; i < ct.length(); ++i) {
            if (etk[counter % etk.length()] == '1') {
                s1.push_back(i);
            }
            else if (etk[counter % etk.length()] == '0') {
                s2.push_back(i);
            }
            else {
                cout << "Error in the transposition key";
                return 0;
            }
            ++counter;
        }

        // Create a plaintext vector array to hold the plaintext characters with the same length as the ciphertext
        vector<char> pt(ct.length());

        // Take the ciphertext characters that have matching position numbers with the number series in section1, and put them in plaintext vector
        int i = 0;
        for (int pos : s1) {
            if (pos < pt.size()) {
                pt[pos] = ct[i++];
            }
        }

        // Take the ciphertext characters that have matching position numbers with the number series in section2, and put them in plaintext vector
        for (int pos : s2) {
            if (pos < pt.size()) {
                pt[pos] = ct[i++];
            }
        }

        // Put all the characters from the plaintext vector in a new plaintext string
        string spt;
        for (char ch : pt) {
            spt += ch;
        }

        //cout << "\nTransposition reversed ciphetext: " << spt << endl;

        //////////////////////// REVERSE SUBSTITUTION //////////////////////////////

        // Initialize the original plaintext
        string opt = "";

        // Loop through the ciphertext characters
        for (int i = 0; i < spt.length(); i++) {
            // Get the ASCII value of the current character in the key
            int passASCII = int(pass[i % pass.length()]);
            // Get the ASCII value of the current character in the ciphertext
            int sptASCII = int(spt[i]);
            // Reverse the encryption processes
            int ptASCII = (sptASCII + 63) - passASCII;
            if (ptASCII < 32) {
                ptASCII = ptASCII + 95;
            }
            else if (ptASCII > 126) {
                ptASCII = ptASCII - 95;
            }
            // Convert the result back into a character and add it to the plaintext
            opt += char(ptASCII);
        }

        // Output the original plaintext
        cout << "\nPlaintext: " << opt << endl;
        break;
    }

          // case default if the user entered invalid input
    default:
        cout << "Invalid input. You have entered something other than 1 or 2. Please try again." << endl;
        break;
    }
    return 0;
}
