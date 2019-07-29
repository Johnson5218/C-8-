/*

// constructing lists
#include <iostream>
#include <list>
using namespace std;
int main()
{
	std::list<int> l1; // ����յ�l1
	std::list<int> l2(4, 100); // l2�з�4��ֵΪ100��Ԫ��
	std::list<int> l3(l2.begin(), l2.end()); // ��l2��[begin(), end()������ҿ������乹��l3
	std::list<int> l4(l3); // ��l3��������l4
	// ������Ϊ���������乹��l5
	int array[] = { 16, 2, 77, 29 };
	std::list<int> l5(array, array + sizeof(array) / sizeof(int));
	// �õ�������ʽ��ӡl5�е�Ԫ��
	for (std::list<int>::iterator it = l5.begin(); it != l5.end(); it++)
		std::cout << *it << " ";
	std::cout << endl;
	// C++11��Χfor�ķ�ʽ����
	for (auto& e : l5)
		std::cout << e << " ";
	std::cout << endl;
	return 0;
}

*/
/*
#include<vector>
#include <list>
#include<iostream>
using namespace std;
void PrintList(list<int>& l)
{
	for (auto& e : l)
		cout << e << " ";
	cout << endl;
}
//=========================================================================================
// push_back/pop_back/push_front/pop_front
void TestList1()
{
	int array[] = { 1, 2, 3 };
	list<int> L(array, array + sizeof(array) / sizeof(array[0]));
	// ��list��β������4��ͷ������0 L.push_back(4);
	L.push_front(0);
	PrintList(L);
	// ɾ��listβ���ڵ��ͷ���ڵ�
	L.pop_back();
	L.pop_front();
	PrintList(L);
}
//=========================================================================================
// insert /erase 
void TestList3()
{
	int array1[] = { 1, 2, 3 };
	list<int> L(array1, array1 + sizeof(array1) / sizeof(array1[0]));
	// ��ȡ�����еڶ����ڵ�
	auto pos = ++L.begin();
	cout << *pos << endl;
	// ��posǰ����ֵΪ4��Ԫ��
	L.insert(pos, 4);
	PrintList(L);
	// ��posǰ����5��ֵΪ5��Ԫ��
	L.insert(pos, 5, 5);
	PrintList(L);
	// ��posǰ����[v.begin(), v.end)�����е�Ԫ��
	vector<int> v{ 7, 8, 9 };
	L.insert(pos, v.begin(), v.end());
	PrintList(L);
	// ɾ��posλ���ϵ�Ԫ��
	L.erase(pos);
	PrintList(L);
	// ɾ��list��[begin, end)�����е�Ԫ�أ���ɾ��list�е�����Ԫ��
	L.erase(L.begin(), L.end());
	PrintList(L);
}
// resize/swap/clear
void TestList4()
{
	// ������������list
	int array1[] = { 1, 2, 3 };
	list<int> l1(array1, array1 + sizeof(array1) / sizeof(array1[0]));
	PrintList(l1);
	// ����l1��l2�е�Ԫ��
	l1.swap(l2);
	PrintList(l1);
	PrintList(l2);
	// ��l2�е�Ԫ�����
	l2.clear();
	cout << l2.size() << endl;
}
*/
#include<iostream>
using namespace std;

