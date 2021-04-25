#include<iostream>
#include<string>
#include<vector>

int main(void)
{
    // int sockfd = socket(domain, type, protocol);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

    int bind(int sockfd, const struct sockaddr &addr, socklen_t optlen);
    int listen(int sockfd, int backlog)

    int new_socket = accept(int sockfd, struct sockaddr &addr, socklen_t *addrlen)

    return 0;
}