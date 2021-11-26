#include "dianTi.h"

int main()
{
	system("title µçÌÝ");
	int flag = 1;
	while (flag) {
		system("cls");
		switch (Menu())
		{
		case 1:
			Start();
			break;
		case 0:
			flag = 0;
			break;
		default:
			break;
		}
	}
}