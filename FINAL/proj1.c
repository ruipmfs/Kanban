#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXDESCLEN 51
#define MAXID 1000
#define MAXUSERS 50
#define MAXACT 10
#define MAXACTLEN 21
#define MAXUSERLEN 21
#define MAXTASKS 10000

typedef struct {
    int id, duration, start_inst;
    char description[MAXDESCLEN], user[MAXUSERLEN], activity[MAXACTLEN];
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

void setDefaultActs() {
    strcpy(act[0].name, "TO DO");
    strcpy(act[1].name, "IN PROGRESS");
    strcpy(act[2].name, "DONE");
}

int readIdList(int id_list[]) {
    char c;
    int id = 0, list_size = 0, in_id = 0, empty_list = 1, negative_num = 0;

    /* Reads the array char by char */
    while ((c = getchar()) != EOF && c != '\n') {
        if (in_id) {
            if (c == ' ' || c == '\t') {
                if (negative_num) {
                    id_list[list_size] = -id;
                    negative_num = 0;
                }
                else
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
        else if (c == '-' && !in_id) {
            negative_num = 1;
            in_id = 1;
        }
        else if (c != ' ' && c != '\t') {
            in_id = 1;
            id = id * 10 + (c - '0');
            empty_list = 0;
        }
    }
    if (!empty_list && in_id) {
        id_list[list_size] = negative_num ? -id : id;
        list_size++;
    }
    return list_size;
}

int verifyID(int id) {
    /* Verifies if the input (ID) is contained in the Tasks
       (check if the task is valid) */
    int i;

    for (i = 0; i < task_counter; i++) {
        if (id == tasks[i].id) {
            return 1;
        }
    }
    return 0;
}

int verifyUser(char user[]) {
    /* Verifies if the input (User) is contained in the listed Users */
    int i;
    for (i = 0; i < user_counter; i++) {
        if (strcmp(user, users[i].name) == 0) {
            return 1;
        }
    }
    return 0;
}

int verifyAct(char activity[]) {
    /* Verifies if the input (Activity) is contained in the listed Activities */
    int i;
    for (i = 0; i < act_counter; i++) {
        if (strcmp(activity, act[i].name) == 0) {
            return 1;
        }
    }
    return 0;
}

int alphabet(char s1[], char s2[]) {
    /* RETURNS TRUE IF 1ST STRING COMES 1ST IN ALPHABETHIC ORDER, FALSE */
    int i;
    /*printf("s1: %s\ns2: %s\n", s1, s2);*/
    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] > s2[i]) {
            return 0;
        }
        else if (s1[i] < s2[i]) {
            return 1;
        }
    }
    return 1;
}

int lessInstanceAndAlphabet(Task t1, Task t2) {
    if (t1.start_inst == t2.start_inst) {
        return alphabet(t1.description, t2.description);
    }
    return t1.start_inst <= t2.start_inst;
}

