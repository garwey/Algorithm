#include "BST.h"
#include <iostream>
using namespace std;
void test(){
	int a = 6;
	const int *p = &a;
	a = 3;
	cout << *p << endl;
}

void main(){
	test();
	system("pause");
}