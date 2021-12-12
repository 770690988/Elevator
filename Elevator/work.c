#include "dianTi.h"

lowFloor = 4; //暂定楼层为5层
cengGao = 10; //暂定层高10
diantiWidth = 15;  //暂定电梯宽度为15
platformWidth = 25; //暂定平台宽度为25
nowceng = 1; //刚开始默认楼层为1
peopleNumMax = 10; //定义最多的人数为10个人

typedef struct PeopleStruct {
    int isInUse;  //定义该人的空间是否在使用中，如果在使用，则为1 否则为0
    int weight;
    int positionx; //轴所在的位置
    int nowFloor; //当前楼层
    int targetFloor; //目标楼层
    int In_or_Out;//往电梯进入为1 出电梯为-1 不动为0
    int isInElevator;  //判断是否在电梯中
}People;

struct PeopleList{
    People people[10];
}peoplelist;

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
void chushihua() {
    for (int i = 0; i <= lowFloor; i++) {
        shangXingButton[i] = 0;
        xiaXingButton[i] = 0;
        target[i] = 0;
    }
    
    for (int i = 0; i < 10; i++) {
        peoplelist.people[i].isInUse = 0;
    }
    nowLocation = cengLocation(nowceng);
    //zhuangTai = 1; //定义刚开始的状态是上行
    refreshZTL();
}

//对人创建的处理
void createPeople() {
    int suijiNum = (int)rand() % 100;
    if (suijiNum <= 2) {
        int position = scanPeopleStruct();
        if (position)
        {
            int nowFloor = (int)rand() % (lowFloor) + 1;
            int targetFloor = (int)rand() % (lowFloor) + 1;
            while (targetFloor == nowFloor) {
                targetFloor = (int)rand() % (lowFloor)+1;
            }
            int weight = (int)rand()%40 + 40;

            //下面就开始对数据进行赋值
            peoplelist.people[position - 1].isInUse = 1;
            peoplelist.people[position - 1].nowFloor = nowFloor;
            peoplelist.people[position - 1].targetFloor = targetFloor;
            peoplelist.people[position - 1].In_or_Out = 1;
            peoplelist.people[position - 1].positionx = diantiWidth * 3 + 14;
            peoplelist.people[position - 1].isInElevator = 0;
        }else {
            return;
        }
    }
}

void movePeople() {
    int positiony;
    for (int i = 0; i < 10; i++)
    {
        //将每个需要移动的人移动一下
        if (peoplelist.people[i].In_or_Out == 0) {
            continue;
        }
        if (isPaiDui(i)) {
            peoplelist.people[i].In_or_Out = 0;
            //人到电梯门前的按按钮处理
            chuLiButton(absto1(peoplelist.people[i].targetFloor - peoplelist.people[i].nowFloor), peoplelist.people[i].nowFloor, 1);
            refreshZTL();
        }else if (peoplelist.people[i].isInUse) {
            positiony = (lowFloor - peoplelist.people[i].nowFloor + 1) * cengGao - 1;
            GotoXY(peoplelist.people[i].positionx, positiony);
            printf(" ");
            GotoXY(peoplelist.people[i].positionx, positiony-1);
            printf(" ");
            peoplelist.people[i].positionx = peoplelist.people[i].positionx - peoplelist.people[i].In_or_Out;
            GotoXY(peoplelist.people[i].positionx, positiony);
            printf("!");
            GotoXY(peoplelist.people[i].positionx, positiony-1);
            printf("%d", peoplelist.people[i].targetFloor);
        }
        //人到达电梯后离开的处理操作
        if (peoplelist.people[i].positionx == diantiWidth * 3 + 16) {
            peoplelist.people[i].isInUse = 0;
            positiony = (lowFloor - peoplelist.people[i].nowFloor + 1) * cengGao - 1;
            GotoXY(peoplelist.people[i].positionx, positiony);
            printf(" ");
            GotoXY(peoplelist.people[i].positionx, positiony-1);
            printf(" ");
        }  
    }
}