namespace bite
{
	// List�Ľڵ���
	template<class T>
	struct ListNode
	{
		ListNode(const T& val = T())
		: _pPre(nullptr)
		, _pNext(nullptr)
		, _val(val)
		{}
		ListNode<T>* _pPre;
		ListNode<T>* _pNext; T _val;
	};
	/*
	List �ĵ�����
	������������ʵ�ַ�ʽ������Ӧ���������ײ����ݽṹʵ�֣�
	1. ԭ��ָ̬�룬���磺vector
	2. ��ԭ��ָ̬����з�װ���������ʹ����ʽ��ָ����ȫ��ͬ��������Զ�������б���ʵ�����·�����
	1. ָ����Խ����ã������������б�������operator*()
	2. ָ�����ͨ��->��������ָ�ռ��Ա�����������б�������oprator->()
	3. ָ�����++����ƶ������������б�������operator++()��operator++(int)
	����operator--()/operator--(int)�ͷ���Ҫ���أ����ݾ���Ľṹ������˫�����������ǰ
	�ƶ���������Ҫ���أ������forward_list�Ͳ���Ҫ����--
	4. ��������Ҫ�����Ƿ���ȵıȽϣ���˻���Ҫ����operator==()��operator!=()
	*/
	template<class T, class Ref, class Ptr>
	class ListIterator
	{
		typedef ListNode<T>* PNode;
		typedef ListIterator<T, Ref, Ptr> Self;
	public:
		ListIterator(PNode pNode = nullptr)
			: _pNode(pNode)
		{}
		ListIterator(const Self& l)
			: _pNode(l._pNode)
		{}
		T& operator*(){ return _pNode->_val; }
		T* operator->(){ return &(operator*()); }
		Self& operator++()
		{
			_pNode = _pNode->_pNext;
			return *this;
		}
		Self operator++(int)
		{
			Self temp(*this);
			_pNode = _pNode->_pNext;
			return temp;
		}
		Self& operator--();
		Self& operator--(int);
		bool operator!=(const Self& l){ return _pNode != l._pNode; }
		bool operator==(const Self& l){ return _pNode != l._pNode; }
		PNode _pNode;
	};
	template<class T>
	class list
	{
		typedef ListNode<T> Node;
		typedef Node* PNode;
	public:
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T&> const_iterator;
	public:
		///////////////////////////////////////////////////////////////
		// List�Ĺ���
		list()
		{
			CreateHead();
		}
		list(int n, const T& value = T())
		{
			CreateHead();
			for (int i = 0; i < n; ++i)
				push_back(value);
		}
		template <class Iterator>
		list(Iterator first, Iterator last)
		{
			CreateHead();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		list(const list<T>& l)
		{
			CreateHead();
			// ��l�е�Ԫ�ع�����ʱ��temp,Ȼ���뵱ǰ���󽻻�
			list<T> temp(l.cbegin(), l.cend());
			this->swap(temp);
		}
		list<T>& operator=(const list<T> l)
		{
			this->swap(l);
			return *this;
		}
		~list()
		{
			clear();
			delete _pHead;
			_pHead = nullptr;
		}
		///////////////////////////////////////////////////////////////
		// List Iterator
		iterator begin(){ return iterator(_pHead->_pNext); }
		iterator end(){ return iterator(_pHead); }
		const_iterator begin(){ return const_iterator(_pHead->_pNext); }
		const_iterator end(){ return const_iterator(_pHead); }
		///////////////////////////////////////////////////////////////
		// List Capacity
		size_t size()const;
		bool empty()const;
		////////////////////////////////////////////////////////////
		// List Access
		T& front();
		const T& front()const; T& back();
		const T& back()const;
		////////////////////////////////////////////////////////////
		// List Modify
		void push_back(const T& val){ insert(begin(), val); }
		void pop_back(){ erase(--end()); }
		void push_front(const T& val){ insert(begin(), val); }
		void pop_front(){ erase(begin()); }
		// ��posλ��ǰ����ֵΪval�Ľڵ�
		iterator insert(iterator pos, const T& val)
		{
			PNode pNewNode = new Node(val);
			PNode pCur = pos._pNode;
			// �Ƚ��½ڵ����
			pNewNode->_pPre = pCur->_pPre;
			pNewNode->_pNext = pCur;
			pNewNode->_pPre->_pNext = pNewNode;
			pCur->_pPre = pNewNode;
			return iterator(pNewNode);
		}
		// ɾ��posλ�õĽڵ㣬���ظýڵ����һ��λ��
		iterator erase(iterator pos)
		{
			// �ҵ���ɾ���Ľڵ�
			PNode pDel = pos._pNode;
			PNode pRet = pDel->_pNext;
			// ���ýڵ�������в�������ɾ��
			pDel->_pPre->_pNext = pDel->_pNext;
			pDel->_pNext->_pPre = pDel->_pPre;
			delete pDel;
			return iterator(pRet);
		}
		void clear();
		void swap(List<T>& l);
	private:
		void CreateHead()
		{
			_pHead = new Node;
			_pHead->_pPre = _pHead;
			_pHead->_pNext = _pHead;
		}
	private:
		PNode _pHead;
	};
}


// �����ӡ����
template<class T>
void PrintList(const bite::list<T>& l) {
	auto it = l.cbegin();
	while (it != l.cend())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
// ����List�Ĺ���
void TestList1()
{
	bite::list<int> l1;
	bite::list<int> l2(10, 5);
	PrintList(l2);
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	bite::list<int> l3(array, array + sizeof(array) / sizeof(array[0]));
	PrintList(l3);
	bite::list<int> l4(l3);
	PrintList(l4);
	l1 = l4;
	PrintList(l1);
	PrintListReverse(l1);
}
// PushBack()/PopBack()/PushFront()/PopFront()
void TestList2()
{
	// ����PushBack��PopBack
	bite::list<int> l; l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	PrintList(l);
	l.pop_back();
	l.pop_back();
	PrintList(l);
	l.pop_back();
	cout << l.size() << endl;
	// ����PushFront��PopFront
	l.push_front(1);
	l.push_front(2);
	l.push_front(3);
	PrintList(l);
	l.pop_front();
	l.pop_front();
	PrintList(l);
	l.pop_front();
	cout << l.size() << endl;
}
void TestList3()
{
	int array[] = { 1, 2, 3, 4, 5 };
	bite::list<int> l(array, array + sizeof(array) / sizeof(array[0]));
	auto pos = l.begin();
	l.insert(l.begin(), 0);
	PrintList(l);
	++pos; l.insert(pos, 2);
	PrintList(l);
	l.erase(l.begin());
	l.erase(pos);
	PrintList(l);
	// posָ��Ľڵ��Ѿ���ɾ����pos������ʧЧ
	cout << *pos << endl;
	auto it = l.begin();
	while (it != l.end())
	{
		it = l.erase(it);
	}
	cout << l.size() << endl;
}


int main()
{
	TestList1();
	TestList2();
	TestList3();
	return 0;
}