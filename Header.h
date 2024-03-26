#pragma once
#include <iostream>
#include <utility>
#include<initializer_list>
using namespace std;
template<typename LT>
class tlist
{
public:
	tlist(); // ����������� �� ���������
	tlist(const tlist& tl); // ����������� �����������
	tlist(tlist&& tl); // ����������� �����������
	tlist(const int psize=0 , const LT* pdata=nullptr );
	tlist(std::initializer_list<LT>il)
	{
		init();				                           //m_pdata = new T[size];//����� ��������� ������ ��������
		for (auto v : il)
		{
			push_back(v); //m_size++;
		}
	}

	~tlist();
protected:
	struct titem // ������� ��������
	{
		LT m_value; // �������� ������
		titem* m_pNext; // ������ �� ��������� �������
		titem()
		{
			m_value = LT(0); // 0 ��� ������� �����, ������ ��� ��������
			m_pNext = nullptr;
		};
	};
protected:
	titem* m_pFirst; // ������ ������ ������
protected:
	void init(); // ������� �������������
	void destroy(titem* pi); // ������� ������� ���������
public:
	int push_back(LT val); // ���������� � ����� ������
	int size(void); // ���������� �������
	int copy(const tlist& tl); // �����������
	int move(tlist& tl) // ����������� ������������

	{
		if (this != &tl) {
			destroy(m_pFirst);
			m_pFirst = tl.m_pFirst;
			tl.init();
		}

		return m_pFirst;
	}
	void output() {
		titem *pLast;
		pLast = m_pFirst; // �������� � �������
		while (pLast->m_pNext) // ���� ���� ���������
		{
			//LT x= pLast->m_value;
			cout << pLast->m_value <<endl;
			pLast = pLast->m_pNext; // ��������� -> ���������
		}
		cout << pLast->m_value <<endl;
	}
};
template<typename LT>
tlist<LT>::tlist()
{
	init();
}
template<typename LT>
tlist<LT>::tlist(const tlist<LT>& tl)
{
	init();
	copy(tl);
}
template<typename LT>
tlist<LT>::tlist(tlist<LT>&& tl)
{
	init();
	move(tl);
}
template<typename LT>
 tlist<LT>::tlist(const int psize, const LT* pdata)
 {
	 for (int i = 0; i < psize; i++) 
	 {
		 this->push_back(pdata[i]);
 }

}
template<typename LT>
tlist<LT>::~tlist()
{
	destroy(m_pFirst);
}
template<typename LT>
void tlist<LT>::init()
{
	m_pFirst = nullptr;
}
template<typename LT>
void tlist<LT>::destroy(titem* pi)
{
	titem* p;
	while (pi) // ���� �� ��������� (���� ������� ����������)
	{
		p = pi->m_pNext; // ���������� ��������� �������
		delete pi; // ������� ������� �������
		pi = p; // ��������� ���� �������
	}
}
template<typename LT>
int tlist<LT>::push_back(LT val) // ���������� � ����� ������
{
	titem* pLast, * pNew;
	pNew = new titem; // ������� �������
	if (pNew) // ���� ������� ��������, �� ��������� � �����
	{
		if (m_pFirst) // ���������, ���� �� �������� �> ���� ���������
		{
			pLast = m_pFirst; // �������� � �������
			while (pLast->m_pNext) // ���� ���� ���������
			{
				pLast = pLast->m_pNext; // ��������� -> ���������
			}
			pLast->m_pNext = pNew; // ����� ��������� -> ����� ���������
		}
		else // ��������� �� ���� -> ����� ������
		{
			m_pFirst = pNew;
		}
		pNew->m_value = val; // ��������� ������
		return size() - 1; // ���������� ����� ������������ ��������
	}
	return -1; // ������
}
template<typename LT>
int tlist<LT>::size(void) // ���������� ������� ������
{
	titem* p;
	int s = 0;
	p = m_pFirst; // �������� � �������
	while (p) // ���� �������� ����
	{
		p = p->m_pNext; // ��������� �������
		s++; // ��������� �������
	}
	return s;
}
template<typename LT>
int tlist<LT>::copy(const tlist<LT>& lt) // �����������
{
	if (this == &lt) return size(); // ��������� �� a = a
	titem* p;
	tlist nl; // ������ ��� ����������� �����������
	p = lt.m_pFirst; // �������� � ������� ��������
	while (p) // ���� �������� ����
	{
		if (nl.push_back(p->m_value) < 0)return 0;// ��������� ��������
		// ���� ������, �� �������
		p = p->m_pNext; // ��������� �������
	}
	return move(nl); // ������� ������ �������� � ������� ������
}
