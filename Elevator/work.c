#include "dianTi.h"

floor = 5; //暂定楼层为5层
cengGao = 10; //暂定层高10
diantiWidth = 15;  //暂定电梯宽度为15
platformWidth = 25; //暂定平台宽度为25
nowceng = 1; //刚开始默认楼层为1
int shangXingButton[6];//上行电梯按钮状态1表示亮起
int xiaXingButton[6];//下行电梯按钮状态1表示亮起

//光标定位函数
void GotoXY(int x, int y)
{
    HANDLE hout;
    COORD cor;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(hout, cor);
}

//隐藏光标
void Hide()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cor_info = { 1, 0 };
    SetConsoleCursorInfo(hout, &cor_info);//隐藏光标

}

//菜单栏目
int Menu() {
    Hide();
    GotoXY(36, 12);   //定位光标的位置
    printf(ORED"欢迎来到电梯小游戏");
    GotoXY(43, 14);
    printf("1. 开始游戏");
    GotoXY(43, 16);
    printf("2. 设置");
    GotoXY(43, 18);
    printf("退出游戏请输入     0"NONE);
    Hide();    //隐藏光标
    char ch;
    int result = 1;
    ch = _getch();
    switch (ch)
    {
      case '1': result = 1; break;
      case '2': result = 2; break;
      case '0': result = 0; break;
      default:  result = 5; break;
    }
    system("cls");  //清空当前页面
    return result;
}

// 初始化一些参数，包括电梯的状态以及电梯运行的状况
void chushihua(){
    for (int i = 0; i <= floor; i++) {
        shangXingButton[i] = 0;
        xiaXingButton[i] = 0;
        target[i] = 0;
    }
    nowLocation = cengLocation(nowceng);
    zhuangTai = 1; //定义刚开始的状态是上行
}

//开始游戏
int Start()
{
    chushihua();
    target[3] = 1;
    shangXingButton[3] = 1;
    printPlatform();
    printElevator();
    
    while (1) {
        if (shangXingButton[nowceng] == 1) {
            kaimen(nowceng);
            //填写人进入电梯中
            guanmen(nowceng);
            Sleep(200);
            shangXingButton[nowceng] = 0;
        }
        nowLocation = nowLocation - zhuangTai;
        if (nowLocation % cengGao == 0) {
            nowceng = nowLocation / cengGao;
        }
        printElevator();
       Sleep(200);
    }
}

//打印电梯主函数
void printElevator()
{
    Hide();
    clearFormerElevator();
    GotoXY(0, nowLocation); //电梯上框
    for (int i = 0; i <= diantiWidth; i++) {
        printf(DGREEN"██"NONE);
    }
    GotoXY(0, nowLocation + 10);//电梯下框
    for (int i = 0; i <= diantiWidth; i++) {
        printf(DGREEN"██"NONE);
    }
    for (int i = 0; i <= 10; i++) {//电梯门
        GotoXY(diantiWidth * 2, i + nowLocation);
        printf(DGREEN"██"NONE);
    }
        //内部人员;
}

//清理之前的电梯
void clearFormerElevator() {
    for (int i = 0; i <= (floor) * cengGao;i++) {
        for (int j = 0; j <= diantiWidth*2; j++) {
            GotoXY(j, i);
            printf("  ");
        }
    }
}

//打印平台函数
void printPlatform() {
    //平台打印
    for (int i = 0; i <= cengGao * (floor); i = i + cengGao) {
        GotoXY(diantiWidth * 2 + 4, i); //平台上框
        for (int i = 0; i <= diantiWidth; i++) {
            printf(PURPLE"██"NONE);
        }
    }

    //造平台门
    for (int i = 0; i <= cengGao * (floor); i++) {
        GotoXY(diantiWidth * 2 + 4, i); 
        printf(YELLOW"██"NONE);
    }
}

void kaimen(int ceng) {
    int dingweiY = (floor - ceng+1) * cengGao;
    //平台门开启
    Sleep(200);
    for (int i = 9; i > 2; i--) {
        //平台门开启
        GotoXY(diantiWidth * 2 + 4, i + dingweiY);
        printf("  ");
        //电梯门开启
        GotoXY(diantiWidth * 2, i + dingweiY);
        printf("  ");
    }
    GotoXY(diantiWidth * 2 + 2, 10 + dingweiY);
    printf(PURPLE"██"NONE);


}

void guanmen(int ceng) {
    int dingweiY = (floor - ceng+1) * cengGao;
    
    for (int i = 1; i < 10; i++) {
        //平台门关闭
        GotoXY(diantiWidth * 2 + 4, i + dingweiY);
        printf(YELLOW"██"NONE);
        //电梯门关闭
        GotoXY(diantiWidth * 2, i + dingweiY);
        printf(DGREEN"██"NONE);
        Sleep(200);
        GotoXY(diantiWidth * 2 + 2, 10 + dingweiY);
        printf("  ");
    }
}