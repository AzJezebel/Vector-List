
#include "pch.h"
#include <iostream>

#include "catch.hpp"

#include "SpyAllocator.h"
#include "Foo.h"
#include "MonContainer.h"

#include "MyVector.h"
#include "MyList.h"

#include <vector>




#define DO(inst) std::printf("\n" #inst "\n"); inst

// Set to 0 to use your containers.
#define USE_STD 0

#if USE_STD
#include <vector>
#include <list>
#include <string>
using namespace std;
#else
using namespace my;
#endif



TEST_CASE("MonContainer", "[VectorList]")
{
	{
		std::printf("===========Test container============\n");
		Foo::ResetCount();
		std::printf("Create container\n");

		MonContainer<Foo, SpyAllocator<Foo>>    foos;

		CHECK(Foo::Count() == 5);

		std::printf("Destroy container\n");


		Foo::ResetCount();
	}

	g_memorySpy.CheckLeaks();
}




/* Test : push_back, capacity, size, operator[]. */
TEST_CASE("VectorInt", "[VectorList]")
{
	{
		std::printf("=======Vector of int================\n\nCreate vector\n");
		vector<int, SpyAllocator<int>>    intVec;

		std::printf("\nsizeof(intVec) : %llu\n", sizeof(intVec));
		std::printf("\nCapacity=%llu, Size=%llu\n", intVec.capacity(), intVec.size());

		DO(intVec.push_back(10);)
		DO(intVec.push_back(20);)
		DO(intVec.push_back(30);)
		DO(intVec.push_back(40);)
		DO(intVec.push_back(50);)

		std::printf("\nCapacity=%llu, Size=%llu\n", intVec.capacity(), intVec.size());

		DO(intVec[3] *= 2;)

			for (size_t i = 0; i < intVec.size(); ++i)
			{
				std::printf("%d ", intVec[i]);
			}
		std::printf("\n");

		std::printf("\nDestroy vector\n\n");
	}

	g_memorySpy.CheckLeaks();
}


/* Test : reserve. */
TEST_CASE("VectorFoo_Reserve", "[VectorList]")
{
	{
		std::printf("\n=======Vector of Foo================\n\nCreate vector\n");

		vector<Foo, SpyAllocator<Foo> > fooVec;

		std::printf("\nsizeof(fooVec) : %llu\n", sizeof(fooVec));

		DO(fooVec.reserve(2));
		DO(fooVec.push_back(Foo()));
		DO(fooVec.push_back(Foo()));
		DO(fooVec.push_back(Foo()));

		std::printf("\nDestroy vector\n\n");
	}

	g_memorySpy.CheckLeaks();

}



/* Test : reserve, clear */
TEST_CASE("VectorFoo_Clear", "[VectorList]")
{
	{
		std::printf("\n=======Vector of Foo================\n\nCreate vector\n");

		vector<Foo, SpyAllocator<Foo> > fooVec;

		DO(fooVec.reserve(2));

		DO(fooVec.push_back(Foo()));
		DO(fooVec.push_back(Foo()));
		DO(fooVec.clear());

		DO(fooVec.push_back(Foo()));

		std::printf("\nDestroy vector\n\n");
	}

	g_memorySpy.CheckLeaks();
}


/* Test : resize, copy ctor */
TEST_CASE("VectorFoo_resize", "[VectorList]")
{
	{
		std::printf("\n=======Vector of Foo================\n\nCreate vector\n");

		vector<Foo, SpyAllocator<Foo> > fooVec;

		DO(fooVec.resize(2));

		DO(fooVec.push_back(Foo()));
		DO(fooVec.push_back(Foo()));

		std::printf("\nDestroy vector\n\n");
	}

	g_memorySpy.CheckLeaks();
}


TEST_CASE("VectorFoo_copy_ctor", "[VectorList]")
{
	{
		std::printf("\n=======Vector of Foo================\n\nCreate vector\n");

		vector<Foo, SpyAllocator<Foo> > fooVec;

		DO(fooVec.push_back(Foo()));
		DO(fooVec.push_back(Foo()));

		std::printf("\nCopy fooVec\n\n");

		vector<Foo, SpyAllocator<Foo> > fooVec2 = fooVec;

		std::printf("\nDestroy vectors \n");
	}


	g_memorySpy.CheckLeaks();
}


TEST_CASE("VectorFoo_operator=", "[VectorList]")
{
	{
		std::printf("\n=======Vector of Foo================\n\nCreate vector\n");

		vector<Foo, SpyAllocator<Foo> > fooVec;

		DO(fooVec.push_back(Foo()));
		DO(fooVec.push_back(Foo()));

		std::printf("\nCopy fooVec\n\n");

		vector<Foo, SpyAllocator<Foo> > fooVec2;
		fooVec2 = fooVec;

		std::printf("\nDestroy vectors \n");
	}

	g_memorySpy.CheckLeaks();
}



