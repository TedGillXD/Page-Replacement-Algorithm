#pragma once
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "Page.h"
#include "Result.h"
using namespace std;

class Processor {
private:
	vector<int> AccessSequence;
	int MerorySize;

	vector<Page> GetPageArray(vector<int> Merory) {
		vector<Page> ret;
		for (auto item : Merory) {
			ret.push_back(Page(item, 0, 0));
		}
		if ((int)ret.size() < MerorySize) {
			for (int i = ret.size(); i < MerorySize; i++) {
				ret.push_back(Page(-1, 0, 0));
			}
		}
		return ret;
	}

public:

	Processor(vector<int> AccessSequence, int MerorySize) {
		this->AccessSequence = AccessSequence;
		this->MerorySize = MerorySize;
	}

	//先进先出算法
	Result FIFO() {
		Result ret;
		int FaultCount = 0;
		list<int> Merory;
		for (int AccessIndex : AccessSequence) {
			vector<int> MeroryCopy(Merory.begin(), Merory.end());
			if (std::find(Merory.begin(), Merory.end(), AccessIndex) != Merory.end()) {
				ret.AddTableInfo(AccessIndex, GetPageArray(MeroryCopy), false);
				continue;
			}

			if ((int)Merory.size() < MerorySize) {
				Merory.push_back(AccessIndex);
			}
			else {
				Merory.pop_front();
				Merory.push_back(AccessIndex);
				FaultCount++;
			}
			MeroryCopy = vector<int>(Merory.begin(), Merory.end());
			ret.AddTableInfo(AccessIndex, GetPageArray(MeroryCopy), true);
		}
		ret.SetFaultCount(FaultCount);
		ret.SetFaultRate((double)FaultCount / (double)AccessSequence.size());
		return ret;
	}

	//最佳置换算法
	Result OPT() {
		Result ret;
		int FaultCount = 0;
		vector<int> Merory;
		for (int i = 0; i < (int)AccessSequence.size(); i++) {
			if (std::find(Merory.begin(), Merory.end(), AccessSequence[i]) != Merory.end()) {
				ret.AddTableInfo(AccessSequence[i], GetPageArray(Merory), false);
				continue;
			}

			if ((int)Merory.size() < MerorySize) {
				Merory.push_back(AccessSequence[i]);
			}
			else {
				FaultCount++;
				int Target;
				int Index = -1;
				for (auto item : Merory) {
					auto it = std::find(AccessSequence.begin() + i, AccessSequence.end(), item);	//find函数返回的是第一个相等的元素的位置
					if (it == AccessSequence.end()) {
						Target = item;
						break;
					}
					else {
						int NewIndex = distance(AccessSequence.begin(), it);
						if (NewIndex > Index) {
							Index = NewIndex;
							Target = item;
						}
					}
				}
				for (int k = 0; k < (int)Merory.size(); k++) {
					if (Merory[k] == Target) {
						Merory[k] = AccessSequence[i];
					}
				}
			}
			ret.AddTableInfo(AccessSequence[i], GetPageArray(Merory), true);
		}
		ret.SetFaultCount(FaultCount);
		ret.SetFaultRate((double)FaultCount / (double)AccessSequence.size());
		return ret;
	}

	//时钟算法
	Result CLOCK() {
		Result ret;
		int FaultCount = 0;
		vector<Page> Merory;
		int Pointer = 0;
		for (int AccessIndex : AccessSequence) {
			vector<Page> MeroryCopy;
			auto it = std::find(Merory.begin(), Merory.end(), Page(AccessIndex));
			if (it != Merory.end()) {
				it->ChangeAccessToOne();
				Pointer = distance(Merory.begin(), it);
				MeroryCopy = Merory;
				MeroryCopy.resize(MerorySize);
				ret.AddTableInfo(AccessIndex, MeroryCopy, false);
				continue;
			}

			if ((int)Merory.size() < MerorySize) {
				Merory.push_back(Page(AccessIndex));
				Pointer = 0;
			}
			else {
				FaultCount++;
				for (int i = 0; i < (int)Merory.size() * 2; i++, Pointer = (Pointer + 1) % Merory.size()) {
					if (Merory[Pointer].GetAccess() == 0) {
						Merory[Pointer] = Page(AccessIndex);
						break;
					}
					else {
						Merory[Pointer].ChangeAccessToZero();
					}
				}
				Pointer = (Pointer + 1) % Merory.size();
			}
			MeroryCopy = Merory;
			MeroryCopy.resize(MerorySize);
			ret.AddTableInfo(AccessIndex, MeroryCopy, true);
		}
		ret.SetFaultCount(FaultCount);
		ret.SetFaultRate((double)FaultCount / (double)AccessSequence.size());
		return ret;
	}

	//最近未使用
	Result LRU() {
		Result ret;
		int FaultCount = 0;
		map<int, int> HashMap;
		vector<int> Merory;
		for (int i = 0; i < (int)AccessSequence.size(); i++) {
			if (std::find(Merory.begin(), Merory.end(), AccessSequence[i]) != Merory.end()) {
				HashMap[AccessSequence[i]] = i;
				ret.AddTableInfo(AccessSequence[i], GetPageArray(Merory), false);
				continue;
			}

			if ((int)Merory.size() < MerorySize) {
				HashMap[AccessSequence[i]] = i;
				Merory.push_back(AccessSequence[i]);
			}
			else {
				FaultCount++;
				int Target = Merory.front();
				int Index = HashMap[Merory.front()];
				for (auto item : Merory) {
					if (HashMap[item] < Index) {
						Target = item;
						Index = HashMap[item];
					}
				}
				for (int j = 0; j < (int)Merory.size(); j++) {
					if (Merory[j] == Target) {
						Merory[j] = AccessSequence[i];
						HashMap[AccessSequence[i]] = i;
					}
				}
			}
			ret.AddTableInfo(AccessSequence[i], GetPageArray(Merory), true);
		}
		ret.SetFaultCount(FaultCount);
		ret.SetFaultRate((double)FaultCount / (double)AccessSequence.size());
		return ret;
	}
};