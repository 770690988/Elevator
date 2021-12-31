#include "dianTi.h"

lowFloor = 4; //�ݶ�¥��Ϊ4��
cengGao = 10; //�ݶ����10
diantiWidth = 15;  //�ݶ����ݿ��Ϊ15
platformWidth = 25; //�ݶ�ƽ̨���Ϊ25
nowceng = 1; //�տ�ʼĬ��¥��Ϊ1
peopleNumMax = 10; //������������Ϊ10����

typedef struct PeopleStruct {
    int isInUse;  //������˵Ŀռ��Ƿ���ʹ���У������ʹ�ã���Ϊ1 ����Ϊ0
    int weight;
    int positionx; //�����ڵ�λ��
    int nowFloor; //��ǰ¥��
    int targetFloor; //Ŀ��¥��
    int In_or_Out;//�����ݽ���Ϊ1 ������Ϊ-1 ����Ϊ0
    int isInElevator;  //�ж��Ƿ��ڵ�����
}People;

struct PeopleList{
    People people[100];
}peoplelist;

//��Ϸ�������ò˵�
int settingMenu() {
    system("cls");
    GotoXY(40, 5);
    printf("1.�޸�¥�����");
    GotoXY(40, 7);
    printf("2.�޸��������");
    GotoXY(40, 10);
    printf("�����밴ǰ��ı�Ž����޸ģ�������������˳�");
   
    char ch;
    int result = 0;
    ch = _getch();
    switch (ch)
    {
    case '1': result = 1; break;
    case '2': result = 2; break;
    default:  result = 5; break;
    }
    system("cls");  //��յ�ǰҳ��
    return result;
}

//��Ϸ��������
int setting(option) {
    if (option == 1) {
        lowFloorSetting();
    }
    else if (option == 2) {
        peopleNumMaxSetting();
    }
    else if (option == 5) {
        return 0;
    }
}

//¥�������
int lowFloorSetting() {
    system("cls");
    GotoXY(40, 4);
    printf("1.¥����Ϊ3");
    GotoXY(40, 6);
    printf("2.¥����Ϊ4");
    GotoXY(40, 8);
    printf("3.¥����Ϊ5");
    GotoXY(40, 10);
    printf("�����밴ǰ��ı�Ž����޸ģ�������������˳�");
    
    char ch;
    int result = 0;
    ch = _getch();
    switch (ch)
    {
    case '1': lowFloor = 3; break;
    case '2': lowFloor = 4; break;
    case '3': lowFloor = 5; break;
    default:  result = 5; break;
    }
    system("cls");  //��յ�ǰҳ��
    return result;
}

//������������
int peopleNumMaxSetting() {
    system("cls");
    GotoXY(40, 4);
    printf("1.��������Ϊ5");
    GotoXY(40, 6);
    printf("2.��������Ϊ10");
    GotoXY(40, 8);
    printf("3.��������Ϊ15");
    GotoXY(40, 10);
    printf("�����밴ǰ��ı�Ž����޸ģ�������������˳�");

    char ch;
    int result = 0;
    ch = _getch();
    switch (ch)
    {
    case '1': peopleNumMax = 5; break;
    case '2': peopleNumMax = 10; break;
    case '3': peopleNumMax = 15; break;
    default:  result = 5; break;
    }
    system("cls");  //��յ�ǰҳ��
    return result;
}


//��궨λ����
void GotoXY(int x, int y)
{
    HANDLE hout;
    COORD cor;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(hout, cor);
}

//���ع��
void Hide()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cor_info = { 1, 0 };
    SetConsoleCursorInfo(hout, &cor_info);//���ع��

}

//�˵���Ŀ
int Menu() {
    Hide();
    GotoXY(36, 12);   //��λ����λ��
    printf(ORED"��ӭ��������С��Ϸ");
    GotoXY(43, 14);
    printf("1. ��ʼ��Ϸ(��Ŵ�ȫ��)");
    GotoXY(43, 16);
    printf("2. ����");
    GotoXY(43, 18);
    printf("�˳���Ϸ������     0"NONE);
    Hide();    //���ع��
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
    system("cls");  //��յ�ǰҳ��
    return result;
}

