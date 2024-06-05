#include "library.h"
#include <iostream>
#include <string>

extern "C" __declspec(dllexport) bool contain(std::wstring line, std::wstring subline) {
    if (line.find(subline) == std::wstring::npos){
        return false;
    } else {
        return true;
    }
}
