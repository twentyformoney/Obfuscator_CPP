
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
    const ___::____ encoded = "I2luY2x1ZGUgPGlvc3RyZWFtPgoKaW50IG1haW4oKSB7CiAgICBzdGQ6OmNvdXQgPDwgIkhlbGxvIFdvcmxkISI7CiAgICByZXR1cm4gMDsKfQ==";
    
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
