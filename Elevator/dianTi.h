#pragma once
#include<stdio.h>
#include<Windows.h>
#include<conio.h>//����̨��һЩ�ļ�
#include<time.h>

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
void Hide();     //���ع�꺯��
void printElevator(int,int);//��ӡ����������
void clearFormerElevator();//��֮ǰ�ĵ���ȥ�ɾ�
void printPlatform(); //��ӡƽ̨����
void kaimen(int);  //���ź���
void guanmen(int); //���ź���

//���Ӻ���
int absto1(int); //����ת��+-1
int cengLocation(int); //��Ķ�λ����

//ģ��ĸ�������
int Menu();      //���˵�����

//�����ǿ�ʼ��Ϸ��������
int Start();       //��ʼ��Ϸ

//��������Ϸ��һЩȫ�ֱ���
int floor; //����¥��ĸ�����>=2��
int cengGao; //����¥��߶�
int diantiWidth; //������ݿ��
int platformWidth; //����ƽ̨���
int nowceng; //���嵱ǰ���ڵ�¥��
int zhuangTai; //���嵱ǰ����������1��������-1