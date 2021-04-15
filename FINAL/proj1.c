/* RUI SANTOS   98966 */
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

Task tasks[MAXTASKS]; /* VECTOR OF ALL TASKS */
Activity act[MAXACT]; /* VECTOR OF ALL ACTIVITIES */
User users[MAXUSERS]; /* VECTOR OF ALL USERS */

int time = 0, task_counter = 0, act_counter = 3, user_counter = 0;

/*
[int] time: system time
[int] task_counter: current number of tasks
[int] act_counter: current number of activities (3 because of the default acts)
[int] user_counter: current number of users
*/

/*############################## AUX FUNCTIONS ##############################*/

void setDefaultActs() {
    /*
    CREATES THE DEFAULT ACTIVITIES
    INPUT: - 
    OUTPUT: - 
    */

    strcpy(act[0].name, "TO DO");
    strcpy(act[1].name, "IN PROGRESS");
    strcpy(act[2].name, "DONE");
}

int readIdList(int id_list[]) {
    /*
    READS A SEQUENCE OF ID'S, CHANGING AN EMPTY LIST WITH THEM
    INPUT:  [int] id_list[]: LIST OF ID'S (EMPTY)
    OUTPUT: [int] list_size: SIZE OF THE LIST
            [int] id_list[]: LIST OF ID'S
    */

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
    /*
    VERIFIES IF THE INPUT (ID) IS CONTAINED IN THE TASKS
    INPUT:  [int] id: AN INTEGER NUMBER (ID)
    OUTPUT: bool (IF THE ID IS VALID OR NOT)
    */
    int i;

    for (i = 0; i < task_counter; i++) {
        if (id == tasks[i].id) {
            return 1;
        }
    }
    return 0;
}

int verifyUser(char user[]) {
    /*
    VERIFIES IF THE INPUT (USER) IS CONTAINED IN THE LISTED USERS
    INPUT:  [char] user: A STRING WITHOUT SPACES AND LESS THAN 21 CHARS (USER)
    OUTPUT: bool (IF THE USER IS VALID OR NOT)
    */
    int i;
    for (i = 0; i < user_counter; i++) {
        if (!strcmp(user, users[i].name)) {
            return 1;
        }
    }
    return 0;
}

int verifyAct(char activity[]) {
    /*
    VERIFIES IF THE INPUT (ACTIVITY) IS CONTAINED IN THE LISTED ACTIVITIES
    INPUT:  [char] activity[]: A STRING WITH LESS THAN 21 CHARS (ACTIVITY)
    OUTPUT: bool (IF THE ACTIVITY IS VALID OR NOT)
    */
    int i;
    for (i = 0; i < act_counter; i++) {
        if (!strcmp(activity, act[i].name)) {
            return 1;
        }
    }
    return 0;
}

