#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXDESC 50
#define MAXID 1000
#define MAXUSERS 50
#define MAXACT 10
#define MAXACTLEN 20
#define MAXUSERLEN 20
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

/*############################## READ FUNCTIONS ##############################*/

int readInt() {
    char c;
    int num = 0, is_num = 0;

    while ((c = getchar()) != EOF && c != '\n' && (c != ' ' || is_num == 0)) {
        if (c >= '0' && c <= '9') {
            num = num * 10 + (c - '0');
            is_num = 1;
        }
        else if (c == ' ' && is_num == 0) {
            continue;
        }
        else {
            printf("readInt: error");
        }
    }
    return num;
}

void readSentence(char sentence[]) {
    char c;
    int i = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        sentence[i++] = c;
    }
    sentence[i] = '\0';
}


/*############################## CASE FUNCTIONS ##############################*/

int caseT(int time, int task_counter, Task tasks[]) {
    int duration, i;
    char description[MAXDESC];
    Task t;
    
    scanf("%d %[^\n]", &duration, description);
    
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

    t.duration = duration;
    t.id = task_counter + 1;
    t.start_inst = time;
    strcpy(t.description, description);
    strcpy(t.activity, "TO DO");

    printf("%s\n", t.description);
    tasks[task_counter] = t;
    task_counter++;

    printf("task %d", t.id);

    return task_counter;
}

void caseL(int task_counter, Task tasks[]) {
    int id_list[MAXUSERS];
    char c;
    int id = 0, list_size = 0, i, j;

    while ((c = getchar()) != EOF && c != '\n') {
        if (c == ' ') {
            id_list[list_size] = id;
            list_size++;
            id = 0;
        }
        else {
            id = id * 10 + (c - '0');
        }
    }
    
    if (list_size == 0) {
        /*SORT*/
        for (i = 1; i < list_size; i++) {
            printf("%d %s #%d %s\n", tasks[i].id, tasks[i].activity, tasks[i].duration, tasks[i].description);
        }
    }
    else {
        for (i = 0; i < list_size; i++) {
            for (j = 0; j < task_counter; j++) {
                if (tasks[j].id == id_list[i]) {
                    printf("%d %s #%d %s\n", tasks[j].id, tasks[j].activity, tasks[j].duration, tasks[j].description);
                }
            }
        }
    }
}

int caseN(int time) {
    int add_time;
    getchar();
    add_time = readInt();
    time += add_time;
    return time;
}

int caseU(int user_counter, User users[]) {
    User new_user;
    char c;
    int i = 0;

    getchar();
    while ((c = getchar()) != EOF && c != ' ' && c != '\n' && i < MAXUSERLEN-1) {
        new_user.name[i] = c;
        i++;
    }
    new_user.name[i] = '\0';

    if (strcmp(new_user.name, "\0") == 0) {
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

void caseM() {

}

void caseD() {
    /*char activity[MAXACTLEN+1], c;
    int i;

    while ((c = getchar()) != EOF && c != '\n' && c != '\0' && i < MAXACTLEN) {
        if (islower(c)) {
            printf("invalid description");
            break;
        }
        else {
            activity[i] = c;
            i++;
        }
    }
    activity[i] = '\0';*/
}

int caseA(int act_counter, Activity act[]) {
    Activity new_a;
    int i, j;

    getchar();
    readSentence(new_a.name);

    if (act_counter >= MAXACT) {
        printf("too many activities");
        return act_counter;
    }

    for (j = 0; new_a.name[j] != '\0'; j++) {
        if (islower(new_a.name[j]) != 0) {
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

    printf("%s\n%s\n%s\n%s\n", act[0].name, act[1].name, act[2].name, act[3].name);
}

/*############################## AUX FUNCTIONS ##############################*/

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
                    /* IN: t <duração> <descrição>
                       OUT: task <id> */
                    task_counter = caseT(time, task_counter, tasks);
                    break;
                case 'l':
                    /* IN: l [<id> <id> ...] 
                       OUT: <id> <actividade> #<duração> <descrição>
                       MOSTRA TAREFA */
                    caseL(task_counter, tasks);
                    break;
                case 'n':
                    /* n <duração> */
                    time = caseN(time);
                    printf("%d", time);
                    break;
                case 'u':
                    /* u [<utilizador>] */
                    /* GERIR UTILIZADORES */
                    user_counter = caseU(user_counter, users);
                    break;
                case 'm':
                    /* m <id> <utilizador> <atividade> */
                    /* MOVE TAREFA */
                    caseM();
                    break;
                case 'd':
                    /* d <atividade> */
                    /* MOSTRA TAREFA NA ATIVIDADE */
                    caseD();
                    break;
                case 'a':
                    /* a [<atividade>] */
                    /* GERIR ATIVIDADES */
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