// ��ʼ��һЩ�������������ݵ�״̬�Լ��������е�״��
void chushihua() {
    for (int i = 0; i <= lowFloor; i++) {
        shangXingButton[i] = 0;
        xiaXingButton[i] = 0;
        target[i] = 0;
    }
    
    for (int i = 0; i < peopleNumMax; i++) {
        peoplelist.people[i].isInUse = 0;
    }
    nowLocation = cengLocation(nowceng);
    //zhuangTai = 1; //����տ�ʼ��״̬������
    for (int i = 0; i < 10; i++) {
        finish[i] = 0;
    }
    refreshZTL();
}

//���˴����Ĵ���
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

            //����Ϳ�ʼ�����ݽ��и�ֵ
            if (finish[0] <= 1) {//����һ���
                finish[0]++;
            }
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
    for (int i = 0; i < peopleNumMax; i++)
    {
        //��ÿ����Ҫ�ƶ������ƶ�һ��
        if (peoplelist.people[i].In_or_Out == 0) {
            continue;
        }
        if (isPaiDui(i)) {
            peoplelist.people[i].In_or_Out = 0;
            //�˵�������ǰ�İ���ť����
            if (finish[1] <= 1) {//��������
                finish[1]++;
            }
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
        //�˵�����ݺ��뿪�Ĵ������
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

//�ж�ǰ���Ƿ��������Ŷ�:0 û�����Ŷ�:1
int isPaiDui(int peopleNum) {
    int nowFloor = peoplelist.people[peopleNum].nowFloor;
    int positionxNext = peoplelist.people[peopleNum].positionx - peoplelist.people[peopleNum].In_or_Out;
    int positionxi;
    int iFloor;
    //������ǽ������û�������
    if (peoplelist.people[peopleNum].positionx == 2 * diantiWidth + 6) {
        return 1;
    }
    for (int i = 0; i < peopleNumMax; i++)
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

// ɨ�����е��˿ռ䣬Ѱ�ҵ������һ��û��ʹ�õ��˿ռ����û�з���0
int scanPeopleStruct() {
    for (int i = 0; i < peopleNumMax; i++)
    {
        if (peoplelist.people[i].isInUse == 0) {
            return i+1;
        }
    }
    return 0;
}

//��������������
int countPeopleInElevator() {
    int number = 0;
    for (int i = 0; i < peopleNumMax; i++) {
        if (peoplelist.people[i].isInUse && peoplelist.people[i].isInElevator) {
            number++;
        }
    }
    return number;
}

//������ǰ��ÿ��¥�������ܺ�
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

//����״̬����ˢ��
void refreshZTL() {
    GotoXY(diantiWidth * 3 + 24, 0);
    printf("������״̬��");
    if (dianTizhuangTai == 0) {
        printf("ֹͣ����");
    }
    else if (dianTizhuangTai == 1) {
        printf("��������");
    }
    else if (dianTizhuangTai == -1) {
        printf("��������");
    }
    GotoXY(diantiWidth * 3 + 24, 1);
    printf("�����ڰ�ť״̬Ϊ��");
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
    printf("����������Ϊ��%d", countPeopleInElevator());

    GotoXY(diantiWidth * 3 + 24, 6);
    printf("������ǰ��ÿ��¥������:");
    for (int i = 1; i <= lowFloor; i++) {
        GotoXY(diantiWidth * 3 + 26, 6 + i);
        printf("ǰ��%d¥������Ϊ��%d", i, countPeopleToFloorElevator(i));
    }

    GotoXY(diantiWidth * 3 + 26, 6 + lowFloor + 2);
    printf("Ŀ��һ���Զ������ˡ�");
    GotoXY(diantiWidth * 3 + 26, 6 + lowFloor + 3);
    printf("Ŀ��������ߵ�����ǰ�Զ����������½���ť");
    GotoXY(diantiWidth * 3 + 26, 6 + lowFloor + 4);
    printf("Ŀ�������˽�����ݺ��µ��ݵİ�ť");
    GotoXY(diantiWidth * 3 + 26, 6 + lowFloor + 5);
    printf("Ŀ���ģ��������е������а�ť��¥�㿪��");
    GotoXY(diantiWidth * 3 + 26, 6 + lowFloor + 6);
    printf("Ŀ���壺�������е��˿���Ҫ�����¥�㿪��");
    GotoXY(diantiWidth * 3 + 26, 6 + lowFloor + 7);
    printf("Ŀ��������������������5����������");
    for (int i = 0; i < 6; i++) {
        if (finish[i] == 1) {
            GotoXY(diantiWidth * 3 + 24, 8 + lowFloor + i);
            printf("��");
        }
    }
    

}

//��ʼ��Ϸ
int Start()
{
    chushihua();
    printPlatform();
    printElevator();
    dianTizhuangTai = 0;
    int timeCount = 1; //ʱ�䵥Ԫ��1~100���ڷ����ٶ�
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
                //״̬���ֲ���
            }
            else if (haveshangXingButton(1, nowceng) || havexiaXingButton(1, nowceng) || haveTargetButton(1, nowceng)) {
                //״̬�����ı�
                dianTizhuangTai = -1;
            }
            else {
                dianTizhuangTai = 0;
            }
        }
        else if (dianTizhuangTai == -1) {
            if (haveshangXingButton(1, nowceng - 1) || havexiaXingButton(1, nowceng) || (haveTargetButton(1, nowceng) && nowceng != 1)) {
                //״̬���ֲ���
            }
            else if (haveshangXingButton(nowceng, lowFloor) || havexiaXingButton(nowceng + 1, lowFloor) || haveTargetButton(nowceng, lowFloor)) {
                //״̬�����ı�
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
                    
                    if (finish[4] <= 1) {//���������
                        finish[4]++;
                    }
                    kaimen(nowceng);
                    if (InOutElevator() == 1) {//�˽�������
                        chuLiButton(dianTizhuangTai, nowceng, 0);
                    }
                    else {
                        refreshZTL();
                        guanmen(nowceng);
                        nowLocation = nowLocation - dianTizhuangTai;
                    }
                    refreshZTL();
                    guanmen(nowceng);
                }else if (dianTizhuangTai == 1 && shangXingButton[nowceng] == 1) {
                    if (finish[3] <= 1) {//���������
                        finish[3]++;
                    }
                    
                    kaimen(nowceng);
                    if(InOutElevator() == 1) {//�˽�������
                        chuLiButton(dianTizhuangTai, nowceng, 0);
                    }
                    else {
                        refreshZTL();
                        guanmen(nowceng);
                        nowLocation = nowLocation - dianTizhuangTai;
                    }
                    refreshZTL();
                    guanmen(nowceng);
                }else if (dianTizhuangTai == -1 && xiaXingButton[nowceng] == 1) {
                    if (finish[3] <= 1) {//���������
                        finish[3]++;
                    }
                    chuLiButton(dianTizhuangTai, nowceng, 0);
                    kaimen(nowceng);
                    if (InOutElevator() == 1) {//�˽�������
                        chuLiButton(dianTizhuangTai, nowceng, 0);
                    }
                    else {
                        refreshZTL();
                        guanmen(nowceng);
                        nowLocation = nowLocation - dianTizhuangTai;
                    }
                    refreshZTL();
                    guanmen(nowceng);
                }
            }
        }
        
        createPeople(); //�����˵Ĵ�������
        movePeople();  //�������ƶ��Ĵ���

        
       if (timeCount == 100)
       {
           timeCount = 0;
       }
       refreshZTL();
       Sleep(50);

    }
}

