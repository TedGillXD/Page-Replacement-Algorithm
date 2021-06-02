#include <iostream>
#include <cstdlib>
#include <random>
#include <algorithm>
#include "Processor.h"
#include "Result.h"

using namespace std;

int main() {

	while (true) {
		//input
		int Length;
		int MerorySize;

		do
		{
			cout << "�������ڴ�������еĳ���(15 - 25)��";
			cin >> Length;
			if (Length < 0) {
				cout << "�������룬����������" << endl;
				system("pause");
				system("cls");
			}
		} while (Length < 0);

		do
		{
			cout << "�������ڴ泤��(3 - 5)��";
			cin >> MerorySize;
			if (MerorySize < 0) {
				cout << "�������룬����������" << endl;
				system("pause");
				system("cls");
			}
		} while (MerorySize < 0);

		int Choose;
		do {
			cout << "��ѡ��ҳ������������ɷ�ʽ��1���û����룻2��������ɣ���ѡ��";
			cin << Choose;
			if (Choose != 0 && Choose != 1) {
				cout << "�������룬������ѡ��:";
			}
		} while(Choose == 0 || Choose == 1);

		vector<int> AccessSequence(Length);

		if (Choose == 0) {
			string str = "";
			while (true) {
				cout << "�������ڴ��������(ÿ������Ϊ0 - 5)��";
				string temp;
				cin >> temp;
				str += temp;
				if (str.length() >= Length) {
					break;
				}
				cout << "���������λ�����㣬���ڶ�������" << Length - str.length() << "������";
				system("pause");
				system("cls");
			}
			for (int i = 0; i < Length; i++) {
				if (isdigit(str[i])) {
					AccessSequence[i] = std::atoi(str[i]);
				}
			}
		}
		else {
			default_random_engine dre;
			uniform_int_distribution<int> uid(0, 5);
			for (int i = 0; i < Length; i++) {
				AccessSequence[i] = uid(dre);
			}
		}

		Processor processor(AccessSequence, MerorySize);

		int operation;

		//process
		while (true) {
			system("pause");
			system("cls");
			cout << "1.����û��㷨" << endl
				<< "2.�Ƚ��ȳ��㷨" << endl
				<< "3.���δʹ���㷨" << endl
				<< "4.ʱ���㷨" << endl
				<< "5.��������" << endl
				<< "6.�˳�����" << endl
				<< "��ѡ��";
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