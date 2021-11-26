#include "dianTi.h"

floor = 5; //�ݶ�¥��Ϊ5��
cengGao = 10; //�ݶ����10
diantiWidth = 15;  //�ݶ����ݿ��Ϊ15
platformWidth = 25; //�ݶ�ƽ̨���Ϊ25
nowceng = 1; //�տ�ʼĬ��¥��Ϊ1
zhuangTai = 1; //����տ�ʼ��״̬������

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

//��ʼ��Ϸ
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

//��ӡ����������
void printElevator(int formerceng, int latterceng)
{
    Hide();
    int dingweiY = (floor - formerceng + 1) * cengGao;
    for (int temp = dingweiY; (temp-cengLocation(formerceng))*(temp - cengLocation(latterceng)) <= 0; temp = temp + absto1(formerceng-latterceng)) {
        //���ݵĿ��
        clearFormerElevator();
        GotoXY(0, temp); //�����Ͽ�
        for (int i = 0; i <= diantiWidth; i++) {
            printf(DGREEN"����"NONE);
        }
        GotoXY(0, temp + 10);//�����¿�
        for (int i = 0; i <= diantiWidth; i++) {
            printf(DGREEN"����"NONE);
        }
        for (int i = 0; i <= 10; i++) {//������
            GotoXY(diantiWidth * 2, i + temp);
            printf(DGREEN"����"NONE);
        }
        //�ڲ���Ա
        Sleep(200);
    }
    nowceng = latterceng;
    


}

//����֮ǰ�ĵ���
void clearFormerElevator() {
    for (int i = 0; i <= (floor+1) * cengGao;i++) {
        for (int j = 0; j <= diantiWidth*2; j++) {
            GotoXY(j, i);
            printf("  ");
        }
    }
}

//��ӡƽ̨����
void printPlatform() {
    //ƽ̨��ӡ
    for (int i = 0; i <= cengGao * (floor+1); i = i + cengGao) {
        GotoXY(diantiWidth * 2 + 4, i); //ƽ̨�Ͽ�
        for (int i = 0; i <= diantiWidth; i++) {
            printf(PURPLE"����"NONE);
        }
    }

    //��ƽ̨��
    for (int i = 0; i <= cengGao * (floor + 1); i++) {
        GotoXY(diantiWidth * 2 + 4, i); 
        printf(YELLOW"����"NONE);
    }
}


void kaimen(int ceng) {
    int dingweiY = (floor - ceng + 1) * cengGao;
    //ƽ̨�ſ���
    for (int i = 9; i > 1; i--) {
        //ƽ̨�ſ���
        GotoXY(diantiWidth * 2 + 4, i + dingweiY);
        printf("  ");
        //�����ſ���
        GotoXY(diantiWidth * 2, i + dingweiY);
        printf("  ");
        Sleep(200);
    }
    GotoXY(diantiWidth * 2 + 2, 10 + dingweiY);
    printf(PURPLE"����"NONE);


}

void guanmen(int ceng) {
    int dingweiY = (floor - ceng + 1) * cengGao;
    
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