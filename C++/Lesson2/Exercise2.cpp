#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>


int randomize() {
    return rand() % 11;
}

int main() {
    srand(time(0)); //initialize time

    int option =  0;
    int score = 0;
    int death = randomize();
    bool playing = true; 


    while (playing){
        std::cout << "\n Choose a option:";
        std::cout << "\n Option 1: eat JUST 1 apple:";
        std::cout << "\n Option 2: Don't EAT NO APPLE BIATCH";
        std::cout << "\n Choose wisely:";
        std::cin >> option;

        if (option == 1){
                //Generate random number to determine if the palyer is dead
                int death = randomize();
                if (death == 0){
                        // 10% chance of death
                        std::cout << "You ate a deadly apple, sorry MATE, you've eaten " << score << " apples" << std::endl;
                        break;
                } else {
                        // If the player is not death, increase the counter
                        score++;
                        std::cout << "you eat an apple and you hate iphone, total score" << score << std::endl;
                }
        } else if (option == 2) {
                //End the game
                std::cout << "Game Over bitch, you ate " << score << " apples" << std::endl;
                break;
        } else {
                // Invalid Option
                std::cout << "Invalid Option, please choose 1 or 2" << std::endl;
        }
    }

    return 0;
}

