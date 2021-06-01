#include <iostream>
#include <cstdlib>
#include "Processor.h"
#include "Result.h"

using namespace std;

int main() {
	//input
	int Length;
	int MerorySize;
	
	do 
	{
		cout << "请输入内存访问序列的长度(正整数)：";
		cin >> Length;
		if (Length < 0) {
			cout << "错误输入，请重新输入" << endl;
			system("pause");
			system("cls");
		}
	} while (Length < 0);
	vector<int> AccessSequence(Length);
	cout << "请输入内存访问序列(正整数)：";
	for (int i = 0; i < Length; i++) {
		cin >> AccessSequence[i];
	}
	do
	{
		cout << "请输入内存长度(正整数)：";
		cin >> MerorySize;
		if (MerorySize < 0) {
			cout << "错误输入，请重新输入" << endl;
			system("pause");
			system("cls");
		}
	} while (MerorySize < 0);
	
	Processor processor(AccessSequence, MerorySize);
	
	//process
	while (true) {
		system("pause");
		system("cls");
		cout << "1.最佳置换算法" << endl
			<< "2.先进先出算法" << endl
			<< "3.最久未使用算法" << endl
			<< "4.时钟算法" << endl
			<< "其他选项为退出" << endl
			<< "请选择：";
		int operation;
		cin >> operation;
		Result result;
		if (operation == 1) {
			result = processor.OPT();
		} else if (operation == 2) {
			result = processor.FIFO();
		} else if (operation == 3) {
			result = processor.LRU();
		} else if (operation == 4){
			result = processor.CLOCK();
		} else {
			break;
		}
		cout << result;
	}
	
	return 0;
}