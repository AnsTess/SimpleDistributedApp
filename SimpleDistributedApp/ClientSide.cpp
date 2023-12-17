#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    SOCKADDR_IN client;

    // Инициализация Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Создание сокета
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Подключение к серверу
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(1111);
    connect(clientSocket, (SOCKADDR*)&client, sizeof(client));
    std::cout << "Ïîäêëþ÷åíî ê ñåðâåðó" << std::endl;

    // Отправка и прием сообщений
    const char* message = "Ïðèâåò îò êëèåíòà!";
    send(clientSocket, message, strlen(message), 0);

    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Ïîëó÷åíî: " << buffer << std::endl;

    // Закрытие сокета
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
