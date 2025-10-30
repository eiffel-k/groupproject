#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	char name[20];
	char occupation[20];
	int gold;
} UserInfo;


int GetUserInput(int optionsMin, int optionsLimit);

void AsteriskWall(int newBefore, int numAsterisks, int newAfter);

UserInfo UserIntro();

int main(void) {
	int i = 0;
	int optionsLimit = 0;
	int optionsMin = 1;
	int tempVal = 0;
	
	bool gameOver = false;
	
	srand(time(NULL));  
	rand(); // I saw someone on stack overflow say you need to add a rand(); prior to your first call, otherwise it continues to be psuedo-random
			// https://stackoverflow.com/a/16569927
	
	int userArea = 0;
	int userChapter = 0; // Designates the chapter of the game the user is in
	
	int userIntroComplete = 0;
	int userChoice = 0;
	int userLocation = 0;
	
	int yesOrNo = 0; // 1 for yes, 2 for no, 0 for default 
	int loopControl = 0; // for prison area loop control 
	int lockNum = 0; // for prison area lock pick
	int randomNum = 0; // for prison area lock pick
	int userInput = 0; // for second user input in prison area
	
	int oldManQuest = 0; // 0: No progress. 1: Quest accepted. 2: Quest complete.
	int hasGoat = 0; // For oldManQuest. 0: No goat. 1: Has goat.
	


	
	// Set the scene for the story
	printf("**********\n");
	printf("You trudge along the path beneath you, your armor weighing down your tired body.\n");
	printf("As you slow to a stop, you see your target in front of you.\n");
	printf("A towering castle emerges from the thicket of trees, and you see the main gate in the distance.\n");
	printf("As you approach the gate, a guard stops you.\n");
	printf("**********\n\n");

	UserInfo user = UserIntro(); // Calls the intro function and sets user.name user.occupation and user.gold

	user.gold = 0;

	
	
	// userArea represents where in the story the player currently is. 0 for main gate, 1 for inside the gate, 2 for jail, 3 for secret entrance etc...
	do {	
		if (userArea == 0) {

			/* FIXME remove redundant intro (replaced by UserIntro())
			if (userIntroComplete == 1) {
				printf("Gate Guard: \"Stop right there!\"\n"); 
				
				while ( userChoice != 1 ) {
					userChoice = 0;
					printf("Gate Guard: \"Please state your name and occupation.\"\n\n");
				
					printf("Name (no spaces) > ");
					
				
				
					printf("Occupation (no spaces) > ");
					
				
				
					
					printf("1) Yes.\n");
					printf("2) No.\n");
					
					while ( userChoice != 1 && userChoice != 2 ) {
						printf("> ");
						scanf("%d", &userChoice);
					}
					printf("\n");
				}

				userIntroComplete = 1;
			}
			*/
			
			userChoice = 0;
			
			printf("Gate Guard: \"Ok %s, if you want to enter, you'll have to pay the entry fee.\"\n", user.name);
			
			printf("1) Pay the entry fee. (50 Gold, %d Gold Owned.)\n", user.gold);
			printf("2) Fight past the guard.\n");
			printf("3) Find another way in.\n");
			
			while ( userChoice != 1 && userChoice != 2 && userChoice != 3 ) {
				
				printf("> ");
				scanf("%d", &userChoice);
			
				if (user.gold < 50 && userChoice == 1) {
					printf("Not enough gold\n");
					userChoice = 0;
				} else if (user.gold >= 50 && userChoice == 1) {
					printf("\nGate Guard: \"Welcome to the castle %s!\"\n", user.name);
					user.gold -= 50;
					userArea = 1;
					continue;
					//go to inside gate;
				} else if (userChoice == 2) {
					printf("\n**********\n");
					printf("You try to fight your way past the guard, but your tired body fails you.\nMore guards rush to the gate, and you are swiftly taken to prison.\n");
					printf("**********\n\n");
					userArea = 2;
					continue;
					// go to prison area;
				} else if (userChoice == 3) {
					AsteriskWall(1, 10, 1);
					printf("As you look around you, you see an unkempt thicket.\n");
					if (oldManQuest == 2) {
						printf("An old man plays happily with his goat, and you can hear the guards letting people in behind you.");
					} else {
						printf("An old man paces worriedly near his pack mule, and you can hear the guards letting people in behind you.");
					}
					AsteriskWall(1, 10, 1);
					userArea = 3;
					continue;
				} else {
					printf("INVALID INPUT\n");
				}
			}	
		}
			
	// OPTION 1 inside gate
		if (userArea == 1) {
			printf("Entering the castle...\n");
			// CODE GOES HERE	
			gameOver = true;
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
			
			printf("1) Pay the prisoner 25 gold to escape. (%d gold owned.)\n", user.gold);
			printf("2) Try to pick the lock.\n");
			printf("3) Wait for a guard to see the consequences of your actions.\n");
	
			userChoice = GetUserInput(1, 3);
			
			if (userChoice == 1) {
				if (user.gold >= 25) {
					printf("\n**********\n");
					printf("You hand the prisoner the gold.\nHe points to a loose stone in the wall.\nIt reveals a tunnel that leads to the inside of the castle.\n");
					printf("**********\n\n");
					user.gold -= 25;
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
	
	// OPTION 3 leave main gate
		if (userArea == 3) {
			
			if (oldManQuest == 1) {
				optionsLimit = 4;
			} else if (oldManQuest == 2) {
				optionsLimit = 2;
			} else {
				optionsLimit = 3;
			}
			
			printf("\n1) Go back to the gate.\n");
			printf("2) Search the bushes near the castle.\n");
			if (oldManQuest != 2) {
				printf("3) Speak to the old man.\n");
			}
			if (oldManQuest == 1 && hasGoat == 0) {
				printf("4) Search deeper in the woods.\n");
			}
			
			tempVal = GetUserInput(1, optionsLimit);
			
			if (tempVal == 1) {
				AsteriskWall(1, 10, 1);
				printf("You give up on your search for now and return to the main gate.");
				AsteriskWall(1, 10, 2);
				userArea = 0;
				continue;
			} else if (tempVal == 2) {
				AsteriskWall(1, 10, 1);
				printf("You search the bushes near the castle and discover a hole in the castle wall.");
				AsteriskWall(1, 10, 1);
				printf("\nDo you want to enter the castle?\n");
				printf("1) Yes.\n");
				printf("2) No.\n");
				tempVal = GetUserInput(1, 2);
				if (tempVal == 1) {
					userArea = 1;
					continue;
				} else if (tempVal == 2) {
					printf("\nYou turn around and pretend you saw nothing.\n");
					userArea = 3;
					continue;
				}
			} else if (tempVal == 3) {
				if (oldManQuest == 0) {
					printf("\nOld Man: \"You look plenty strong. Could you please give an old man a hand?\"\n");
					printf("1) Help the old man.\n");
					printf("2) Turn around and ignore him\n");
					tempVal = GetUserInput(1, 2);
					if (tempVal == 1) {
						printf("\nOld Man: \"Thank you so much kind stranger! My beloved goat has wandered off and I can't find him.\"\n");
						printf("Old Man: \"If you spot him please bring him back to me. I'll reward you with as much gold as I can part with.\"\n");
						oldManQuest = 1;
						userArea = 3;
						continue;
					} else if (tempVal == 2) {
						printf("\nOld Man: \"You could at least answer me...\"\n");
						userArea = 3;
						continue;
					} else {
						printf("Something went wrong...\n");
					}
				} else if (oldManQuest == 1) {
					if (hasGoat == 0) {
						printf("\nOld Man: \"Have you found my goat yet? I get more worried the longer he's missing...'\"\n");
						continue;
					} else if (hasGoat == 1) {
						printf("\nOld Man: \"My goat! Thank you so much kind stranger. Please take 50 gold for your time.\"\n");
						printf("Old Man: \"My dear goat here doesn't seem to be able to hear very well. I was worried an animal would sneak up on it...\"\n");
						user.gold = user.gold + 50;
						oldManQuest = 2;
						userArea = 3;
						continue;
					}
				}
			} else if (tempVal == 4 && oldManQuest == 1 && hasGoat == 0) {
				tempVal = 0;
				AsteriskWall(1, 10, 1);
				printf("As you walk deeper into the woods you grow closer to a clearing.\n");
				printf("Your ears are filled with the sounds of the forest, and the bleating of a goat.");
				AsteriskWall(1, 10, 1);
				while (tempVal != 2) {
					printf("\n1) Call out to the goat to come closer\n");
					printf("2) Sneak up on the goat\n");
					tempVal = GetUserInput(1, 2);
					if (tempVal == 1) {
						AsteriskWall(1, 10, 1);
						printf("You call out to the goat, but it doesn't seem to hear you.");
						AsteriskWall(1, 10, 1);
					} else if (tempVal == 2) {
						AsteriskWall(1, 10, 1);
						printf("You creep up on the goat, your armor making a racket the whole way. It's a miracle the goat didn't hear you.\n");
						printf("With the goat still screaming in your arms, you make your way back the way you came.");
						AsteriskWall(1, 10, 1);
						hasGoat = 1;
						userArea = 3;
						continue;
					}
				}
			}
			
			
			
		}

		

	} while (gameOver == false);
	

	return 0;
}

int GetUserInput(int optionsMin, int optionsLimit) { // Function for getting user input. Parameters are inclusive, GetUserInput(1, 4); has a valid input of 1, 2, 3, or 4.
	int userIn = 0;
	
	do {
		printf("> ");
		scanf("%d", &userIn);
		if (userIn < optionsMin || userIn > optionsLimit) {
			printf("Invalid input\n");
		}
	} while (userIn < optionsMin || userIn > optionsLimit);
	
	return userIn;
}

void AsteriskWall(int newBefore, int numAsterisks, int newAfter) { // newBefore = number of newlines before asterisks | numAsterisks = number of asterisks | newAfter = number of newlines after asterisks
	int i = 0;
	for (i = 0; i < newBefore; i++) {
		printf("\n");
	}
	
	for (i = 0; i < numAsterisks; i++) {
		printf("*");
	}

	for (i = 0; i < newAfter; i++) {
		printf("\n");
	}

	return;
}

UserInfo UserIntro() {

	UserInfo info;

	int userChoice = 0;

	printf("Gate Guard: \"Stop right there!\"\n"); 
				
	while ( userChoice != 1 ) {
		userChoice = 0;
		printf("Gate Guard: \"Please state your name and occupation.\"\n\n");
	
		printf("Name (no spaces) > ");
		scanf("%s", info.name);
	
	
		printf("Occupation (no spaces) > ");
		scanf("%s", info.occupation);
	
	
		printf("\nGate Guard: \"%s the %s?\"\n", info.name, info.occupation); 
		printf("1) Yes.\n");
		printf("2) No.\n");
		
		while ( userChoice != 1 && userChoice != 2 ) {
			printf("> ");
			scanf("%d", &userChoice);
		}
		printf("\n");

		
	}

	return info;

}






