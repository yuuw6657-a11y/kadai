#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20  // 縦のサイズ
#define COLS 40  // 横のサイズ

int main(void){
    printf("指定した時間の間に画面にでた■の数の合計を入力してください\n");
    printf("その数に近いほどもらえる点数が多くなります。\n");
    getchar();

    // 画面を消去するコマンドを実行
    // Windowsの場合は "cls"、それ以外（Mac/Linux）は "clear"
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    int screen[ROWS][COLS] = {0};
    int a,num, count=0,p,q;
    srand((unsigned int)time(NULL));

    printf("時間を指定してください（秒）:");
    scanf("%d",&a);
    printf("5から20個の■を表示します。");
    num=rand()% 16+5;
    while (count < num) {
        int r = rand() % ROWS;
        int c = rand() % COLS;

        // まだ 1 が入っていない場所なら配置
        if (screen[r][c] == 0) {
            screen[r][c] = 1; 
            count++;
        }
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (screen[i][j] == 1) {
                printf("■");
            } else {
                printf("  "); // 空白（全角スペースと同じ幅にするため半角2つ）
            }
        }
        printf("\n");
    }
    fflush(stdout);
    sleep(a);
    printf("\033[2J\033[H");
    fflush(stdout);
    
    printf("■の数を入力してください：");
    scanf("%d",&p);
    q=5-abs(p-num);
    if(q>=0){
        q=q;
    }else{
        q=0;
    }
    
    printf("あなたの点数は%dです。\n",q);
    printf("■の数は%dです。\n\n",num);
    return 0;

}  
    