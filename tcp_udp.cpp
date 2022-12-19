#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;

int main()
{
    // TCP haberleşmesi için socket oluşturma
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        cerr << "HATA: Socket oluşturulamadı!" << endl;
        return -1;
    }

    // Socket nesnesine IP adresi ve port numarası atama
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    if(inet_pton(AF_INET, "192.168.1.1", &serv_addr.sin_addr)<=0)
    {
        cerr << "HATA: Geçersiz IP adresi!" << endl;
        return -1;
    }

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        cerr << "HATA: Socket bağlanamadı!" << endl;
        return -1;
    }

    // TCP haberleşmesi için bağlantı kurma
    listen(sockfd, 5);
    int connfd = accept(sockfd, (struct sockaddr*)NULL, NULL);

    // Veri gönderme
    char* send_data = "Merhaba, bu bir TCP haberleşmesi!";
    send(connfd, send_data, strlen(send_data), 0);

    // Veri alma
    char recv_data[1024];
    recv(connfd, recv_data, 1024, 0);
    cout << "Alınan veri: " << recv_data << endl;

    // Bağlantı kapatma
    close(connfd);

    // UDP haberleşmesi için socket oluşturma
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        cerr << "HATA: Socket oluşturulamadı!" << endl;
        return -1;
    }

    // Veri gönderme
    send_data = "Merhaba, bu bir UDP haberleşmesi!";
    sendto(sockfd, send_data,
