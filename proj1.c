#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXDESC 50
#define MAXID 1000
#define MAXUSERS 50
#define MAXACT 10
#define MAXACTLEN 21
#define MAXUSERLEN 21
#define MAXTASKS 20

typedef struct {
    int id, duration, start_inst;
    char description[MAXDESC], user, activity[MAXACTLEN];
} Task;

typedef struct {
    char name[MAXACTLEN];
} Activity;

typedef struct {
    char name[MAXUSERLEN];
} User;

/*############################## GLOBAL VARS ##############################*/

Task tasks[MAXTASKS];
Activity act[MAXACT];
User users[MAXUSERS];

int time = 0, task_counter = 0, act_counter = 3, user_counter = 0;

/*############################## AUX FUNCTIONS ##############################*/

int readIdList(int id_list[]) {
    char c;
    int id = 0, list_size = 0, in_id = 0, empty_list = 1;

    while ((c = getchar()) != EOF && c != '\n') {
        if (in_id == 1) {
            if (c == ' ' || c == '\t') {
                id_list[list_size] = id;
                list_size++;
                id = 0;
                in_id = 0;
            }
            else {
                id = id * 10 + (c - '0');
                empty_list = 0;
            }
        }
        else {
            if (c != ' ' && c != '\t') {
                in_id = 1;
                id = id * 10 + (c - '0');
            }
        }
    }

    if (empty_list == 0) {
        id_list[list_size] = id;
        list_size++;
    }
    return list_size;
}

int verifyID(int id) {
    int i, valid_id = 0;

    for (i = 0; i < task_counter; i++) {
        if (id == tasks[i].id) {
            valid_id = 1;
        }
    }
    return valid_id;
}

int verifyUser(char user[]) {
    int i, valid_user = 0;
    for (i = 0; i < user_counter; i++) {
        if (strcmp(user, users[i].name) == 0) {
            valid_user = 1;
        }
    }
    return valid_user;
}

int verifyAct(char activity[]) {
    int i, valid_act = 0;
    for (i = 0; i < act_counter; i++) {
        if (strcmp(activity, act[i].name) == 0) {
            valid_act = 1;
        }
    }
    return valid_act;
}

/*############################## CASE FUNCTIONS ##############################*/

void caseT() {
    int duration, i;
    char description[MAXDESC], c;
    Task t;
    
    scanf("%d %50[^\n]", &duration, description);

    while ((c = getchar()) != EOF && c != '\n');

    if (task_counter >= MAXTASKS) {
        printf("too many tasks");
        return;
    }
    
    for (i = 0; i <= task_counter; i++) {
        if (strcmp(description, tasks[i].description) == 0) {
            printf("duplicate description");
            return;
        }
    }

    if (duration <= 0) {
        printf("invalid duration");
        return;
    }

    t.duration = duration;
    t.id = task_counter + 1;
    t.start_inst = 0;
    strcpy(t.description, description);
    strcpy(t.activity, "TO DO");

    tasks[task_counter] = t;
    task_counter++;

    printf("task %d", t.id);

    return;
}

void caseL() {
    int list_size, i, j, id_list[MAXUSERS];

    list_size = readIdList(id_list);

    if (list_size == 0) {
        /*SORT*/
        for (i = 0; i < list_size; i++) {
            printf("%d %s #%d %s\n", tasks[i].id, tasks[i].activity, tasks[i].duration, tasks[i].description);
            return;
        }
    }
    else {
        for (i = 0; i < list_size; i++) {
            for (j = 0; j < task_counter; j++) {
                if (tasks[j].id == id_list[i]) {
                    printf("%d %s #%d %s\n", tasks[j].id, tasks[j].activity, tasks[j].duration, tasks[j].description);
                    return;
                }
            }
        }
    }
}

void caseN() {
    int add_time, verifier = 0;
    char c;

    verifier = scanf("%d", &add_time);
    while ((c = getchar()) != EOF && c != '\n');
    if (verifier != 1 || add_time < 0) {
        printf("invalid time");
        return;
    }
    else {
        printf("%d", (time + add_time));
        time += add_time;
        return;
    }
}

