#include<iostream>
////��ͨ�������ռ�
//namespace N1
//{
//	int a = 10;
//	int Add(int left, int right)
//	{
//		return left + right;
//	}
//}
////�����ռ����Ƕ��
//namespace N2
//{
//	int a = 20;
//	int b = 30;
//	namespace N3
//	{
//		int Add(int left, int right)
//		{
//			return left + right;
//		}
//	}
//}
////�����ռ�����������������ռ�����ʱ���������ռ�ʵ������ͬһ�飬���������ռ��е����б����ͺ�����ϲ������������������治�ܳ�����ͬ�����ı����ͺ���
//namespace N1 
//{ 
//	int Mul(int left, int right)   
//	{ 
//		return left * right;
//	} 
//}
//
//#include<iostream>
//void TestFunc(int a = 0)
//{
//	cout << a << endl;
//}
//
//int main()
//{
//	TestFunc();//û�д���ʱ��ʹ�ò�����Ĭ��ֵ
//	TestFunc(10);//����ʱ��ʹ��ָ���Ĳ���
//	return 0;
//}


//a.h void TestFunc(int a = 10);

// a.c void TestFunc(int a = 20) {}

// ע�⣺��������붨��λ��ͬʱ���֣�ǡ������λ���ṩ��ֵ��ͬ���Ǳ��������޷�ȷ�����׸����Ǹ� ȱʡֵ��
int Add(int left, int right)
{ 
	return left + right;
}

double Add(double left, double right)
{
	return left + right;
}
