#pragma once
#include<stdio.h>
#include<Windows.h>
#include<conio.h>//����̨��һЩ�ļ�
#include<time.h>
#include<math.h>

//��ɫ�Ķ���
#define RED "\033[0;32;31m"
#define NONE "\033[m"
#define YELLOW "\033[44;34m"
#define BLUE "\033[43;34m"
#define GREEN "\033[40;32m"
#define PURPLE "\033[43;35m"
#define DGREEN "\033[40;36m"
#define WHITE "\033[46;37m"
#define OBLUE "\033[40;34m"
#define ORED "\033[40;31m"
#define OPURPLE "\033[40;35m"
#define OWHITE "\033[47;37m"

//�����ܹ�����
void GotoXY(int, int);  //��궨λ����
void Hide();//���ع�꺯��
void printElevator();//��ӡ����������
void clearFormerElevator();//��֮ǰ�ĵ���ȥ�ɾ�
void printPlatform(); //��ӡƽ̨����
void kaimen(int);  //���ź���
void guanmen(int); //���ź���
void chushihua(); //��ʼ����Ӧ��һЩ����

//���Ӻ���
int absto1(int); //����ת��+-1
int cengLocation(int); //��Ķ�λ����
int haveshangXingButton(int, int); //�ж����а�ť����������������1��ֵ
int havexiaXingButton(int, int); //�ж����а�ť����������������1��ֵ
int haveTargetButton(int, int); //�жϵ�����������������Ҫ�����¥��
void chuLiButton(int, int, int); //��ÿ��¥�㰴�µ�button���п��ӻ�����(����1��-1�£�¥�㣬��ť1��0������)
void createPeople(); //���˴����Ĵ���
void movePeople(); //�������ƶ��Ĵ���
int scanPeopleStruct();//ɨ�����е��˿ռ䣬Ѱ�ҵ������һ��û��ʹ�õ��˿ռ����û�з���0
int isPaiDui(int); //�ж�ǰ���Ƿ��������Ŷ�
int InOutElevator(); //������ݺ���
void refreshZTL(); //����״̬����ˢ��
int countPeopleInElevator(); //�����������ļ���
int countPeopleToFloorElevator(int); //������ǰ��ÿ��¥�������ܺ�

//ģ��ĸ�������
int Menu();      //���˵�����

//�����ǿ�ʼ��Ϸ��������
int Start();       //��ʼ��Ϸ
int settingMenu();     //��Ϸ��Ϣ���ò˵�
int setting(int);     //��Ϸ��Ϣ����
int lowFloorSetting(); //¥�������
int peopleNumMaxSetting(); //������������

//��������Ϸ��һЩȫ�ֱ���
int lowFloor; //����¥��ĸ�����>=2��
int cengGao; //����¥��߶�
int diantiWidth; //������ݿ��
int platformWidth; //����ƽ̨���
int nowceng; //���ڵ��ݵ�ǰ���ڵ�¥��
int dianTizhuangTai; //���嵱ǰ����������1��������-1
int target[6]; //����Ŀ��¥�� 1��ʾ��¥��������г˿���Ҫ�ִ�
int nowLocation; //���嵱ǰͼƬ����λ�ü�����cengGao��ֵ
int shangXingButton[6];//���е��ݰ�ť״̬1��ʾ����
int xiaXingButton[6];//���е��ݰ�ť״̬1��ʾ����
int peopleNumMax;  //�������������ֵ
int finish[10];  //����ÿ���¼��Ƿ����