void caseU() {
    User new_user;
    char c;
    int i = 0, state = 0;

    while ((c = getchar()) != '\n') {
        state = scanf("%20s[^ \n]", new_user.name);
    }

    if (state == 0) {
        for (i = 0; i < user_counter; i++) {
            printf("%s\n", users[i].name);
        }
        return;
    }
    else {
        if (user_counter >= MAXUSERS) {
            printf("too many users");
            return;
        }

        for (i = 0; i <= user_counter; i++) {
            if (strcmp(new_user.name, users[i].name) == 0) {
                printf("user already exists");
                return;
            }
        }
        
        strcpy(users[user_counter].name, new_user.name);
        user_counter++;
        return;
    }
}

void caseM() {
    int id, i, gasto, slack;
    char user[MAXUSERLEN], activity[MAXACTLEN], c;

    scanf("%d %20s %20[^\n]", &id, user, activity);
    while ((c = getchar()) != EOF && c != '\n');

    if (!verifyID(id)) {
        printf("no such task");
        return;
    }
    else if (strcmp(activity, "TO DO") == 0) {
        printf("task already started");
        return;
    }
    else if (!verifyUser(user)) {
        printf("no such user");
        return;
    }
    else if (!verifyAct(activity)) {
        printf("no such activity");
        return;
    }
    else {
        for (i = 0; i < task_counter; i++) {
            if (id == tasks[i].id) {
                if (strcmp(activity, "DONE") == 0) {
                    gasto = time - tasks[i].start_inst;
                    slack = gasto - tasks[i].duration;
                    printf("duration=%d slack=%d", gasto, slack);
                    return;
                }
                else if (strcmp(tasks[i].activity, "TO DO") == 0) {
                    tasks[i].start_inst = time;
                }
                strcpy(tasks[i].activity, activity);
                return;
            }
        }
    }
}

void caseD() {
    char activity[MAXACTLEN], c;
    int i;

    while ((c = getchar()) != EOF && c != '\n') {
        scanf("%20[^\n]", activity);
    }

    for (i = 0; i < act_counter; i++) {
        if (strcmp(activity, act[i].name) == 0) {
            /* SORT */
            return;
        }
    }

    printf("no such activity");
    return;
}

void caseA() {
    Activity new_a;
    int i, state = 0;
    char c;

    while ((c = getchar()) != EOF && c != '\n') {
        state = scanf("%20[^\n]", new_a.name);
    }

    if (state == 0) {
        for (i = 0; i < act_counter; i++) {
            printf("%s\n", act[i].name);
        }
        return;
    }

    else {
        if (act_counter >= MAXACT) {
            printf("too many activities");
            return;
        }

        for (i = 0; new_a.name[i] != '\0'; i++) {
            if (islower(new_a.name[i]) != 0) {
                printf("invalid description");
                return;
            }
        }

        for (i = 0; i < act_counter; i++) {
            if (strcmp(act[i].name, new_a.name) == 0) {
                printf("duplicate activity");
                return;
            }
        }

        strcpy(act[act_counter].name, new_a.name);
        act_counter++;
        return;
    }
}

/*############################## MAIN FUNCTION ##############################*/

int main() {
    char c;
    int exit = 0;

    strcpy(act[0].name, "TO DO");
    strcpy(act[1].name, "IN PROGRESS");
    strcpy(act[2].name, "DONE");
    
    while (!exit) {
        c = getchar();
        switch (c) {
                case 't':
                    caseT();
                    break;
                case 'l':
                    caseL();
                    break;
                case 'n':
                    caseN();
                    break;
                case 'u':
                    caseU();
                    break;
                case 'm':
                    caseM();
                    break;
                case 'd':
                    caseD();
                    break;
                case 'a':
                    caseA();
                    break;
                case 'q':
                    exit = 1;
                    break;
                default:
                    printf("main: error\n");
        }
    }
    return 0;
}