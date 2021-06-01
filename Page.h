#pragma once
class Page {
private:
	int PageNumber; //ҳ���
	int Access;	//����λ
	int Modify;	//�޸�λ

public:
	Page(int PageNumber, int Access = 1, int Modify = 0) {
		this->PageNumber = PageNumber;
		this->Access = Access;
		this->Modify = Modify;
	}

	void ChangeAccessToOne() {
		this->Access = 1;
	}

	void ChangeAccessToZero() {
		this->Access = 0;
	}

	void ChangeModifyToOne() {
		this->Access = 1;
	}

	void ChangeModifyToZero() {
		this->Access = 0;
	}

	int GetAccess() {
		return Access;
	}

	int GetModify() {
		return Modify;
	}

	int GetPageNumber() {
		return PageNumber;
	}

	friend bool operator==(Page a, Page b) {
		return a.GetPageNumber() == b.GetPageNumber();
	}

};