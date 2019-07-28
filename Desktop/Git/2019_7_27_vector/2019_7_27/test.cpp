/*
#include <iostream>
#include <vector>
int main()
{
	size_t sz;
	std::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i = 0; i<100; ++i) {
		foo.push_back(i);
		if (sz != foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
}
*/
/*
#include <iostream>
#include <vector>
int main()
{
	size_t sz;
	std::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i = 0; i<100; ++i) {
		foo.push_back(i);
		if (sz != foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	std::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100); // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i = 0; i<100; ++i) {
		bar.push_back(i);
		if (sz != bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	return 0;
}
*/


/*

#include <iostream>
#include <vector>
int main()
{
	std::vector<int> myvector;
	// set some initial content:
	for (int i = 1; i<10; i++)
	myvector.push_back(i);
	myvector.resize(5);
	myvector.resize(8, 100);
	myvector.resize(12);
	std::cout << "myvector contains:";
	for (int i = 0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	return 0;
}

*/

/*
// push_back/pop_back
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int a[] = { 1, 2, 3, 4 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));
	vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl; v.pop_back();
	v.pop_back();
	it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
	return 0;
}

*/

/*

// find / insert / erase
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
	int a[] = { 1, 2, 3, 4 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));
	// ʹ��find����3����λ�õ�iterator
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);
	// ��posλ��֮ǰ����30
	v.insert(pos, 30);
	vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
	pos = find(v.begin(), v.end(), 3);
	// ɾ��posλ�õ�����
	v.erase(pos);
	it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
	return 0;
}

*/



/*
// operator[]+index �� C++11��vector����ʽfor+auto�ı���
// vectorʹ�������ֱ�����ʽ�ǱȽϱ�ݵġ�
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int a[] = { 1, 2, 3, 4 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));
	// ͨ��[]��д��0��λ�á�
	v[0] = 10;
	cout << v[0] << endl;
	// ͨ��[i]�ķ�ʽ����vector
	for (size_t i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
		cout << endl;
	vector<int> swapv;
	swapv.swap(v);
	cout << "v data:";
	for (size_t i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << endl;
	cout << "swapv data:";
	for (size_t i = 0; i < swapv.size(); ++i)
		cout << swapv[i] << " ";
	cout << endl;
	// C++11֧�ֵ���ʽ��Χfor����
	for (auto x : v)
		cout << x << " ";
	cout << endl;
	return 0;
}

*/

/*
// insert/erase���µĵ�����ʧЧ
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
	int a[] = { 1, 2, 3, 4 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));
	// ʹ��find����3����λ�õ�iterator
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);
	// ɾ��posλ�õ����ݣ�����pos������ʧЧ��
	v.erase(pos);
	cout << *pos << endl; // �˴��ᵼ�·Ƿ�����
	// ��posλ�ò������ݣ�����pos������ʧЧ��
	// insert�ᵼ�µ�����ʧЧ������Ϊinsert��
	// �ܻᵼ�����ݣ����ݺ�pos��ָ��ԭ���Ŀռ䣬��ԭ���Ŀռ��Ѿ��ͷ��ˡ�
	pos = find(v.begin(), v.end(), 3);
	v.insert(pos, 30);
	cout << *pos << endl; // �˴��ᵼ�·Ƿ�����
	return 0;
}

*/


/*

// �����ĵ�����ʧЧ�ĳ���
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
	int a[] = { 1, 2, 3, 4 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));
	// ʵ��ɾ��v�е�����ż��
	// ����ĳ����������������ż����erase����itʧЧ
	// ��ʧЧ�ĵ���������++it���ᵼ�³������
	
	//vector<int>::iterator it = v.begin();
	//while (it != v.end())
	//{
	//	if (*it % 2 == 0) v.erase(it);
	//	++it;
	//}

	
	// ���ϳ���Ҫ�ĳ�����������erase�᷵��ɾ��λ�õ���һ��λ��
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
			it = v.erase(it);
		else
			++it;
	}
	return 0;
}


*/

