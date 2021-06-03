#pragma once
#include <iostream>
#include <string>
using namespace std;

class Result {
private:
	//缺页次数
	int FaultCount;

	//缺页率
	double FaultRate;

	string AnsTable;

public:
	Result(int FaultCount = 0, double FaultRate = 0) {
		this->FaultCount = FaultCount;
		this->FaultRate = FaultRate;
		AnsTable = "访问页面           物理块            缺页中断\n";
	}

	int GetFaultCount() {
		return FaultCount;
	}

	double GetFaultRate() {
		return FaultRate;
	}

	string GetTable() {
		return AnsTable;
	}

	void AddTableInfo(int PageIndex, vector<Page> Blocks, bool isPageFault) {
		AnsTable += "   ";
		AnsTable = AnsTable + to_string(PageIndex);
		AnsTable += "              ";
		for (auto item : Blocks) {
			int Index = item.GetPageNumber();
			if (Index == -1) {
				AnsTable += "&";
			} else {
				AnsTable += to_string(Index);
			}
			
			if (item.GetAccess() == 1) {
				AnsTable += "*";
			}
			AnsTable += " ";
		}
		AnsTable += "               ";
		if (isPageFault) {
			AnsTable += "T";
		} else {
			AnsTable += "F";
		}
		AnsTable += "\n";
	}

	void SetFaultCount(int FaultCount) {
		this->FaultCount = FaultCount;
	}

	void SetFaultRate(double FaultRate) {
		this->FaultRate = FaultRate;
	}

	friend ostream& operator<<(ostream& out, Result NeedToPrint) {
		out << NeedToPrint.GetTable();
		out << "缺页次数：" << NeedToPrint.GetFaultCount() << ",缺页率：" << NeedToPrint.GetFaultRate() << endl;
		return out;
	}

};