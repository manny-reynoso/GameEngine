#include <iostream>
#include <ctime> // for time()
#include <string> 
#include <cstdlib> // for rand() and srand()
#include <chrono>
#include <thread>
using namespace std;


void typewrite(const std::string& text, int delayMs) {
    for (char c : text) {
        std::cout << c << std::flush; // force this character to appear
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}



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
        cout << name << " \n\nrolled " << attackRoll << "!!" << endl;
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

int blockAttack() {}
};

int main() {
    srand(time(NULL)); // Seed the random number generator once
    int round = 1;

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

    

    while (player1.health > 0 && cpu.health > 0) {
         typewrite(string("\n============= Round ")
          + to_string(round)
          + " =================\n", 30);

         cout << player1.name << " HP: " << player1.health
             << " | CPU HP: " << cpu.health << "\n";

        // ------------------------
        //  PLAYER TURN
        // ------------------------
        cout << "\nChoose an action:\n";
        cout << "1. Attack\n";
        cout << "2. Block\n";
        cout << "3. Heal\n";
        cout << "4. Quit\n";
        cout << "Enter choice: ";

        int choice ;
        cin >> choice;

        if (choice ==1){
            cout << "\nYou chose ATTACK!\n";
            player1.performAttack(cpu);
        }

        else if (choice ==2){
            cout << "\nYou chose BLOCK! But it is not in game...\n";
            //player1.isBlocking = true;   // Blocks the next hit
        }

        else if (choice == 3){
            cout << "\nYou chose HEAL! But it is not in game...\n";
            //player1.heal();
        }

        else if (choice ==4){
            cout << "\n You ran away from battle...\n";
            break;
        }

        else {
            cout << "\nInvalid choice. You lose your turn!\n";
        };

        if (cpu.health <= 0) break;

        cpu.performAttack(player1);
        if (player1.health <= 0) break;
    
    round++ ;
    }

    
     if (player1.health == 0 && cpu.health == 0) {
        std::cout << "Both " << player1.name << " and " << cpu.name
                  << " have fallen!" << std::endl;
    } else if (player1.health == 0) {
        std::cout << cpu.name << " killed " << player1.name << "!" << std::endl;
    } else if (cpu.health == 0) {
        std::cout << player1.name << " killed " << cpu.name << "!" << std::endl;
    }
   

    return 0;
}



