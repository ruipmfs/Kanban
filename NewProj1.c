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

int verifyID(int task_counter, int id, Task tasks[]) {
    int i, valid_id = 0;

    for (i = 0; i < task_counter; i++) {
        if (id == tasks[i].id) {
            valid_id = 1;
        }
    }
    return valid_id;
}

int verifyUser(int user_counter, char user[], User users[]) {
    int i, valid_user = 0;
    for (i = 0; i < user_counter; i++) {
        if (strcmp(user, users[i].name) == 0) {
            valid_user = 1;
        }
    }
    return valid_user;
}

int verifyAct(int act_counter, char activity[], Activity act[]) {
    int i, valid_act = 0;
    for (i = 0; i < act_counter; i++) {
        if (strcmp(act, tasks[i].activity) == 0) {
            valid_act = 1;
        }
    }
    return valid_act;
}

/*char readUser() {
    char c, user[MAXUSERLEN];
    int in_user = 0, i = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (in_user == 1) {
            if (c != ' ' && c != '\t') {
                user[i] = c;
                i++;
            }
            else {
                break;
            }
        }
        else {
            if (c != ' ' && c != '\t') {
                user[i] = c;
                i++;
            }
        }
    }
}*/

/*############################## CASE FUNCTIONS ##############################*/

int caseT(int time, int task_counter, Task tasks[]) {
    int duration, i;
    char description[MAXDESC], c;
    Task t;
    
    scanf("%d %50[^\n]", &duration, description);

    while ((c = getchar()) != EOF && c != '\n');
    
    printf("Duration: %d, Description: %s\n", duration, description);

    if (task_counter >= MAXTASKS) {
        printf("too many tasks");
        return task_counter;
    }
    
    for (i = 0; i <= task_counter; i++) {
        if (strcmp(description, tasks[i].description) == 0) {
            printf("duplicate description");
            return task_counter;
        }
    }

    if (duration <= 0) {
        printf("invalid duration");
        return task_counter;
    }

    t.duration = duration;
    t.id = task_counter + 1;
    t.start_inst = 0;
    strcpy(t.description, description);
    strcpy(t.activity, "TO DO");

    printf("%s\n", t.description);
    tasks[task_counter] = t;
    task_counter++;

    printf("task %d", t.id);

    return task_counter;
}

void caseL(int task_counter, Task tasks[]) {
    int list_size, i, j, id_list[MAXUSERS];

    list_size = readIdList(id_list);
    printf("%d %d %d", id_list[0], id_list[1], id_list[2]);

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

int caseN(int time) {
    int add_time, verifier = 0;
    char c;

    verifier = scanf("%d", &add_time);
    while ((c = getchar()) != EOF && c != '\n');
    if (verifier != 1 || add_time < 0) {
        printf("invalid time");
        return time;
    }
    else {
        printf("%d", (time + add_time));
        return (time + add_time);
    }
}

int caseU(int user_counter, User users[]) {
    User new_user;
    char c;
    int i = 0, state = 0;

    while ((c = getchar()) != '\n') {
        state = scanf("%20s[^ \n]", new_user.name);
        printf("%s", new_user.name);
    }

    if (state == 0) {
        for (i = 0; i < user_counter; i++) {
            printf("%s\n", users[i].name);
        }
        return user_counter;
    }
    else {
        if (user_counter >= MAXUSERS) {
            printf("too many users");
            return user_counter;
        }

        for (i = 0; i <= user_counter; i++) {
            if (strcmp(new_user.name, users[i].name) == 0) {
                printf("user already exists");
                return user_counter;
            }
        }
        
        strcpy(users[user_counter].name, new_user.name);
        user_counter++;
        return user_counter;
    }
}

void caseM(int time, int task_counter, int user_counter, int act_counter, Task tasks[], User users[], Activity act[]) {
    int id, i, valid_id = 0, gasto, slack, id_task;
    char user[MAXUSERLEN], activity[MAXACTLEN], c;

    scanf("%d %20s %20[^\n]", &id, user, activity);
    while ((c = getchar()) != EOF && c != '\n');

    printf("ID:%d\nUSER:%s\nACT:%s\n", id, user, activity);

    if (!verifyID(task_counter, id, tasks)) {
        printf("no such task");
        return;
    }
    else if (strcmp(activity, "TO DO") == 0) {
        printf("task already started");
        return;
    }
    else if (!verifyUser(user_counter, user, users)) {
        printf("no such user");
        return;
    }
    else if (!verifyAct(act_counter, act, activity)) {
        printf("no such activity");
        return;
    }
    else {
        if (strcmp(activity, "DONE") == 0) {
            gasto = 0;
            slack = 0;
            return;
        }
        else {
            for (i = 0; i < task_counter; i++) {
                if (id == tasks[i].id) {
                    if (strcmp(tasks[i].activity, "TO DO") == 0) {
                        tasks[i].start_inst = time;
                    }
                    strcpy(tasks[i].activity, activity);
                    return;
                }
            }
        }
    }
}

void caseD(int act_counter, Activity act[]) {
    char activity[MAXACTLEN], c;
    int i;

    while ((c = getchar()) != EOF && c != '\n') {
        scanf("%20[^\n]", activity);
        printf("%s", activity);
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

int caseA(int act_counter, Activity act[]) {
    Activity new_a;
    int i, state = 0;
    char c;

    while ((c = getchar()) != EOF && c != '\n') {
        state = scanf("%20[^\n]", new_a.name);
        printf("%s", new_a.name);
    }

    if (state == 0) {
        for (i = 0; i < act_counter; i++) {
            printf("%s\n", act[i].name);
        }
        return act_counter;
    }

    else {
        if (act_counter >= MAXACT) {
            printf("too many activities");
            return act_counter;
        }

        for (i = 0; new_a.name[i] != '\0'; i++) {
            if (islower(new_a.name[i]) != 0) {
                printf("invalid description");
                return act_counter;
            }
        }

        for (i = 0; i < act_counter; i++) {
            if (strcmp(act[i].name, new_a.name) == 0) {
                printf("duplicate activity");
                return act_counter;
            }
        }

        strcpy(act[act_counter].name, new_a.name);
        act_counter++;
        return act_counter;
    }
}

/*############################## MAIN FUNCTIONS ##############################*/

void displayMenu() {
    printf("\n**** K A N B A N ****\n");
    printf("t - Criar tarefa\n");
    printf("l - Mostrar tarefas\n");
    printf("n - Avancar tempo\n");
    printf("u - Gerir utilizadores\n");
    printf("m - Mover tarefa\n");
    printf("d - Mostrar tarefas na atividade\n");
    printf("a - Gerir atividades\n");
    printf("q - Sair\n");
    printf("************************\n");
}

int main() {
    char c;
    int exit = 0, time = 0, task_counter = 0, act_counter = 3, user_counter = 0;
    Task tasks[MAXTASKS];
    Activity act[MAXACT];
    User users[MAXUSERS];

    strcpy(act[0].name, "TO DO");
    strcpy(act[1].name, "IN PROGRESS");
    strcpy(act[2].name, "DONE");

    while (!exit) {
        displayMenu();
        c = getchar();
        switch (c) {
                case 't':
                    task_counter = caseT(time, task_counter, tasks);
                    break;
                case 'l':
                    caseL(task_counter, tasks);
                    break;
                case 'n':
                    time = caseN(time);
                    break;
                case 'u':
                    user_counter = caseU(user_counter, users);
                    break;
                case 'm':
                    caseM();
                    break;
                case 'd':
                    caseD(act_counter, act);
                    break;
                case 'a':
                    act_counter = caseA(act_counter, act);
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