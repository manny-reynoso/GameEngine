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


    int armourMechanic(int armour, int finalDamage) {
        
        
        int damageTaken = static_cast<int>(finalDamage*((armour / 100.0)-100.0));
        cout << "Player has an armour rating of "  << armour << endl;
        cout << "Player got hit for " << damageTaken << endl;
    }

    int attackMechanic() {
        int attackRoll = (rand() % 20) + 1; // random number between 1 and 20

        // LERP calculation for true damage
        int trueDamage = minDamage + static_cast<int>(
            ((attackRoll - 1) / 19.0) * (maxDamage - minDamage)
        );
        cout << "Player rolled " << attackRoll << "!!" << endl;
        cout << "Player base damage for " << trueDamage << "!!" << endl;

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

    int performAttack ( ){

        int baseDamage = attackMechanic();        // get base damage
        int finalDamage = critAttack(baseDamage); // apply crit if any

        cout << "Player hit for " << damageTaken << "!" << endl;
        return finalDamage;
    };



};

int main() {
    srand(time(NULL)); // Seed the random number generator once

    Player player1;
    player1.health = 100;
    player1.minDamage = 1;
    player1.maxDamage = 10;
    player1.armour = 8;
    player1.critChance = 15;
    player1.critMultiplier =150;

    Player cpu;
    cpu.health = 100;
    cpu.minDamage = 1;
    cpu.maxDamage = 10;
    cpu.armour = 8;
    cpu.critChance = 15;
    player1.critMultiplier =150;

    cout << "Player health: " << player1.health << endl;
    player1.performAttack(); 
    
    

    return 0;
}



