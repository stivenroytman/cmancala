#include <stdio.h>

// Declaring some templates for printing the board.
#define SIDE1_FMT "\n%i -- %i | %i | %i | %i | %i | %i      \n"
#define SIDE2_FMT "     %i | %i | %i | %i | %i | %i -- %i\n"

// Holds each player's side of the board and a shared pointer for manipulating
// their values.
struct Board {
    int side1[7];
    int side2[7];
    int * choiceptr;
};

// Fills up each side with 7 marbles, except for the last field which is given 0.
// That's where player scored marbles go.
struct Board init() {
    struct Board gameboard;
    gameboard.choiceptr = &gameboard.side1[0];
    for (; gameboard.choiceptr != &gameboard.side1[6]; gameboard.choiceptr++){
        *gameboard.choiceptr = 7;
    };
    *gameboard.choiceptr = 0;
    gameboard.choiceptr = &gameboard.side2[0];
    for (; gameboard.choiceptr != &gameboard.side2[6]; gameboard.choiceptr++){
        *gameboard.choiceptr = 7;
    };
    *gameboard.choiceptr = 0;
    return gameboard;
}

// Sets the game board pointer to the side given by playernum and the field given by choice.
int * set_choiceptr(struct Board * boardptr, int playernum, int choice){
    int * endptr;
    if (playernum == 1) {
        boardptr->choiceptr = &boardptr->side1[choice];
        endptr = &boardptr->side1[6];
    } else if (playernum == 2) {
        boardptr->choiceptr = &boardptr->side2[choice];
        endptr = &boardptr->side2[6];
    } 
    return endptr;
}

// Performs a valid move. Catches if bonus move is granted.
int makemove(struct Board * boardptr, int playernum, int choice) {
    int * endptr = set_choiceptr(boardptr, playernum, choice);
    int marblenum = *boardptr->choiceptr;
    if (marblenum != 0) {
        *boardptr->choiceptr = 0;
        for (int i=0; i<marblenum; i++) {
            if (boardptr->choiceptr == &boardptr->side1[6]) {
                boardptr->choiceptr = &boardptr->side2[0];
            } else if (boardptr->choiceptr == &boardptr->side2[6]) {
                boardptr->choiceptr = &boardptr->side1[0];
            } else {
                boardptr->choiceptr++;
            }
           (*boardptr->choiceptr)++;
        }
    } else {
        printf("\nmakemove[55]: chosen cell cannot be empty");
        return 0; // input error
    }
    if (boardptr->choiceptr == endptr) {
        printf("\nExtra move!");
        return 0;
    } else { return 1; }
}

// Takes pointers to an array with values (to be copied) and an empty array.
// Copies the number of values from filled array specified by copysize into 
// empty array.
void copyarray (int * inptr, int * outptr, int copysize) {
   for (int i=0; i<=copysize; i++, outptr++, inptr++) {
       *outptr = *inptr;
   }
}

// Uses the predefined constant templates to print the state of the board.
void printboard (struct Board * boardptr, int sidesize) {
    int s1[sidesize], s2[sidesize];
    copyarray(boardptr->side1, s1, sidesize);
    copyarray(boardptr->side2, s2, sidesize);
    printf(SIDE1_FMT, s1[6], s1[5], s1[4], s1[3], s1[2], s1[1], s1[0]);
    printf(SIDE2_FMT, s2[0], s2[1], s2[2], s2[3], s2[4], s2[5], s2[6]);
}

// Takes user input from stdin, parses it, and validates it.
int userinput (struct Board * boardptr, int playernum) {
    int inputval;
    int boardsize = 7;
    printboard(boardptr, boardsize);
    printf("player %i: ", playernum);
    scanf("%i", &inputval);
    // if (inputval >= 7 || inputval < 1) {
    //     printf("\nuserinput[84]: Invalid input!");
    //     return 99; // invalid input
    // } 
    if (!(playernum == 1 || playernum == 2)) {
        printf("\nuserinput[88]: invalid input!");
        return 99;
    }
    if (inputval < 7 && inputval >= 1) {
        inputval--;
        return inputval;
    } else {
        printf("\nuserinput[108]: cell value out of range!");
        return 99;
    }

}

// Represents a single turn taken by the player.
// Also catches invalid inputs thrown by userinput.
int userturn (struct Board * boardptr, int playernum) {
    int * turnexit;
    int inputval = userinput(boardptr, playernum);
    if (inputval != 99) {
        return makemove(boardptr, playernum, inputval);
    } else { return 0; } // this part a lil sus
}

// char * tochardigits(int numarr[], int arrlen){
//     char buff;
//     char * digitarr[arrlen][2];
//     char * digptr = &digitarr;
//     for (int i=0; i<arrlen; i++, digptr++) {
//         buff = numarr[i];
//     }  
// }

int main() {
    struct Board gameboard;
    gameboard = init();
    struct Board * boardptr = &gameboard;
    int turndone = 0;
    while (1) {
        // Player 1 turn
        while (!turndone) {
            turndone = userturn(boardptr, 1);
        }
        turndone = 0;
        // Player 2 turn
        while (!turndone) {
            turndone = userturn(boardptr, 2);
        }
        turndone = 0;
    }
};