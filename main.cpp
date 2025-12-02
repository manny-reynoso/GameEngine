#include <iostream>
#include <ctime> // for time()
#include <cstdlib> // for rand() and srand()
using namespace std;

// Classes
class Player {
    public:
        int health;
        int maxDamage;
        int minDamage;
        int armour;
        int critChance;
        int critMultiplier;
        string name;


    int armourMechanic(int armour) {
        
        
        int damageTaken = static_cast<int>(finalDamage*((armour / 100.0)-100.0));
        cout << name << " has an armour rating of "  << armour << endl;
        cout << name << " got hit for " << damageTaken << endl;

        return damageTaken;
    }

    int attackMechanic() {
        int attackRoll = (rand() % 20) + 1; // random number between 1 and 20

        // LERP calculation for true damage
        int trueDamage = minDamage + static_cast<int>(
            ((attackRoll - 1) / 19.0) * (maxDamage - minDamage)
        );
        cout << name << " rolled " << attackRoll << "!!" << endl;
        cout << name <<" base damage for " << trueDamage << "!!" << endl;

        return trueDamage;

    }

    int critAttack(int trueDamage){
    //Determines if attack hits a crit.
        bool isCrit = (rand() % 100) < critChance ;

        if (isCrit){

            cout << "CRITICAL HIT!" << endl;

            // Multiply by crit multiplier (150 means 1.5x)
            int critDamage = static_cast<int>(trueDamage * (critMultiplier / 100.0));

             return critDamage;
        }   
        return trueDamage;
    }

        void takeDamage(int ){

            health -= armourMechanic(armour, finalDamage) ; //Substract the damage from targets health

            //output the result!
            cout <<this->name << "took" << damageTaken << " damage!" << endl;

        };

    int performAttack (Player& cpu){

        int baseDamage = attackMechanic();        // get base damage
        int finalDamage = critAttack(baseDamage); // apply crit if any
        int damageDealt = 


        cout << name << " hit for " << finalDamage<< "!" << endl;
        return finalDamage;
    };



};

int main() {
    srand(time(NULL)); // Seed the random number generator once

    Player player1;
    player1.name = "Player1";
    player1.health = 100;
    player1.minDamage = 1;
    player1.maxDamage = 10;
    player1.armour = 8;
    player1.critChance = 15;
    player1.critMultiplier =150;

    Player cpu;
    cpu.name = "cpu" ;
    cpu.health = 100;
    cpu.minDamage = 1;
    cpu.maxDamage = 10;
    cpu.armour = 8;
    cpu.critChance = 15;
    player1.critMultiplier =150;

    cout << player1.name << " health: " << player1.health << endl;
    player1.performAttack(Player& cpu); 
    
    
    

    return 0;
}



