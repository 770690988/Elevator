#include "dianTi.h"

//����ת��+-1
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

//�ж����а�ť����������������1��ֵ
int haveshangXingButton(int min, int max) {
	for (int i = min; i <= max; i++) {
		if (shangXingButton[i]) {
			return 1;
		}
	}
	return 0;
}

//�ж����а�ť����������������1��ֵ
int havexiaXingButton(int min, int max) {
	for (int i = min; i <= max; i++) {
		if (xiaXingButton[i]) {
			return 1;
		}
	}
	return 0;
}

//�жϵ�����������������Ҫ�����¥��
int haveTargetButton(int min, int max) {
	for (int i = min; i <= max; i++) {
		if (target[i]) {
			return 1;
		}
	}
	return 0;
}

//��ÿ��¥�㰴�µ�button���п��ӻ�����
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
			printf("��");
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
			printf("��");
		}
		else if (data == 0) {
			printf("  ");
		}
	}
	
	

}