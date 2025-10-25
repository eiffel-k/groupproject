#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



int main(void) {
	
	bool gameOver = false;
	
	srand(time(NULL));  
	rand(); // I saw someone on stack overflow say you need to add a rand(); prior to your first call, otherwise it continues to be psuedo-random
			// https://stackoverflow.com/a/16569927
	
	while (gameOver == false) {
		
		int userArea = 0;
		char userName[20];
		char userOccupation[20];
		int userChoice = 0;
		int userLocation = 0;
		int userGold = 0;
		
		int yesOrNo = 0; // 1 for yes, 2 for no, 0 for default 
		int loopControl = 0; // for prison area loop control 
		int lockNum = 0; // for prison area lock pick
		int randomNum = 0; // for prison area lock pick
		int userInput = 0; // for second user input in prison area
	
	
		
		// Set the scene for the story
		printf("**********\n");
		printf("You trudge along the path beneath you, your armor weighing down your tired body.\n");
		printf("As you slow to a stop, you see your target in front of you.\n");
		printf("A towering castle emerges from the thicket of trees, and you see the main gate in the distance.\n");
		printf("As you approach the gate, a guard stops you.\n");
		printf("**********\n\n");
		
		// userArea represents where in the story the player currently is. 0 for main gate, 1 for inside the gate, 2 for jail, 3 for secret entrance etc...
		do {	
			if (userArea == 0) {
				printf("Gate Guard: \"Stop right there!\"\n"); 
				
				while ( userChoice != 1 ) {
					userChoice = 0;
					printf("Gate Guard: \"Please state your name and occupation.\"\n\n");
				
					printf("Name (no spaces) > ");
					scanf("%s", userName);
				
				
					printf("Occupation (no spaces) > ");
					scanf("%s", userOccupation);
				
				
					printf("\nGate Guard: \"%s the %s?\"\n", userName, userOccupation); 
					printf("1) Yes.\n");
					printf("2) No.\n");
					
					while ( userChoice != 1 && userChoice != 2 ) {
						printf("> ");
						scanf("%d", &userChoice);
					}
					printf("\n");
				}
				
				userChoice = 0;
				
				printf("Gate Guard: \"Ok %s, if you want to enter, you'll have to pay the entry fee.\"\n", userName);
				
				printf("1) Pay the entry fee. (50 Gold, %d Gold Owned.)\n", userGold);
				printf("2) Fight past the guard.\n");
				printf("3) Find another way in.\n");
				
				while ( userChoice != 1 && userChoice != 2 && userChoice != 3 ) {
					
					printf("> ");
					scanf("%d", &userChoice);
				
					if (userGold < 50 && userChoice == 1) {
						printf("Not enough gold\n");
						userChoice = 0;
					} else if (userGold >= 50 && userChoice == 1) {
						printf("Gate Guard: \"Welcome to the castle %s!\"\n", userName);
						userGold -= 50;
						userArea = 1;
						//go to inside gate;
					} else if (userChoice == 2) {
						printf("\n**********\n");
						printf("You try to fight your way past the guard, but your tired body fails you.\nMore guards rush to the gate, and you are swiftly taken to prison.\n");
						printf("**********\n\n");
						userArea = 2;
						continue;
						// go to prison area;
					} else if (userChoice == 3) {
						printf("\n**********\n");
						printf("You don't have the money to pay the entry fee, so you decide to find another way to get in.\n");
						printf("**********\n\n");
						userArea = 3;
						continue;
					} else {
						printf("INVALID INPUT\n");
					}
				}	
			}
				
		// OPTION 1 inside gate
			if (userArea == 1) {
				printf("Entering the castle gate...\n");
				// CODE GOES HERE	
				break;
			}
		
		// OPTION 2 prison area
			if (userArea == 2) {
				printf("Entering prison...\n");
				printf("\n**********\n");
				printf("You awaken in a cold, damp cell, surrounded by stone walls and the steady echo of dripping water.\n");
				printf("In the shadowed corner, a prisoner watches you. \nHis eyes burn with intensity, and a wavering grin stretches across his face.\n");
				printf("He whispers from the corner, only loud enough for you to hear. \nPrisoner: \"There's a way out, but it will cost you.\"\n");
				printf("**********\n\n");
				
				printf("1) Pay the prisoner 25 gold to escape. (%d gold owned.)\n", userGold);
				printf("2) Try to pick the lock.\n");
				printf("3) Wait for a guard to see the consequences of your actions.\n");
				
				while (loopControl != 1) {
					printf("> ");
					scanf("%d", &userChoice);
					
					if (userChoice == 1) {
						if (userGold >= 25) {
							printf("\n**********\n");
							printf("You hand the prisoner the gold.\n He points to a loose stone in the wall.\n It reveals a tunnel that leads to the inside of the castle.\n");
							printf("**********\n\n");
							userGold -= 25;
							loopControl = 1;
							userArea = 1;
							continue;
							//go to inside gate
						} else {
							printf("Not enough gold.\n");
						} 
					} else if (userChoice == 2) {
						printf("\n**********\n");
						printf("You find an old rusty nail in the cracks of the floor.\nYou use it to try and pick the lock.\n");
						printf("**********\n\n");
						printf("Pick a number from 1 to 3, the correct number will unlock the lock.\n");						
						lockNum = 0;
						randomNum = (rand() % 3) + 1;
						while (lockNum != randomNum) {
							printf("> ");
							scanf("%d", &lockNum);
							if (lockNum != randomNum) {
								printf("Try again.\n");
							}
						} 
						printf("\n**********\n");
						printf("You hear a click as the lock opens.\nYou push open the door and run down a hall, up some stairs, and out a door into the halls of the castle.\n");
						printf("You peak through a window and notice a wagon getting ready to leave.\nKnowing the guards will notice you've escaped, you figure this is your only way out of the castle.\n");
						printf("You decide to try and sneak into the back of the wagon.\nAs you sneak into the wagon. You catch the attention of a guard nearby.\n");
						printf("**********\n\n");
						printf("Guard: \"Hey! what are you doing in there?!\"\n");
						
						printf("1) Tell him you are from the nearby village that was transporting ale to the castle and you are getting the wagon ready to go back home\n");
						printf("2) Tell him the King asked you to check the wagons for any food or goods left.\n");
						
						while (loopControl != 1) {
							printf("> ");
							scanf("%d", &userInput);
							if (userInput == 1) {
								printf("\n**********\n");
								printf("The guard takes a couple seconds to respond. Putting you on edge. Maybe he already knows about you escaping.\n");
								printf("He smiles and laughs. \nGuard: \"That ale sure is good! Just make sure you bring double the amount next time.\" \nGuard: \"Us guards sure love to get into the ale after work. Well, carry on.\"\n");
								printf("You nod as he turns and walks away. You decide to grab a blanket out of the back and take the wagon for yourself. \nYou hop on and head to the gate. The guards open the gate and you carry on through to freedom. Never looking back.\n");
								printf("**********\n\n");
								printf("Game Over.\n");
								gameOver = true;
								loopControl = 1;							
							} else if (userInput == 2) {
								printf("\n**********\n");
								printf("The guard doesn't seem to believe your story. He asked you to step out of the wagon.\nGuard: \"Why don't we go see the king?\"\n");
								printf("As you and the guard are walking back into the halls of the castle, multiple guards rush by. \nYou recognize one of them as the one that brought you to the prison.\n");
								printf("You both lock eyes and he recognizes you.\n2nd Guard: \"Hey! that's the escaped prisoner!\"\n");
								printf("You are brought back to a more secure prison cell where you will be sentenced to a life of manual labor.\n");
								printf("**********\n\n");
								printf("Game Over.\n");
								gameOver = true;
								loopControl = 1;							
							} else {
								printf("INVALID INPUT\n");
							}
						}
								
						loopControl = 1;
						
					} else if (userChoice == 3) {
						printf("\n**********\n");
						printf("Days have gone by as you sit in your cell.\nGuards finally come and get you.\nYou've been banished from the castle forever.\n");
						printf("**********\n\n");
						printf("Game Over.\n");
						gameOver = true;
						loopControl = 1;
					} else {
						printf("INVALID INPUT\n");
					} 
				} 
				
				break;
			}
		
	 	// OPTION 3 leave main gate
			if (userArea == 3) {
				printf("Leaving the main gate...\n");
				// CODE GOES HERE
				gameOver = true;
				break;
			}

	
	
		} while (gameOver == false);
		
		break; // NEEDS TO BE REPLACED WITH A PROPER GAMEOVER
	}
	
	return 0;
}
