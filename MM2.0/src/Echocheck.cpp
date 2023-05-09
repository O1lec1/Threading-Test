#include <chrono>
#include <cstring>
#include <string>
#include <thread>
#include <string>

#include "Echocheck.h"
static int portchange = 6558;
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


	sf::UdpSocket socket;
	sf::IpAddress sender;
	unsigned short port;
	char data[100];
	unsigned short sender_port;

	// bind the socket to a port
	if (isServer) {

	std::cout<<"ETc Start 1 \n";
        if (socket.bind(portchange) != sf::Socket::Done){
            std::cout << "Error Socket Binding\n";
            socket.setBlocking(false);
            return;
        }
        std::cout<<"\n : "<<socket.isBlocking()<<"\n";
	}
}
//Server
void Echocheck::serveout(){

	sf::Packet packet;
	packet.clear();
	sf::IpAddress remoteAddress=sf::IpAddress::None;

	unsigned short remotePort = portchange;
    sf::Socket::Status statusvar;
	//auto Status = bind (unsigned short port,const IpAddress &address=IpAddress::Any);
	//while(socket.NotReady)std::cout <<".";
	std::cout <<"\n";
	while (remoteAddress == sf::IpAddress::None){
	while (statusvar!= socket.Done){
        packet.clear();
        socket.setBlocking(true);
        statusvar =socket.receive(packet,remoteAddress,remotePort);

		if (statusvar== socket.Error)
		{
			std::cout << "Error receiving UDP\n  (server) \n";
            //

//			std::cout<<packet;
		}
		}
}

		std::cout<<"DN<< "<<remoteAddress<<"  /\n";
		std::string s;
		packet >> s;
		std::cout << "Echocheck: received: '" << s << "'\n";
		packet.clear();
		packet << "Hi, I'm a server";
		while (socket.send (packet, remoteAddress,remotePort!= socket.Done))std::cout<<".";
		std::cout<<"\n";




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
	sf::IpAddress recipient = "152.105.67.126";
    int sendx=0;
	unsigned short port = portchange;
	//std::cout<<"-2-\n";
    sf::Packet data;
	// UDP socket:
	sf::IpAddress sender;
	//unsigned short port;

	while (data.getDataSize()==0){
	std::cout<<"["<<std::to_string(data.getDataSize())<<"]\n";
	std::cout<<"-1-\n";
	sf::Socket::Status statusvar;
	while (statusvar != sf::Socket::Done){
	sendx++;
	std::cout<<"Attempt send ("<<sendx<<") "<<recipient<<"/ "<<"\n ";
	statusvar =socket.send(reca,recipient, port);
	if (statusvar == sf::Socket::Error)
	{
		std::cout << "Error Sending UDP\n";
            return;
	}
	}
	std::cout<<"-2-\n";
	sf::Packet data;
	// UDP socket:
	sf::IpAddress sender;
	//unsigned short port;

	//if (socket.receive(data, sender,  port)== sf::Socket::Done){
	//	std::cout << "Error receiving UDP\n  (Client) \n";
    //        return;
	//}
	//std::cout<<"-3-\n";
    //std::string received;
	//data >> received;
	//std::cout << "Received " << received << " bytes from "<< sender << " on port " << port << std::endl;
	//return(true);#
	socket.setBlocking(false);
	socket.receive(data, sender,  port);
}}

