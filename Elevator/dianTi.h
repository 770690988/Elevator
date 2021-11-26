#pragma once
#include<stdio.h>
#include<Windows.h>
#include<conio.h>//控制台的一些文件
#include<time.h>

//颜色的定义
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

//基本架构函数
void GotoXY(int, int);  //光标定位函数
void Hide();     //隐藏光标函数
void printElevator(int,int);//打印电梯主函数
void clearFormerElevator();//将之前的电梯去干净
void printPlatform(); //打印平台函数
void kaimen(int);  //开门函数
void guanmen(int); //关门函数

//附加函数
int absto1(int); //正负转化+-1
int cengLocation(int); //层的定位函数

//模块的各个函数
int Menu();      //主菜单函数

//下面是开始游戏函数部分
int Start();       //开始游戏

//下面是游戏中一些全局变量
int floor; //定义楼层的个数（>=2）
int cengGao; //定义楼层高度
int diantiWidth; //定义电梯宽度
int platformWidth; //定义平台宽度
int nowceng; //定义当前所在的楼层
int zhuangTai; //定义当前天梯是上行1还是下行-1