/*

#include <iostream>
using namespace std;
#include <assert.h>


namespace bit
{
	template<class T>
	class vector
	{
	public:
		// Vector�ĵ�������һ��ԭ��ָ��
		typedef T* iterator;
		typedef const T* const_iterator;
		iterator begin() { return _start; }
		iterator end() { return _finish; }
		const_iterator cbegin() const { return _start; }
		const_iterator cend() const { return _finish; }
		// construct and destroy
		vector()
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{}
		vector(int n, const T& value = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			reserve(n);
			while (n--)
			{
				push_back(value);
			}
		}
		// ���ʹ��iterator�����������ᵼ�³�ʼ���ĵ���������[first,last)ֻ����vector�ĵ�����
		// ��������������������������[first,last]���������������ĵ�����
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			reserve(last - first);
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		vector(const vector<T>& v)
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			reserve(v.capacity());
			iterator it = begin();
			const_iterator vit = v.cbegin();
			while (vit != v.cend())
			{
				*it++ = *vit++;
			}
			_finish = _start + v.size();
			_endOfStorage = _start + v.capacity();
		}
		vector<T>& operator= (vector<T> v)
		{
			swap(v);
			return *this;
		}
		~vector()
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}
		// capacity
		size_t size() const { return _finish - _start; }
		size_t capacity() const { return _endOfStorage - _start; }
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t oldSize = size();
				T* tmp = new T[n];
				// ����ֱ��ʹ��memcpy���������
				// �Ժ����ǻ��ø��õķ������
				//if (_start)
				// memcpy(tmp, _start, sizeof(T)*size);
				if (_start)
				{
					for (size_t i = 0; i < oldSize; ++i)
						tmp[i] = _start[i];
				}
				_start = tmp;
				_finish = _start + size;
				_endOfStorage = _start + n;
			}
		}
		void resize(size_t n, const T& value = T())
		{
			// 1.���nС�ڵ�ǰ��size�������ݸ�����С��n
			if (n <= size())
			{
				_finish = _start + n;
				return;
			}
			// 2.�ռ䲻��������
			if (n > capacity())
				reserve(n);
			// 3.��size����n
			iterator it = _finish;
			iterator _finish = _start + n;
			while (it != _finish)
			{
				*it = value;
				++it;
			}
		}
		///////////////access///////////////////////////////
		T& operator[](size_t pos){ return _start[pos]; }
		const T& operator[](size_t pos)const { return _start[pos]; }
		///////////////modify/////////////////////////////
		void push_back(const T& x){ insert(end(), x); }
		void pop_back(){ erase(--end()); }
		void swap(vector<T>& v)
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_endOfStorage, v._endOfStorage);
		}
		iterator insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);
			// �ռ䲻���Ƚ�������
			if (_finish == _endOfStorage)
			{
				size_t size = size();
				size_t newCapacity = (0 == capacity()) ? 1 : capacity() * 2;
				reserve(newCapacity);
				// ������������ݣ���Ҫ����pos
				pos = _start + size;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;
			return pos;
		}
		// ����ɾ�����ݵ���һ������
		// ������:һ�߱���һ��ɾ���ĵ�����ʧЧ����
		iterator erase(Iterator pos)
		{
			// Ų�����ݽ���ɾ��
			iterator begin = pos + 1;
			while (begin != _finish) {
				*(begin - 1) = *begin;
				++begin;
			}
			--_finish;
			return pos;
		}
private:
	iterator _start; // ָ�����ݿ�Ŀ�ʼ
	iterator _finish; // ָ����Ч���ݵ�β
	iterator _endOfStorage; // ָ��洢������β
};
}


// constructing vectors
void TestVector1()
{
	// constructors used in the same order as described above:
	bite::vector<int> first; // empty vector of ints
	bite::vector<int> second(4, 100); // four ints with value 100
	bite::vector<int> third(second.Begin(), second.End()); // iterating through second
	bite::vector<int> fourth(third); // a copy of third
	// the iterator constructor can also be used to construct from arrays:
	int myints[] = { 16, 2, 77, 29 };
	bit::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
	std::cout << "The contents of fifth are:";
	for (bit::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << *it << " ";
	std::cout << endl;
	// ����T��stringʱ����������
	bit::vector<string> strV;
	strV.PushBack("1111");
	strV.PushBack("2222");
	strV.PushBack("3333");
	strV.PushBack("4444");
	for (size_t i = 0; i < strV.size(); ++i)
	{
		cout << strV[i] << " ";
	}
	cout << endl;
}
//vector iterator��ʹ��
void PrintVector(const bite::vector<int>& v) {
	// ʹ��const���������б�����ӡ
	bit::vector<int>::const_iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void TestVector2()
{
	// ʹ��push_back����4������
	bite::vector<int> v; v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	PrintVector(v);
	// ʹ�õ����������޸�
	auto it = v.begin();
	while (it != v.end())
	{
		*it *= 2;
		++it;
	}
	PrintVector(v);
	// ������Կ���C++11֧��iterator���ӿڣ���֧�ַ�Χfor
	for (auto e : v)
		cout << e << " ";
}
// find / insert / erase
void TestVector3()
{
	int a[] = { 1, 2, 3, 4 };
	bite::vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
	// ʹ��find����3����λ�õ�iterator
	auto pos = find(v.begin(), v.end(), 3);
	// ��posλ��֮ǰ����30
	v.insert(pos, 30);
	PrintVector(v);
	// ɾ��posλ�õ�����
	pos = find(v.begin(), v.end(), 3);
	v.Erase(pos);
	PrintVector(v);
}
// iteratorʧЧ����
void TestVector4()
{
	int a[] = { 1, 2, 3, 4 };
	bite::vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
	// ɾ��posλ�õ����ݣ�����pos������ʧЧ
	auto pos = find(v.begin(), v.end(), 3);
	v.erase(pos);
	cout << *pos << endl; // �˴��ᵼ�·Ƿ�����
	// ��posλ�ò������ݣ�����pos������ʧЧ��
	// insert�ᵼ�µ�����ʧЧ������Ϊinsert��
	// �ܻᵼ�����ݣ����ݺ�pos��ָ��ԭ���Ŀռ䣬��ԭ���Ŀռ��Ѿ��ͷ��ˡ�
	pos = find(v.begin(), v.end(), 3);
	v.insert(pos, 30);
	cout << *pos << endl; // �˴��ᵼ�·Ƿ�����
	// ʵ��ɾ��v�е�����ż��
	// ����ĳ����������������ż����erase����itʧЧ
	// ��ʧЧ�ĵ���������++it���ᵼ�³������
	auto it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0) v.erase(it);
		++it;
	}
	// ���ϳ���Ҫ�ĳ�����������erase�᷵��ɾ��λ�õ���һ��λ��
	it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
			it = v.erase(it);
		else
			++it;
	}
}
**************************************************************************
������ʧЧ�����ܽ᣺
1. ɾ��pos������λ����ָ��Ԫ��û�м�ʱ��pos��ֵ������v.erase(pos)
2. ���ܻ�����vector�ײ�ռ�ı�Ĳ��������磺push_back��insert��resize��reserve��
**************************************************************************
*/

