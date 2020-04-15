#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

int main()
{
    // 1.创建SOCKET
    int sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ == -1)
    {
        printf("建立SOCKET失败...\n");
    }
    else
    {
        printf("建立SOCKET成功...\n");
    }
    
    // 2.连接服务器
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(4567);
    int ret = connect(sock_, (sockaddr*)&server_addr, sizeof(sockaddr_in));
    if (ret == -1)
    {
        printf("连接服务器失败...\n");
    }
    else
    {
        printf("连接服务器成功...\n");
    }

    while (true)
    {
        // 3. 输入请求命令
        char cmdBuf[128] = {};
        scanf("%s", cmdBuf);
        // 4. 处理请求
        if (0 == strcmp(cmdBuf, "exit"))
        {
            break;
        }
        else
        {
            // 5. 发送数据到服务器
            send(sock_, cmdBuf, strlen(cmdBuf)+1, 0);
        }
        // 7. 接收服务器信息recv
        char recvBuf[128] = {};
        int nlen = recv(sock_, recvBuf, 128, 0);
        if (nlen > 0)
        {
            printf("接收到数据： %s\n", recvBuf);
        }
    }
    // 4.关闭SOCKET
    close(sock_);
    printf("退出，任务结束。\n");
    getchar();
    return 0;
}