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
		cout << "�������ڴ�������еĳ���(������)��";
		cin >> Length;
		if (Length < 0) {
			cout << "�������룬����������" << endl;
			system("pause");
			system("cls");
		}
	} while (Length < 0);
	vector<int> AccessSequence(Length);
	cout << "�������ڴ��������(������)��";
	for (int i = 0; i < Length; i++) {
		cin >> AccessSequence[i];
	}
	do
	{
		cout << "�������ڴ泤��(������)��";
		cin >> MerorySize;
		if (MerorySize < 0) {
			cout << "�������룬����������" << endl;
			system("pause");
			system("cls");
		}
	} while (MerorySize < 0);
	
	Processor processor(AccessSequence, MerorySize);
	
	//process
	while (true) {
		system("pause");
		system("cls");
		cout << "1.����û��㷨" << endl
			<< "2.�Ƚ��ȳ��㷨" << endl
			<< "3.���δʹ���㷨" << endl
			<< "4.ʱ���㷨" << endl
			<< "����ѡ��Ϊ�˳�" << endl
			<< "��ѡ��";
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