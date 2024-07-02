
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>


struct A
{
	static int val;
	
	void operator()(int &i)
	{
		i+=val;
		val--;
	}
};


int A::val = -1; //jak inicjalizuje pamiętać o tym że nazwe typu muszę dać przed




int main() {
	std::list<int> coll(11); //zainicjalizowana zerami
	std::for_each( std::begin(coll), std::end(coll), A());
	std::copy( coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout,"; "));
	return 0;
}
//to ma się wyświetlić:
// -1; -2; -3; -4; -5; -6; -7; -8; -9; -10; -11;
