#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <locale>
#include <codecvt>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);

    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult;
    SOCKET ClientSocket = INVALID_SOCKET;

    char recvBuffer[512];

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData); //Инициализация WinSock
    if (result != 0) {
        wcout << L"WSAStartup failed" << endl;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints)); //Очистка памяти
    hints.ai_family = AF_INET; //IPv4
    hints.ai_socktype = SOCK_STREAM; //TCP
    hints.ai_protocol = IPPROTO_TCP; //Протокол TCP

    result = getaddrinfo("localhost", "788", &hints, &addrResult); // Получение информации для создания сокета
    if (result != 0) {
        wcout << L"getaddrinfo failed" << endl;
        WSACleanup();
        return 1;
    }

    ClientSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol); //Создание сокета с заданными параметрами
    if (ClientSocket == INVALID_SOCKET) {
        wcout << L"socket creation with error" << endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    result = connect(ClientSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen); //установка соединения с сервером
    if (result == SOCKET_ERROR) {
        wcout << L"Ошибка подключения к серверу" << endl;
        freeaddrinfo(addrResult);
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    string sendBuffer;
    wstring message;

    while (true) {
        wcout << L"Введите сообщение:";
        wstring message;
        getline(wcin, message);

        if (message == L"exit") {
            break;
        }

        sendBuffer  = converter.to_bytes(message);
        result = send(ClientSocket, sendBuffer.c_str(), (int)sendBuffer.size(), MSG_DONTROUTE); //Отправка сообщения на сервер
        if (result == SOCKET_ERROR) {
            wcout << L"Ошибка отправки" << endl;
            closesocket(ClientSocket);
            freeaddrinfo(addrResult);
            WSACleanup();
            return 1;
        }

        wcout << L"Отправлено " << result << L" байтов" << endl;

        ZeroMemory(recvBuffer, sizeof(recvBuffer)); //Очистка памяти
        result = recv(ClientSocket, recvBuffer, 512, 0); //Получение ответа от сервера
        if (result > 0) {
            string recvStr(recvBuffer, result);
            wstring wideStr = converter.from_bytes(recvStr);

            wcout << L"Получено " << result << L" байта" << endl;
            wcout << L"Сообщение: " << wideStr << endl;
        } else if (result == 0) {
            wcout << L"Соединение закрыто" << endl;
            break;
        } else {
            wcout << L"Ошибка соединения" << endl;
            break;
        }
    }

    result = shutdown(ClientSocket, SD_SEND); // Завершение отправки данных
    if (result == SOCKET_ERROR) {
        wcout << L"Ошибка закрытия соединения" << endl;
        closesocket(ClientSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    closesocket(ClientSocket); //Закрытие сокета
    freeaddrinfo(addrResult); //Очистка информации о сервере
    WSACleanup(); //Завершение использования WinSock
    return 0;
}
