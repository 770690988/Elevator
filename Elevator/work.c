#include "dianTi.h"

floor = 5; //�ݶ�¥��Ϊ5��
cengGao = 10; //�ݶ����10
diantiWidth = 15;  //�ݶ����ݿ��Ϊ15
platformWidth = 25; //�ݶ�ƽ̨���Ϊ25
nowceng = 1; //�տ�ʼĬ��¥��Ϊ1
int shangXingButton[6];//���е��ݰ�ť״̬1��ʾ����
int xiaXingButton[6];//���е��ݰ�ť״̬1��ʾ����

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
    printf("1. ��ʼ��Ϸ");
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
void chushihua(){
    for (int i = 0; i <= floor; i++) {
        shangXingButton[i] = 0;
        xiaXingButton[i] = 0;
        target[i] = 0;
    }
    nowLocation = cengLocation(nowceng);
    zhuangTai = 1; //����տ�ʼ��״̬������
}

//��ʼ��Ϸ
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
            //��д�˽��������
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
    for (int i = 0; i <= (floor) * cengGao;i++) {
        for (int j = 0; j <= diantiWidth*2; j++) {
            GotoXY(j, i);
            printf("  ");
        }
    }
}

//��ӡƽ̨����
void printPlatform() {
    //ƽ̨��ӡ
    for (int i = 0; i <= cengGao * (floor); i = i + cengGao) {
        GotoXY(diantiWidth * 2 + 4, i); //ƽ̨�Ͽ�
        for (int i = 0; i <= diantiWidth; i++) {
            printf(PURPLE"����"NONE);
        }
    }

    //��ƽ̨��
    for (int i = 0; i <= cengGao * (floor); i++) {
        GotoXY(diantiWidth * 2 + 4, i); 
        printf(YELLOW"����"NONE);
    }
}

void kaimen(int ceng) {
    int dingweiY = (floor - ceng+1) * cengGao;
    //ƽ̨�ſ���
    Sleep(200);
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
    int dingweiY = (floor - ceng+1) * cengGao;
    
    for (int i = 1; i < 10; i++) {
        //ƽ̨�Źر�
        GotoXY(diantiWidth * 2 + 4, i + dingweiY);
        printf(YELLOW"����"NONE);
        //�����Źر�
        GotoXY(diantiWidth * 2, i + dingweiY);
        printf(DGREEN"����"NONE);
        Sleep(200);
        GotoXY(diantiWidth * 2 + 2, 10 + dingweiY);
        printf("  ");
    }
}