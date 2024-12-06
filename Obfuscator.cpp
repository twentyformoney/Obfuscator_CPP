#include <iostream> // Printing Output
#include <random> // Rng
#include <vector> // Vector for parsing the fstream
#include <fstream> // Filestream for reading the file 
#include <string> // String for the file name
#include <sstream> // Stringstream for parsing the fstream
#include <algorithm> // Algorithm for the find function
#include <iterator> // Iterator for the find function
#include <iomanip> // Iomanip for the setprecision

std::string base64_encode(const std::string &in) { // Base64 encode function
    std::string out; // Output string
    int val=0, valb=-6; // Value and valueb for the bit manipulation
    for (unsigned char c : in) { // For each character in the input string
        val = (val<<8) + c; // Shift the value by 8 and add the character
        valb += 8; // Add 8 to the valueb
        while (valb>=0) { // While the valueb is greater than 0
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val>>valb)&0x3F]); // Push the base64 character to the output
            valb-=6; // Subtract 6 from the valueb
        }
    }
    if (valb>-6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val<<8)>>(valb+8))&0x3F]); // If the valueb is greater than -6 then push the base64 character to the output
    while (out.size()%4) out.push_back('='); // While the output size is not divisible by 4 push "=" to the output
    return out; // Return the output
}

int main (){ // Main function
    std::fstream fs; // Filestream declaration
    std::string cppFile; // String for the cpp file name
    std::cout << "Put CPP file name (Make sure .cpp file in the same workfile)" << std::endl; //Output for the asking
    std::cin >> cppFile; // Input for the cpp file name .ex "main.cpp"
    fs.open(cppFile); // Opening the file from the input in cin
    if(!fs.is_open()){ // If the file is not open then return 1
        std::cout << "Error opening file" << std::endl;
        return 1;
    }

    std::stringstream buffer; // Stringstream for the buffer
    buffer << fs.rdbuf(); // Put the filestream to the buffer
    std::string fileContent = buffer.str(); // Put the buffer to the fileContent
    fs.close();

    std::string obfuscatedContent = base64_encode(fileContent); // Obfuscate the file content
    std::string obfuscatedFile = cppFile + "_obfuscated" + ".cpp"; // Add the obfuscated to the file name
    fs.open(obfuscatedFile, std::ios::out | std::ios::trunc); // Open the file in output mode
    if (!fs.is_open()){ // If the file is not open then return 1
        std::cout << "Error opening file for writing" << std::endl;
        return 1;
    }
   fs << R"(
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#define _ using
#define __ namespace
#define ___ std
#define ____ string
#define _____ int
#define ______ main
#define _______ return
#define ________ system

_ __ ___ ;

class Decoder {
    public:
        static ___::____ decode(const ___::____& input) {
            ___::____ out;
            ___::vector<_____> T(256, -1);
            const char* b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            for(_____ i = 0; i < 64; i++) T[b64[i]] = i;
            
            _____ val = 0, valb = -8;
            for(unsigned char c : input) {
                if(T[c] == -1) break;
                val = (val << 6) + T[c];
                valb += 6;
                if(valb >= 0) {
                    out.push_back(char((val >> valb) & 0xFF));
                    valb -= 8;
                }
            }
            _______ out;
        }
};

_____ ______() {
    const ___::____ encoded = ")" 
    << base64_encode(fileContent) << R"(";
    
    // Decode and write to temp file
    ___::____ decoded = Decoder::decode(encoded);
    const char* temp_file = "/tmp/decoded_XXXXXX";
    char filename[L_tmpnam];
    ___::tmpnam(filename);
    ___::____ temp_cpp = ___::____(filename) + ".cpp";
    
    ___::ofstream temp(temp_cpp);
    temp << decoded;
    temp.close();
    
    // Compile and run
    ___::____ compile_cmd = "g++ " + temp_cpp + " -o " + filename;
    ___::____ run_cmd = filename;
    
    ________(compile_cmd.c_str());
    ________(run_cmd.c_str());
    
    // Cleanup
    ___::remove(temp_cpp.c_str());
    ___::remove(filename);
    
    _______ 0;
}
)";
    fs.close(); // Close the file
    std::cout << "File obfuscated successfully and saved as" << obfuscatedFile << std::endl; // Output for the obfuscation done
    return 0; // Return 0
}