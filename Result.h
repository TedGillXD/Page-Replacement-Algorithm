#pragma once
#include <iostream>
using namespace std;

class Result {
private:
	//ȱҳ����
	int FaultCount;

	//ȱҳ��
	double FaultRate;

public:
	Result(int FaultCount = 0, double FaultRate = 0) {
		this->FaultCount = FaultCount;
		this->FaultRate = FaultRate;
	}

	int GetFaultCount() {
		return FaultCount;
	}

	double GetFaultRate() {
		return FaultRate;
	}

	friend ostream& operator<<(ostream& out, Result NeedToPrint) {
		out << "ȱҳ������" << NeedToPrint.GetFaultCount() << ",ȱҳ�ʣ�" << NeedToPrint.GetFaultRate() << endl;
		return out;
	}

};