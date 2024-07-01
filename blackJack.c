#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>





typedef struct{
    char *suit;
    char *rank;
} Card;

typedef struct 
{
    Card cards[52];
    int top;
} Deck;


int getCardValue(char *rank) {
    if (strcmp(rank, "2") == 0) return 2;
    if (strcmp(rank, "3") == 0) return 3;
    if (strcmp(rank, "4") == 0) return 4;
    if (strcmp(rank, "5") == 0) return 5;
    if (strcmp(rank, "6") == 0) return 6;
    if (strcmp(rank, "7") == 0) return 7;
    if (strcmp(rank, "8") == 0) return 8;
    if (strcmp(rank, "9") == 0) return 9;
    if (strcmp(rank, "10") == 0) return 10;
    if (strcmp(rank, "Jack") == 0) return 10;
    if (strcmp(rank, "Queen") == 0) return 10;
    if (strcmp(rank, "King") == 0) return 10;
    if (strcmp(rank, "Ace") == 0) return 11; // Or 1 depending on game rules
    
    return 0; // Default case, should not happen if inputs are valid
}


void initDeck(Deck *deck){
    char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

    int cardIndex = 0;
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 0; rank < 13; rank++) {
            deck->cards[cardIndex].suit = suits[suit];
            deck->cards[cardIndex].rank = ranks[rank];
            cardIndex++;
        }
    }
    deck->top = 51;
}


void shuffleDeck(Deck *deck){
    deck->top = 51;

    for(int i =51; i >=0; i--){
        int j = rand() % (i+1);
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

Card dealCard(Deck *deck, bool *needShuffle){
    deck->top --;
    if(deck->top <=10){
        printf("shuffling deck after this round \n");
        *needShuffle = true;
    }
    return deck->cards[deck->top];
}


int main(){
    // this is a blackjack game
    Deck deck;
    initDeck(&deck);
    shuffleDeck(&deck);

    bool needsShuffle = false;
    bool inRound = true;
    int winner =2 ; // 0 -> dealer, 1 -> player , 2 no one
    char action;
    while(true){
        printf(" \n \n \n \n");
        inRound = true;
        if(needsShuffle == true){
            shuffleDeck(&deck);
        }
        while(inRound){
            int playerSum = 0;
            int dealerSum = 0;
            for(int i = 0; i < 3; i ++){
                Card card = dealCard(&deck, &needsShuffle);
                int cardVal = getCardValue(card.rank);
                if(i %2 ==0){
                    playerSum += cardVal;
                }
                else{
                    dealerSum+= cardVal;
                }

            }

            printf("player has %d \n dealer has %d \n \n", playerSum, dealerSum);
            scanf("%c", &action);
            if(action == 'h'){
                Card dealt = dealCard(&deck, &needsShuffle);
                int cardVal = getCardValue(dealt.rank);
                playerSum += cardVal;
                printf("player hit!\n");
                printf("card is %s %s and needs a shuffle is %d\n", dealt.rank, dealt.suit, needsShuffle);
                printf("player has %d \n" , playerSum);
            }
            else if(action == 's'){
                printf("player stayed! \n player has %d \n dealer has %d", playerSum, dealerSum);

            }
            if(playerSum > 21){
                printf("PLAYER BUSTED \n");
                winner = 0;
                inRound = false;
            }

            if(inRound == true){
                while(dealerSum < 17){
                    Card dealt = dealCard(&deck, &needsShuffle);
                    int cardVal = getCardValue(dealt.rank);
                    dealerSum += cardVal;
                    printf("dealer drew %s %s \n dealer has %d \n", dealt.rank, dealt.suit, dealerSum);
                }
                if(dealerSum > 21){
                    printf("DEALER BUST! PLAYER WON! \n");
                    winner = 1;
                    inRound = false;
                }

                if(dealerSum > playerSum && inRound){ 
                    // dealer won
                    printf("DEALER WON! \n player has %d . dealer has %d \n", playerSum, dealerSum);
                    winner = 0;
                }
                else if(inRound){
                    // player won
                    printf("PLAYER WON! \n player has %d . dealer has %d \n", playerSum, dealerSum);
                    winner = 1;
                }
                inRound = false;
            }

        }
    }
    return 0;
}