int partitionByInstance(Task list[], int start, int end) {
    /* AUX Func. of the quicksort algorithm.
       Defines a pivot and sort the list given in the input by putting
       the minor numbers (num < pivot) on the left side of the pivot
       and the major numbers (num < pivot) on the right side of the pivot */
    int i = start-1, j = end;
    Task pivot = list[end], temp;
    /*printf("i: %d\nj: %d", i, j);*/

    while (i < j) {
        while (lessInstanceAndAlphabet(list[++i], pivot) && i < j && i < end);
        while (lessInstanceAndAlphabet(pivot, list[--j])) {
            if (j == start) break;
        }
        
        if (i < j) {
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    temp = list[i];
    list[i] = list[end];
    list[end] = temp;
    return i;
}

void sortByInstance(Task list[], int left, int right) {
    /* Main func. of the sprt algorithm.
       Divides the array and call itself by recursion with the
       splitted array */
    int part;

    if (right <= left)
        return;
    
    part = partitionByInstance(list, left, right);

    sortByInstance(list, left, part-1);
    sortByInstance(list, part+1, right);
}

int partitionByAlphabet(Task list[], int start, int end) {
    /* AUX Func. of the quicksort algorithm.
       Defines a pivot and sort the list given in the input by putting
       the minor numbers (num < pivot) on the left side of the pivot
       and the major numbers (num < pivot) on the right side of the pivot */
    int i = start-1, j = end;
    Task pivot = list[end], temp;

    while (i < j) {
        while (alphabet(list[++i].description, pivot.description) && i < j && i < end);
        while (alphabet(pivot.description, list[--j].description)) {
            if (j == start) break;
        }

        if (i < j) {
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    temp = list[i];
    list[i] = list[end];
    list[end] = temp;
    return i;
}

void sortByAlphabet(Task list[], int left, int right) {
    /* Main func. of the sprt algorithm.
       Divides the array and call itself by recursion with the
       splitted array */
    int part;

    if (right <= left)
        return;

    part = partitionByAlphabet(list, left, right);

    sortByAlphabet(list, left, part-1);
    sortByAlphabet(list, part+1, right);
}

/*############################## CASE FUNCTIONS ##############################*/

void caseT() {
    /* Main func. of the command 't' */
    int duration, i;
    char description[MAXDESCLEN], c;
    
    scanf("%d %50[^\n]", &duration, description);

    while ((c = getchar()) != '\n'); /* Read the remaining char(s) in the line */

    /* Error testing */
    if (task_counter >= MAXTASKS) {
        printf("too many tasks\n");
        return;
    }
    
    for (i = 0; i < task_counter; i++) {
        if (strcmp(description, tasks[i].description) == 0) {
            printf("duplicate description\n");
            return;
        }
    }

    if (duration <= 0) {
        printf("invalid duration\n");
        return;
    }

    tasks[task_counter].duration = duration;
    tasks[task_counter].id = task_counter + 1;
    tasks[task_counter].start_inst = 0;
    strcpy(tasks[task_counter].description, description);
    strcpy(tasks[task_counter].activity, "TO DO");

    task_counter++;

    printf("task %d\n", tasks[task_counter-1].id);
}

void caseL() {
    /* Main func. of the command 'l' */
    int list_size, i, j, id_list[MAXTASKS];
    Task t[MAXTASKS];

    for (i = 0; i < task_counter; i++) {
        t[i] = tasks[i];
    }

    /* Reads the ID's of the input and returns the size of the array */
    list_size = readIdList(id_list);

    /* If no arguments recieved */
    if (list_size == 0) {
        sortByAlphabet(t, 0, task_counter-1);
        for (i = 0; i < task_counter; i++) {
            printf("%d %s #%d %s\n", t[i].id, t[i].activity, t[i].duration, t[i].description);
        }
    }
    /* If at least 1 ID recieved */
    else {
        for (i = 0; i < list_size; i++) {
            if (id_list[i] > task_counter || id_list[i] <= 0) {
                    printf("%d: no such task\n", id_list[i]);
                }
            for (j = 0; j < task_counter; j++) {
                if (id_list[i] == tasks[j].id) {
                    printf("%d %s #%d %s\n", tasks[j].id, tasks[j].activity, tasks[j].duration, tasks[j].description);
                }
            }
        }
    }
}

void caseN() {
    /* Main func. of the command 'n' */
    int add_time, status = 0;
    char c;

    /* Recieve the time and check if it is valid */
    status = scanf("%d", &add_time);
    while ((c = getchar()) != EOF && c != '\n');

    if (status != 1 || add_time < 0) {
        printf("invalid time\n");
    }
    else {
        time += add_time;
        printf("%d\n", time);
    }
}

void caseU() {
    /* Main func. of the command 'u' */
    User new_user;
    char c;
    int i = 0, state = 0;

    /* Reads the new user */
    while ((c = getchar()) != '\n') {
        state = scanf("%20s[^ \n]", new_user.name);
    }

    /* if state = 0: no users (input) found
       if state = 1: user (input) found */
    if (state == 0) {
        for (i = 0; i < user_counter; i++) {
            printf("%s\n", users[i].name);
        }
    }
    else {
        for (i = 0; i <= user_counter; i++) {
            if (strcmp(new_user.name, users[i].name) == 0) {
                printf("user already exists\n");
                return;
            }
        }
        if (user_counter >= MAXUSERS) {
            printf("too many users\n");
            return;
        }
        strcpy(users[user_counter].name, new_user.name);
        user_counter++;
    }
}

void caseM() {
    /* Main func. of the command 'm' */
    int id, i, waste, slack;
    char user[MAXUSERLEN], next_activity[MAXACTLEN], c;

    /* Reads the input */
    scanf("%d %20s %20[^\n]", &id, user, next_activity);
    while ((c = getchar()) != EOF && c != '\n');

    /* Error testing */
    if (!verifyID(id)) {
        printf("no such task\n");
    }
    else if (strcmp(next_activity, "TO DO") == 0) {
        for (i = 0; i < task_counter; i++) {
            if (tasks[i].id == id) {
                if (strcmp(tasks[i].activity, "TO DO") != 0) {
                    printf("task already started\n");
                }
            }
        }
    }
    else if (!verifyUser(user)) {
        printf("no such user\n");
    }
    else if (!verifyAct(next_activity)) {
        printf("no such activity\n");
    }
    else {
        /* if current activity is "TO DO": the task start instant is that time instant
           if the activity we want to move is "DONE": calculate the waste and slack and print it */
        for (i = 0; i < task_counter; i++) {
            if (id == tasks[i].id) {
                if (strcmp(tasks[i].activity, "TO DO") == 0) {
                    tasks[i].start_inst = time;
                }
                /* If the task is going to be "DONE", print the waste / slack */
                if (strcmp(next_activity, "DONE") == 0 && strcmp(tasks[i].activity, "DONE") != 0) {
                    waste = time - tasks[i].start_inst;
                    slack = waste - tasks[i].duration;
                    printf("duration=%d slack=%d\n", waste, slack);
                }
                strcpy(tasks[i].activity, next_activity);
            }
        }
    }
}

void caseD() {
    /* Main func. of the command 'd' */
    char activity[MAXACTLEN], c;
    int i, sort_list_counter = 0;
    Task sort_list[MAXTASKS];

    /* Reads the input */
    while ((c = getchar()) != EOF && c != '\n') {
        scanf("%20[^\n]", activity);
    }

    /* Error testing */
    if (!verifyAct(activity)) {
        printf("no such activity\n");
    }
    else {
        /* Checks which tasks are in the the activity asked in the input */
        for (i = 0; i < task_counter; i++) {
            if (strcmp(activity, tasks[i].activity) == 0) {
                sort_list[sort_list_counter] = tasks[i];
                sort_list_counter++;
            }
        }
        /* Sort by numeric order of the start instant */
        sortByInstance(sort_list, 0, sort_list_counter-1);

        for (i = 0; i < sort_list_counter; i++) {
            printf("%d %d %s\n", sort_list[i].id, sort_list[i].start_inst, sort_list[i].description);
        }
    }
}

void caseA() {
    /* Main func. of the command 'a' */
    Activity new_a;
    char activity[MAXACTLEN];
    int i;

    /* Reads the input, can't use scanf() because activities can contain
       some strange chars */
    fgets(activity, MAXACTLEN, stdin);
    sscanf(activity, " %[^\n]", new_a.name);

    /* If activity[0] = '\n' means that there was no argument
       on the input */
    if (activity[0] == '\n') {
        for (i = 0; i < act_counter; i++) {
            printf("%s\n", act[i].name);
        }
    }

    else {
        /* Error testing */
        if (act_counter >= MAXACT) {
            printf("too many activities\n");
            return;
        }

        for (i = 0; new_a.name[i] != '\0'; i++) {
            if (islower(new_a.name[i]) != 0) {
                printf("invalid description\n");
                return;
            }
        }

        for (i = 0; i < act_counter; i++) {
            if (strcmp(act[i].name, new_a.name) == 0) {
                printf("duplicate activity\n");
                return;
            }
        }

        strcpy(act[act_counter].name, new_a.name);
        act_counter++;
    }
}

/*############################## MAIN FUNCTION ##############################*/

int main() {
    char c;
    int exit = 0;
    
    setDefaultActs();

    while (!exit) {
        switch (c = getchar()) {
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
                exit = 1;
        }
    }
    return 0;
}