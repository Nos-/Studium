/// Diese Programm dient dem Ausprobieren einer Funktionsüberladung.

#include <iostream>
#include <cstdlib>

using namespace std;

// Variante mit Integer und Rest
// int divide(int& x, int& y, int & Rest) {					// Alternative Variante zum Ausprobieren
int divide(int x, int y, int & Rest) {
	Rest = x % y;
	return (x / y);
}

// Variante mit Double und ohne Rest
double divide(int x, int y) {
	return ((double)x / (double)y);
}


int main() {
	int rest, quotient_Int;
	double quotient_Double;
//	int x=10, y=3;

//	quotient_Int = divide(x, y, rest); 
	quotient_Int = divide(10,3,rest); 
	cout <<10<<"/"<<3<<"="<<quotient_Int<<" Rest="<<rest<<endl;
//	quotient_Double = divide(x, y); 
	quotient_Double = divide(10,3);
	cout <<10<<"/"<<3<<"="<<quotient_Double<<endl;
		
	return 0;
}
