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

public:

	Processor(vector<int> AccessSequence, int MerorySize) {
		this->AccessSequence = AccessSequence;
		this->MerorySize = MerorySize;
	}

	//先进先出算法
	Result FIFO() {
		int FaultCount = 0;
		list<int> Merory;
		for (int AccessIndex : AccessSequence) {
			if (std::find(Merory.begin(), Merory.end(), AccessIndex) != Merory.end()) {
				continue;
			}

			if ((int)Merory.size() < MerorySize) {
				Merory.push_back(AccessIndex);
			} else {
				Merory.pop_front();
				Merory.push_back(AccessIndex);
				FaultCount++;
			}
		}
		return Result(FaultCount, (double)FaultCount / (double)AccessSequence.size());
	}

	//最佳置换算法
	Result OPT() {
		int FaultCount = 0;
		vector<int> Merory;
		for (int i = 0; i < (int)AccessSequence.size(); i++) {
			if (std::find(Merory.begin(), Merory.end(), AccessSequence[i]) != Merory.end()) {
				continue;
			}

			if ((int)Merory.size() < MerorySize) {
				Merory.push_back(AccessSequence[i]);
			} else {
				FaultCount++;
				int Target;
				int Index = -1;
				for (auto item : Merory) {
					auto it = std::find(AccessSequence.begin() + i, AccessSequence.end(), item);	//find函数返回的是第一个相等的元素的位置
					if (it == AccessSequence.end()) {
						Target = item;
						break;
					} else {
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
		}
		return Result(FaultCount, (double)FaultCount / (double)AccessSequence.size());
	}

	//时钟算法
	Result CLOCK() {
		int FaultCount = 0;
		vector<Page> Merory;
		int Pointer = 0;
		for (int AccessIndex : AccessSequence) {
			auto it = std::find(Merory.begin(), Merory.end(), Page(AccessIndex));
			if (it != Merory.end()) {
				Pointer = distance(Merory.begin(), it);
				continue;
			}

			if ((int)Merory.size() < MerorySize) {
				Merory.push_back(Page(AccessIndex));
				Pointer = 0;
			} else {
				FaultCount++;
				for (int i = 0; i < (int)Merory.size() * 2; i++, Pointer = (Pointer + 1) % Merory.size()) {
					if (Merory[Pointer].GetAccess() == 0) {
						Merory[Pointer] = Page(AccessIndex);
						break;
					} else {
						Merory[Pointer].ChangeAccessToZero();
					}
				}
				Pointer = (Pointer + 1) % Merory.size();
			}
		}
		return Result(FaultCount, (double)FaultCount / (double)AccessSequence.size());
	}

	//最近未使用
	Result LRU() {
		int FaultCount = 0;
		map<int, int> HashMap;
		vector<int> Merory;
		for (int i = 0; i < (int)AccessSequence.size(); i++) {
			if (std::find(Merory.begin(), Merory.end(), AccessSequence[i]) != Merory.end()) {
				HashMap[AccessSequence[i]] = i;
				continue;
			}

			if ((int)Merory.size() < MerorySize) {
				HashMap[AccessSequence[i]] = i;
				Merory.push_back(AccessSequence[i]);
			} else {
				FaultCount++;
				auto it = HashMap.begin();
				int Target = it->first;
				int Index = it->second;
				for (auto item : HashMap) {
					if (item.second < Index) {
						Target = item.first;
						Index = item.second;
					}
				}
				for (int j = 0; j < (int)Merory.size(); j++) {
					if (Merory[j] == Target) {
						Merory[j] = AccessSequence[i];
						HashMap[AccessSequence[i]] = i;
					}
				}
			}
		}
		return Result(FaultCount, (double)FaultCount / (double)AccessSequence.size());
	}
};