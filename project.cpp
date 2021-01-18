#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"

userList *createUser(const char *username, const char *password){
    userList *newNode = (userList *) malloc(sizeof(userList));
    strcpy(newNode->username, username);
    strcpy(newNode->password, password);
    newNode->headFriendInbox = newNode->tailFriendInbox = NULL;
    newNode->headFriendReq = newNode->tailFriendReq = NULL;
    newNode->headFriendList = newNode->tailFriendList = NULL;
    newNode->headRecycleBin = newNode->tailRecycleBin = NULL;
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushUser(const char *username, const char *password){ // pushTail (Queue)
    userList *temp = createUser(username, password);
    if(!headUser){
        headUser = tailUser = temp;
    } else {
        temp->prev = tailUser;
        tailUser->next = temp;
        tailUser = temp;
    }
}

friendReq *createFriendReq(const char *username){
    friendReq *newNode = (friendReq *) malloc(sizeof(friendReq));
    strcpy(newNode->username, username);
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushFriendReq(userList *user, const char *username){ // pushTail (Queue)
    friendReq *temp = createFriendReq(username);
    if(user->headFriendReq == NULL){
        user->headFriendReq = user->tailFriendReq = temp;
    } else {
        temp->prev = user->tailFriendReq;
        user->tailFriendReq->next = temp;
        user->tailFriendReq = temp;
    }
}

void popHeadFriendReq(userList *user){
    if (!user->headFriendReq){
        return ;
    } else if(user->headFriendReq == user->tailFriendReq){
        free(user->headFriendReq);
        user->headFriendReq = NULL;
    } else {
        friendReq *candidateHead = user->headFriendReq->next;
        candidateHead->prev = NULL;
        user->headFriendReq->next = NULL;
        free(user->headFriendReq);
        user->headFriendReq = candidateHead;
    }
}

void popTailFriendReq(userList *user){
    if (!user->headFriendReq){
        return ;
    } else if(user->headFriendReq == user->tailFriendReq){
        free(user->headFriendReq);
        user->headFriendReq = NULL;
    } else {
        friendReq *candidateTail = user->tailFriendReq->prev;
        candidateTail->next = NULL;
        user->tailFriendReq->prev = NULL;
        free(user->tailFriendReq);
        user->tailFriendReq = candidateTail;
    }
}

void popFriendReq(userList *user, const char *username){
    if (!user->headFriendReq){
        return;
    } else if(strcmp(user->headFriendReq->username, username) == 0){
        popHeadFriendReq(user);
    } else if(strcmp(user->tailFriendReq->username, username) == 0){
        popTailFriendReq(user);
    } else {
        friendReq *curr = user->headFriendReq;
        while(curr && strcmp(curr->username, username) != 0){
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = NULL;
        curr->next = NULL;
        free(curr);
        curr = NULL;
    }
}

friendInbox *createFriendInbox(const char *username){
    friendInbox *newNode = (friendInbox *) malloc(sizeof(friendInbox));
    strcpy(newNode->username, username);
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushFriendInbox(userList *user, const char *username){ // pushTail (Queue)
    friendInbox *temp = createFriendInbox(username);
    if(!user->headFriendInbox){
        user->headFriendInbox = user->tailFriendInbox = temp;
    } else {
        temp->prev = user->tailFriendInbox;
        user->tailFriendInbox->next = temp;
        user->tailFriendInbox = temp;
    }
}

void popHeadFriendInbox(userList *user){
    if (!user->headFriendInbox){
        return ;
    } else if(user->headFriendInbox == user->tailFriendInbox){
        free(user->headFriendInbox);
        user->headFriendInbox = NULL;
    } else {
        friendInbox *candidateHead = user->headFriendInbox->next;
        candidateHead->prev = NULL;
        user->headFriendInbox->next = NULL;
        free(user->headFriendInbox);
        user->headFriendInbox = candidateHead;
    }
}

void popTailFriendInbox(userList *user){
    if (!user->headFriendInbox){
        return ;
    } else if(user->headFriendInbox == user->tailFriendInbox){
        free(user->headFriendInbox);
        user->headFriendInbox = NULL;
    } else {
        friendInbox *candidateTail = user->tailFriendInbox->prev;
        candidateTail->next = NULL;
        user->tailFriendInbox->prev = NULL;
        free(user->tailFriendInbox);
        user->tailFriendInbox = candidateTail;
    }
}

void popFriendInbox(userList *user, const char *username){
    if (!user->headFriendInbox){
        return;
    } else if(strcmp(user->headFriendInbox->username, username) == 0){
        popHeadFriendInbox(user);
    } else if(strcmp(user->tailFriendInbox->username, username) == 0){
        popTailFriendInbox(user);
    } else {
        friendInbox *curr = user->headFriendInbox;
        while(curr && strcmp(curr->username, username) != 0){
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = NULL;
        curr->next = NULL;
        free(curr);
        curr = NULL;
    }
}

friendList *createFriendList(const char *username){
    friendList *newNode = (friendList *) malloc(sizeof(friendList));
    strcpy(newNode->username, username);
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushFriendList(userList *user, const char *username){ // pushTail (Queue)
    friendList *temp = createFriendList(username);
    if(!user->headFriendList){
        user->headFriendList = user->tailFriendList = temp;
    } else {
        temp->prev = user->tailFriendList;
        user->tailFriendList->next = temp;
        user->tailFriendList = temp;
    }
}

void popHeadFriendList(userList *user){
    if (!user->headFriendList){
        return ;
    } else if(user->headFriendList == user->tailFriendList){
        free(user->headFriendList);
        user->headFriendList = NULL;
    } else {
        friendList *candidateHead = user->headFriendList->next;
        candidateHead->prev = NULL;
        user->headFriendList->next = NULL;
        free(user->headFriendList);
        user->headFriendList = candidateHead;
    }
}

void popTailFriendList(userList *user){
    if (!user->headFriendList){
        return ;
    } else if(user->headFriendList == user->tailFriendList){
        free(user->headFriendList);
        user->headFriendList = NULL;
    } else {
        friendList *candidateTail = user->tailFriendList->prev;
        candidateTail->next = NULL;
        user->tailFriendList->prev = NULL;
        free(user->tailFriendList);
        user->tailFriendList = candidateTail;
    }
}

void popFriendList(userList *user, const char *username){
    if (!user->headFriendList){
        return;
    } else if(strcmp(user->headFriendList->username, username) == 0){
        popHeadFriendList(user);
    } else if(strcmp(user->tailFriendList->username, username) == 0){
        popTailFriendList(user);
    } else {
        friendList *curr = user->headFriendList;
        while(curr && strcmp(curr->username, username) != 0){
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = NULL;
        curr->next = NULL;
        free(curr);
        curr = NULL;
    }
}

void addFriend(userList *user, const char *username){
    userList *curr = headUser;
    while(curr && strcmp(curr->username, username) != 0){
        curr = curr->next;
    }
    // printf("%s\n", curr->username);
    pushFriendInbox(user, username);
    pushFriendReq(curr, user->username);
}

void cancelFriendReq(userList *user, const char *username){
    userList *curr = headUser;
    while(curr && strcmp(curr->username, username) != 0){
        curr = curr->next;
    }
    popFriendInbox(user, username);
    popFriendInbox(curr, user->username);
}

void acceptFriend(userList *user, const char *username){
    userList *curr = headUser;
    while(curr && strcmp(curr->username, username) != 0){
        curr = curr->next;
    }
    pushFriendList(user, username);
    popFriendInbox(user, username);
    pushFriendList(curr, user->username);
    popFriendReq(curr, user->username);
}

void removeFriend(userList *user, const char *username){
    userList *curr = headUser;
    while(curr && strcmp(curr->username, username) != 0){
        curr = curr->next;
    }
    // printf("%s\n", curr->username);
    popFriendList(user, username);
    popFriendList(curr, user->username);
}

void printFriendToAdd(userList *user){
    userList *curr = headUser;
    int count = 1;
    while(curr){
        int flag = 1;
        if(strcmp(curr->username, user->username) == 0){
            flag = 0;
        }
        friendList *currList = user->headFriendList;
        while(currList){
            if(strcmp(currList->username, curr->username) == 0){
                flag = 0;
                break;
            }
            currList = currList->next;
        }
        friendReq *currReq = user->headFriendReq;
        while(currReq){
            if(strcmp(currReq->username, curr->username) == 0){
                flag = 0;
                break;
            }
            currReq = currReq->next;
        }
        friendInbox *currInbox = user->headFriendInbox;
        while(currInbox){
            if(strcmp(currInbox->username, curr->username) == 0){
                flag = 0;
                break;
            }
            currInbox = currInbox->next;
        }
        if(flag == 1){
            printf("%d. %s\n", count++, curr->username);
        }
        curr = curr->next;
    }
}

void printUser(){
    int count = 1;
    userList *curr = headUser;
    while (curr){
        printf("%d. %s\n", count++, curr->username);
        curr = curr->next;
    }
}

void printFriendList(userList *user){
    int count = 1;
    friendList *curr = user->headFriendList;
    while (curr){
        printf("%d. %s\n", count++, curr->username);
        curr = curr->next;
    }
}

void printFriendReq(userList *user){
    int count = 1;
    friendReq *curr = user->headFriendReq;
    while (curr){
        printf("%d. %s\n", count++, curr->username);
        curr = curr->next;
    }
}

void printFriendInbox(userList *user){
    int count = 1;
    friendInbox *curr = user->headFriendInbox;
    while (curr){
        printf("%d. %s\n", count++, curr->username);
        curr = curr->next;
    }
}

bool validateUsernameRegis(const char *username){
    userList *curr = headUser;
    while(curr){
        if(strcmp(curr->username, username) == 0){
            return false;
        }
        curr = curr->next;
    }

    return true;
}

userList *validateUsernameLogIn(const char *username, const char *password){
    userList *curr = headUser;
    while(curr){
        if(strcmp(curr->username, username) == 0 && strcmp(curr->password, password) == 0){
            return curr;
        }
        curr = curr->next;
    }

    return false;
}

note *createNote(const char *title, const char *content, const char *category){
    note *newNote = (note *) malloc(sizeof(note));
    strcpy(newNote->title, title);
    strcpy(newNote->content, content);
    strcpy(newNote->category, category);
    newNote->next = newNote->prev = NULL;

    return newNote;
}

void pushNote(userList *user, const char *title, const char *content, const char *category){
    note *temp = createNote(title, content, category);
    if(!user->headNote){
        user->headNote = user->tailNote = temp;
    } else {
        temp->prev = user->tailNote;
        user->tailNote->next = temp;
        user->tailNote = temp;
    }
}

void popHeadNote(userList *user){
    if (!user->headNote){
        return ;
    } else if(user->headNote == user->tailNote){
        free(user->headNote);
        user->headNote = NULL;
    } else {
        note *candidateHead = user->headNote->next;
        candidateHead->prev = NULL;
        user->headNote->next = NULL;
        free(user->headNote);
        user->headNote = candidateHead;
    }
}

void popTailNote(userList *user){
    if (!user->headNote){
        return ;
    } else if(user->headNote == user->tailNote){
        free(user->headNote);
        user->headNote = NULL;
    } else {
        note *candidateTail = user->tailNote->prev;
        candidateTail->next = NULL;
        user->tailNote->prev = NULL;
        free(user->tailNote);
        user->tailNote = candidateTail;
    }
}

void popNote(userList *user, const char *title){
    if (!user->headNote){
        return;
    } else if(strcmp(user->headNote->title, title) == 0){
        popHeadNote(user);
    } else if(strcmp(user->tailNote->title, title) == 0){
        popTailNote(user);
    } else {
        note *curr = user->headNote;
        while(curr && strcmp(curr->title, title) != 0){
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = NULL;
        curr->next = NULL;
        free(curr);
        curr = NULL;
    }
}

void editNote(userList *user, const char *title, const char *newTitle, const char *newContent, const char *newCategory){
    note *curr = user->headNote;
    while(curr && strcmp(curr->title, title) != 0){
        curr = curr->next;
    }
    strcpy(curr->title, newTitle);
    strcpy(curr->content, newContent);
    strcpy(curr->category, newCategory);
}

void printNote(userList *user){
    int count = 1;
    note *curr = user->headNote;
    while(curr){
        printf("%d. %s\n", count++, curr->title);
        curr = curr->next;
    }
}

bool validateNoteHeader(userList *user, const char *title){
    note *curr = user->headNote;
    while(curr){
        if(strcmp(curr->title, title) == 0){
            return false;
        }
        curr = curr->next;
    }

    return true;
}

recycleBin *createRecycle(const char *title, const char *content, const char *category){
    recycleBin *newNote = (recycleBin *) malloc(sizeof(recycleBin));
    strcpy(newNote->title, title);
    strcpy(newNote->content, content);
    strcpy(newNote->category, category);
    newNote->next = newNote->prev = NULL;

    return newNote;
}

void pushRecycle(userList *user, const char *title, const char *content, const char *category){
    recycleBin *temp = createRecycle(title, content, category);
    if(!user->headRecycleBin){
        user->headRecycleBin = user->tailRecycleBin = temp;
    } else {
        temp->prev = user->tailRecycleBin;
        user->tailRecycleBin->next = temp;
        user->tailRecycleBin = temp;
    }
}

void popHeadRecycle(userList *user){
    if (!user->headRecycleBin){
        return ;
    } else if(user->headRecycleBin == user->tailRecycleBin){
        free(user->headRecycleBin);
        user->headRecycleBin = NULL;
    } else {
        recycleBin *candidateHead = user->headRecycleBin->next;
        candidateHead->prev = NULL;
        user->headRecycleBin->next = NULL;
        free(user->headRecycleBin);
        user->headRecycleBin = candidateHead;
    }
}

void popTailRecycle(userList *user){
    if (!user->headRecycleBin){
        return ;
    } else if(user->headRecycleBin == user->tailRecycleBin){
        free(user->headRecycleBin);
        user->headRecycleBin = NULL;
    } else {
        recycleBin *candidateTail = user->tailRecycleBin->prev;
        candidateTail->next = NULL;
        user->tailRecycleBin->prev = NULL;
        free(user->tailRecycleBin);
        user->tailRecycleBin = candidateTail;
    }
}

void popRecycle(userList *user, const char *title){
    if (!user->headRecycleBin){
        return;
    } else if(strcmp(user->headRecycleBin->title, title) == 0){
        popHeadRecycle(user);
    } else if(strcmp(user->tailRecycleBin->title, title) == 0){
        popTailRecycle(user);
    } else {
        recycleBin *curr = user->headRecycleBin;
        while(curr && strcmp(curr->title, title) != 0){
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = NULL;
        curr->next = NULL;
        free(curr);
        curr = NULL;
    }
}

void printRecycle(userList *user){
    int count = 1;
    recycleBin *curr = user->headRecycleBin;
    while(curr){
        printf("%d. %s\n", count++, curr->title);
        curr = curr->next;
    }
}

void removeNote(userList *user, const char *title){
    note *curr = user->headNote;
    while(curr && strcmp(curr->title, title) != 0){
        curr = curr->next;
    }
    pushRecycle(user, curr->title, curr->content, curr->category);
    popNote(user, title);
}

void replaceNote(userList *user, const char *title){
    recycleBin *curr = user->headRecycleBin;
    while(curr && strcmp(curr->title, title) != 0){
        curr = curr->next;
    }
    pushNote(user, curr->title, curr->content, curr->category);
    popRecycle(user, title);
}

privateFriend *createPrivateFriend(const char *username){
    privateFriend *newNode = (privateFriend *) malloc(sizeof(privateFriend));
    strcpy(newNode->username, username);
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushPrivateFriend(publicDashboard *publicDash, const char *username){ // pushTail (Queue)
    privateFriend *temp = createPrivateFriend(username);
    if(!publicDash->headPrivate){
        publicDash->headPrivate = publicDash->tailPrivate = temp;
    } else {
        temp->prev = publicDash->tailPrivate;
        publicDash->tailPrivate->next = temp;
        publicDash->tailPrivate = temp;
    }
}

publicDashboard *createPublicDashboard(const char *username, const char *title, const char *content, const char *category, bool privateOrPublic){
    publicDashboard *newNote = (publicDashboard *) malloc(sizeof(publicDashboard));
    strcpy(newNote->username, username);
    strcpy(newNote->title, title);
    strcpy(newNote->content, content);
    strcpy(newNote->category, category);
    newNote->like = 0;
    newNote->privateOrPublic = privateOrPublic;
    newNote->headPrivate = newNote->tailPrivate = NULL;
    newNote->headComment = newNote->tailComment = NULL;
    newNote->next = newNote->prev = NULL;

    return newNote;
}

void pushPublicDashboard(const char *username, const char *title, const char *content, const char *category, bool privateOrPublic){
    publicDashboard *temp = createPublicDashboard(username, title, content, category, privateOrPublic);
    if(!headPd){
        headPd = tailPd = temp;
    } else {
        temp->prev = tailPd;
        tailPd->next = temp;
        tailPd = temp;
    }
}

void announceNote(userList *user, const char *title, bool privateOrPublic){
    note *curr = user->headNote;
    while(curr && strcmp(curr->title, title) != 0){
        curr = curr->next;
    }
    pushPublicDashboard(user->username, curr->title, curr->content, curr->category, privateOrPublic);
    popNote(user, title);
}

void addPrivateFriend(userList *user, const char *title, const char *username){
    publicDashboard *curr = headPd;
    while(curr && strcmp(curr->username, user->username) == 0 && strcmp(curr->title, title)){
        curr = curr->next;
    }
    pushPrivateFriend(curr, username);
}

commentNotes *createCommentNotes(const char *username, const char *comment){
    commentNotes *newNode = (commentNotes *) malloc(sizeof(commentNotes));
    strcpy(newNode->username, username);
    strcpy(newNode->comment, comment);
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushComment(publicDashboard *publicDash, const char *username, const char *comment){ // pushTail (Queue)
    commentNotes *temp = createCommentNotes(username, comment);
    if(!publicDash->headComment){
        publicDash->headComment = publicDash->tailComment = temp;
    } else {
        temp->prev = publicDash->tailComment;
        publicDash->tailComment->next = temp;
        publicDash->tailComment = temp;
    }
}

bool validatePrivate(userList *user, publicDashboard *dashboard){
    privateFriend *curr = dashboard->headPrivate;
    while(curr){
        if(strcmp(curr->username, user->username) == 0 || strcmp(dashboard->username, user->username) == 0){
            return true;
        }
        curr = curr->next;
    }

    return false;
}

int main(){
    int globalFlag = 1;
    while(globalFlag == 1){
        printf("Oo====================================oO\n");
        printf("\t      STUDY NETWORK\n");
        printf("Oo====================================oO\n");

        printf("[All User]\nNo.\tUsername\n");
        printUser();
        printf("----------------------------------------\n");
        printf("[1] Register\n[2] Login\n[3] Exit\n");
        printf("----------------------------------------\n");
        printf("Press 0 and enter to abort an operation\n");
        printf("----------------------------------------\n");
        printf(">> ");
        int menu;
        scanf("%d", &menu);
        printf("----------------------------------------\n");
        if(menu == 1){
            char username[25], password[25];
            printf("Please type in your username [lowercase || 1..24]: ");
            scanf("%s", username);
            printf("Please type in your password [lowercase || 1..24]: ");
            scanf("%s", password);
            if(validateUsernameRegis(username)){
                pushUser(username, password);
                printf("-- Registration Successfull --\n");
            } else {
                printf("Username already in use\n");
            }
        } else if(menu == 2){
            char username[25], password[25];
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);
            userList *curr = validateUsernameLogIn(username, password);
            if(curr){
                printf("--Login Successfull--\n");
                int flagLogin = 1;
                while(flagLogin == 1){
                    printf("Oo====================================oO\n");
                    printf("Welcome, %s\n", curr->username);
                    printf("Oo====================================oO\n");
                    printf("Logged in: %s\n", curr->username);
                    printf("----------------------------------------\n\n");
                    printf("[All friends of %s\n", curr->username);//user
                    printf("No.\t Username\n");
                    printFriendList(curr);
                    printf("----------------------------------------\n");
                    printf("\t >>MENU<< \t\n");
                    printf("----------------------------------------\n");
                    printf("[1] Add Friend\n");
                    printf("[2] Remove Friend\n");
                    printf("[3] View Inbox\n");
                    printf("[4] View Sent Request\n");
                    printf("[5] Add,Edit,Announce,Delete,Replace Note\n");
                    printf("[6] View Public Dashboard\n");
                    printf("[7] Log Out\n");
                    printf("----------------------------------------\n");
                    printf(">> ");
                    int menuLogin;
                    scanf("%d", &menuLogin);
                    printf("----------------------------------------\n");
                    if(menuLogin == 1){
                        printf("[ All Users You Can Add ]\n"); //input nama
                        printf("No. \t Username\n");
                        printFriendToAdd(curr);
                        printf("Which user do you want to add?\n");
                        printf(">> ");
                        char addUsername[25];
                        scanf("%s", addUsername);
                        addFriend(curr, addUsername);
                        printf("--Your request has been sent to %s --\n", addUsername);
                    } else if(menuLogin == 2){
                        printf("[All Friend of  %s]\n", curr->username); //nama user
                        printf("No. \t Username\n");
                        printFriendList(curr);
                        printf("Which user d you want to remove?\n");
                        printf(">> ");
                        char removeUsername[25];
                        scanf("%s", removeUsername);
                        removeFriend(curr, removeUsername);
                        printf("--You are no longer friends with %s --\n", removeUsername);
                    } else if(menuLogin == 3){
                        printf("[All Friend Inbox of %s]\n", curr->username); //input nama
                        printf("No. \t Username\n");
                        printFriendInbox(curr);
                        printf("Which user do you want to cancel friend request?\n");
                        printf(">> ");
                        char cancelUsername[25];
                        scanf("%s", cancelUsername);
                        cancelFriendReq(curr, cancelUsername);
                        printf("--You canceled the friend request to %s--\n", cancelUsername);
                    } else if(menuLogin == 4){
                        printf("[All Friend Request of %s]\n", curr->username); //input nama
                        printf("No. \t Username\n");
                        printFriendReq(curr);
                        printf("Which user do you want to accepted?\n");
                        printf(">> ");
                        char accUsername[25];
                        scanf("%s", accUsername);
                        acceptFriend(curr, accUsername);
                        printf("--You accepted the request from %s--\n", accUsername);
                    } else if(menuLogin == 5){
                        printf("[1] Add Note\n");
                        printf("[2] Edit Note\n");
                        printf("[3] Announce Note\n");
                        printf("[4] Delete Note\n");
                        printf("[5] Replace Note\n");
                        printf("----------------------------------------\n");
                        printf(">> ");
                        int menuNote;
                        scanf("%d", &menuNote);
                        printf("----------------------------------------\n");
                        if(menuNote == 1){
                            char titleNote[25], contentNote[255], categoryNote[25];
                            printf("Please type in title note [lowercase || 1..24]: ");
                            scanf("%s", titleNote);
                            printf("Please type in content note [lowercase || 1..224]: ");
                            scanf("%s", contentNote);
                            printf("----------------------------------------\n");
                            printf("[1] Backlog\n");
                            printf("[2] InProgress\n");
                            printf("[3] PeerReview\n");
                            printf("[4] InTest\n");
                            printf("[5] Done\n");
                            printf("[6] Blocked\n");
                            printf("Which category do you choose?\n");
                            printf(">> ");
                            scanf("%s", categoryNote);
                            if(validateNoteHeader(curr , titleNote)){
                                pushNote(curr, titleNote, contentNote, categoryNote);
                                printf("--Your note added successfully--\n");
                            } else {
                                printf("Note title is already in use\n");
                            }
                        } else if(menuNote == 2){
                            printf("[All Note of %s]\n", curr->username); //input nama
                            printf("No. \t Title\n");
                            printNote(curr);
                            printf("Which note do you want to edit?\n");
                            printf(">> ");
                            char oldTitle[25];
                            scanf("%s", oldTitle);
                            printf("----------------------------------------\n");
                            char titleNote[25], contentNote[255], categoryNote[25];
                            printf("Please type in new title note [lowercase || 1..24]: ");
                            scanf("%s", titleNote);
                            printf("Please type in new content note [lowercase || 1..224]: ");
                            scanf("%s", contentNote);
                            printf("----------------------------------------\n");
                            printf("[1] Backlog\n");
                            printf("[2] InProgress\n");
                            printf("[3] PeerReview\n");
                            printf("[4] InTest\n");
                            printf("[5] Done\n");
                            printf("[6] Blocked\n");
                            printf("Which category do you choose?\n");
                            printf(">> ");
                            scanf("%s", categoryNote);
                            editNote(curr, oldTitle, titleNote, contentNote, categoryNote);
                            printf("--Your note edited successfully--\n");
                        } else if(menuNote == 3){
                            printf("[All Note of %s]\n", curr->username); //input nama
                            printf("No. \t Title\n");
                            printNote(curr);
                            printf("Which note do you want to announce?\n");
                            printf(">> ");
                            char annTitle[25];
                            scanf("%s", annTitle);
                            printf("Do you want to make this note private (yes/no)?\n");
                            printf(">> ");
                            char prv[5];
                            scanf("%s", prv);
                            if(strcmp(prv, "yes") == 0){
                                announceNote(curr, annTitle, true);
                                printf("----------------------------------------\n");
                                printf("[All Friend of  %s]\n", curr->username); //nama user
                                printf("No. \t Username\n");
                                printFriendList(curr);
                                int flagAdditional = 1, i = 0;
                                while(flagAdditional == 1 && i < 3){
                                    printf("Who is the friend you want to exclude?\n");
                                    printf(">> ");
                                    char friendName[25];
                                    scanf("%s", friendName);
                                    addPrivateFriend(curr, annTitle, friendName);
                                    printf("Any additional friends (yes/no)?\n");
                                    printf(">> ");
                                    char additionalFriend[10];
                                    scanf("%s", additionalFriend);
                                    if(strcmp(additionalFriend, "no") == 0){
                                        flagAdditional = 0;
                                        break;
                                    }
                                    i++;
                                }
                            } else {
                                announceNote(curr, annTitle, false);
                            }
                        } else if(menuNote == 4){
                            printf("[All Note of %s]\n", curr->username); //input nama
                            printf("No. \t Title\n");
                            printNote(curr);
                            printf("Which note do you want to delete?\n");
                            printf(">> ");
                            char rmvTitle[25];
                            scanf("%s", rmvTitle);
                            removeNote(curr, rmvTitle);
                            printf("--Your note deleted successfully--\n");
                        } else if(menuNote == 5){
                            printf("[All Recycle Bin Note of %s]\n", curr->username); //input nama
                            printf("No. \t Title\n");
                            printRecycle(curr);
                            printf("Which note do you want to replace?\n");
                            printf(">> ");
                            char rplTitle[25];
                            scanf("%s", rplTitle);
                            replaceNote(curr, rplTitle);
                            printf("--Your note replaced successfully--\n");
                        }
                    } else if(menuLogin == 6){
                        publicDashboard *currPublic = headPd;
                        int flagDashboard = 1;
                        while (currPublic && flagDashboard == 1){
                            if(!validatePrivate(curr, currPublic)){
                                currPublic = currPublic->next;
                            } else {
                                if(currPublic->next != NULL){
                                    printf("Title : %s\n", currPublic->title);
                                    printf("Author : %s\n", currPublic->username);
                                    printf("Category : %s\n", currPublic->category);
                                    printf("Content : %s\n", currPublic->content);
                                    printf("Like : %d\n", currPublic->like);
                                    printf("Comments--------------------------------\n");
                                    commentNotes *currComment = currPublic->headComment;
                                    while (currComment){
                                        printf("%s\n%s\n---\n", currComment->username, currComment->comment);
                                        currComment = currComment->next;
                                    }
                                    printf("What do you want to do (like/comment/next/exit)?");
                                    printf(">> ");
                                    char ans[10];
                                    scanf("%s", ans);
                                    if(strcmp(ans, "like") == 0){
                                        currPublic->like++;
                                    } else if(strcmp(ans, "comment") == 0){
                                        printf("Please write your comment [lowercase || 1..224]: ");
                                        printf(">> ");
                                        char commentTemp[255];
                                        scanf("%s", commentTemp);
                                        pushComment(currPublic, curr->username, commentTemp);
                                    } else if(strcmp(ans, "next") == 0){
                                        currPublic = currPublic->next;
                                    } else if(strcmp(ans, "exit") == 0){
                                        flagDashboard = 0;
                                    }
                                } else if(currPublic->next == NULL){
                                    printf("Title : %s\n", currPublic->title);
                                    printf("Author : %s\n", currPublic->username);
                                    printf("Category : %s\n", currPublic->category);
                                    printf("Content : %s\n", currPublic->content);
                                    printf("Like : %d\n", currPublic->like);
                                    printf("Comments--------------------------------\n");
                                    commentNotes *currComment = currPublic->headComment;
                                    while (currComment){
                                        printf("%s\n%s\n---\n", currComment->username, currComment->comment);
                                        currComment = currComment->next;
                                    }
                                    printf("What do you want to do (like/comment/exit)?\n");
                                    printf(">> ");
                                    char ans[10];
                                    scanf("%s", ans);
                                    if(strcmp(ans, "like") == 0){
                                        currPublic->like++;
                                    } else if(strcmp(ans, "comment") == 0){
                                        printf("Please write your comment [lowercase || 1..224]: ");
                                        printf(">> ");
                                        char commentTemp[255];
                                        scanf("%s", commentTemp);
                                        pushComment(currPublic, curr->username, commentTemp);
                                    } else if(strcmp(ans, "exit") == 0){
                                        flagDashboard = 0;
                                    }
                                }
                            }
                        }
                    } else if(menuLogin == 7){
                        curr = NULL;
                        flagLogin = 0;
                        break;
                    }
                }
            } else {
                printf("Wrong username or password\n");
            }
        } else if(menu == 3){
            printf("Thank You\n");
            globalFlag = 0;
            break;
        }
    }
    
    return 0;
}