int lessAlphabet(char s1[], char s2[]) {
    /*
    VERIFIES WHICH BETWEEN 2 STRINGS COMES 1ST ALPHABETICALLY
    INPUT:  [char] s1[]: STRING
            [char] s2[]: STRING
    OUTPUT: bool (AS DESCRIBED)
    */
    int i;
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
    /*
    CHECKS IF 2 TASKS HAVE THE SAME START INSTANT. IF SO CHECK WHICH COMES 1ST
    ALPHABETICALLY (CALL FUNCTION lessAlphabet()), OTHERWISE CHECK IF THE START
    INSTANT OF T1 IS LESS OR EQUAL FROM T2 
    INPUT:  [Task] t1: TASK
            [Task] t2: TASK
    OUTPUT: bool (AS DESCRIBED)
    */
    if (t1.start_inst == t2.start_inst) {
        return lessAlphabet(t1.description, t2.description);
    }
    return t1.start_inst <= t2.start_inst;
}
/*
int partitionByInstance(Task list[], int start, int end) {
    /*
    AUX FUNC OF THE QUICKSORT ALGORITHM
    SORTS SMALL PARTITIONS OF THE MAIN LIST
    INPUT:  [Task] list[]: LIST OF TASKS. THE FUNC WILL USE ELEMENTS FROM THE
                           STRUCT TASK IN AUX FUNCS
            [int] start: START INDEX OF THE FUNC WE WANT TO SORT
            [int] end: FINAL INDEX OF THE FUNC WE WANT TO SORT
    OUTPUT: [int] i: INDEX OF WHERE THE LIST STARTS, TO BE USED ON MAIN
                     FUNC OF QUICKSORT

    int i = start-1, j = end;
    Task pivot = list[end], temp;

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
    /*
    MAIN FUNC OF THE SORT ALGORITHM (RECUSIVE FUNC)
    DIVIDES THE LIST BY TWO, CALL ITSELF TWICE AND partitionByInstance() TO SORT
    INPUT:  [Task] list[]: LIST OF TASKS. THE FUNC WILL USE ELEMENTS FROM THE
                           STRUCT TASK IN AUX FUNCS
            [int] left: START INDEX OF THE FUNC WE WANT TO SORT
            [int] right: FINAL INDEX OF THE FUNC WE WANT TO SORT
    OUTPUT: [int] i: INDEX OF WHERE THE LIST STARTS, TO BE USED ON MAIN
                     FUNC OF QUICKSORT
    
    int part;

    if (right <= left)
        return;
    
    part = partitionByInstance(list, left, right);

    sortByInstance(list, left, part-1);
    sortByInstance(list, part+1, right);
}
int partitionByAlphabet(Task list[], int start, int end) {
    /*
    AUX FUNC OF THE QUICKSORT ALGORITHM
    SORTS SMALL PARTITIONS OF THE MAIN LIST
    INPUT:  [Task] list[]: LIST OF TASKS. THE FUNC WILL USE ELEMENTS FROM THE
                           STRUCT TASK IN AUX FUNCS
            [int] start: START INDEX OF THE FUNC WE WANT TO SORT
            [int] end: FINAL INDEX OF THE FUNC WE WANT TO SORT
    OUTPUT: [int] i: INDEX OF WHERE THE LIST STARTS, TO BE USED ON MAIN
                     FUNC OF QUICKSORT
    int i = start-1, j = end;
    Task pivot = list[end], temp;

    while (i < j) {
        while (lessAlphabet(list[++i].description, pivot.description) && i < j && i < end);
        while (lessAlphabet(pivot.description, list[--j].description)) {
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
    /*
    MAIN FUNC OF THE SORT ALGORITHM (RECUSIVE FUNC)
    DIVIDES THE LIST BY TWO, CALL ITSELF TWICE AND partitionByAlphabet() TO SORT
    INPUT:  [Task] list[]: LIST OF TASKS. THE FUNC WILL USE ELEMENTS FROM THE
                           STRUCT TASK IN AUX FUNCS
            [int] left: START INDEX OF THE FUNC WE WANT TO SORT
            [int] right: FINAL INDEX OF THE FUNC WE WANT TO SORT
    OUTPUT: [int] i: INDEX OF WHERE THE LIST STARTS, TO BE USED ON MAIN
                     FUNC OF QUICKSORT
    int part;

    if (right <= left)
        return;

    part = partitionByAlphabet(list, left, right);

    sortByAlphabet(list, left, part-1);
    sortByAlphabet(list, part+1, right);
}
*/

