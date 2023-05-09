#ifndef ECHOCHECK_H
#define ECHOCHECK_H




#include <chrono>
#include <cstring>

#include <thread>
#include <string>



#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#include <cmath>
#include <iostream>

class Echocheck
{
    public:
        void Client();
        void tcpserver();
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
