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

 combatant attack(combatant target){
 if(rand()%50>20)
 target.health=-rand()%3;
 }

 combatant check2(combatant target2){
 if (check>target2.health){
 check=target2.health;
 std::cout<<name <<"hits their target "<<target2.name<<" who is now at "<<check <<" HP.\n";
 }
 }


 };


int main()
{

    std::thread([]{
    combatant Rolfor(100,"Rolfor",100);
    combatant Dan(100,"Guard Dan",100);
    while(Rolfor.health>0&&Dan.health>0){
    Rolfor=Dan.attack(Rolfor);
    Dan=Rolfor.attack(Dan);
    Dan.check2(Rolfor);
    Rolfor.check2(Dan);
    }

    }
    ).join();
    std::cout << "Fin\n";
    return 0;
}
