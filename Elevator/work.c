#include "dianTi.h"

floor = 5; //暂定楼层为5层
cengGao = 10; //暂定层高10
diantiWidth = 15;  //暂定电梯宽度为15
platformWidth = 25; //暂定平台宽度为25
nowceng = 1; //刚开始默认楼层为1
zhuangTai = 1; //定义刚开始的状态是上行

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

//开始游戏
int Start()
{
    char ch; 
    printPlatform();
    printElevator(1,5);
    ch = _getch();
    kaimen(nowceng);
    ch = _getch();
    guanmen(nowceng);

    return 1;
}

//打印电梯主函数
void printElevator(int formerceng, int latterceng)
{
    Hide();
    int dingweiY = (floor - formerceng + 1) * cengGao;
    for (int temp = dingweiY; (temp-cengLocation(formerceng))*(temp - cengLocation(latterceng)) <= 0; temp = temp + absto1(formerceng-latterceng)) {
        //电梯的框架
        clearFormerElevator();
        GotoXY(0, temp); //电梯上框
        for (int i = 0; i <= diantiWidth; i++) {
            printf(DGREEN"██"NONE);
        }
        GotoXY(0, temp + 10);//电梯下框
        for (int i = 0; i <= diantiWidth; i++) {
            printf(DGREEN"██"NONE);
        }
        for (int i = 0; i <= 10; i++) {//电梯门
            GotoXY(diantiWidth * 2, i + temp);
            printf(DGREEN"██"NONE);
        }
        //内部人员
        Sleep(200);
    }
    nowceng = latterceng;
    


}

//清理之前的电梯
void clearFormerElevator() {
    for (int i = 0; i <= (floor+1) * cengGao;i++) {
        for (int j = 0; j <= diantiWidth*2; j++) {
            GotoXY(j, i);
            printf("  ");
        }
    }
}

//打印平台函数
void printPlatform() {
    //平台打印
    for (int i = 0; i <= cengGao * (floor+1); i = i + cengGao) {
        GotoXY(diantiWidth * 2 + 4, i); //平台上框
        for (int i = 0; i <= diantiWidth; i++) {
            printf(PURPLE"██"NONE);
        }
    }

    //造平台门
    for (int i = 0; i <= cengGao * (floor + 1); i++) {
        GotoXY(diantiWidth * 2 + 4, i); 
        printf(YELLOW"██"NONE);
    }
}


void kaimen(int ceng) {
    int dingweiY = (floor - ceng + 1) * cengGao;
    //平台门开启
    for (int i = 9; i > 1; i--) {
        //平台门开启
        GotoXY(diantiWidth * 2 + 4, i + dingweiY);
        printf("  ");
        //电梯门开启
        GotoXY(diantiWidth * 2, i + dingweiY);
        printf("  ");
        Sleep(200);
    }
    GotoXY(diantiWidth * 2 + 2, 10 + dingweiY);
    printf(PURPLE"██"NONE);


}

void guanmen(int ceng) {
    int dingweiY = (floor - ceng + 1) * cengGao;
    
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