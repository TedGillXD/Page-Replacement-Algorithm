#pragma once
#include <iostream>
#include <string>
using namespace std;

class Result {
private:
	//ȱҳ����
	int FaultCount;

	//ȱҳ��
	double FaultRate;

	string AnsTable;

public:
	Result(int FaultCount = 0, double FaultRate = 0) {
		this->FaultCount = FaultCount;
		this->FaultRate = FaultRate;
		AnsTable = "����ҳ��           �����            ȱҳ�ж�\n";
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
		out << "ȱҳ������" << NeedToPrint.GetFaultCount() << ",ȱҳ�ʣ�" << NeedToPrint.GetFaultRate() << endl;
		return out;
	}

};