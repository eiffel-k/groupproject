#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



typedef struct { // Holds important information about the user

	char name[20];
	char occupation[20];
	int gold;
	int choice;

	int oldManQuest; // 0: No progress. 1: Quest accepted. 2: Quest complete.
	int hasGoat; // For oldManQuest. 0: No goat. 1: Has goat.
	int numChoices; // For oldManQuest (for now). Max number of choices that show up for the user

	int area;
	bool gameOver;
	
} UserInfo;

// Function declarations

int GetUserInputNum(int optionsMin, int optionsLimit);

void AsteriskWall(int newBefore, int numAsterisks, int newAfter);

UserInfo UserIntro();

UserInfo MainGate(UserInfo user); // user.area 0

UserInfo PrisonArea(UserInfo user); // user.area 1

UserInfo OutsideGate(UserInfo user); // user.area 2

UserInfo InsideGate(UserInfo user); // user.area 3

int main(void) {

	int i = 0;
	
	srand(time(NULL));  
	rand(); // I saw someone on stack overflow say you need to add a rand(); prior to your first call, otherwise it continues to be psuedo-random
			// https://stackoverflow.com/a/16569927


	UserInfo user = UserIntro(); // Calls the intro function and sets initial user values

	
	// user.area represents where in the story the player currently is. 0 for main gate, 1 for inside the gate, 2 for prison, 3 for outside gate etc...
	do {	

		if (user.area == 0) { 

			user = MainGate(user);

		} else if (user.area == 1) { 

			user = InsideGate(user);

		} else if (user.area == 2) {

			user = PrisonArea(user);

		} else if (user.area == 3) {

			user = OutsideGate(user);
			
		}

	} while (user.gameOver == false);
	

	return 0;
	
}


int GetUserInputNum(int optionsMin, int optionsLimit) { // Function for getting user input. Parameters are inclusive, GetUserInputNum(1, 4); has a valid input of 1, 2, 3, or 4.
	
	int userIn = 0;
	
	do {

		printf("> ");
		scanf("%d", &userIn);
		if (userIn < optionsMin || userIn > optionsLimit) {
			printf("Invalid input\n");
		} else {
			break;
		}

	} while (1);
	
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

	UserInfo temp;

	temp.gold = 0;
	temp.area = 0;
	temp.oldManQuest = 0;
	temp.hasGoat = 0;
	temp.gameOver = false;
	temp.numChoices = 0;

	int userConfirm = 0;

	// Set the scene for the story
	AsteriskWall(0, 10, 1);
	printf("You trudge along the path beneath you, your armor weighing down your tired body.\n");
	printf("As you slow to a stop, you see your target in front of you.\n");
	printf("A towering castle emerges from the thicket of trees, and you see the main gate in the distance.\n");
	printf("As you approach the gate, a guard stops you.");
	AsteriskWall(1, 10, 2);

	printf("Gate Guard: \"Stop right there!\"\n"); 
				
	while ( userConfirm != 1 ) {

		printf("Gate Guard: \"Please state your name and occupation.\"\n\n");
	
		printf("Name (no spaces) > ");
		scanf("%s", temp.name);
	
	
		printf("Occupation (no spaces) > ");
		scanf("%s", temp.occupation);
	
	
		printf("\nGate Guard: \"%s the %s?\"\n", temp.name, temp.occupation); 
		printf("1) Yes.\n");
		printf("2) No.\n");
		

		userConfirm = GetUserInputNum(1, 2);

		printf("\n");

	}

	return temp;

}


UserInfo MainGate(UserInfo user) {

	user.choice = 0;
	
	printf("Gate Guard: \"Ok %s, if you want to enter, you'll have to pay the entry fee.\"\n", user.name);
	
	printf("1) Pay the entry fee. (50 Gold, %d Gold Owned.)\n", user.gold);
	printf("2) Fight past the guard.\n");
	printf("3) Find another way in.\n");
	
	do { // Handles invalid input if gold is < 50
		user.choice = GetUserInputNum(1, 3);
		if (user.gold < 50 && user.choice == 1) {
			printf("Not enough gold.\n");
		} else {
			break;
		}
		
	} while (1);


	if (user.choice == 1) { //go to inside gate

		printf("\nGate Guard: \"Welcome to the castle %s!\"\n", user.name);
		user.gold -= 50;
		user.area = 1;
		return user;

	} else if (user.choice == 2) { // go to prison area

		AsteriskWall(1, 10, 1);
		printf("You try to fight your way past the guard, but your tired body fails you.\nMore guards rush to the gate, and you are swiftly taken to prison.");
		AsteriskWall(1, 10, 2);
		user.area = 2;
		return user;

	} else if (user.choice == 3) { // go to outside gate
		
		AsteriskWall(1, 10, 1);
		printf("As you look around you, you see an unkempt thicket.\n");

		if (user.oldManQuest == 2) {

			printf("An old man plays happily with his goat, and you can hear the guards letting people in behind you.");

		} else {

			printf("An old man paces worriedly near his pack mule, and you can hear the guards letting people in behind you.");

		}

		AsteriskWall(1, 10, 1);
		user.area = 3;
		return user;
		
	}
	
}

