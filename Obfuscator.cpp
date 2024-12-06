#include <iostream>  // Printing Output
#include <random>    // Rng
#include <vector>    // Vector for parsing the fstream
#include <fstream>   // Filestream for reading the file
#include <string>    // String for the file name
#include <sstream>   // Stringstream for parsing the fstream
#include <algorithm> // Algorithm for the find function
#include <iterator>  // Iterator for the find function
#include <iomanip>   // Iomanip for the setprecision

std::string base64_encode(const std::string &in) {
    static const char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out;
    out.reserve((in.size() + 2) / 3 * 4);
    
    unsigned val = 0;
    int valb = -6;
    
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out += b64_table[(val >> valb) & 0x3F];
            valb -= 6;
        }
    }
    
    if (valb > -6) out += b64_table[((val << 8) >> (valb + 8)) & 0x3F];
    while (out.size() % 4) out += '=';
    return out;
}

int main()
{                                                                                             // Main function
    std::fstream fs;                                                                          // Filestream declaration
    std::string cppFile;                                                                      // String for the cpp file name
    std::cout << "Put CPP file name (Make sure .cpp file in the same workfile)" << std::endl; // Output for the asking
    std::cin >> cppFile;                                                                      // Input for the cpp file name .ex "main.cpp"
    fs.open(cppFile);                                                                         // Opening the file from the input in cin
    if (!fs.is_open())
    { // If the file is not open then return 1
        std::cout << "Error opening file" << std::endl;
        return 1;
    }

    // Read file more efficiently
    fs.seekg(0, std::ios::end);
    size_t size = fs.tellg();
    std::string fileContent(size, '\0');
    fs.seekg(0);
    fs.read(&fileContent[0], size);
    fs.close();

    std::string encodedContent = base64_encode(fileContent);
    const size_t targetPartSize = 12; // Target size for each part
    size_t numParts = (encodedContent.size() + targetPartSize - 1) / targetPartSize;

    fs.open(cppFile + "_obfuscated" + ".cpp", std::ios::out | std::ios::trunc); // Open the file in output mode
    if (!fs.is_open())
    { // If the file is not open then return 1
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
#define _________ fstream
#define __________ ios
#define ___________ rdbuf
#define ____________ open
#define _____________ close
#define ______________ out
#define _______________ trunc
#define ________________ class
#define _________________ public
#define __________________ static
#define ___________________ ________
#define ____________________ constexpr

_ __ ___;

static const char* encoded = )";

    // Write encoded parts efficiently
    std::string part;
    part.reserve(targetPartSize + 10);
    for(size_t i = 0, pos = 0; i < numParts; i++) {
        size_t len = std::min(targetPartSize, encodedContent.size() - pos);
        if (i > 0) fs << " ";
        fs << "\"" << encodedContent.substr(pos, len) << "\"";
        pos += len;
    }

    fs << R"(;

________________ ___________________ {
    _________________:
        static ____________________ char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        static ___::vector<_____> T;
        static bool initialized;

        static void init_table() {
            if (!initialized) {
                T.resize(256, -1);
                for(_____ i = 0; i < 64; i++) T[b64_table[i]] = i;
                initialized = true;
            }
        }

        __________________ ___::____ ______________________(const ___::____& input) {
            init_table();
            ___::____ out;
            out.reserve(input.size() * 3 / 4);
            
            _____ val = 0, valb = -8;
            for(unsigned char c : input) {
                if(c == '=') break;
                if(T[c] == -1) continue;
                val = (val << 6) + T[c];
                valb += 6;
                if(valb >= 0) {
                    out += char((val >> valb) & 0xFF);
                    valb -= 8;
                }
            }
            _______ out;
        }
};

// Initialize static members outside the class
bool ___________________::initialized = false;
___::vector<_____> ___________________::T;

_____ ______() {
    ___::____ 编码 = encoded;
    ___::____ 解码 = ___________________::______________________(编码);
    ___::ofstream 临时文件("temp.cpp", ___::ios::binary);
    临时文件.write(解码.c_str(), 解码.size());
    临时文件.close();
    
    ________("g++ temp.cpp -o temp && ./temp");
    ___::remove("temp.cpp");
    ___::remove("temp");
    
    _______ 0;
}
)";

    fs.close();                                                                              // Close the file
    std::cout << "File obfuscated successfully and saved as" << cppFile + "_obfuscated" + ".cpp" << std::endl; // Output for the obfuscation done
    return 0;                                                                                // Return 0
}