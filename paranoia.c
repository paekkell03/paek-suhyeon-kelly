    /***********************************************************************
     * Name(s)  Kelly Paek                                                 *
     * Assignment name (Homework 6 Paranoia)                               *
     * Help obtained: Seunghyeon Kim                                       *
     * King, K. N. (2008). C Programming: A Modern Approach . W.W. Norton  *
     * & Company.                                                          *
     * https://eikmeier.sites.grinnell.edu/csc-161-fall-2023/readings/wordl*
     * e.html                                                              *
     * Due Date 12/06                                                      *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     [include textbook(s), CSC 161 labs or readings;                 *
     *       complete citations for Web or other written sources           *
     *      write "none" if no sources used]                               *
     *   Help obtained                                                     *
     *     [indicate names of instructor, class mentors                    *
     *      or evening tutors, consulted according to class policy;        *
     *      write "none" if none of these sources used]                    *
     *     ["none" required for Homework Problems                          *
     *   My/our typed name(s) below confirms that the above list of sources*
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students, tutors) about the solutions              *
     *                                                                     *
     *   Signature:  Kelly Paek                                            *
     ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "plist.h"
#define MAX_BUFFER 50

int main() {
    //Prompt for user
    printf("The Paranoia Game\n");
    printf("Enter a player's name (press enter to begin game): ");
    //Mallocs lists for user input and tagged list
    plist * user_names = make_list();
    plist * tagged_list = make_list();
    //aname is where the user input name is going to be stored
    char * aname = NULL;
    int temp = -1;
    do {
        aname = (char *)malloc(sizeof(char)*MAX_BUFFER);
        temp = get_line(aname, MAX_BUFFER);
        if (temp != 0) {
            if (contains(user_names, aname)) {
                printf("Player %s is already participating in the game!\n", aname);
            } else {
                list_insert(user_names, aname);
            }
        } else {
            free(aname);
            continue;
        } 
        aname = NULL;
        printf("Enter another player's name: ");
    } while (temp != 0); 

    //checks if there is one player
    if (list_size(user_names) == 1) {
        printf("You need at least 2 players to play the game!\n");
        return -1;
    } 

    //checks if there are no players entered
    if (user_names->first == NULL) {
        printf("No players in the game!\n");
        return -1;
    } 

    //initial tagged ring and tagged list
    print_as_target_ring(user_names);
    print_as_tagged_list(tagged_list);

    printf("\n");

    //where the player-to-be-tagged is stored
    char * bname = NULL;

    do {
        //indicates how many players are left in the game
        printf("There are %d people left!\n", list_size(user_names));
        printf("Enter a target: ");
        bname = (char *)malloc(sizeof(char)*MAX_BUFFER);
        temp = get_line(bname, MAX_BUFFER);
        //removes player from the ring once tagged
        if (list_remove(user_names, bname)) {
            printf("%s was tagged!\n", bname);
            list_insert(tagged_list, bname);
        } else {
        //if entered name is not a player, moves on and gets another name from the user
            printf("%s is not a target!\n", bname);
            free(bname);
            bname = NULL;
        }
        print_as_target_ring(user_names);
        print_as_tagged_list(tagged_list);
        bname = NULL;
        printf("\n");
    } while (list_size(user_names) != 1);

    free_list(user_names);
    free_list(tagged_list);
    return 0;
}
