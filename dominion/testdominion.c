#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "rngs.h"
#include "interface.h"


int main(int argc, char *argv[]){
	time_t t;
	srand((unsigned) time(&t));

	struct gameState *state = newGame();

	int k[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int card, checkSame, players, seed, x, i, coins, curPlayer;
	int curCard = 0;
	int cardLocation;
	char cardName[100];
	int actionCard;

	int getWin[MAX_PLAYERS];

	if(argc == 2){
		seed = atoi(argv[1]);
	}
	else{
		seed = rand();
	}

	checkSame = 0;
	for(int i = 0; i < 10; i++){
		// Find random card between adventurer and treasure_map
		card = (rand() % 20) + adventurer;
		//floor(Random() * 20)+ adventurer;
		for(int j = 0; j < i; j++){
			if(card == k[j]){
				checkSame = 1;
				break;
			}
			else
				checkSame = 0;
		}
		// If duplicate back track
		if(checkSame == 1)
			i--;
		// otherwise assign kingdom card
		else
			k[i] = card;
	}

	printf("--------- BEGIN GAME ---------\n");
	printf("Here are the kindom cards: \n");
	for(int i = 0; i < 10; i++){
		cardNumToName(k[i], cardName);
		printf("%s\n", cardName);
	}

	// Between 2-4 players
	players = (rand() % 3) + 2;
	//floor(Random() * 3) + 2;
	state->numPlayers = players;

	x = initializeGame(players, k, seed, state);
	if(x == -1)
		printf("Initialize game failed\n");

	while(!isGameOver(state)){
		curPlayer = state->whoseTurn;
		printf("--- Starting turn for player: %d ---\n", curPlayer);
		cardLocation = 0;

		// Avoid feast and tribute infinite loop
		actionCard = 0;
		for(i = 0; i < numHandCards(state); i++){
			if(handCard(i, state) < treasure_map && handCard(i, state) >= adventurer
					&& handCard(i, state) != feast && handCard(i, state) != tribute){
				actionCard = i;
				break;
			}
		}

		printf("Starting action phase\n");
		while(state->numActions > 0 && actionCard != 0){
			curCard = handCard(i, state);
			cardNumToName(curCard, cardName);

			x = playCard(actionCard, -1, -1, -1, state);

			if(x == -1){
				discardCard(cardLocation, curPlayer, state, 0);
			}
			else{
				printf("Played card: %s, %d\n", cardName, curCard);
			}

			if(state->numActions <= 0){
				printf("All actions used, action phase over\n");
				break;
			}

			// Look for next action card
			for(i = actionCard; i < numHandCards(state); i++){
				if(handCard(i, state) < treasure_map && handCard(i, state) >= adventurer
						&& handCard(i, state) != feast && handCard(i, state) != tribute){
					actionCard = i;
					break;
				}
				else
					actionCard = 0;
			}
		}

		printf("Buy Phase\n");
		coins = 0;
		for(i = 0; i < numHandCards(state); i++){
			if(handCard(i, state) == copper)
				coins++;
			else if(handCard(i, state) == silver)
				coins = coins + 2;
			else if(handCard(i, state) == gold)
				coins = coins + 3;
		}
		// Buy while you still can
		while(state->numBuys > 0 && coins > 0){
			do{
				x = rand() % 2;
				cardLocation = rand() % 10;

				if(x)
					card = k[cardLocation];
				else
					card = rand() % treasure_map;
			}while(buyCard(card, state) != 0);

			cardNumToName(card, cardName);
			printf("Buying card: %s\n", cardName);
		}
		printf("Buy Phase over\n");
		printf("End turn\n");
		endTurn(state);
	}

	getWinners(getWin, state);
	printf("\n -------- SCOREBOARD --------\n\n");
	int winnerPlayer;
	for(i = 0; i < state->numPlayers; i++){
		printf("Final Player %d has a score of: %d\n", i, scoreFor(i, state));
		if(getWin[i] == 1){
			winnerPlayer = i;
		}
	}

	printf("\nThe winner is player: %d\n", winnerPlayer);
	printf("Their Final score was: %d\n", scoreFor(winnerPlayer, state));
	printf("Game Over\n\n");
}
