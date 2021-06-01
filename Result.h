#pragma once
#include <iostream>
using namespace std;

class Result {
private:
	//缺页次数
	int FaultCount;

	//缺页率
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
		out << "缺页次数：" << NeedToPrint.GetFaultCount() << ",缺页率：" << NeedToPrint.GetFaultRate() << endl;
		return out;
	}

};