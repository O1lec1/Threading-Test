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
Echocheck::Echocheck(bool isServer)
{

    int playercount=0;
    sf::UdpSocket socket;
    sf::IpAddress sender;
    unsigned short port;
    char data[100];
    unsigned short sender_port;

    // bind the socket to a port
    if (isServer)
    {

        std::cout<<"ETc Start 1 \n";
        if (socket.bind(portchange) != sf::Socket::Done)
        {
            std::cout << "Error Socket Binding\n";
            socket.setBlocking(false);
            return;
        }
        std::cout<<"\n : "<<socket.isBlocking()<<"\n";
    }
}
void closeout()
{
//try{socket.close();}
//atch(...){std::cout<<"Port Locked :"<<portchange<<"\n";}

//Whatever issue is causing all udps to fail, also locked them up, Closing them doesnt even work.--------------


}
//Server
bool Echocheck::serveout()
{

    sf::Packet packet;
    packet.clear();
    sf::IpAddress remoteAddress=sf::IpAddress::None;

    unsigned short remotePort = portchange;
    sf::Socket::Status statusvar;
    //auto Status = bind (unsigned short port,const IpAddress &address=IpAddress::Any);
    //while(socket.NotReady)std::cout <<".";
    std::cout <<"\n";

    int trys=100;
    while ((remoteAddress == sf::IpAddress::None )&&(trys>0))
    {
        trys--;
        while (statusvar!= socket.Done)
        {
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
    while (socket.send (packet, remoteAddress,remotePort!= socket.Done))
        std::cout<<".";
    std::cout<<"\n";




}
bool Echocheck::Clientin(int a)
{
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

    //while (data.getDataSize()==0){
    std::cout<<"["<<std::to_string(data.getDataSize())<<"]\n";
    std::cout<<"-1-\n";
    sf::Socket::Status statusvar;
    while (statusvar != sf::Socket::Done)
    {
        sendx++;
        std::cout<<"Attempt send ("<<sendx<<") "<<recipient<<"/ "<<"\n ";
        statusvar =socket.send(reca,recipient, port);
        if (statusvar == sf::Socket::Error)
        {
            std::cout << "Error Sending UDP\n";
            return(false);
        }
        else if (statusvar == sf::Socket::Disconnected)
        {
            std::cout << "EDisconnected";
            return(false);
        }
        else if (statusvar == sf::Socket::NotReady)
        {
            std::cout << "EAwait";
            return(false);
        }
    }
    std::cout<<"-2-\n";
    std::string received;
    data >> received;
    if(data.getDataSize()>1)
        std::cout << "Received " << received << " bytes from "<< sender << " on port " << port << std::endl;
    //return(true);
    socket.setBlocking(false);
    statusvar = socket.receive(data, sender,  port);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    if (statusvar!=socket.Done)
        return(false);
    else if (statusvar==socket.Done)
        return(true);
}
//}
//tcp pure manual
void Echocheck::Client()
{
    int playerme;
    std::cout<<"You can use the local server and host by entering the above server information \n";
    std::cout<<"Please enter the port that the server is using : " ;
    std::cin>>port;
    sf::IpAddress server ;
    std::cout<<"Please enter the IpAddress that the server is using : " ;
    std::cin>>server;
    sf::TcpSocket socket;
    socket.connect(server, port);
    std::string message = "ping";
    socket.send(message.c_str(), message.size() + 1);
    char buffer[1024];
    std::size_t received = 0;
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << "The server said: " << buffer << std::endl;
    if (sf::IpAddress::getPublicAddress()==server){
    std::string message = "host";
    socket.send(message.c_str(), message.size() + 1);
    }
    else {
    std::string message = "query";
    socket.send(message.c_str(), message.size() + 1);
    socket.receive(buffer, sizeof(buffer), received);
    playerme=buffer[0];
    }
    std::string inputstart;
    while (inputstart!="start"){
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout<<"Input 'start' to start \nOr 'add' to let another join:  ";
    std::cin>>inputstart;
    if (inputstart!="add"){
    message="add";
    socket.send(message.c_str(), message.size() + 1);
    socket.receive(buffer, sizeof(buffer), received);
    }
    }
    message="start";
    socket.send(message.c_str(), message.size() + 1);
    socket.receive(buffer, sizeof(buffer), received);
}
void Echocheck::tcpserver()
{
    sf::IpAddress server = sf::IpAddress::getPublicAddress();
    std::cout<<server<<" Host Ip\n";
    srand(time(NULL));
    int randport=2000+(rand()%3000);
    std::cout<<randport<<" Host port\n";
    sf::TcpListener listener;
    //Server Prepped
    int player = 1;
    listener.listen(randport);
    char buffer[1024];
    sf::TcpSocket socket;
    std::size_t received = 0;
    while(std::string(buffer)!="start")
    {
    playercount++;
    player++;
    //socket.receive(buffer, sizeof(buffer), received);
    listener.accept(socket);
    std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;



    socket.receive(buffer, sizeof(buffer), received);
    std::cout << "Received: " << buffer << std::endl;
    if (std::string(buffer)=="ping")
    {
        std::string message = "pong";
        socket.send(message.c_str(), message.size() + 1);
    }
        socket.receive(buffer, sizeof(buffer), received);
    std::cout << "Received: " << buffer << std::endl;
    if (std::string(buffer)=="host"){
    std::cout<<"Host privilages";
        std::string message = std::to_string(1);
        socket.send(message.c_str(), message.size() + 1);
    }
    else {
        std::string message = std::to_string(player);
        socket.send(message.c_str(), message.size() + 1);
    }
    socket.receive(buffer, sizeof(buffer), received);



}}






