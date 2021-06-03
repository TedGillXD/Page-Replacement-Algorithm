#include <iostream>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <ctime>
#include "Processor.h"
#include "Result.h"

using namespace std;

int main() {

	system("cls");

	while (true) {
		//input
		int Length;
		int MerorySize;

		do
		{
			cout << "请输入内存访问序列的长度(15 - 25)：";
			cin >> Length;
			if (Length < 15 || Length > 25) {
				cout << "错误输入，请重新输入" << endl;
				system("pause");
				system("cls");
			}
		} while (Length < 15 || Length > 25);

		do
		{
			cout << "请输入内存长度(3 - 5)：";
			cin >> MerorySize;
			if (MerorySize < 3 || MerorySize > 5) {
				cout << "错误输入，请重新输入" << endl;
				system("pause");
				system("cls");
			}
		} while (MerorySize < 3 || MerorySize > 5);

		int Choose;
		do {
			cout << "请选择页面访问序列生成方式：1、用户输入；2、随机生成，请选择：";
			cin >> Choose;
			if (Choose != 1 && Choose != 2) {
				cout << "错误输入，请重新选择:";
			}
		} while(Choose != 1 && Choose != 2);

		vector<int> AccessSequence(Length);

		if (Choose == 1) {
			string str = "";
			while (true) {
				cout << "请输入内存访问序列(每个数字为0 - 5)：";
				string temp;
				cin >> temp;
				str += temp;
				if (str.length() >= Length) {
					break;
				}
				if (to_string(stoi(temp)).length() != temp.length()) {
					cout << "含有非法字符，请重新输入" << endl;
					system("pause");
					system("cls");
					continue;
				}
				cout << "输入的数据位数不足，请在额外输入" << Length - str.length() << "个数据";
				system("pause");
				system("cls");
			}
			if (str.length() > Length) {
				cout << "你输入的序列超出长度，将截取前十五个作为输入数据，数据如下" << endl;
			}
			for (int i = 0; i < Length; i++) {
				if (isdigit(str[i])) {
					AccessSequence[i] = std::stoi(string(1, str[i]));
				}
			}
		}
		else {
			default_random_engine dre(time(0));
			uniform_int_distribution<int> uid(0, 5);
			for (int i = 0; i < Length; i++) {
				AccessSequence[i] = uid(dre);
			}
			cout << "你选择了随机生成，结果如下\n";
		}

		for (auto item : AccessSequence) {
			cout << item << " ";
		}
		cout << "\n";

		Processor processor(AccessSequence, MerorySize);

		int operation;

		//process
		while (true) {
			system("pause");
			system("cls");
			cout << "1.最佳置换算法" << endl
				<< "2.先进先出算法" << endl
				<< "3.最久未使用算法" << endl
				<< "4.时钟算法" << endl
				<< "5.更换数据" << endl
				<< "6.退出程序" << endl
				<< "请选择：";
			cin >> operation;
			Result result;
			if (operation == 1) {
				result = processor.OPT();
			}
			else if (operation == 2) {
				result = processor.FIFO();
			}
			else if (operation == 3) {
				result = processor.LRU();
			}
			else if (operation == 4) {
				result = processor.CLOCK();
			}
			else {
				break;
			}
			cout << result;
		}

		if (operation == 6) {
			break;
		}
	}
	
	return 0;
}