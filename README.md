# C++ Code Obfuscator

A simple C++ code obfuscator that uses Base64 encoding and macro obfuscation techniques to make your code harder to read while maintaining functionality.

## Features

- Base64 encoding of source code
- Macro-based identifier obfuscation
- Automatic compilation and execution of obfuscated code
- Works with any C++ source file

## Usage

1. Compile the obfuscator:
```bash
g++ Obfuscator.cpp -o obfuscator
```

## Example

### Original Code (example.cpp):
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

### Obfuscated (obfuscated_example.cpp):
```cpp


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

static const char* encoded = "I2luY2x1ZGUg" "PGlvc3RyZWFt" "PgoKaW50IG1h" "aW4oKSB7CiAg" "ICBzdGQ6OmNv" "dXQgPDwgIkhl" "bGxvLCBXb3Js" "ZCEiIDw8IHN0" "ZDo6ZW5kbDsK" "ICAgIHJldHVy" "biAwOwp9";

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



```