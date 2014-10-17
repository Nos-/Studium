#include <iostream>
#include "Warteschlange.h"

int main() {
	Warteschlange<int>* MeineWs = new Warteschlange<int>;
	int a[]= {23, 42, 76};

	MeineWs -> push(&a[0]);
	MeineWs -> push(&a[1]);
	MeineWs -> push(&a[2]);

	for (int i=0; i< 3; i++) {
		std::cout<< *MeineWs -> getFirst() << std::endl;
		MeineWs -> pop();
	}
		
	return 0;
}