//������ݺ���
int InOutElevator() {
    for (int i = 0; i < peopleNumMax; i++) {
        if (peoplelist.people[i].isInElevator == 1 && peoplelist.people[i].targetFloor == nowceng) {
            int positiony = (lowFloor - peoplelist.people[i].nowFloor + 1) * cengGao - 1;
            peoplelist.people[i].positionx = diantiWidth * 3 + 6;
            peoplelist.people[i].In_or_Out = -1;
            peoplelist.people[i].nowFloor = nowceng;
            peoplelist.people[i].isInElevator = 0;
        }
    }

    for (int i = 0; i < peopleNumMax; i++) {
        if (peoplelist.people[i].In_or_Out == 0 && peoplelist.people[i].nowFloor == nowceng && peoplelist.people[i].isInElevator == 0 && countPeopleInElevator() < 5) {
            if (dianTizhuangTai == absto1(peoplelist.people[i].targetFloor - peoplelist.people[i].nowFloor)) {
                int positiony = (lowFloor - peoplelist.people[i].nowFloor + 1) * cengGao - 1;
                GotoXY(peoplelist.people[i].positionx, positiony);
                printf(" ");
                GotoXY(peoplelist.people[i].positionx, positiony - 1);
                printf(" ");
                peoplelist.people[i].positionx = 6;
                target[peoplelist.people[i].targetFloor] = 1;
                if (finish[2] <= 1) {//���������
                    finish[2]++;
                }
                refreshZTL();
                peoplelist.people[i].isInElevator = 1;
            }
        }
        if (countPeopleInElevator() == 5) {
            if (finish[5] <= 1) {//���������
                finish[5]++;
            }
            refreshZTL();
            return 0;//��ʾ������
            
        }
    }
    return 1;//��ʾû����

    
}

