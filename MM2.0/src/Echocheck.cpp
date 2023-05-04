#include <chrono>
#include <cstring>

#include <thread>
#include <string>

#include "Echocheck.h"
static int portchange = 2558;
#include <functional>
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
Echocheck::Echocheck(bool isServer){
	std::cout<<"ETc Start \n";

	sf::UdpSocket socket;
	sf::IpAddress sender;
	unsigned short port;
	char data[100];
	unsigned short sender_port;
	// bind the socket to a port
	if (isServer) {
        if (socket.bind(portchange) != sf::Socket::Done){
            std::cout << "Error Socket Binding\n";
            return;
        }
	}
}
//Server
void Echocheck::serveout(){

	sf::Packet packet;
	packet << "Server ping!";
	sf::IpAddress remoteAddress;

	unsigned short remotePort;

	//auto Status = bind (unsigned short port,const IpAddress &address=IpAddress::Any);
	while (1){
        packet.clear();

		if (socket.receive(packet, remoteAddress,remotePort) != sf::Socket::Done)
		{
			std::cout << "Error receiving UDP\n  (server) \n";
            //return;

//			std::cout<<packet;
		}
		std::string s;
		packet >> s;
		std::cout << "Echocheck: received: '" << s << "'\n";
		packet.clear();
		packet << "Hi, I'm a server";
		socket.send (packet, remoteAddress,remotePort);
	}


}
void Echocheck::Clientin(int a){
	//The client
	sf::UdpSocket socket;
	//char data[100] ;
	sf::Packet reca;
	reca<<"Test"<<21;
	// UDP socket:
//	sf::IpAddress recipient = "152.105.17.60";
    //std::cout<<"Sending (client) ";
	sf::IpAddress recipient = sf::IpAddress::Broadcast;

	unsigned short port = portchange;
	//std::cout<<"-2-\n";
	std::cout<<"-1-\n";
	if (socket.send(reca,recipient, port) != sf::Socket::Done)
	{
		std::cout << "Error Sending UDP\n";
            return;
	}
	std::cout<<"-2-\n";
	sf::Packet data;
	// UDP socket:
	sf::IpAddress sender;
	//unsigned short port;
	if (socket.receive(data, sender,  port)!= sf::Socket::Done){
		std::cout << "Error receiving UDP\n  (Client) \n";
            return;
	}
	std::cout<<"-3-\n";
    std::string received;
	data >> received;
	std::cout << "Received " << received << " bytes from "<< sender << " on port " << port << std::endl;
	//return(true);
}

