#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2

typedef enum {fail, succeed} result;
typedef enum {right, left, up, down} direction;


result isEnd(int board[][N]){
    int i,j;
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j) {
            if( board[i][j] != i*N+j+1 )
                return fail;
        }
    return succeed;

}

void fillBoard(int board[][N] ) {
    int i, j;
    srand(time(NULL));
    
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j) {
            board[i][j] = i * N + j + 1;
        }

    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j) {
            int x = rand() % N;
            int y = rand() % N;
            int temp = board[i][j];
            board[i][j] = board[x][y];
            board[x][y] = temp;
        }
}

void printBoard(int board[][N]){
    int i;
    printf("\n\n");

    for (i = 0; i < 2+N; ++i)
        {
          if(i !=0 && i!= 1+N)
            printf("%d  ",i-1);
        else
            printf("      ");
    }

    printf("\n\n   ");

    for (i = 0; i < 2+N; ++i)
        printf("*  ");
    printf("\n");

    for (i = 0; i < N; ++i)
    {
        int j;
        if(N < 4)
            printf("%d  *",i);
        else
            printf("%d  * ",i);
    
        for (j = 0; j < N; ++j) {
            if(board[i][j] != N*N)
            {
                if(j == 0 && N > 3)
                    printf("%2d ", board[i][j]);
                else {
                    if (board[i][j] < 10 && N > 3)
                        printf(" %-2d", board[i][j]);
                    else
                        printf("%3d", board[i][j]);
                }
            }
            else
                printf("   ");
        }
        if(N < 4)
            printf("  *");
        else
            printf(" *");
        printf("\n");
    }
    printf("   ");
    for (i = 0; i < 2+N; ++i)
        printf("*  ");
    printf("\n");
}

short get_free_cell(int board[][N], int x, int y, direction dir){       /* returns the free cell if its on given direction */
    int i = -1,j;
    if(dir == right || dir == down)
        i = 1;
    if(dir == right || dir == left)
        for(j=y; j<N && j>=0; j+=i ){
            if(board[x][j] == N*N)
                return j;
        }
    else
        for(j=x; j<N && j>=0; j+=i ){
            if(board[j][y] == N*N)
                return j;
        }
        return -1;
}

result move(int board[][N], int x, int y, direction dir){
    int i = 1,j;
    int loc = get_free_cell(board, x, y, dir);
    if(loc == -1)
        return fail;
    
    if(dir == right || dir == down)
        i = -1;

    if(dir == right || dir == left) {                                                      /* if the move is horizantal */
        for (j = loc; j < N && j >= 0; j += i) {
            if (dir == right) {
                board[x][j] = board[x][j - 1];
            } else
                board[x][j] = board[x][j + 1];
            if(y == j)
                break;
        }
        board[x][y] = N*N;
    }
    else {                                                                                  /* if the move is vertical */
        for (j = loc; j < N && j >= 0; j += i) {
            if (dir == up && j+1 <N)
                board[j][y] = board[j+1][y];
            else if( j-1 >= 0)
                board[j][y] = board[j - 1][y];
            if(x == j)
                break;

        }
        board[x][y] = N*N;
    }
    return succeed;
}


int main() {

    int x, y;
    char direct;
    direction dir;
    int board[N][N];
    fillBoard(board);
    printBoard(board);

    do {
        char garbage[20];
        int b;
        printf("Enter movement [row column direction] (right:r, up:u, down:d, left:l): ");
        if( scanf("%d %d %c", &x, &y,&direct) == -1)
            scanf("%s",garbage);

        if(direct == 'r')
            dir = right;
        else if(direct == 'l')
            dir = left;
        else if(direct == 'u')
            dir = up;
        else if(direct == 'd')
            dir = down;
        else {
            printf("Wrong direction !! \n");
            continue;
        }

        b = move(board, x, y, dir);
        if(b == fail)
            printf("The input is not correct\n");
        printBoard(board);
    }while (! isEnd(board));

    printf("Congrutulations !!!\n");
    return 0;
}