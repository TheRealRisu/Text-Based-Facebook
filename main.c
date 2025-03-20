/********* main.c ********
    Student Name 	= George Tzemenakis
    Student Number	= 101296691
*/

// Includes go here
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

#define MAXARRAYSIZE 100
#define MAXPOSTSIZE 250
#define POSTSBYNUMBER 3

int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);

    //add link to friends post
    add_link_to_posts(users);
    printf("below is a test to make sure that the above function works, the function should add a connection between a friend and their posts\n");
    printf("The posts displayed are the posts for user: georgeharry, the first friend of user: luciusmolly, using the connection between friend and post\nTHIS IS A PROOF FOR TASK 4\n\n");
    user_t *curruser = find_user(users, "luciusmolly");
    post_t *currpost = *(curruser->friends->posts);
    while(currpost != NULL){
        printf("%s",currpost->content);
        currpost = currpost->next;
        printf("\n");
    }
    printf("\n\n");

    int user_choice_2 = 0;
    unsigned short int error_trigger = 0;
    unsigned short int login_trigger = 0;
    while (user_choice_2 != 3){
        char current_user[MAXARRAYSIZE] = ""; //reset start of each loop
        login_trigger = 0; //reset
        print_menu_login();

        error_trigger = 0;
        while (error_trigger == 0){
            error_trigger = 1;
            printf("\n Please enter your choice: ");
            scanf(" %i",&user_choice_2);
            if (user_choice_2 < 1 || user_choice_2 > 3){
                error_trigger = 0;
                printf("Sorry, Please enter a valid number");
            }
        }

        if(user_choice_2 == 1){
            char new_user_name[MAXARRAYSIZE] = "";
            char new_user_pass[MAXARRAYSIZE] = "";
            printf("\nEnter a Username for this new user: ");
            scanf(" %s",new_user_name);
            for (int i = 0; new_user_name[i] ; i++){
                new_user_name[i] = tolower(new_user_name[i]);
            }

            user_t *user_to_change = find_user(users, new_user_name);

            if (user_to_change == NULL){
                error_trigger = 0;
                while (error_trigger == 0){
                    error_trigger = 1;
                    printf("\nEnter a Password for this new user: ");
                    scanf(" %s",new_user_pass);
                    if (strlen(new_user_pass) < 8 || strlen(new_user_pass) > 15){
                        printf("Incorrect password length, please try again.");
                        error_trigger = 0;
                    }
                }
                users = add_user(users, new_user_name, new_user_pass);
                printf("User Registered!");
                //go back ask question
            }
            else{
                printf("\n------------------------\n");
                printf("     Username taken     \n");
                printf("------------------------\n");
            }
        }
        else if (user_choice_2 == 2){
            char user_name[MAXARRAYSIZE] = "";
            char user_pass[MAXARRAYSIZE] = "";
            printf("\nEnter a Username to log in: ");
            scanf(" %s",user_name);
            printf("\nEnter the password: ");
            scanf(" %s",user_pass);
            for (int i = 0; user_name[i] ; i++){
                user_name[i] = tolower(user_name[i]);
            }

            user_t *user_to_change = find_user(users, user_name);

            if (user_to_change != NULL && (strcmp(user_to_change->password,user_pass) == 0)){
                strcpy(current_user,user_to_change->username);
                login_trigger = 1;
            }
            else{
                printf("\n----------------------------\n");
                printf("Username Or Password Invalid\n");
                printf("         Try again          \n");
                printf("----------------------------\n");
            }
        }
        else if(user_choice_2 == 3){
            printf("\nGoodbye !");
            teardown(users);
        }

        if (login_trigger == 1){
            int user_choice = 0;
            while (user_choice != 5){
                print_menu(current_user);

                error_trigger = 0;
                while (error_trigger == 0){
                    error_trigger = 1;
                    printf("\n Please enter your choice: ");
                    scanf(" %i",&user_choice);
                    if (user_choice < 1 || user_choice > 5){
                        error_trigger = 0;
                        printf("Sorry, Please enter a valid number");
                    }
                }
                if(user_choice == 1){
                    
                    user_t *user_to_change = find_user(users, current_user); //he exists 10000%
                    char user_input[MAXARRAYSIZE] = "";

                    printf("To continue, please enter your current password: ");
                    scanf("%s",user_input);

                    if (strcmp(user_input,user_to_change->password) == 0){
                        error_trigger = 0;
                        while (error_trigger == 0){
                            error_trigger = 1;
                            printf("\nEnter a NEW Password for this user: ");
                            scanf(" %s",user_input);
                            if (strlen(user_input) < 8 || strlen(user_input) > 15){
                                printf("Incorrect password length, please try again.");
                                error_trigger = 0;
                            }
                        }
                        strcpy(user_to_change->password,user_input);
                        printf("\n******* Password Changed *******\n\n");

                    }
                    else{
                        printf("\n------------------------\n");
                        printf("Sorry, Invalid Password.\n");
                        printf("------------------------\n");
                    }
                }
                if(user_choice == 2){
                    user_t *user_to_change = find_user(users, current_user);
                    int user_choice_2 = 0;
                    while(user_choice_2 != 3){

                        display_all_user_posts(user_to_change);

                        printf("\n1. Add a new post");
                        printf("\n2. Remove a post");
                        printf("\n3. Return to main menu");
                        error_trigger = 0;
                        while (error_trigger == 0){
                            error_trigger = 1;
                            printf("\nEnter your choice: ");
                            scanf(" %i", &user_choice_2);
                            if (user_choice_2 <= 0 || user_choice_2 >= 4){
                                error_trigger = 0;
                                printf("Sorry, Please enter a valid number");
                            }
                        }

                        if (user_choice_2 == 1){
                            printf("\nEnter the New Posts' Contents: ");
                            char new_post_content[MAXPOSTSIZE] = "";
                            scanf(" %[^\n]s", new_post_content);
                            add_post(user_to_change, new_post_content);
                        }

                        if (user_choice_2 == 2){
                            _Bool result = delete_post(user_to_change);
                            if (result == 0){
                                printf("\nSorry, there are no posts to be deleted.");
                            }
                            else if (result == 1){
                                printf("\nPost Deleted!\n");    
                            }
                        }
                    }
                }
                if(user_choice == 3){
                    user_t *user_to_change = find_user(users, current_user);
                        int user_choice_2 = 0;
                        while(user_choice_2 != 3){

                        display_user_friends(user_to_change);

                        printf("1. Add a new friend");
                        printf("\n2. Remove a friend");
                        printf("\n3. Return to main menu");

                        error_trigger = 0;
                        while (error_trigger == 0){
                            error_trigger = 1;
                            printf("\nEnter your choice: ");
                            scanf(" %i", &user_choice_2);
                            if (user_choice_2 <= 0 || user_choice_2 >= 4){
                                error_trigger = 0;
                                printf("Sorry, Please enter a valid number");
                            }
                        }

                        if (user_choice_2 == 1){
                            printf("\nEnter the new friends' username: ");
                            char friend_name[MAXARRAYSIZE] = "";
                            scanf(" %s", friend_name);
                            user_t *valid_user = find_user(users, friend_name);
                            if (valid_user != NULL){
                                add_friend(user_to_change, friend_name);
                            }
                            else{
                                printf("\n------------------------\n");
                                printf("     User not found     \n");
                                printf("------------------------\n");
                            }
                        }

                        if (user_choice_2 == 2){
                            printf("\nPlease enter the friend's name who you would like to delete: ");
                            char friend_name[MAXARRAYSIZE] = "";
                            scanf(" %s", friend_name);
                            _Bool result = delete_friend(user_to_change,friend_name);
                            if (result == 0){
                                printf("\nSorry, Invalid friend name, Friend could not be Deleted\n");
                            }
                            else if (result == 1){
                                printf("\nFriend Succesfully Deleted\n");
                            }

                        }
                    }
                }
                if(user_choice == 4){
                    char user_input[MAXARRAYSIZE] = "";
                    user_t *user_to_change = find_user(users, current_user);

                    display_user_friends(user_to_change);
                    printf("please select a friend's username to display their posts: ");
                    scanf(" %s", user_input);

                    _Bool valid_friend = find_friend(user_to_change, user_input);
                    if (valid_friend == 1){
                        user_t *user_to_display = find_user(users, user_input);
                        display_posts_by_n(user_to_display, POSTSBYNUMBER);
                    }
                    else{
                        printf("\n------------------------\n");
                        printf("    Friend Not Found    \n");
                        printf("------------------------\n");
                    }
                }
            }
        }
        login_trigger = 0;
    }

}