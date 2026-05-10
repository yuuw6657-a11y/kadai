#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include <math.h>
// FB:
// 不要です.
// 意図はわかりませんが、
// abs()ならstdlib.hで十分です

// FB:
// 定数化しているのは良いことです
#define ROWS 20  // 縦のサイズ
#define COLS 40  // 横のサイズ


// FB:
// これからはmainに全処理を書くのはやめましょう.
// 関数化することで可読性が向上しますし、拡張性も増します.
int main(void){

    printf("指定した時間の間に画面にでた■の数の合計を入力してください\n");
    printf("その数に近いほどもらえる点数が多くなります。\n");
    getchar();

    // FB:
    // 悪くはないですが、遅いですし環境依存なのでお勧めはしません.
    // Linux系(winでも一応動くかも)ならprintf("\033[2J\033[H");だけで十分です.
    //
    // どこで動かすことを想定していますか？
    // WSL2ですか？普通のWindows環境ですか？
    // 後のsleep関数は基本的にWin環境に存在しないので、
    // 私ならここではLinux用の対応だけを考えるか、
    // 後のsleepも#ifdefでwin/linuxで分岐すると思います
    // 目的を最初に考えましょう
    //
    //
    // 画面を消去するコマンドを実行
    // Windowsの場合は "cls"、それ以外（Mac/Linux）は "clear"
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    int screen[ROWS][COLS] = {0};

    // FB:
    // 変数名は気をつけましょう.
    // a,p,qは絶対に変えるべきです.
    // numも"何の"数値かわかりません.
    //
    // 私なら例えば、
    // int display_time; 
    // int block_count; 
    // int placed_count = 0; 
    // int answer;
    // int score;
    // のように定義します.
    int a,num, count=0,p,q;

    // seed初期化
    srand((unsigned int)time(NULL));

    // FB:
    // 空行いれてなるべく処理でまとめた方が見やすいです.
    printf("時間を指定してください（秒）:");
    
    // FB:
    // ここで、"aaa"などの入力がきたらどうでしょうか？
    // あと、10000でも通ってしまいますよね？
    // Maxは設定したほうがよさそうなのと、
    // scanfを使うなら
    // if (scanf("%d", &a) != 1) {}で処理する癖があると良いです.
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
                // FB:
                // 全角Spaceは端末依存があるので、
                // これはかなり懸命な判断です.
                printf("  "); // 空白（全角スペースと同じ幅にするため半角2つ）
            }
        }
        printf("\n");
    }
    fflush(stdout);

    // FB:
    // 基本的にWin環境にsleepは無いです
    // 完全に対応するにはSleep(ms)が必要になります
    // そもそもWSL2でのみうごかすことを想定しているなら、
    // 途中のWIN分岐などもいらないわけです.
    sleep(a);
    

    // FB:
    // 最初の方でclear(外部コマンド)を使っていながら、
    // ここで２種類目の方法で消去しているのは一貫性がないです.
    printf("\033[2J\033[H");
    fflush(stdout);
    
    printf("■の数を入力してください：");
    scanf("%d",&p);

    q=5-abs(p-num);


    if(q>=0){
        // FB: これは何もしていません..
        // if (q < 0) {
        //   q = 0;
        // }
        // これだけで良いです
        q=q;
    }else{
        q=0;
    }
    
    printf("あなたの点数は%dです。\n",q);
    printf("■の数は%dです。\n\n",num);

    return 0;

}  
    
