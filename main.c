#include <stdio.h>
#include<windows.h>


char grid_variable[9][9] =
        {
        {0,0, 3 ,0,0,2,6,1,4},
         {0,0,2,6,4,1,0,0,8},
         {0,1,6,0,3,5,0,7,0},
         {0,0,0,3,0,0,0,9,7},
         {6,5,0,0,0,7,0,3,1},
         {0,3,7,0,5,4,0,0,0},
         {0,7,9,0,0,6,2,0,0},
         {0,0,0,5,8,3,7,0,0},
         {8,4,0,0,2,0,0,6,0}
        };

void setColor(int ForgC){

    //We will need this handle to get the current background attribute
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    //we use csbi for the wAttributes word.
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
        //Mask out all but the background attribute
        //, and add in the foreground color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

void grid(char grid_sys[][9])
{
    setColor(18);
    printf("------------------------------------------\n");
    setColor(15);
    printf("      ");
    for (int i = 0; i < 9 ; ++i)
    {
        setColor(4);
        printf(">%d< ",i+1);
        setColor(15);
    }
    setColor(18);
    printf("\n------------------------------------------\n");
    setColor(15);
    for (int i = 0; i < 9 ; ++i)
    {
        setColor(4);
        printf(">%d<  ",i+1);
        setColor(18);
        printf("|");
        setColor(15);

        for (int j = 0; j < 9 ; ++j)
        {
            if(grid_sys[i][j]==0)
            {
                if (grid_variable[i][j]!=0)
                {
                    setColor(3);
                    printf("%2d ",grid_variable[i][j]);
                    setColor(18);
                    printf("|");
                    setColor(15);
                    continue;
                }
                printf("   ");
                setColor(18);
                printf("|");
                setColor(15);
                continue;
            }
            printf("%2d ",grid_variable[i][j]);
            setColor(18);
            printf("|");
            setColor(15);
        }
        setColor(18);
        printf("\n------------------------------------------\n");
        setColor(15);
    }

}

char check_row_col(char row , char col, char playing)
{
    for (int i = 0; i < 9 ; ++i)
    {
        if(grid_variable[row-1][i]==playing || grid_variable[i][col-1]==playing)
        {
            printf("choose another value\n");
            return 0;
        }
    }
    return 1;
}

char system_check(char row , char col ,char grid_sys[][9])
{
    if(grid_sys[row-1][col-1] != 0)
    {
        printf("this is the system grid\n");
        return 0;
    }

    return 1;

}

void get_position(char* row,char* col,char* playing,char* red_flag,char grid_sys[][9])
{

    if(*red_flag==0)
    {
        printf("the range of number of row , col or playing from 1 to 9\n");
    }
    row:printf("Please enter the number of row: ");
        scanf("%hhu",row);
        if(*row < 1 || *row > 9)
        {
            printf("OUT OF RANGE\n");
            goto row;
        }
    col:printf("Please enter the number of column: ");
        scanf("%hhu",col);
        if(*col < 1 || *col > 9)
        {
            printf("OUT OF RANGE\n");
            goto col;
        }
    char sys_grid = system_check(*row,*col,grid_sys);
    if(sys_grid == 0)
    {
        goto row;
    }
    playing:printf("Please enter the value of playing: ");
    scanf("%hhu",playing);
    if(*playing < 1 || *playing > 9)
    {
        printf("OUT OF RANGE\n");
        goto playing;
    }
    char vaild = check_row_col(*row,*col,*playing);
    if (vaild==0)
        goto playing;

    *red_flag=1;
}

void sys(char (*grid_sys)[9])
{
    for (int i = 0; i < 9 ; ++i)
    {
        for (int j = 0; j < 9 ; ++j)
        {
            grid_sys[i][j]=grid_variable[i][j];
        }
    }
}

void put(char row , char col ,char playing ,char (*grid_sys)[9])
{

    grid_variable[row-1][col-1]= playing;
}

char check_win()
{
    for (int i = 0; i < 9 ; ++i)
    {
        for (int j = 0; j < 9 ; ++j)
        {
            if(grid_variable[i][j]==0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void rest(char (*grid_sys)[9])
{
    for (int i = 0; i < 9 ; ++i)
    {
        for (int j = 0; j < 9 ; ++j)
        {
            grid_variable[i][j]=grid_sys[i][j];
        }

    }
}

int main ()
{
    char row , col , playing ,red_flag=0 ,grid_sys[9][9],win,again;

    start:
    sys(grid_sys);
    while (1)
    {
        system("cls");
        grid(grid_sys);
        get_position(&row,&col,&playing,&red_flag,grid_sys);
        put(row,col,playing,grid_sys);
        win = check_win();
        if(win==1)
        {
            grid(grid_sys);
            printf("THE GAME IS DONE\n");
            printf("--------------------------\n");
            printf("Do you want to play again\n1)YES\n2)NO\n");
            printf("Please enter your choose: ");
            scanf("%hhu",&again);
            if(again==2)
            {
                printf("GOOD BYE\n");
                return 0;
            }
            else
            {
                system("cls");
                rest(grid_sys);
                goto start;
            }
        }
    }
}