UserInfo PrisonArea(UserInfo user) {

	int loopControl = 0; // for prison area loop control 
	int lockNum = 0; // for prison area lock pick
	int randomNum = 0; // for prison area lock pick

	printf("Entering prison...\n");
	AsteriskWall(1, 10, 1);
	printf("You awaken in a cold, damp cell, surrounded by stone walls and the steady echo of dripping water.\n");
	printf("In the shadowed corner, a prisoner watches you. \nHis eyes burn with intensity, and a wavering grin stretches across his face.\n");
	printf("He whispers from the corner, only loud enough for you to hear. \nPrisoner: \"There's a way out, but it will cost you.\"");
	AsteriskWall(1, 10, 2);
	
	printf("1) Pay the prisoner 25 gold to escape. (%d gold owned.)\n", user.gold);
	printf("2) Try to pick the lock.\n");
	printf("3) Wait for a guard to see the consequences of your actions.\n");

	do { // Handles invalid input if gold is < 25
		user.choice = GetUserInputNum(1, 3);
		if (user.gold < 25 && user.choice == 1) {
			printf("Not enough gold.\n");
		} else {
			break;
		}
		
	} while (1);
	
	if (user.choice == 1) { //go to inside gate

		AsteriskWall(1, 10, 1);
		printf("You hand the prisoner the gold.\nHe points to a loose stone in the wall.\nIt reveals a tunnel that leads to the inside of the castle.");
		AsteriskWall(1, 10, 2);
		user.gold -= 25;
		loopControl = 1;
		user.area = 1;
		

	} else if (user.choice == 2) {

		AsteriskWall(1, 10, 1);
		printf("You find an old rusty nail in the cracks of the floor.\nYou use it to try and pick the lock.");
		AsteriskWall(1, 10, 2);
		printf("Pick a number from 1 to 3, the correct number will unlock the lock.\n");						
		lockNum = 0;
		randomNum = (rand() % 3) + 1;

		while (lockNum != randomNum) {

			lockNum = GetUserInputNum(1, 3);

			if (lockNum != randomNum) {
				printf("Try again.\n");
			}
			
		} 

		AsteriskWall(1, 10, 1);
		printf("You hear a click as the lock opens.\nYou push open the door and run down a hall, up some stairs, and out a door into the halls of the castle.\n");
		printf("You peak through a window and notice a wagon getting ready to leave.\nKnowing the guards will notice you've escaped, you figure this is your only way out of the castle.\n");
		printf("You decide to try and sneak into the back of the wagon.\nAs you sneak into the wagon. You catch the attention of a guard nearby.");
		AsteriskWall(1, 10, 2);
		printf("Guard: \"Hey! what are you doing in there?!\"\n");
		
		printf("1) Tell him you are from the nearby village that was transporting ale to the castle and you are getting the wagon ready to go back home\n");
		printf("2) Tell him the King asked you to check the wagons for any food or goods left.\n");
		
		while (loopControl != 1) {

			user.choice = GetUserInputNum(1, 3);

			if (user.choice == 1) {

				AsteriskWall(1, 10, 1);
				printf("The guard takes a couple seconds to respond. Putting you on edge. Maybe he already knows about you escaping.\n");
				printf("He smiles and laughs. \nGuard: \"That ale sure is good! Just make sure you bring double the amount next time.\" \nGuard: \"Us guards sure love to get into the ale after work. Well, carry on.\"\n");
				printf("You nod as he turns and walks away. You decide to grab a blanket out of the back and take the wagon for yourself. \nYou hop on and head to the gate. The guards open the gate and you carry on through to freedom. Never looking back.");
				AsteriskWall(1, 10, 2);
				printf("Game Over.\n");
				user.gameOver = true;
				loopControl = 1;		

			} else if (user.choice == 2) {

				AsteriskWall(1, 10, 1);
				printf("The guard doesn't seem to believe your story. He asked you to step out of the wagon.\nGuard: \"Why don't we go see the king?\"\n");
				printf("As you and the guard are walking back into the halls of the castle, multiple guards rush by. \nYou recognize one of them as the one that brought you to the prison.\n");
				printf("You both lock eyes and he recognizes you.\n2nd Guard: \"Hey! that's the escaped prisoner!\"\n");
				printf("You are brought back to a more secure prison cell where you will be sentenced to a life of manual labor.");
				AsteriskWall(1, 10, 2);
				printf("Game Over.\n");
				user.gameOver = true;
				loopControl = 1;	

			} else {
				printf("INVALID INPUT\n");
			}
		}
				
		loopControl = 1;
		
	} else if (user.choice == 3) {

		AsteriskWall(1, 10, 1);
		printf("Days have gone by as you sit in your cell.\nGuards finally come and get you.\nYou've been banished from the castle forever.");
		AsteriskWall(1, 10, 2);
		printf("Game Over.\n");
		user.gameOver = true;
		loopControl = 1;

	} else {
		printf("INVALID INPUT\n");
	} 

	return user;
	
}


