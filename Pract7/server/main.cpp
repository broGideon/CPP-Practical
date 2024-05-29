#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <locale>
#include <codecvt>

using namespace std;

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);

    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult;
    SOCKET ClientSocket = INVALID_SOCKET;
    SOCKET ListenSocket = INVALID_SOCKET;

    const char* sendBuffer = "Сообщение получено";
    char recvBuffer[512];

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData); // Инициализация WinSock
    if (result != 0) {
        wcout << L"WSAStartup failed" << endl;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_protocol = IPPROTO_TCP; // Протокол TCP
    hints.ai_flags = AI_PASSIVE; // Использовать текущий IP-адрес

    result = getaddrinfo(NULL, "788", &hints, &addrResult); // Получение информации для создания сокета
    if (result != 0) {
        wcout << L"getaddrinfo failed" << endl;
        WSACleanup();
        return 1;
    }

    ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol); // Создание сокета для прослушивания
    if (ListenSocket == INVALID_SOCKET) {
        wcout << L"socket creation with error" << endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    result = bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen); // Привязка сокета к адресу
    if (result == SOCKET_ERROR) {
        wcout << L"Ошибка подключения клиента" << endl;
        freeaddrinfo(addrResult);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    result = listen(ListenSocket, SOMAXCONN); // Начало прослушивания подключений
    if (result == SOCKET_ERROR) {
        wcout << L"Listening failed" << endl;
        freeaddrinfo(addrResult);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    ClientSocket = accept(ListenSocket, NULL, NULL); // Принятие входящего подключения
    if (ClientSocket == INVALID_SOCKET) {
        wcout << L"Accepting error" << endl;
        freeaddrinfo(addrResult);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    closesocket(ListenSocket); // Закрытие сокета для прослушивания

    do {
        ZeroMemory(recvBuffer, 512); // Очистка буфера перед приемом данных
        result = recv(ClientSocket, recvBuffer, 512, 0); // Поличение данных от клиента
        if (result > 0) {

            string recvStr(recvBuffer, result);
            wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
            wstring wideStr = converter.from_bytes(recvStr);

            wcout << L"Получено " << result << L" байт" << endl;
            wcout << L"Сообщение: " << wideStr << endl;

            result = send(ClientSocket, sendBuffer, (int)strlen(sendBuffer), 0);// Отправка ответа клиенту
            if (result == SOCKET_ERROR){
                wcout << L"Ошибка отправки" << endl;
                closesocket(ClientSocket);
                freeaddrinfo(addrResult);
                WSACleanup();
                return 1;
            }
        }
        else if (result == 0) {
            wcout << L"Соединение закрыто клиентом" << endl;
        }
        else {
            wcout << L"Ошибка приема данных" << endl;
            closesocket(ClientSocket);
            freeaddrinfo(addrResult);
            WSACleanup();
            return 1;
        }
    } while (result > 0);

    result = shutdown(ClientSocket, SD_SEND);// Завершение отправки данных
    if (result == SOCKET_ERROR) {
        wcout << L"Ошибка закрытия соединения" << endl;
        closesocket(ClientSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    closesocket(ClientSocket); // Закрытие клиентского сокета
    freeaddrinfo(addrResult); //Очистка информации о сервере
    WSACleanup(); //Прекращение использования WinSock
    return 0;
}