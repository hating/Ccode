#include <iostream>
#include "person.h"
#include "Date.h"
using namespace std;
int main()
{
	Person person(111223333, 1970, 5, 3);
	cout << "Birth year before the change is " << person.getBirthDate()->getYear() << endl;
	Date *pDate = person.getBirthDate();
	pDate->setYear(2015);
	cout << "Birth year after the change is " << person.getBirthDate()->getYear() << endl;
	return 0;
}