/* List.insert, remove, push_back, begin, end, size */
TEST_CASE("ListInt", "[VectorList]")
{
	{
		std::printf("\n=======List================\n\nCreate list\n");

		list<int, SpyAllocator<int>> maList;

		//DO(maList.push_back(10));
		//DO(maList.push_back(20));
		//DO(maList.push_back(30));
		//DO(maList.push_back(40));
		//DO(maList.push_back(50));

		//std::printf("\nList size : %llu\n", maList.size());3


	//	std::printf("\nPrint list:\n");
	//	for (list<int, SpyAllocator<int>>::iterator it = maList.begin(); it != maList.end(); ++it)
	//	{
	//		std::printf("%d ", *it);
	//	}
	//	std::printf("\n\n");

	//	DO(maList.remove(20));
	//	DO(maList.remove(40));

	//	for (list<int, SpyAllocator<int>>::iterator it = maList.begin(); it != maList.end(); ++it)
	//	{
	//		std::printf("%d ", *it);
	//	}
	//	std::printf("\n\n");


	//	DO(maList.insert(std::find(maList.begin(), maList.end(), 30), 60));

	//	std::printf("\nList size : %llu\n", maList.size());

	//	std::printf("\nPrint list:\n");
	//	for (list<int, SpyAllocator<int>>::iterator it = maList.begin(); it != maList.end(); ++it)
	//	{
	//		std::printf("%d ", *it);
	//	}
	//	std::printf("\n\n");

	//	std::printf("\nDestroy list\n\n");
	}

	//g_memorySpy.CheckLeaks();

}


/* List.copy ctor */
TEST_CASE("List_CopyCtor", "[VectorList]")
{
	//{
	//	std::printf("\n=======List================\n\nCreate list\n");

	//	list<int, SpyAllocator<int>> list;

	//	DO(list.push_back(10));
	//	DO(list.push_back(20));
	//	DO(list.push_back(30));
	//	DO(list.push_back(40));
	//	DO(list.push_back(50));


	//	std::printf("\n\nCopy list = list2\n");
	//	list<int, SpyAllocator<int>>    list2 = list;

	//	DO(list.remove(20));
	//	DO(list.remove(40));
	//	DO(list.insert(std::find(list.begin(), list.end(), 30), 60));



	//	std::printf("\nPrint list:\n");
	//	for (list<int, SpyAllocator<int>>::iterator it = list.begin(); it != list.end(); ++it)
	//	{
	//		std::printf("%d ", *it);
	//	}
	//	std::printf("\n\n");

	//	std::printf("\nPrint list2:\n");
	//	for (list<int, SpyAllocator<int>>::iterator it = list2.begin(); it != list2.end(); ++it)
	//	{
	//		std::printf("%d ", *it);
	//	}
	//	std::printf("\n\n");

	//	std::printf("\nDestroy lists\n\n");
	//}

	//g_memorySpy.CheckLeaks();
}




/* String */
TEST_CASE("String", "[VectorList]")
{
	//{
	//	std::printf("\n=======Strings================\n");

	//	std::printf("Sizeof String : %llu\n", sizeof(string));

	//	{
	//		DO(string s);
	//		std::printf("Length of s : %llu\n", s.length());
	//	}

	//	{
	//		DO(string s = "Moins de 16 car");
	//		std::printf("Length of s : %llu\n", s.length());
	//	}

	//	{
	//		DO(string s = "Plus de 16 car, 27 au total");
	//		std::printf("Length of s : %llu\n", s.length());
	//	}

	//	{
	//		DO(string s = "Plus de 32 car, 34 pour etre exact");
	//		std::printf("Length of s : %llu\n", s.length());
	//	}

	//	{
	//		DO(string s = "Plus de 48 car, 51 pour etre exact, bon ca suffit ?");
	//		std::printf("Length of s : %llu\n", s.length());
	//	}

	//	{
	//		DO(string s1 = "toto est vraiment une personne incroyable");
	//		DO(string s2 = s1);
	//		DO(s1[1] = 'a');
	//		DO(s1[3] = 'a');
	//		std::printf("s1 : %s\n", s1.c_str());
	//		std::printf("s2 : %s\n", s2.c_str());
	//		DO(s2 = s1);
	//		DO(s2[3] = 'i');
	//		std::printf("s1 : %s\n", s1.c_str());
	//		std::printf("s2 : %s\n", s2.c_str());
	//	}

	//	DO(string s1 = "Bonjour");
	//	DO(string s2 = " le monde !");
	//	DO(string s3 = s1 + s2);
	//	std::printf("s3 : %s\n", s3.c_str());


	//	std::printf("\nDestroy vector\n\n");
	//}


	//g_memorySpy.CheckLeaks();
}










TEST_CASE("STD_WarningTest", "[!mayfail]")
{
#if USE_STD
	std::printf("!!!!!!!!!!! WARNING !!!!!!!!!!!\nYou're using the standard containers. Set USE_STD to 0 to test your own !\n");
#endif

	CHECK(!USE_STD);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
