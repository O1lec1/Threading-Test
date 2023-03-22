    #include <iostream>
    #include <thread>
    #include <SFML/Graphics.hpp>
    #include <SFML/Network.hpp>
    //#include "queuec.h"

    //queue------------------
    #ifndef QUEUE_HPP //ifnot add QUEUE_HPP
    #define QUEUE_HPP

    #include <condition_variable>
    #include <mutex>
    #include <queue>
    template <typename T>

    class Queue
{
    public:
        T pop() // Blocking pop
        {
            std::unique_lock<std::mutex> mlock(mutex_);
            cond_.wait(mlock, [this]{return !queue_.empty();});
            auto val = queue_.front();
            queue_.pop();
            return val;
        }

        void pop(T& item) // pop will not wait with an empty queue
        {
            std::unique_lock<std::mutex> mlock(mutex_);
            if (queue_.empty())
            {
                return;
            }
            item = queue_.front();
            queue_.pop();
        }

        void push(const T& item)
        {
            std::unique_lock<std::mutex> mlock(mutex_);
            queue_.push(item);
            cond_.notify_one();
        }
        Queue()=default;
        Queue(const Queue&) = delete;            // disable copying
        Queue& operator=(const Queue&) = delete; // disable assignment

    private:
        std::queue<T> queue_;
        std::mutex mutex_;
        std::condition_variable cond_;
};

#endif






    //_______________________

    using namespace std;
    void server(){
        // queue of messages
        Queue<sf::Packet> mainqueue;
        // map/list (socket*)
        sf::TcpListener listner;
        unsigned short port = 1067;
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
        status = socket.connect(address, 1067);
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
