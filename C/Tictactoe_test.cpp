#include <stdio.h>
#include <graphics.h>
#include <time.h>
void circle(int k);
void cross(int k);
void win(int k);
void response(int *player1, int i, int *botmove, int check[][3], int *botcount, int ms)
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
    //delay(ms);
    printf("Computer move is %d\n", botmove[bot]);
    cross(botmove[bot]);
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
            win(k);
            botmove[4]=5;
        }
    }
    bot++;
}
void pvp(int check[][3],int *onlyplayer1,int *botmove,int *player1,int *count,int *botcount)
{
    int k=0,l=0,temp,flag=0;
    printf("Enter the moves from 1 to 9\n");
    for(int i=1; i<=9; i++)
    {
        if(i%2==1)
        {
remove:
            printf("\nPlayer 1:");
            scanf("%d",&temp);
            for(int r=0; r<9; r++)
            {
                if(temp==player1[r] || temp>9 || temp<1)
                {
                    printf("Invalid move, Enter your move again..\n");
                    goto remove;
                }
            }
            onlyplayer1[k]=temp;
            cross(onlyplayer1[k]);
            for(int a=0; a<9; a++)
            {

                for(int c=0; c<3; c++)
                {
                    if(onlyplayer1[k]==check[a][c])
                        count[a]++;
                }


                if(count[a]==3)
                {
                    win(a);
                    printf("Player 1 wins!!");
                    flag=1;
                    break;
                }
            }
            player1[i-1]=onlyplayer1[k];
            k++;
        }
        else
        {
remove1:
            printf("Player 2:");
            scanf("%d",&temp);
            for(int r=0; r<9; r++)
            {

                if(temp==player1[r] || temp>9 || temp<1)
                {

                    printf("Invalid move, Enter your move again..\n");
                    goto remove1;
                }

            }
            botmove[l]=temp;
            circle(botmove[l]);
            for(int a=0; a<9; a++)
            {

                for(int c=0; c<3; c++)
                {
                    if(botmove[l]==check[a][c])
                        botcount[a]++;
                }


                if(botcount[a]==3)
                {
                    win(a);
                    printf("Player 1 wins!!");
                    flag=1;
                    break;
                }
            }
            player1[i-1]=botmove[l];
            l++;
        }
        if(flag==1)
            break;

    }

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

    int player1[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}, onlyplayer1[5], botmove[5];
    int gamemode;
    unsigned int ms;
    int flag = 0;
    int p = 0;
    int error;
    int temp;
    int check[8][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {3, 5, 7}, {1, 5, 9}};
    int botcount[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int count[] = {0, 0, 0, 0, 0, 0, 0, 0};
    // printf("enter the delay of computer(in milliseconds):");
    printf("Play mode?\n1.Human vs Human\n2.Human vs Computer\n");
    printf("Your choice:");
    scanf("%d",&gamemode);
    switch (gamemode)
    {
    case 1:
    {
        pvp(check,onlyplayer1,botmove,player1,count,botcount);
        break;
    }
    case 2:
    {
        //scanf("%u", &ms);
        printf("enter your move from 1 to 9:\n");
        for (int i = 0; i < 9; i = i + 2)
        {
            printf("move %d:", i + 1);
label1:
            scanf("%d", &temp);
            for (int k = 0; k < 9; k++)
            {
                error = 0;
                if (temp == player1[k] || temp > 9 || temp < 1)
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
            circle(player1[i]);

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
                    win(k);
                    break;
                }
            }
            if (flag == 1)
            {
                break;
            }

            response(player1, i + 1, botmove, check, botcount, ms);
            if (botmove[4] == 5)
            {
                printf("YOU LOSE.");
                break;
            }


        }

    }
    default:
        {
            printf("\nInvalid Input.");
            exit(0);
        }

    }
    printf("\nPress any key to exit.");
    getch();
}
void win(int k)
{
    if(k==0)
        line(150,200,300,200);
    else if(k==1)
        line(150,250,300,250);
    else if(k==2)
        line(150,300,300,300);
    else if(k==3)
        line(175,175,175,325);
    else if(k==4)
        line(225,175,225,325);
    else if(k==5)
        line(275,175,275,325);
    else if(k==6)
        line(300,175,150,325);
    else if(k==7)
        line(150,175,300,325);

}
void circle(int k)
{
    if(k==1)
        circle(175, 200, 15);

    else if(k==2)
        circle(225, 200, 15);

    else if(k==3)
        circle(275, 200, 15);

    else if(k==4)
        circle(175, 250, 15);

    else if(k==5)
        circle(225, 250, 15);

    else if(k==6)
        circle(275, 250, 15);

    else if(k==7)
        circle(175, 300, 15);

    else if(k==8)
        circle(225, 300, 15);

    else if(k==9)
        circle(275, 300, 15);

}
void cross(int k)
{
    switch (k)
    {
    case 5:
    {
        line(220, 245, 230, 255);
        line(230, 245, 220, 255);
        break;
    }
    case 1:
    {
        line(170, 195, 180, 205);
        line(170, 205, 180, 195);
        break;
    }
    case 2:
    {
        line(220, 195, 230, 205);
        line(220, 205, 230, 195);
        break;
    }
    case 3:
    {
        line(270, 195, 280, 205);
        line(270, 205, 280, 195);
        break;
    }
    case 4:
    {
        line(170, 245, 180, 255);
        line(170, 255, 180, 245);
        break;
    }
    case 6:
    {

        line(270, 245, 280, 255);
        line(270, 255, 280, 245);
        break;
    }
    case 7:
    {
        line(170, 305, 180, 295);
        line(170, 295, 180, 305);
        break;
    }
    case 8:
    {
        line(220, 295, 230, 305);
        line(220, 305, 230, 295);
        break;
    }
    case 9:
    {
        line(270, 295, 280, 305);
        line(270, 305, 280, 295);
        break;
    }
    }
}
