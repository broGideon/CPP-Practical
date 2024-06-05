#include <iostream>
#include <locale>
#include <codecvt>
#include <fcntl.h>
#include <Windows.h>
#include <string>
#include "library.h"

using namespace std;

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);

    wcout << L"Введите строку:";
    wstring line;
    getline(wcin, line);

    wcout << L"Введите подстроку:";
    wstring subline;
    getline(wcin, line);

    HINSTANCE load = LoadLibraryW(L"libcontain.dll");

    typedef bool (*contain_func)(std::wstring, std::wstring);
    contain_func Contain = (contain_func)GetProcAddress(load, "contain");

    if (Contain(line, subline)){
        wcout << L"Строка надена" << endl;
    } else {
        wcout << L"Строка не найдена" << endl;
    }

    FreeLibrary(load);

    return 0;
}