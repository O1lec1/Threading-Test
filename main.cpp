#include <iostream>
#include <thread>
using namespace std;
 class combatant{
 public:
     int health;
     string name;
     int check;
     combatant(int hp,string targetname, int opponenthealth){
         health=hp;
         name=targetname;
         check=opponenthealth;
     };

     void attack(combatant &target){
         if(rand()%50>20)
         {
            target.health -= rand()%30;
            std::cout<<name <<" hits their target "<<target.name<<" who is now at "<<target.health<<" HP.\n";
         }
     }

//     void check2(combatant target2){
//         if (check>target2.health){
//             check=target2.health;
//             std::cout<<name <<"hits their target "<<target2.name<<" who is now at "<<check <<" HP.\n";
//         }
//
//     }


 };



using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
int main()
{
    srand(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
    std::cout << "Start\n";
    combatant Rolfor(100,"Rolfor",100);
    combatant Dan(100,"Guard Dan",100);
    std::thread([&Rolfor, &Dan]{
        while(Rolfor.health > 0 && Dan.health > 0){
//            cout << "Attack\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000*rand()%6));
            Dan.attack(Rolfor);
//            Rolfor.attack(Dan);
//            cout << "Pre check\n";
//            Dan.check2(Rolfor);
//            Rolfor.check2(Dan);
//            cout<<"Check \n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000*rand()%6));

        }

        }
    ).detach();
    std::thread([&Rolfor, &Dan]{
        while(Rolfor.health > 0 && Dan.health > 0){
            std::this_thread::sleep_for(std::chrono::milliseconds(1000*rand()%6));
//            cout << "Attack\n";
//            Dan.attack(Rolfor);
            Rolfor.attack(Dan);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000*rand()%6));
//            cout << "Pre check\n";
//            Dan.check2(Rolfor);
//            Rolfor.check2(Dan);
//            cout<<"Check \n";

        }

        }
    ).join();
//    cout.flush();
    std::cout << "Fin\n";
    return 0;
}
