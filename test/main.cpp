
#include "../utility/Utility.h"

class TestClass 
	: ghost::utility::NoCopyable
	, public ghost::utility::Cloneable
	, public ghost::utility::Associateable
{
	TestClass* m_pAnother;

public:
	TestClass()
		: m_pAnother(0)
	{

	}
	virtual ~TestClass()
	{
		DisassociateFromAll();
	}

public:
	virtual TestClass* Clone()
	{
		return 0;
	}

public:
	virtual bool AllowAssociatingWidth(Associateable* pObj) const
	{
		return 0 != dynamic_cast<TestClass*>(pObj);
	}
	virtual void DisassociateFromAll()
	{
		DisassociateFrom(m_pAnother);
	}

private:
	virtual bool IsAssociatedWidth(Associateable* pObj) const
	{
		return dynamic_cast<TestClass*>(pObj) == m_pAnother;
	}

	virtual void DoAssociateWith(Associateable* pObj)
	{
		m_pAnother = dynamic_cast<TestClass*>(pObj);
	}
	virtual void DoDisassociateFrom(Associateable* pObj)
	{
		m_pAnother = 0;
	}
};

void Test()
{
	TestClass test1;
	//TestClass test2(test1); // illegal
	TestClass test3;
	//test3 = test1; // illegal

	TestClass* pTest1 = new TestClass();
	test1.AssociateWith(pTest1);
	delete pTest1;
}

int main()
{
	Test();
	return 0;
}