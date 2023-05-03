

#include <chrono>
#include <cstring>

#include <thread>
#include <string>

#include "Echocheck.h"


#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
   sf::UdpSocket socket;
   sf::IpAddress sender;
   sf::IpAddress received ;
   unsigned short port;
    sf::Packet data;
    unsigned short sender_port;
#include <cmath>
#include <iostream>
Echocheck::Echocheck(){



   // bind the socket to a port
   if (socket.bind(13000) != sf::Socket::Done){
   // error...
   }
}
   //Server
void serveout(){
while (1){
if (socket.receive(data,sender,sender_port)!= sf::Socket::Done)
{//return(true);
// error...
}
if (socket.send(data,sender,sender_port)!= sf::Socket::Done){
// error...
}
}

}
void Clientin(){
//The client
sf::UdpSocket socket;
//char data[100] ;
sf::Packet reca;
// UDP socket:
sf::IpAddress recipient = "152.105.17.60";
unsigned short port = 13000;
if (socket.send(reca,recipient, port) !=sf::Socket::Done)
{
// error...
}
sf::Packet data;
// UDP socket:
sf::IpAddress sender;
//unsigned short port;
if (socket.receive(data, received,  port)!= sf::Socket::Done){
// error...
}std::cout << "Received " << received << " bytes from "<< sender << " on port " << port << std::endl;
//return(true);
}

