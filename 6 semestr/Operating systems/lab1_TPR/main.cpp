#include <iostream>
#include <list>
#include <iterator>
//#include <algorithm>

using namespace std;


struct A {
    int Q1;
    int Q2;
};

//Функція порівняння Парето
bool FP(A a,A b) {
	if((a.Q1<b.Q1)||(a.Q2<b.Q2)) return false;
	if((a.Q1>b.Q1)||(a.Q2>b.Q2)) return true;
	return false;
}

//Функція порівняння Слейтера
bool FS(A a,A b) {
	if((a.Q1<=b.Q1)||(a.Q2<=b.Q2)) return false;
	return true;
}

int main() {
    // cout << "Hello world!" << endl;
    A List[]={{8,3},{8,6},{7, 7},{1,5},{9,3} };

    list<A> PList(List, List + 5);

    for (list<A>::iterator i = PList.begin(); i != PList.end(); ) {
		for (list<A>::iterator j = i; j!= PList.end(); ) {
			if(FS(*i,*j)) {
                j=PList.erase(j);
			}
			else {
				if(FS(*j,*i)) {
                    i=PList.erase(i);
                    break;
                }
				if(j == PList.back() - 1 ) {
					i++;
                    break;
				}
				else{
					j++;
				}
			}
		}
	}
    return 0;
}


