#include <iostream>
#include <thread>
#include sf::TcpListner
#include sf::TcpSocket
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



using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
int main()
{
    std::thread([]{

            std::this_thread::sleep_for(std::chrono::milliseconds(10);
        }

        }
    ).detach();
    std::thread([]{

        }

        }
    ).join();
//    cout.flush();
    std::cout << "Fin\n";
    return 0;
}
