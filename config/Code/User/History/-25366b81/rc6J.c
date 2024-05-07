#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person Person_create(char *name, int age, int height, int weight) {
    struct Person who = {
        .name = name, .age = age, .height = height, .weight = weight};

    return who;
}

void Person_print(struct Person who) {
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[]) {
    // make two people structures
    struct Person joe = Person_create("Joe Alex", 32, 64, 140);

    struct Person frank = Person_create("Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);

    char *whoelse = "Whoelsewhateveridontcarerightwhocareshahahahahaha";
    // char *whoelse = "Whoelse";
    // strdup - malloc enough space to duplicate a str
    // strcpy - copy src to dest, you need to make sure
    // dest must be large enough. Beware of buffer overruns!
    // frank->name = strdup(whoelse);
    // this example can cause overlap.
    strcpy(frank->name, whoelse);
    Person_print(frank);

    // destroy them both so we clean up
    Person_destroy(joe);
    Person_destroy(frank);
    // Person_destroy(NULL);

    return 0;
}