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
        Echocheck();
        bool Clientin();
        bool serveout();
    protected:

    private:
};

#endif // ECHOCHECK_H
