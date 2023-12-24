#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct grid
{
    int num;
    int show;
};

struct record
{
    char first[20];
    char last[20];
    double timings;
};

struct grid gr[9][9];
struct record records[100];

void board()
{
    gr[0][0].num = 3;
    gr[0][1].num = 4;
    gr[0][2].num = 7;
    gr[0][3].num = 5;
    gr[0][4].num = 8;
    gr[0][5].num = 9;
    gr[0][6].num = 1;
    gr[0][7].num = 6;
    gr[0][8].num = 2;
    gr[1][0].num = 5;
    gr[1][1].num = 2;
    gr[1][2].num = 8;
    gr[1][3].num = 4;
    gr[1][4].num = 1;
    gr[1][5].num = 6;
    gr[1][6].num = 9;
    gr[1][7].num = 3;
    gr[1][8].num = 7;
    gr[2][0].num = 9;
    gr[2][1].num = 1;
    gr[2][2].num = 6;
    gr[2][3].num = 2;
    gr[2][4].num = 3;
    gr[2][5].num = 7;
    gr[2][6].num = 4;
    gr[2][7].num = 5;
    gr[2][8].num = 8;
    gr[3][0].num = 2;
    gr[3][1].num = 6;
    gr[3][2].num = 1;
    gr[3][3].num = 8;
    gr[3][4].num = 7;
    gr[3][5].num = 5;
    gr[3][6].num = 3;
    gr[3][7].num = 4;
    gr[3][8].num = 9;
    gr[4][0].num = 7;
    gr[4][1].num = 3;
    gr[4][2].num = 9;
    gr[4][3].num = 1;
    gr[4][4].num = 6;
    gr[4][5].num = 4;
    gr[4][6].num = 8;
    gr[4][7].num = 2;
    gr[4][8].num = 5;
    gr[5][0].num = 8;
    gr[5][1].num = 5;
    gr[5][2].num = 4;
    gr[5][3].num = 3;
    gr[5][4].num = 9;
    gr[5][5].num = 2;
    gr[5][6].num = 7;
    gr[5][7].num = 1;
    gr[5][8].num = 6;
    gr[6][0].num = 4;
    gr[6][1].num = 9;
    gr[6][2].num = 3;
    gr[6][3].num = 6;
    gr[6][4].num = 5;
    gr[6][5].num = 8;
    gr[6][6].num = 2;
    gr[6][7].num = 7;
    gr[6][8].num = 1;
    gr[7][0].num = 1;
    gr[7][1].num = 7;
    gr[7][2].num = 5;
    gr[7][3].num = 9;
    gr[7][4].num = 2;
    gr[7][5].num = 3;
    gr[7][6].num = 6;
    gr[7][7].num = 8;
    gr[7][8].num = 4;
    gr[8][0].num = 6;
    gr[8][1].num = 8;
    gr[8][2].num = 2;
    gr[8][3].num = 7;
    gr[8][4].num = 4;
    gr[8][5].num = 1;
    gr[8][6].num = 5;
    gr[8][7].num = 9;
    gr[8][8].num = 3;
}

void dekhabo_naki()
{
    int i, j;
    srand(time(0));
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            gr[i][j].show = rand() % 2;
        }
    }
}

void dekhan()
{
    int i, j;
    printf("-------------------------------------\n");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (gr[i][j].show == 1) {//1=hide, 0=show
                printf("|   ");
            }
            else {
                printf ("| %d ", gr[i][j].num);
            }
        }
        printf("|\n");
        printf("-------------------------------------\n");
    }
}