//判断前面是否有人在排队:0 没有人排队:1
int isPaiDui(int peopleNum) {
    int nowFloor = peoplelist.people[peopleNum].nowFloor;
    int positionxNext = peoplelist.people[peopleNum].positionx - peoplelist.people[peopleNum].In_or_Out;
    int positionxi;
    int iFloor;
    //处理到达墙但是门没开的情况
    if (peoplelist.people[peopleNum].positionx == 2 * diantiWidth + 6) {
        return 1;
    }
    for (int i = 0; i < 10; i++)
    {
        positionxi = peoplelist.people[i].positionx;
        iFloor = peoplelist.people[i].nowFloor;
        if (peoplelist.people[i].isInUse && (nowFloor == iFloor) && (peoplelist.people[i].In_or_Out == 0)) {
            if (positionxi == positionxNext) {
                return 1;
            }
        }
        
    }
    return 0;
}

// 扫描所有的人空间，寻找到最近的一个没有使用的人空间如果没有返回0
int scanPeopleStruct() {
    for (int i = 0; i < 10; i++)
    {
        if (peoplelist.people[i].isInUse == 0) {
            return i+1;
        }
    }
    return 0;
}

//电梯内人数计算
int countPeopleInElevator() {
    int number = 0;
    for (int i = 0; i < peopleNumMax; i++) {
        if (peoplelist.people[i].isInUse && peoplelist.people[i].isInElevator) {
            number++;
        }
    }
    return number;
}

//电梯内前往每层楼人数的总和
int countPeopleToFloorElevator(targetFloor) {
    int number = 0;
    for (int i = 0; i < peopleNumMax; i++) {
        if (peoplelist.people[i].isInUse && peoplelist.people[i].isInElevator) {
            if (peoplelist.people[i].targetFloor == targetFloor) {
                number++;
            }
        }
    }
    return number;
}

//电梯状态栏的刷新
void refreshZTL() {
    GotoXY(diantiWidth * 3 + 24, 0);
    printf("电梯内状态：");
    if (dianTizhuangTai == 0) {
        printf("停止运行");
    }
    else if (dianTizhuangTai == 1) {
        printf("电梯上行");
    }
    else if (dianTizhuangTai == -1) {
        printf("电梯下行");
    }
    GotoXY(diantiWidth * 3 + 24, 1);
    printf("电梯内按钮状态为：");
    GotoXY(diantiWidth * 3 + 28, 2);
    for (int i = 1; i <= lowFloor; i++) {
        if (target[i] == 0) {
            printf("%d ", i);
        }
        else {
            printf(BLUE"%d"NONE, i);
            printf(" ");
        }
        
    }
    GotoXY(diantiWidth * 3 + 24, 4);
    printf("电梯内人数为：%d", countPeopleInElevator());

    GotoXY(diantiWidth * 3 + 24, 6);
    printf("电梯内前往每层楼的人数:");
    for (int i = 1; i <= lowFloor; i++) {
        GotoXY(diantiWidth * 3 + 26, 6 + i);
        printf("前往%d楼的人数为：%d", i, countPeopleToFloorElevator(i));
    }
    

}

