/*
*���demon����string��һЩ����
*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;


//
//int main()
//{
//	string s = {};
//	cout << s.capacity() << endl;
//	s.reserve(31);
//	cout << s.capacity() << endl;
//	s.reserve(15);
//	cout << s.capacity() << endl;
//	return 0;
//}

/*
void test1()
{
string s("hello,world");
cout << s.length() << endl; // 11
cout << s.size() << endl; // 11
cout << s.capacity() << endl;
// 15 ,capacity��15����ʵ���Ͽ�����16��char�Ŀռ䣬�����`\0`
cout << s << endl;//string�����֧��ֱ����cin��cout�����������

//������s�е��ַ�����գ�ֻ�ı���Ч���ݵĴ�С�����ı������Ĵ�С
s.clear();
cout << s.size() << endl; // 0
cout << s.capacity() << endl; // 15
// ��s����Ч�ַ��������ӵ�10�������λ����'j'�������
s.resize(10, 'j');
cout << s.size() << endl; // 10
cout << s.capacity() << endl; // 15
cout << s << endl; // jjjjjjjjjj
//��s����Ч�ַ��������ӵ�15�������λ����ȱʡֵ'\0'�������
s.resize(15);
cout << s.size() << endl; // 15
cout << s.capacity() << endl; // 15
cout << s << endl; // jjjjjjjjjj\0\0\0\0\0
//��s����Ч�ַ�������С��5��
s.resize(5);
cout << s.size() << endl; // 5
cout << s.capacity() << endl; // 15
cout << s << endl; // jjjjj
cout << "--------------" << endl;
//����reserve
string s2("hehe");
//reserve����ı�string����ЧԪ�ظ���
cout << s2.size() << endl;//4
cout << s2.capacity() << endl;//15
s2.reserve(100);
cout << s2.size() << endl;//4
cout << s2.capacity() << endl;//111
//��reserve�Ĳ���С�� string�ĵײ�ռ��ܴ�Сʱ��reserver����ı�������С
s2.reserve(50);
cout << s2.size() << endl; // 4
cout << s2.capacity() << endl; // 111
}
*/


/*
void test1()
{
	string s1("hello");
	const string s2("world");
	cout << s1[0] << " " << s2[0] << endl; //h w
	s1[0] = 'x';
	// s2[0] = 'x';��������޸ģ���Ϊ����const���εĶ������޸�
	cout << s1[0] << endl;// x
}
*/

/*
void test2()
{
	string str("hello");
	str.push_back('C');//��str���׷���ַ�C
	cout << str << endl;
	str.append(" world");//��str���׷���ַ���
	cout << str << endl;
	str += 'X'; //str���׷���ַ�X
	cout << str << endl;
	str += "xxx";//str���׷���ַ���xxx
	cout << str << endl;
	cout << str.c_str() << endl;//��C������ʽ��ӡ�ַ���
}
// npos��string�����һ����̬��Ա����    
// static const size_t npos = -1;
void test3()
{
	string file("test.cpp");
	size_t pos = file.rfind('.');
	if (pos == string::npos)
	{
		cout << "�ļ������ں�׺" << endl;
	}
	else{
		cout << file.substr(pos, file.size() - pos) << endl;
	}
}
void test4()
{
	string url("http://www.baidu.com/");
	size_t start = url.find("://");
	if (start == string::npos){
		cout << "url error" << endl;
		return;
	}
	//find�Ҳ�������-1��������size_t����finish��һ���ܴ������
	size_t finish = url.find('/', start + 3);
	cout << url.substr(start + 3, finish - start - 3) << endl;
	//ɾ��url��ǰ׺
	int pos = url.find("://");
	url.erase(0, pos + 3);
	cout << url << endl;
}
*/

//void test()
//{
//	string num = "1234";
//	string::iterator it = num.begin();
//	int res = 0;
//	while (it != num.end())
//	{
//		res += 10;
//		res += (*it) - '0';
//		cout << *it << '-';
//		cout << res << endl;
//		it++;
//	}
//
//	vector<int> v;
//	v.push_back(1);
//	v.push_back(2);
//	vector<int>::iterator vit = v.begin();
//	while (vit != v.end())
//	{
//		cout << *vit << endl;
//		vit++;
//	}
//	cout << "--------------------------" << endl;
//	vector<int>::reverse_iterator rvit = v.rbegin();
//	while (rvit != v.rend())
//	{
//		cout << *rvit << endl;
//		rvit++;
//	}
//	cout << "--------------------------" << endl;
//
//}
//int main()
//{
//	test1();
//	test2();
//	test3();
//	test4();
//	test();
//	return 0;
//}