//��ӡ����������
void printElevator()
{
    Hide();
    clearFormerElevator();
    GotoXY(0, nowLocation); //�����Ͽ�
    for (int i = 0; i <= diantiWidth; i++) {
        printf(DGREEN"����"NONE);
    }
    GotoXY(0, nowLocation + 10);//�����¿�
    for (int i = 0; i <= diantiWidth; i++) {
        printf(DGREEN"����"NONE);
    }
    for (int i = 0; i <= 10; i++) {//������
        GotoXY(diantiWidth * 2, i + nowLocation);
        printf(DGREEN"����"NONE);
    }
        //�ڲ���Ա;
}

//����֮ǰ�ĵ���
void clearFormerElevator() {
    for (int i = 0; i <= lowFloor * cengGao; i++) {
        for (int j = 0; j <= diantiWidth*2; j++) {
            GotoXY(j, i);
            printf("  ");
        }
    }
}

//��ӡƽ̨����
void printPlatform() {
    //ƽ̨��ӡ
    for (int i = 0; i <= cengGao * lowFloor; i = i + cengGao) {
        GotoXY(diantiWidth * 2 + 4, i); //ƽ̨�Ͽ�
        for (int i = 0; i <= 16; i++) {
            printf(PURPLE"����"NONE);
        }
    }

    //��ƽ̨��
    for (int i = 0; i <= cengGao * lowFloor; i++) {
        GotoXY(diantiWidth * 2 + 4, i); 
        printf(YELLOW"����"NONE);
    }
}

void kaimen(int ceng) {
    int dingweiY = (lowFloor - ceng) * cengGao;//����¥���Ͽ�
    //ƽ̨�ſ���
    Sleep(50);
    for (int i = 9; i > 2; i--) {
        //ƽ̨�ſ���
        GotoXY(diantiWidth * 2 + 4, i + dingweiY);
        printf("  ");
        //�����ſ���
        GotoXY(diantiWidth * 2, i + dingweiY);
        printf("  ");
    }
    GotoXY(diantiWidth * 2 + 2, 10 + dingweiY);
    printf(PURPLE"����"NONE);


}

void guanmen(int ceng) {
    int dingweiY = (lowFloor - ceng) * cengGao;//����¥���Ͽ�
    
    for (int i = 1; i < 10; i++) {
        //ƽ̨�Źر�
        GotoXY(diantiWidth * 2 + 4, i + dingweiY);
        printf(YELLOW"����"NONE);
        //�����Źر�
        GotoXY(diantiWidth * 2, i + dingweiY);
        printf(DGREEN"����"NONE);
        Sleep(100);
        GotoXY(diantiWidth * 2 + 2, 10 + dingweiY);
        printf("  ");
    }
}