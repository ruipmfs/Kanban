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

int main() {
    Task t[3], temp;
    int i;

    t[0].id = 0, t[0].duration = 000, t[0].start_inst = 0; 
    strcpy(t[0].description, "desc0");
    strcpy(t[0].user, "user0");
    strcpy(t[0].activity, "ACT0");

    t[1].id = 1, t[1].duration = 100, t[1].start_inst = 1;
    strcpy(t[1].description, "desc1");
    strcpy(t[1].user, "user1");
    strcpy(t[1].activity, "ACT1");

    t[2].id = 2, t[2].duration = 200, t[2].start_inst = 2;
    strcpy(t[2].description, "desc2");
    strcpy(t[2].user, "user2");
    strcpy(t[2].activity, "ACT2");

    temp = t[0];
    t[0] = t[2];
    t[2] = temp;

    for (i = 0; i < 3; i++) {
        printf("%d %s #%d %s\n", t[i].id, t[i].activity, t[i].duration, t[i].description);
    }
    return 0;
}

