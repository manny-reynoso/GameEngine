#include <iostream>
#include <ctime> // for time()
#include <string> 
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

    int armourMechanic(int incomingDamage) {
        
        double reduction = armour / 100.0; // 8 → 0.08 = 8% reduction
        int damageTaken = static_cast<int>(incomingDamage * (1.0 - reduction));

        cout << name << " has an armour rating of "  << armour << endl;
        cout << name << " got hit for " << damageTaken << endl;

        return damageTaken;
    }

        void takeDamage(int incomingDamage){

            int damageTaken = armourMechanic(incomingDamage);
            health -= damageTaken ; //Substract the damage from targets health

            if(health < 0){
                health = 0;
            }
            //output the result!

            cout << name << " took " << damageTaken << " and now has " << health << " health!" << endl;


        };  

    int performAttack(Player& target) {
        int baseDamage = attackMechanic();
        int finalDamage = critAttack(baseDamage);

        std::cout << name << " hits " << target.name
                << " for " << finalDamage << " before armour!" << std::endl;

        target.takeDamage(finalDamage); // actually change target HP

    return finalDamage;
}

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
    cpu.critMultiplier =150;

    cout << player1.name << " health: " << player1.health << endl;

    while (player1.health > 0 && cpu.health > 0){
    player1.performAttack(cpu); 
    cpu.performAttack(player1);
    }

    if (player1.health == 0){
            cout << cpu.name <<  " killed " << player1.name << " !" <<endl; };
    
    if (cpu.health == 0){
            cout << player1.name <<  " killed " << cpu.name << " !" <<endl; };

    return 0;
}



