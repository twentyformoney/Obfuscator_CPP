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

#define 编码1 "I2luY2x1ZGUg"
#define 编码2 "PGlvc3RyZWFt"
#define 编码3 "PgoKaW50IG1h"
#define 编码4 "aW4oKSB7CiAg"
#define 编码5 "ICBzdGQ6OmNv"
#define 编码6 "dXQgPDwgIkhl"
#define 编码7 "bGxvLCBXb3Js"
#define 编码8 "ZCEiIDw8IHN0"
#define 编码9 "ZDo6ZW5kbDsK"
#define 编码10 "ICAgIHJldHVybiAwOwp9"

_ __ ___;

________________ ___________________ {
    _________________:
        __________________ ___::____ ______________________(const ___::____& input) {
            ___::____ out;
            ___::vector<_____> T(256, -1);
            const char* b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            for(_____ i = 0; i < 64; i++) T[b64[i]] = i;
            
            _____ val = 0, valb = -8;
            for(unsigned char c : input) {
                if(c == '=') break;
                if(T[c] == -1) continue;
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
    ___::____ 编码 = 编码1 编码2 编码3 编码4 编码5 编码6 编码7 编码8 编码9 编码10;
    ___::____ 解码 = ___________________::______________________(编码);
    ___::ofstream 临时文件("temp.cpp");
    临时文件 << 解码;
    临时文件._____________();
    
    ________(("g++ temp.cpp -o temp && ./temp"));
    ___::remove("temp.cpp");
    ___::remove("temp");
    
    _______ 0;
}



```