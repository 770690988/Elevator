#include "dianTi.h"

//正负转化+-1
int absto1(int i) {
	if (i > 0) {
		return 1;
	}
	else if(i < 0){
		return -1;
	}
	return 0;
}

int cengLocation(int i) {
	return (lowFloor - i) * cengGao;
}

//判断上行按钮在两个整数中有无1的值
int haveshangXingButton(int min, int max) {
	for (int i = min; i <= max; i++) {
		if (shangXingButton[i]) {
			return 1;
		}
	}
	return 0;
}

//判断下行按钮在两个整数中有无1的值
int havexiaXingButton(int min, int max) {
	for (int i = min; i <= max; i++) {
		if (xiaXingButton[i]) {
			return 1;
		}
	}
	return 0;
}

//判断电梯两个整数间有无要到达的楼层
int haveTargetButton(int min, int max) {
	for (int i = min; i <= max; i++) {
		if (target[i]) {
			return 1;
		}
	}
	return 0;
}

//将每个楼层按下的button进行可视化处理
void chuLiButton(int direction, int ceng, int data) {
	if (direction == 1) {
		if (shangXingButton[ceng] == data) {
			return;
		}
		shangXingButton[ceng] = data;
		Hide();
		int y = cengLocation(ceng) + 2;
		int x = diantiWidth * 2 + 7;
		GotoXY(x, y);

		if (data == 1) {
			printf("▲");
		}
		else if (data == 0) {
			printf("  ");
		}
	}
	else if (direction == -1) {
		if (xiaXingButton[ceng] == data) {
			return;
		}
		xiaXingButton[ceng] = data;
		Hide();

		int y = cengLocation(ceng) + 5;
		int x = diantiWidth * 2 + 7;
		GotoXY(x, y);

		if (data == 1) {
			printf("▼");
		}
		else if (data == 0) {
			printf("  ");
		}
	}
	
	

}