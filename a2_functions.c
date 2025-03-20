/*****************
    Student Name 	= George Tzemenakis
    Student Number	= 101296691
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

user_t *add_user(user_t *users, const char *username, const char *password){
    user_t *new_user = malloc(sizeof(user_t));
    assert(new_user != NULL);
    strcpy(new_user->username,username);
    strcpy(new_user->password,password);
    new_user->friends = NULL;
    new_user->posts = NULL;
    new_user->next = NULL;

    user_t *curr = users;

    if (users == NULL || strcmp(curr->username, new_user->username) > 0) {
        new_user->next = users;
        users = new_user;
    }
    else{
        while (curr->next != NULL && strcmp(curr->next->username, username) < 0) {
            curr = curr->next;
        }
        new_user->next = curr->next;
        curr->next = new_user;

    }
    
    return users;
}

user_t *find_user(user_t *users, const char *username){
    user_t *curr = users;
    while (curr != NULL){
        if (strcmp(curr->username, username) == 0){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

friend_t *create_friend(const char *username){
    friend_t *newfriend = malloc(sizeof(friend_t));
    assert(newfriend != NULL);
    newfriend->posts = NULL;
    newfriend->next = NULL;
    strcpy(newfriend->username, username);
    return newfriend;
}

void add_friend(user_t *user, const char *friend){
    
    friend_t *curr = user->friends;
    friend_t *newfriend = create_friend(friend);

    if (curr == NULL ||strcmp(curr->username, newfriend->username) > 0) {
        newfriend->next = user->friends;
        user->friends = newfriend;
    }
    else{
        while (curr->next != NULL && strcmp(curr->next->username, newfriend->username) < 0) {
            curr = curr->next;
        }
        newfriend->next = curr->next;
        curr->next = newfriend;
    }

}

_Bool delete_friend(user_t *user, char *friend_name){
    friend_t *temp = user->friends;

    if(strcmp(temp->username, friend_name) == 0){
        user->friends = temp->next;
        free(temp);
        return 1;
    }

    while (temp != NULL && temp->next != NULL){
        if (strcmp(temp->next->username, friend_name) == 0){
            friend_t *deleted_friend = temp->next;
            temp->next = temp->next->next;
            free(deleted_friend);
            return 1;
        }
        temp = temp->next;
    }
    return 0;

}

post_t *create_post(const char *text){
    post_t *newpost = malloc(sizeof(post_t));
    assert(newpost != NULL);
    newpost->next = NULL;
    strcpy(newpost->content, text);
    return newpost;
}

void add_post(user_t *user, const char *text){
    post_t *newpost = create_post(text);

    if (user->posts == NULL) {
        user->posts = newpost;
    } 
    else {
        post_t *curr = user->posts;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newpost;
    }
}

_Bool delete_post(user_t *user){ 
    if (user->posts == NULL){
        return false;
    }

    if (user->posts->next == NULL) { //if 1 post
        free(user->posts);
        user->posts = NULL;
        return true;
    }

    post_t *curr = user->posts;
    while (curr->next != NULL && curr->next->next != NULL) {
        curr = curr->next;
    }

    post_t *post_deleted = curr->next;
    curr->next = NULL;
    free(post_deleted);

    return true;
}

void display_all_user_posts(user_t *user){
    if (user->posts == NULL){
        printf("\n---------------------------------------\n");
        printf("          Managing %s's Posts          \n",user->username);
        printf("---------------------------------------\n");
        printf("Note: User %s has 0 Posts",user->username);
    }
    else{
        printf("\n---------------------------------------\n");
        printf("          %s's Posts          \n",user->username);
        printf("---------------------------------------\n");

        post_t *post = user->posts;
        unsigned int i = 1;
        while (post != NULL){
            printf("%i:\n%s\n\n",i,post->content);
            post = post->next;
            i++;
        }
    }
}

void display_user_friends(user_t *user){
    printf("\n---------------------------------------\n");
    printf("          %s's Friends          \n",user->username);
    printf("---------------------------------------\n");

    friend_t *friend = user->friends;
    unsigned int i = 1;
    if (friend == NULL){
        printf("User has 0 friends\n");
    }
    while (friend != NULL){
        printf("%i:\n%s\n\n",i,friend->username);
        friend = friend->next;
        i++;
    }
}

void display_posts_by_n(user_t *users, int number){

    post_t *curr = users->posts;
    unsigned short int counter = 0;
    if (curr == NULL){
        printf("\nSorry, this friend has no posts\n");
    }
    while (curr != NULL){
        counter++;
        printf("\n%i:\n%s\n",counter,curr->content);
        curr = curr->next;
        if (counter %3 == 0 && curr != NULL){
            char answer;
            printf("\nWould you like to show the next 3 posts?, Y or N: ");
            scanf(" %c", &answer);
            if (tolower(answer) == 'n'){
                return;
            }
        }
    }
}

void teardown(user_t *users){
    user_t *curr = users;
    while (curr) {
        user_t *temp = curr;
        curr = curr->next;

        friend_t *friend_curr = temp->friends;
        while(friend_curr){
            friend_t *friend_temp = friend_curr;
            friend_curr = friend_curr->next;
            free(friend_temp);
        }

        post_t *post_curr = temp->posts;
        while(post_curr){
            post_t *post_temp = post_curr;
            post_curr = post_curr->next;
            free(post_temp);
        }
        free(temp);
    }
}

void print_menu(char *username){
    printf("\n*************************************\n");
    printf("\tWelcome %s\t\n",username);
    printf("*************************************\n");
    printf("1. Manage profile (change password)\n");
    printf("2. Manage posts (add/remove)\n");
    printf("3. Manage friends (add/remove)\n");
    printf("4. Display a friend's posts\n");
    printf("5. exit \n");
}

void print_menu_login(){
    printf("\n******************************\n");
    printf("Welcome To Text Based Facebook\n");
    printf("******************************\n");
    printf("\n************************\n");
    printf("        Main Menu       \n");
    printf("***********************\n");
    printf("1. Registering a new user\n");
    printf("2. Login with Existing User\n");
    printf("3. exit \n");
}

_Bool find_friend(user_t *current_user, const char *friend_name){
    friend_t *curr = current_user->friends;
    while (curr != NULL){
        if (strcmp(curr->username, friend_name) == 0){
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void add_link_to_posts(user_t *users){
    
    user_t *currUser = users;
    while (currUser != NULL){
        friend_t *currFriend = currUser->friends;
        while (currFriend != NULL){
            user_t *tempFriend = find_user(users, currFriend->username);
            currFriend->posts = &tempFriend->posts;
            currFriend = currFriend->next;
        }
        currUser = currUser->next;
    }
    return;
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
