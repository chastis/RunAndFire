#include "stdafx.h"
//#include "CppUnitTest.h"
#include "../RunAndFire/map.h"
#include "../RunAndFire/map.cpp"
//#include "../RunAndFire/headers_which_you_need.h"

//#include "../RunAndFire/Bullet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			sf::Image im;
			Map test_map(im, 30, 40, "map1");
			Assert::AreEqual(test_map.get_h(), 30);
			Assert::AreEqual(test_map.get_w(), 40);
		}

	};
}