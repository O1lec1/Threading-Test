    #include <iostream>
    #include <thread>
    #include <SFML/Graphics.hpp>
    #include <SFML/Network.hpp>
    #include "queuec.h"
    using namespace std;
    //class combatant{
    //public:
    //    int health;
    //    string name;
    //    int check;
    //    combatant(int hp,string targetname, int opponenthealth){
    //        health=hp;
    //        name=targetname;
    //        check=opponenthealth;
    //    };

    //    void attack(combatant &target){
    //        if(rand()%50>20)
    //        {
    //          target.health -= rand()%30;
    //          if(target.health<0)target.health=0;
    //          std::cout<<name <<" hits their target "<<target.name<<" who is now at "<<target.health<<" HP.\n";
    //       }
    //   }

    //     void check2(combatant target2){
    //         if (check>target2.health){
    //             check=target2.health;
    //             std::cout<<name <<"hits their target "<<target2.name<<" who is now at "<<check <<" HP.\n";
    //         }
    //
    //     }


    //};

    void server(){
        // queue of messages
        // map/list (socket*)
        sf::TcpListener listner;
        unsigned short port = 2847;
        sf::Socket::Status status;

        // LISTEN
        status = listner.listen(port);
        if (status != sf::Socket::Done){
            std::cout<<"Error Listening\n";
            return;
        }

        // spawn new accepter thread (queue, map)

        // dequeue messages (blocking)
        // send message to the whole map

        // ACCEPTer thread (knows the queue and a map of clients)
        // needs to move to *socket
        sf::TcpSocket socket;

        status = listner.accept(socket);
        if (status != sf::Socket::Done){
            std::cout<<"Error Accepting\n";
            return;
        }

        // spawn new receive thread(queue)
        // add socket to client map

        // RECEIVE thread (knows the queue)
        sf::Packet packet;

        socket.receive(packet);
        if (status != sf::Socket::Done){
            std::cout<<"Error Receiving\n";
            return;
        }
        std::string msg;
        packet >> msg;
        std::cout << msg;
        // enqueue message

        // SEND
        packet.clear();
        packet << "server msg\n";
        socket.send(packet);
        if (status != sf::Socket::Done){
            std::cout<<"Error Sending\n";
            return;
        }
    }

    void client(){

        // CONNECT
        sf::TcpSocket socket;
        sf::Socket::Status status;
        sf::IpAddress address("152.105.67.126"); // ifconfig
        status = socket.connect(address, 2845);
        if (status != sf::Socket::Done){
            std::cout<<"Error Connecting\n";
            return;
        }

        // queue

        // spawn receive thread
        // except that we just want to print messages

        // SENDING
        // reading std::cin
        sf::Packet packet;
        packet << "client sent\n";
        status = socket.send(packet);
        if (status != sf::Socket::Done){
            std::cout<<"Error Sending\n";
            return;
        }


        // RECEIVING thread
        status = socket.receive(packet);
        if (status != sf::Socket::Done){
            std::cout<<"Error Receiving\n";
            return;
        }
        std::string message;
        packet>>message;
        std::cout<<message;
    }
    //using std::chrono::duration_cast;
    //using std::chrono::milliseconds;
    //using std::chrono::seconds;
    //using std::chrono::system_clock;

    int main()
    {
        std::thread serverThread(&server);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        client();
        serverThread.join();
    //    cout.flush();
        std::cout << "Fin\n";
        return 0;
    }