//开始游戏
int Start()
{
    chushihua();
    printPlatform();
    printElevator();
    dianTizhuangTai = 0;
    int timeCount = 1; //时间单元，1~100用于分配速度
    while (1) {
        timeCount++;

        if (timeCount % 4 == 0)
        {
            nowLocation = nowLocation - dianTizhuangTai;
            if (nowLocation % cengGao == 0) {
                nowceng = lowFloor - (nowLocation / cengGao);
            }
            if (dianTizhuangTai != 0) {
                printElevator();
            }
        }

        if (dianTizhuangTai == 1) {
            if (haveshangXingButton(nowceng, lowFloor) || havexiaXingButton(nowceng + 1, lowFloor) || (haveTargetButton(nowceng, lowFloor) && nowceng != lowFloor)) {
                //状态保持不变
            }
            else if (haveshangXingButton(1, nowceng) || havexiaXingButton(1, nowceng) || haveTargetButton(1, nowceng)) {
                //状态发生改变
                dianTizhuangTai = -1;
            }
            else {
                dianTizhuangTai = 0;
            }
        }
        else if (dianTizhuangTai == -1) {
            if (haveshangXingButton(1, nowceng - 1) || havexiaXingButton(1, nowceng) || (haveTargetButton(1, nowceng) && nowceng != 1)) {
                //状态保持不变
            }
            else if (haveshangXingButton(nowceng, lowFloor) || havexiaXingButton(nowceng + 1, lowFloor) || haveTargetButton(nowceng, lowFloor)) {
                //状态发生改变
                dianTizhuangTai = 1;
            }
            else {
                dianTizhuangTai = 0;
            }
        }
        if (dianTizhuangTai == 0) {
            if (haveshangXingButton(nowceng, lowFloor) || havexiaXingButton(nowceng + 1, lowFloor) || haveTargetButton(nowceng, lowFloor)) {
                dianTizhuangTai = 1;
            }
            else if (haveshangXingButton(1, nowceng) || havexiaXingButton(1, nowceng) || haveTargetButton(1, nowceng)) {
                dianTizhuangTai = -1;
            }
        }

        if (nowLocation % cengGao == 0) {
            if (shangXingButton[nowceng] == 1 || xiaXingButton[nowceng] == 1 || target[nowceng] == 1) {
                if (target[nowceng] == 1) {
                    target[nowceng] = 0;
                    chuLiButton(dianTizhuangTai, nowceng, 0);
                    kaimen(nowceng);
                    InOutElevator();//人进出电梯
                    refreshZTL();
                    guanmen(nowceng);
                }else if (dianTizhuangTai == 1 && shangXingButton[nowceng] == 1) {
                    chuLiButton(dianTizhuangTai, nowceng, 0);
                    kaimen(nowceng);
                    InOutElevator();//人进出电梯
                    refreshZTL();
                    guanmen(nowceng);
                }else if (dianTizhuangTai == -1 && xiaXingButton[nowceng] == 1) {
                    chuLiButton(dianTizhuangTai, nowceng, 0);
                    kaimen(nowceng);
                    InOutElevator();//人进出电梯
                    refreshZTL();
                    guanmen(nowceng);
                }
            }
        }
        
        createPeople(); //定义人的创建过程
        movePeople();  //对人物移动的处理

        
       if (timeCount == 100)
       {
           timeCount = 0;
       }
       Sleep(50);

    }
}

//出入电梯函数
int InOutElevator() {
    for (int i = 0; i < 10; i++) {
        if (peoplelist.people[i].In_or_Out == 0 && peoplelist.people[i].nowFloor == nowceng && peoplelist.people[i].isInElevator == 0) {
            if (dianTizhuangTai == absto1(peoplelist.people[i].targetFloor - peoplelist.people[i].nowFloor)) {
                int positiony = (lowFloor - peoplelist.people[i].nowFloor + 1) * cengGao - 1;
                GotoXY(peoplelist.people[i].positionx, positiony);
                printf(" ");
                GotoXY(peoplelist.people[i].positionx, positiony - 1);
                printf(" ");
                peoplelist.people[i].positionx = 6;
                target[peoplelist.people[i].targetFloor] = 1;
                peoplelist.people[i].isInElevator = 1;
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        if (peoplelist.people[i].isInElevator == 1 && peoplelist.people[i].targetFloor == nowceng) {
            int positiony = (lowFloor - peoplelist.people[i].nowFloor + 1) * cengGao - 1;
            peoplelist.people[i].positionx = diantiWidth * 3 + 6;
            peoplelist.people[i].In_or_Out = -1;
            peoplelist.people[i].nowFloor = nowceng;
            peoplelist.people[i].isInElevator = 0;
        }
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
    for (int i = 0; i <= lowFloor * cengGao; i++) {
        for (int j = 0; j <= diantiWidth*2; j++) {
            GotoXY(j, i);
            printf("  ");
        }
    }
}

//打印平台函数
void printPlatform() {
    //平台打印
    for (int i = 0; i <= cengGao * lowFloor; i = i + cengGao) {
        GotoXY(diantiWidth * 2 + 4, i); //平台上框
        for (int i = 0; i <= 16; i++) {
            printf(PURPLE"██"NONE);
        }
    }

    //造平台门
    for (int i = 0; i <= cengGao * lowFloor; i++) {
        GotoXY(diantiWidth * 2 + 4, i); 
        printf(YELLOW"██"NONE);
    }
}

void kaimen(int ceng) {
    int dingweiY = (lowFloor - ceng) * cengGao;//定义楼层上框
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
    int dingweiY = (lowFloor - ceng) * cengGao;//定义楼层上框
    
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