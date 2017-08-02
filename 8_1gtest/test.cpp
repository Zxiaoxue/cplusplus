/*************************************************************************
	> File Name: main.cpp
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Mon 31 Jul 2017 08:04:58 PM PDT
 ************************************************************************/

#include <iostream>
#include <gtest/gtest.h>
#include <stdlib.h>
using namespace std;

/* TEST(TestCaseName, TestName)
{
	cout<<"hello"<<endl;
}
*/

//int Abs(int x)
//{
//	return x>0?x:-x;
//}
//
//TEST(TestCaseAbs, TestAbs1)
//{
//	ASSERT_TRUE(Abs(1)==1)<<"Abs(1)"<<Abs(1);
//	ASSERT_TRUE(Abs(0)==0)<<"Abs(0)"<<Abs(0);
//	ASSERT_TRUE(Abs(-1)==1)<<"Abs(-1)"<<Abs(-1);
//	EXPECT_TRUE(Abs(1)==-1)<<"Abs(1)"<<Abs(1);
//	ASSERT_TRUE(Abs(-1)==-1)<<"Abs(-1)"<<Abs(-1);
//	
//}
//
//TEST(TestCaseName, TestAbs2)
//{
//	ASSERT_EQ(Abs(1),1)<<"Abs(1)"<<Abs(1);
//	ASSERT_EQ(Abs(0),0)<<"Abs(0)"<<Abs(0);
//	ASSERT_EQ(Abs(-1),1)<<"Abs(-1)"<<Abs(-1);
//
//}

//int Add(int x, int y)
//{
//	return x+y;
//}
//
//TEST(TestCaseAdd, TestAdd)
//{
//	EXPECT_EQ(3,Add(1,2));
//
//}
//
//
//TEST(StringComTest, Demo)
//{
//	char* pszCoderZh = "CoderZh";
//	wchar_t* wszCoderZh = L"CoderZh";
//	string strCoderZh = "CoderZh";
//	wstring wstrCoderZh = L"CoderZh";
//
//	EXPECT_STREQ("CoderZh", pszCoderZh);
//	EXPECT_STREQ(L"CoderZh", wszCoderZh);
//	EXPECT_STRNE("CnBlogs", pszCoderZh);
//	EXPECT_STRNE(L"CnBlogs", wszCoderZh);
//	EXPECT_STRCASEEQ("coderzh", pszCoderZh);
//	EXPECT_STREQ("CoderZh", strCoderZh.c_str());
//	EXPECT_STREQ(L"CoderZh", wstrCoderZh.c_str());
//
//}
//
//TEST(ExplicitTest, Demo)
//{
//	//ADD_FAILURE()<<"Sorry";
////	FAIL();	//Fatal Assertion
//	SUCCEED();
//}

//int Foo(int a, int b)
//{
//	if(a == 0 || b == 0)
//	{
//		throw "don't do that";
//	}
//
//	int c = a%b;
//	if(c == 0)
//		return b;
//	return Foo(b,c);
//}
//
//TEST(FooTest, HandleZeroInput)
//{
//	EXPECT_ANY_THROW(Foo(10,0));
//	EXPECT_THROW(Foo(0, 5), char*);
//}
//
//bool MutuallyPrime(int m, int n)
//{
//	return Foo(m, n);
//}
//
//TEST(PredicateAssertionTest, Demo)
//{
//	int m = 5,n = 6;
//	EXPECT_PRED2(MutuallyPrime,m,n);
//}


//class  FooEnvironment : public testing::Environment
//{
//	public:
//		void SetUp()
//		{
//			cout<<"Foo FooEnvironment SetUp"<<endl;
//		}
//
//		void TearDown()
//		{
//			cout<<"Foo FooEnvironment TearDown"<<endl;
//		}
//};
//
//class TestMap : public testing::Test
//{
//	public:
//		//virtual void SetUp()
//		void SetUp()
//		{
//
//			test_map.insert(make_pair(1,1));
//			test_map.insert(make_pair(2,1));
//			test_map.insert(make_pair(3,1));
//			test_map.insert(make_pair(4,1));
//			test_map.insert(make_pair(5,1));
//			test_map.insert(make_pair(6,1));
//			cout<<"SetUp()"<<endl;
//		}
//		static void SetUpTestCase()
//		{
//			cout<<"SetUpTestCase()"<<endl;
//		}
//		
//		//virtual void TearDown()
//		void TearDown()
//		{
//			test_map.clear();
//			cout<<"TearDown()"<<endl;
//		}
//		static void TearDownTestCase()
//		{
//			
//			cout<<"TearDownTestCase()"<<endl;
//		}
//
//	public:
//		map<int,int> test_map;
//};
//
//TEST_F(TestMap, Find)
//{
//	map<int,int>::iterator it = test_map.begin();
//	ASSERT_NE(it, test_map.end());
//	
//	ASSERT_EQ(test_map.size(), 6);
//}
//
//TEST_F(TestMap, Size)
//{
//	ASSERT_EQ(test_map.size(), 6);
//}

//canshuhua
//bool IsPrime(int n)
//{
//	if(n <= 1)
//		return false;
//	if(n%2 == 0)
//		return n == 2;
//
//	//n >=3
//	for(int i = 3; ; i+=2)
//	{
//		if(i > n/i)
//			break;
//		if(n %i == 0)
//			return false;
//	}
//	return true;
//}
//
//
//TEST(IsPrimeTest, HandleTRrueReturn)
//{
//	EXPECT_TRUE(IsPrime(3));
//	EXPECT_TRUE(IsPrime(5));
//	EXPECT_TRUE(IsPrime(7));
//	EXPECT_TRUE(IsPrime(11));
//	EXPECT_TRUE(IsPrime(23));
//
//}
//
//class IsPrimeParamTest : public ::testing::TestWithParam<int> {};
//
//TEST_P(IsPrimeParamTest, HandleTrueReturn)
//{
//	int n = GetParam();
//	EXPECT_TRUE(IsPrime(n));
//}
//
//INSTANTIATE_TEST_CASE_P(TrueReturn, IsPrimeParamTest, testing::Values(3,5,7,9,11,23,17));

//类型参数化
//
//template <typename T>
//class FooTest:public testing::Test
//{
//	public:
//		typedef list<T> List;
//		static T _shared;
//		T _value;
//};
//
//typedef testing::Types<char, int, unsigned int> MyTypes;
//TYPE_TEST_CASE(FooTest, MyTypes);
//
//TYPED_TEST(FooTEst, DoesBlah)
//{
//	TypeParam n = this->_value;
//
//	n += TestFixture::_shared;
//	typename TestFixture::List values;
//	values.push_back(n);
//}

template <typename T>
class FooTest : public testing::Test {};

TYPED_TEST_CASE_P(FooTest);

TYPED_TEST_P(FooTest,DoesBlah)
{
	TypeParam n = 0;

}

TYPED_TEST_P(FooTest, HasPropertyA)
{}

REGISTER_TYPED_TEST_CASE_P(FooTest, DoesBlah, HasPropertyA);

typedef testing::Types<char, int, unsigned int> MyTypes;

INSTANTIATE_TYPED_TEST_CASE_P(My, FooTest, MyTypes);

int main(int argc, char*  argv[])
{
	testing::GTEST_FLAG(output) = "xml:";

//	FooEnvironment* env = new FooEnvironment();
//	testing::AddGlobalTestEnvironment(env);

	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}

