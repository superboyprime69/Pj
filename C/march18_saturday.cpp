#include <stdio.h>
#include <graphics.h>
#include <time.h>
int response(int *player1, int i, int *botmove, int check[][3], int *botcount,int ms)
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    time_t t1;
    int index;
    int bot = 0;
// generates unique index from array of moves
labelx:
    for (int k = 0; k < 10; k++)
    {
        srand((unsigned)time(&t1));
        index = rand() % 8;
        for (int j = 0; j < 9; j++)
        {
            if (a[index] == player1[j])
            {
                goto labelx;
            }
        }
    }
    // first move
    if (i == 1 && player1[0] != 5)
    {
        botmove[bot] = 5;
        player1[i] = botmove[bot];
    }
    else
    {
        // botmove here
        botmove[bot] = a[index];
        player1[i] = a[index];
    }
    delay(ms);
    printf("Computer move is %d\n", botmove[bot]);

    if (botmove[bot] == 5)
    {
        line(220, 245, 230, 255);
        line(230, 245, 220, 255);
    }
    else if (botmove[bot] == 1)
    {
        line(170, 195, 180, 205);
        line(170, 205, 180, 195);
    }

    else if (botmove[bot] == 2)
    {

        line(220, 195, 230, 205);
        line(220, 205, 230, 195);
    }
    else if (botmove[bot] == 3)
    {
        line(270, 195, 280, 205);
        line(270, 205, 280, 195);
    }
    else if (botmove[bot] == 4)
    {
        line(170, 245, 180, 255);
        line(170, 255, 180, 245);
    }
    else if (botmove[bot] == 6)
    {
        line(270, 245, 280, 255);
        line(270, 255, 280, 245);
    }
    else if (botmove[bot] == 7)
    {
        line(170, 295, 180, 305);
        line(170, 305, 180, 295);
    }
    else if (botmove[bot] == 8)
    {
        line(220, 295, 230, 305);
        line(220, 305, 230, 295);
    }
    else if (botmove[bot] == 9)
    {
        line(270, 295, 280, 305);
        line(270, 305, 280, 295);
    }
    // checking for computer wins
    for (int k = 0; k < 8; k++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (botmove[bot] == check[k][j])
                botcount[k]++;
        }
        if (botcount[k] == 3)
        {
            return 123;
            break;
        }
    }
    bot++;
}
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm," ");
    setcolor(WHITE);
    line(200, 175, 200, 325); // first vertical
    line(250, 175, 250, 325); // second vertical
    line(150, 225, 300, 225); // first horizontal
    line(150, 275, 300, 275); // second horizontal

    int player1[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}, onlyplayer1[5], botmove[4];

    unsigned int ms;
    int flag = 0;
    int p = 0;
    int error;
    int temp;
    int check[8][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {3, 5, 7}, {1, 5, 9}};
    int botcount[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int count[] = {0, 0, 0, 0, 0, 0, 0, 0};
    printf("enter the delay of computer(in milliseconds):");
    scanf("%u",&ms);
    printf("enter your move from 1 to 9:\n");
    for (int i = 0; i < 9; i = i + 2)
    {
        printf("move %d:", i + 1);
    label1:
        scanf("%d", &temp);
        for (int k = 0; k < 9; k++)
        {
            error = 0;
            if (temp == player1[k] || temp>9 || temp<1)
            {
                error = 1;
                break;
            }
        }
        if (error == 0)
        {
            player1[i] = temp;
            onlyplayer1[p] = temp;
            p++;
        }
        else if (error == 1)
        {
            printf("invalid move.\n");
            printf("enter your move again:");
            goto label1;
        }
        if (player1[i] == 1)
        {
            circle(175, 200, 15);
        }
        if (player1[i] == 5)
        {
            circle(225, 250, 15);
        }
        if (player1[i] == 2)
        {
            circle(225, 200, 15);
        }
        if (player1[i] == 3)
        {
            circle(275, 200, 15);
        }
        if (player1[i] == 4)
        {
            circle(175, 250, 15);
        }
        if (player1[i] == 6)
        {
            circle(275, 250, 15);
        }
        if (player1[i] == 7)
        {
            circle(175, 300, 15);
        }
        if (player1[i] == 8)
        {
            circle(225, 300, 15);
        }
        if (player1[i] == 9)
        {
            circle(275, 300, 15);
        }

        // checking win
        int q = i / 2;
        for (int k = 0; k < 8; k++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (onlyplayer1[q] == check[k][j])
                    count[k]++;
            }
            if (count[k] == 3)
            {
                printf("YOU WIN!!");
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            break;
        }

        int result = response(player1, i + 1, botmove, check, botcount,ms);
        if (result == 123)
        {
            printf("YOU LOSE.");
            break;
        }
    }

    printf("\nPress any key to exit.");
    getch();

}