int partition(Task list[], int left, int right, int less_instance) {
    int i = left-1, j = right;
    Task pivot = list[right], temp;

    while (i < j) {
        if (less_instance) {
            while (lessInstanceAndAlphabet(list[++i], pivot) && i < j && i < right);
            while (lessInstanceAndAlphabet(pivot, list[--j])) 
                if (j == left) break;  
        }
        else {
            while (lessAlphabet(list[++i].description, pivot.description) && i < j && i < right);
            while (lessAlphabet(pivot.description, list[--j].description)) 
                if (j == left) break;  
        }

        if (i < j) {
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    temp = list[i];
    list[i] = list[right];
    list[right] = temp;
    return i;
}

void quicksort(Task list[], int left, int right, int less_instance) {
    int part;

    if (right <= left)
        return;

    part = partition(list, left, right, less_instance);

    quicksort(list, left, part-1, less_instance);
    quicksort(list, part+1, right, less_instance);
}

/*############################## CASE FUNCTIONS ##############################*/

void caseT() {
    /*
    MAIN FUNCTION OF THE COMMAND 't'
    CREATES A NEW TASK
    INPUT: -
    OUTPUT: -
    */
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
        if (!strcmp(description, tasks[i].description)) {
            printf("duplicate description\n");
            return;
        }
    }

    if (duration <= 0) {
        printf("invalid duration\n");
        return;
    }

    /* Task creation */
    tasks[task_counter].duration = duration;
    tasks[task_counter].id = task_counter + 1;
    tasks[task_counter].start_inst = 0;
    strcpy(tasks[task_counter].description, description);
    strcpy(tasks[task_counter].activity, "TO DO");

    task_counter++;

    printf("task %d\n", tasks[task_counter-1].id);
}

void caseL() {
    /*
    MAIN FUNCTION OF THE COMMAND 'l'
    PRINTS A COUPLE OF TASKS, RECIEVED IN THE id_list[].
    IF NO ID'S RECIEVED, PRINTS ALL THE TASKS BY CREATION ORDER
    ALPHABETIC ORDER (DESCRIPTION)
    INPUT: -
    OUTPUT: -
    */
    int list_size, i, j, id_list[MAXTASKS];
    Task sorted_tasks[MAXTASKS];

    for (i = 0; i < task_counter; i++) {
        sorted_tasks[i] = tasks[i];
    }

    list_size = readIdList(id_list);

    /* If no arguments recieved */
    if (list_size == 0) {
        quicksort(sorted_tasks, 0, task_counter-1, 0);
        for (i = 0; i < task_counter; i++) {
            printf("%d %s #%d %s\n", sorted_tasks[i].id, sorted_tasks[i].activity, sorted_tasks[i].duration, sorted_tasks[i].description);
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
    /*
    MAIN FUNCTION OF THE COMMAND 'n'
    ADVANCES IN TIME
    INPUT: -
    OUTPUT: -
    */
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
    /*
    MAIN FUNCTION OF THE COMMAND 'u'
    CREATES A NEW USER
    INPUT: -
    OUTPUT: -
    */
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
            if (!strcmp(new_user.name, users[i].name)) {
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
    /*
    MAIN FUNCTION OF THE COMMAND 'm'
    MOVE A TASK TO A DIFFERENT ACTIVITY
    INPUT: -
    OUTPUT: -
    */
    int id, i, waste, slack;
    char user[MAXUSERLEN], next_activity[MAXACTLEN], c;

    /* Reads the input */
    scanf("%d %20s %20[^\n]", &id, user, next_activity);
    while ((c = getchar()) != EOF && c != '\n');

    /* Error testing */
    if (!verifyID(id)) {
        printf("no such task\n");
    }
    else if (!strcmp(next_activity, "TO DO")) {
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
                if (!strcmp(tasks[i].activity, "TO DO")) {
                    tasks[i].start_inst = time;
                }
                /* If the task is going to be "DONE", print the waste / slack */
                if (!strcmp(next_activity, "DONE") && strcmp(tasks[i].activity, "DONE") != 0) {
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
    /*
    MAIN FUNCTION OF THE COMMAND 'd'
    SORT ALL THE TASKS IN A CERTAIN ACTIVITY BY START INSTANT. IF THERE IS
    TASKS WITH THE SAME START INSTANT, IT SHOULD BE SORT BY ALPHABETIC ORDER
    OF THE DESCRIPTION
    INPUT: -
    OUTPUT: -
    */
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
            if (!strcmp(activity, tasks[i].activity)) {
                sort_list[sort_list_counter] = tasks[i];
                sort_list_counter++;
            }
        }
        /* Sort by numeric order of the start instant */
        quicksort(sort_list, 0, sort_list_counter-1, 1);

        for (i = 0; i < sort_list_counter; i++) {
            printf("%d %d %s\n", sort_list[i].id, sort_list[i].start_inst, sort_list[i].description);
        }
    }
}

void caseA() {
    /*
    MAIN FUNCTION OF THE COMMAND 'a'
    CREATES A NEW ACTIVITY
    INPUT: -
    OUTPUT: -
    */
    Activity new_a;
    char c;
    int i;
    new_a.name[0] = '\0';

    /* Reads the input */
    while ((c = getchar()) && c != '\n') {
        scanf("%20[^\n]", new_a.name);
    }

    /* If activity[0] = '\0' means that there was no argument
       on the input */
    if (new_a.name[0] == '\0') {
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
            if (!strcmp(act[i].name, new_a.name)) {
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
    /* FUNCTION THAT CONTROLS ALL THE PROJECT */
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