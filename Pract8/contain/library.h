#ifndef CONTAIN_LIBRARY_H
#define CONTAIN_LIBRARY_H

#include <string>

extern "C" __declspec(dllexport) bool contain(std::wstring line, std::wstring subline);

#endif //CONTAIN_LIBRARY_H