int check()
{
    int i, j, flag=0;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (gr[i][j].show == 1) {
                flag = 1;
                break;
            }
        }
    }
    if (flag == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void menu()
{
    printf("\n1. Play\n");
    printf("2. Scoreboard\n");
    printf("3. Instructions\n");
    printf("4. Exit\n");
}

void ScoreBoard()
{
    system("clear");
    FILE *score;
    score = fopen("score.txt", "r");
    int count = 0;
    
    if (score == NULL) {
        printf("File not found!\n");
        return;
    }
    
    while(fscanf(score, "%s %s %lf", records[count].first, records[count].last, &records[count].timings) != EOF) {
        count++;
    }
    fclose(score);

    for(int i = 0; i < count-1; i++) {
        for (int j = 0; j < count-1; j++) {
            if (records[j].timings > records[j+1].timings) {
                double temp = records[j].timings;
                records[j].timings = records[j+1].timings;
                records[j+1].timings = temp;
            }
        }
    }
    
    for(int i = 0; i < count; i++) {
        printf("%s %s %.3lf\n", records[i].first, records[i].last, records[i].timings);
    }
    
    printf("Press 'm' to go back to the menu.\n");
    while (1) {
        char c;
        scanf("%c", &c);
        if (c == 'm') {
            system("clear");
            break;
        }
    }
}

void play ()
{
    FILE *fp;
    char file[] = "score.txt";
    fp = fopen(file, "a");
    int m, n, in, life=0;
    clock_t start_time, end_time;
    double time_elapsed;
    char first_name[20], last_name[20];

    board();
    dekhabo_naki();

    printf("Enter your first name: \n");
    scanf("%s", first_name);
    printf("Enter your last name: \n");
    scanf("%s", last_name);

    system("clear");
    start_time = clock();
    while(1) {
        dekhan();

        printf("Enter the location of the tile (Row Column):\n(Enter 10 10 if you want to quit)\n");
        scanf("%d %d", &m, &n);
        if (m == 10 && n == 10) {
            system("clear");
            printf("Taking you back to the menu...\n");
            break;
        }

        else if (gr[m-1][n-1].show == 0) {
            system("clear");
            printf("This tile is already visible. Try again.\n");
            continue;
        }

        printf("Enter you guess: \n");
        scanf("%d", &in);
        
        if (gr[m-1][n-1].num == in) {
            system("clear");
            printf("Brilliant !!!\n");
            gr[m-1][n-1].show = 0;
        }
        else {
            life++;
            if (life < 9) {
                system("clear");
                printf("Nope! Try again !\n");
                printf("You have %d chances left.\n", 9-life);
            }
            if (life == 9) {
                printf("Game over!\n");
                break;
            }
        }
        
        if (check() == 1) {
            dekhan();
            system("clear");
            printf("Congratulations!!! You did it!\n");
            ScoreBoard();
            end_time = clock();
            time_elapsed = (double) (end_time - start_time) / CLOCKS_PER_SEC;
            printf("It took you %.3lf seconds\n", time_elapsed);
            fprintf(fp, "%s %s %.3lf\n", first_name, last_name, time_elapsed);
            fclose(fp);
            break;
        }
    }

    return;
}

void instruct()
{
    system("clear");
    printf("The goal is to fill a 9x9 grid with numbers so that each row, column, and 3x3 square contain a number between 1 to 9 only once. While some numbers will be visible others will be invisible. You have to guess the invisible ones.\n");
    printf("First you will have to put in the location of the tile in this format: Row Column. Then the number you have guessed. If you make 9 failed attempts you will lose.\n");
    printf("But if you succeed you will added to the scoreboard along with how much time you took to solve the puzzle.\n");
    
    printf("Press 'm' to go back to the menu.\n");
    while (1) {
        char c;
        scanf("%c", &c);
        if (c == 'm') {
            system("clear");
            break;
        }
    }
}



int main ()
{
    printf("                    Assalamu Alaikum. WELCOME TO SUDOKU!!!\nA DIGITAL VERSION OF THE CLASSIC JAPANESE PUZZLE GAME TO STIMULATE YOUR BRAIN.\n\n");
    int key, colbe=1;
    while (colbe) {
        menu();
        printf("\nWhat would you like to do?\n");
        scanf("%d", &key);
        switch (key) {
        case 1:
            play();
            break;
        case 2:
            ScoreBoard();
            break;
        case 3:
            instruct();
            break;
        case 4:
            printf("Thank you for playing. See you again. InshaAllah.\n");
            colbe = 0;
            break;
        default:
            printf("That's not an option. Try again .\n");
            break;
        }
    }
    
    return 0;
}