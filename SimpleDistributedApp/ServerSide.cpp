#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    SOCKADDR_IN server, client;
    int clientSize = sizeof(client);

    // Инициализация Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Создание сокета
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Привязка сокета
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(1111);
    bind(serverSocket, (SOCKADDR*)&server, sizeof(server));

    // Ожидание входящих соединений
    listen(serverSocket, 0);
    std::cout << "Сервер слушает..." << std::endl;

    // Принятие входящих соединений
    clientSocket = accept(serverSocket, (SOCKADDR*)&client, &clientSize);
    std::cout << "Клиент подключен" << std::endl;

    // Прием и отправка сообщений
    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Получено: " << buffer << std::endl;

    const char* message = "Привет от сервера!";
    send(clientSocket, message, strlen(message), 0);

    // Закрытие сокета
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
