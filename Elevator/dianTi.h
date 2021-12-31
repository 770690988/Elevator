#pragma once
#include<stdio.h>
#include<Windows.h>
#include<conio.h>//控制台的一些文件
#include<time.h>
#include<math.h>

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
void Hide();//隐藏光标函数
void printElevator();//打印电梯主函数
void clearFormerElevator();//将之前的电梯去干净
void printPlatform(); //打印平台函数
void kaimen(int);  //开门函数
void guanmen(int); //关门函数
void chushihua(); //初始化相应的一些参数

//附加函数
int absto1(int); //正负转化+-1
int cengLocation(int); //层的定位函数
int haveshangXingButton(int, int); //判断上行按钮在两个整数中有无1的值
int havexiaXingButton(int, int); //判断下行按钮在两个整数中有无1的值
int haveTargetButton(int, int); //判断电梯两个整数间有无要到达的楼层
void chuLiButton(int, int, int); //将每个楼层按下的button进行可视化处理(方向1上-1下，楼层，按钮1上0下上下)
void createPeople(); //对人创建的处理
void movePeople(); //对人物移动的处理
int scanPeopleStruct();//扫描所有的人空间，寻找到最近的一个没有使用的人空间如果没有返回0
int isPaiDui(int); //判断前面是否有人在排队
int InOutElevator(); //出入电梯函数
void refreshZTL(); //电梯状态栏的刷新
int countPeopleInElevator(); //电梯内人数的计算
int countPeopleToFloorElevator(int); //电梯内前往每层楼人数的总和

//模块的各个函数
int Menu();      //主菜单函数

//下面是开始游戏函数部分
int Start();       //开始游戏
int settingMenu();     //游戏信息设置菜单
int setting(int);     //游戏信息设置
int lowFloorSetting(); //楼层的设置
int peopleNumMaxSetting(); //人数上限设置

//下面是游戏中一些全局变量
int lowFloor; //定义楼层的个数（>=2）
int cengGao; //定义楼层高度
int diantiWidth; //定义电梯宽度
int platformWidth; //定义平台宽度
int nowceng; //定于电梯当前所在的楼层
int dianTizhuangTai; //定义当前天梯是上行1还是下行-1
int target[6]; //定义目标楼层 1表示该楼层电梯内有乘客需要抵达
int nowLocation; //定义当前图片所在位置即乘上cengGao的值
int shangXingButton[6];//上行电梯按钮状态1表示亮起
int xiaXingButton[6];//下行电梯按钮状态1表示亮起
int peopleNumMax;  //定义人数的最大值
int finish[10];  //定义每个事件是否完成