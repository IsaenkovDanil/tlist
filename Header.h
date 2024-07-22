#pragma once
#include <iostream>
#include <utility>
#include<initializer_list>
using namespace std;
template<typename LT>
class tlist
{
public:
	tlist(); // конструктор по умолчанию
	tlist(const tlist& tl); // конструктор копирования
	tlist(tlist&& tl); // конструктор перемещения
	tlist(const int psize=0 , const LT* pdata=nullptr );
	tlist(std::initializer_list<LT>il)
	{
		init();				                           //m_pdata = new T[size];//перед выделение памяти обнулить
		for (auto v : il)
		{
			push_back(v); //m_size++;
		}
	}

	~tlist();
protected:
	struct titem // элемент хранения
	{
		LT m_value; // значение данных
		titem* m_pNext; // ссылка на следующий элемент
		titem()
		{
			m_value = LT(0); // 0 для простых типов, пустой для объектов
			m_pNext = nullptr;
		};
	};
protected:
	titem* m_pFirst; // храним начало списка
protected:
	void init(); // функция инициализации
	void destroy(titem* pi); // функция очистки элементов
public:
	int push_back(LT val); // добавление в конец списка
	int size(void); // вычисление размера
	int copy(const tlist& tl); // копирование
	int move(tlist& tl) // копирование перемещением

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
		pLast = m_pFirst; // начинаем с первого
		while (pLast->m_pNext) // пока есть следующий
		{
			//LT x= pLast->m_value;
			cout << pLast->m_value <<endl;
			pLast = pLast->m_pNext; // следующий -> последний
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
	while (pi) // цикл по элементам (пока элемент существует)
	{
		p = pi->m_pNext; // запоминаем следующий элемент
		delete pi; // удаляем текущий элемент
		pi = p; // следующий стал текущим
	}
}
template<typename LT>
int tlist<LT>::push_back(LT val) // добавление в конец списка
{
	titem* pLast, * pNew;
	pNew = new titem; // создаем элемент
	if (pNew) // если элемент создался, то добавляем в конец
	{
		if (m_pFirst) // проверяем, были ли элементы –> ищем последний
		{
			pLast = m_pFirst; // начинаем с первого
			while (pLast->m_pNext) // пока есть следующий
			{
				pLast = pLast->m_pNext; // следующий -> последний
			}
			pLast->m_pNext = pNew; // нашли последний -> новый следующий
		}
		else // элементов не было -> новый первый
		{
			m_pFirst = pNew;
		}
		pNew->m_value = val; // сохраняем данные
		return size() - 1; // возвращаем номер добавленного элемента
	}
	return -1; // ошибка
}
template<typename LT>
int tlist<LT>::size(void) // вычисление размера списка
{
	titem* p;
	int s = 0;
	p = m_pFirst; // начинаем с первого
	while (p) // пока элементы есть
	{
		p = p->m_pNext; // следующий элемент
		s++; // добавляем счетчик
	}
	return s;
}
template<typename LT>
int tlist<LT>::copy(const tlist<LT>& lt) // копирование
{
	if (this == &lt) return size(); // проверяем на a = a
	titem* p;
	tlist nl; // объект для безопасного копирования
	p = lt.m_pFirst; // начинаем с первого элемента
	while (p) // пока элементы есть
	{
		if (nl.push_back(p->m_value) < 0)return 0;// добавляем значение
		// если ошибка, то выходим
		p = p->m_pNext; // следующий элемент
	}
	return move(nl); // готовые данные передаем в текущий объект
}
