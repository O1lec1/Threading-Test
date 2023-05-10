#ifndef ECHOCHECK_H
#define ECHOCHECK_H




#include <chrono>
#include <cstring>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <string>
#include <queue>
#include "queue.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#include <cmath>
#include <iostream>

class Echocheck
{
    public:
        std::vector<sf::IpAddress> Players;
        sf::TcpSocket socketa;
        Queue<std::string> messagequeue;
        int playercount;
        unsigned short port;
        void Client();
        void tcpserver();
        void tcpserver(bool run);
        sf::TcpSocket tcpsocket;
        sf::UdpSocket socket;
        void closeout();
        Echocheck(bool isServer = false);
        bool Clientin(int a);
        bool serveout();
    protected:

    private:
};

#endif // ECHOCHECK_H
