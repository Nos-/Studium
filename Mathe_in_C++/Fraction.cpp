/** Mathe für Informatiker - Eine Klasse für gebrochenrationale Zahlen in C++ (Lern-Bsp.)
 * 
 * @Author s70341@htw-dresden.de, 2014
 */
// Ohne Gewähr! Nutzung auf eigene Gefahr!


#include <iostream>
#include <iomanip>

using namespace std;

/// Gebrochenrationale Zahlen als C++ Klasse incl. Grundrechenoperationen
class Fraction
{
	private:

		long Numerator;							 			///< Zähler (intern)
		long Denom;											///< Nenner (intern)

	public:

		Fraction() {Numerator=0; Denom=1;}					///< überladener Konstruktor mit Standardwerten (0/1=0)
		Fraction(long Num, long Den);						///< Konstruktor
		long getNumerator() {return Numerator;}				///< Gibt den Zähler zurück
		long getDenom() {return Denom;}						///< Gibt den Nenner zurück
		void Display();										///< Ausgabe des Bruches
		float getValue();									///< Gibt den Bruch als Dezimalbruch zurück
		Fraction getReciprocal();							///< Gibt den Kehrwert des Bruches (das Reziproke) zurück

		// Rechenoperationen
		Fraction add(const Fraction & others);				///< 2 Brüche miteinander addieren
		Fraction substract(const Fraction & others);		///< 2 Brüche voneinander substrahieren
		Fraction multiply(const Fraction & others);			///< 2 Brüche miteinander multiplizieren
		Fraction divide(const Fraction & others);			///< 2 Brüche durcheinander dividieren

	private:
	
		// interne Hilfsfunktionen
		long min(long a, long b);							///< Gibt den kleineren der beiden Werten zurück (intern)
		long ggt(long first, long sec);						///< Größten gemeinsamen Teiler (kurz: ggT; wurde auch *gcf* genannt) zurückgeben (intern)
		long kgv(long first, long sec);						///< Kleinstes gemeinsames Vielfaches (kurz: kgV) zurückgeben (intern)
};

/// Konstruktor, der den neuen Bruch auch gleich kürzt.
Fraction::Fraction(long Num, long Den)
{
	Den<0 ? (Den=-Den,Num=-Num) : (Num=Num);				// Bsp. des ?-Operators: `<Bedingung> ? <Aktion> : <Ansonsten-Aktion>;`
	long ggt1 = ggt(Num, Den);
	Numerator = Num / ggt1;
	Denom = Den / ggt1;
}

//Hillfsfunktionen
/// Gibt den Größten gemeinsamen Teiler (kurz: ggT) zurück. TODO: Auf *EUKLIDischen Algorithmus* umstellen.
long Fraction::ggt(
  long first,												///< 1. Teil
  long sec											 		///< 2. Teil
)
{
	long l, m = min(first, sec); // /2;
	for (l=m; l > 0; l--)
	{
		if ((first % l == 0) && (sec % l == 0)) return l;
	}
	return 1;
}

long Fraction::kgv(
  long first,
  long sec
  ) {
	return (first * sec / ggt(first, sec));					// TODO: Ggf. nochmal kontrollieren
}

long Fraction::min(
  long a,
  long b
  ) {
	if (a < b) return a;
	else return b;
}

void Fraction::Display()
{
	cout << Numerator << " / " << Denom;
}

float Fraction::getValue()
{
	return Numerator / Denom;
}

Fraction Fraction::getReciprocal()
{
	Fraction reciprocal(Denom, Numerator);
	return reciprocal;
}

// Rechenoperationen
/// 2 Brüche miteinander addieren
Fraction Fraction::add(
  const Fraction & others									///< der 2. Summand
  ) {
	long sum_num    = (Numerator * others.getDenom()) + (others.getNumerator() * Denom);	/// 1. Zähler mit Nenner des jeweils anderen Bruches erweitern und mit dessen Zähler addieren.
	long main_denom = Denom * others.getDenom();			/// 2. Haupnenner bilden (=Nenner1 * Nenner2)
	Fraction Sum(sum_num, main_denom);
	return Sum;
}

Fraction Fraction::substract(
  const Fraction & others
  ) {
	long dif_num    = (Numerator * others.getDenom()) - (others.getNumerator() * Denom);	/// 1. Zähler mit Nenner des jeweils anderen Bruches erweitern und desses Zähler substrahieren.
	long main_denom = Denom * others.getDenom();			/// 2. Haupnenner bilden (=Nenner1 * Nenner2)
	Fraction Difference(dif_num, main_denom);
	return Difference;
}

Fraction Fraction::multiply(
  const Fraction & others
  ) {
	long prod_num   = Numerator * others.getNumerator();	/// Zähler = Zähler1 * Zähler2
	long prod_denom = Denom * others.getDenom();			/// Nenner = Nenner1 * Nenner2
	Fraction Product(prod_num, prod_denom);
	return Product;
}

Fraction Fraction::divide(
  const Fraction & others
  ) {
	return multiply(others.getReciprocal());				/// Bruch1 / Bruch2 = Bruch1 * Reziproke(Bruch2)
}


// Hauptprogramm
int main ()
{
	Fraction Frac1, Frac2(4, 8), Frac3(5, 4);
	
	cout << "Bruchrechnen mit C++" << endl;
	cout << "vorher:" << endl;
	cout << "Frac1=";
	Frac1.Display();
	cout << endl << "Frac2=";
	Frac2.Display();
	cout << endl << "Frac3=";
	Frac3.Display();
	cout << endl;

	Frac1.add(Frac2);
	Frac3.multiply(Frac1);
	Frac3.divide(Frac2);

	cout << "nachher:" << endl;
	cout << "Frac1=";
	Frac1.Display();
	cout << endl << "Frac2=";
	Frac2.Display();
	cout << endl << "Frac3=";
	Frac3.Display();
	cout << endl;
	
}