UserInfo OutsideGate(UserInfo user) {


	user.choice = 0;


	if (user.oldManQuest == 1) {
		user.numChoices = 4;
	} else if (user.oldManQuest == 2) {
		user.numChoices = 2;
	} else {
		user.numChoices = 3;
	}
	
	printf("\n1) Go back to the gate.\n");
	printf("2) Search the bushes near the castle.\n");

	if (user.oldManQuest != 2) {

		printf("3) Speak to the old man.\n");

	} else if (user.oldManQuest == 1 && user.hasGoat == 0) {

		printf("4) Search deeper in the woods.\n");

	}
	
	user.choice = GetUserInputNum(1, user.numChoices);
	
	if (user.choice == 1) {

		AsteriskWall(1, 10, 1);
		printf("You give up on your search for now and return to the main gate.");
		AsteriskWall(1, 10, 2);
		user.area = 0;
		return user;
		
	} else if (user.choice == 2) {

		AsteriskWall(1, 10, 1);
		printf("You search the bushes near the castle and discover a hole in the castle wall.");
		AsteriskWall(1, 10, 2);
		printf("Do you want to enter the castle?\n");
		printf("1) Yes.\n");
		printf("2) No.\n");
		user.choice = GetUserInputNum(1, 2);

		if (user.choice == 1) {

			user.area = 1;
			return user;

		} else if (user.choice == 2) {

			printf("\nYou turn around and pretend you saw nothing.\n");
			user.area = 3;
			return user;

		}

	} else if (user.choice == 3) {

		if (user.oldManQuest == 0) {

			printf("\nOld Man: \"You look plenty strong. Could you please give an old man a hand?\"\n");
			printf("1) Help the old man.\n");
			printf("2) Turn around and ignore him\n");
			user.choice = GetUserInputNum(1, 2);

			if (user.choice == 1) {

				printf("\nOld Man: \"Thank you so much kind stranger! My beloved goat has wandered off and I can't find him.\"\n");
				printf("Old Man: \"If you spot him please bring him back to me. I'll reward you with as much gold as I can part with.\"\n");
				user.oldManQuest = 1;
				user.area = 3;
				return user;

			} else if (user.choice == 2) {

				printf("\nOld Man: \"You could at least answer me...\"\n");
				user.area = 3;
				return user;

			} else {

				printf("Something went wrong...\n");

			}

		} else if (user.oldManQuest == 1) {

			if (user.hasGoat == 0) {

				printf("\nOld Man: \"Have you found my goat yet? I get more worried the longer he's missing...'\"\n");
				return user;

			} else if (user.hasGoat == 1) {

				printf("\nOld Man: \"My goat! Thank you so much kind stranger. Please take 50 gold for your time.\"\n");
				printf("Old Man: \"My dear goat here doesn't seem to be able to hear very well. I was worried an animal would sneak up on it...\"\n");
				user.gold = user.gold + 50;
				user.oldManQuest = 2;
				user.area = 3;
				return user;

			}
		}

	} else if (user.choice == 4 && user.oldManQuest == 1 && user.hasGoat == 0) {

		user.choice = 0;
		AsteriskWall(1, 10, 1);
		printf("As you walk deeper into the woods you grow closer to a clearing.\n");
		printf("Your ears are filled with the sounds of the forest, and the bleating of a goat.");
		AsteriskWall(1, 10, 1);

		while (user.choice != 2) {

			printf("\n1) Call out to the goat to come closer\n");
			printf("2) Sneak up on the goat\n");
			user.choice = GetUserInputNum(1, 2);

			if (user.choice == 1) {

				AsteriskWall(1, 10, 1);
				printf("You call out to the goat, but it doesn't seem to hear you.");
				AsteriskWall(1, 10, 1);

			} else if (user.choice == 2) {

				AsteriskWall(1, 10, 1);
				printf("You creep up on the goat, your armor making a racket the whole way. It's a miracle the goat didn't hear you.\n");
				printf("With the goat still screaming in your arms, you make your way back the way you came.");
				AsteriskWall(1, 10, 1);
				user.hasGoat = 1;
				user.area = 3;
				return user;

			}
			
		}
		
	}
			
}


UserInfo InsideGate(UserInfo user) { //FIXME area needs to be created

	printf("Entering the castle...\n");
	// CODE GOES HERE	
	user.gameOver = true;
    return user;
	
}



