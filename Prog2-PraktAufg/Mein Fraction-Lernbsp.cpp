	/// Mathe für Informatiker - Eine Klasse für gebrochenrationale Zahlen in C++ (Lern-Bsp.)

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
			long getNumerator() const {return Numerator;}		///< Gibt den Zähler zurück
			long getDenom() const {return Denom;}				///< Gibt den Nenner zurück
			void Display() const;								///< Ausgabe des Bruches
			float getValue();									///< Gibt den Bruch als Dezimalbruch zurück
			~Fraction(){Numerator=0;Denom=0;};					///< Der Destruktor

			// Rechenoperationen
			Fraction add(const Fraction & others) const;		///< 2 Brüche miteinander addieren
			Fraction operator+(const Fraction & others) const;	///< 2 Brüche miteinander addieren per *Operatorenüberladung* (Hiermit geht nun auch etwas wie: `BruchA + BruchB`)
			Fraction substract(const Fraction & others) const;	///< 2 Brüche voneinander substrahieren

			/* Lust selber zu programmieren?
			 * Ja, dann ergänze doch noch die Rechenoperationen für Multiplikation und Division...
			 */

		private:
		
			// interne Hilfsfunktionen
			long min(long a, long b) const;						///< Gibt den kleineren der beiden Werten zurück (intern)
			long ggt(long first, long sec) const;				///< Größten gemeinsamen Teiler (kurz: ggT; wurde auch *gcf* genannt) zurückgeben (intern)
	};

	/// Konstruktor, der den neuen Bruch auch gleich kürzt
	Fraction::Fraction(long Num, long Den)
	{	
		Numerator = Num;

		// Falls der Nenner 0 ist, ihn auf 1 setzen
		Denom = Den ? Den : 1;	//! ggf. wegen Fehlermeldung überlegen

		// Vorzeichen prüfen
		Denom<0 ? (Denom=-Denom,Numerator=-Numerator) : (Numerator=Numerator);				// Bsp. des ?-Operators: `<Bedingung> ? <Aktion> : <Ansonsten-Aktion>;`

		// Bruch kürzen
		long ggt1 = ggt(Numerator, Denom);
		if (ggt1 > 1) {
			Numerator /= ggt1;
			Denom /= ggt1;
		}
	}

	//Hilfsfunktionen

	/// Gibt den Größten gemeinsamen Teiler (kurz: ggT) zurück.
	long Fraction :: ggt(long first, long sec) const
	{
		int tmp;

		// Vorzeichen entfernen
		if (first < 0)first=-first;
		if (sec< 0)sec=-sec;

		// die eigentl. Berechn.
		while (sec)
		{
			tmp = first % sec;
			first   = sec;
			sec  = tmp;
		}
		
		return first;
	}

	long Fraction::min(
	  long a,
	  long b
	  ) const {
		if (a < b) return a;
		else return b;
	}

	/// Sollte der auszugebende Bruch ganzzahlig sein, wird nur der Zähler ausgegeben.
	void Fraction::Display()const
	{
		Denom !=1 ? (cout << Numerator << " / " << Denom) : (cout << Numerator);
	}

	float Fraction::getValue()
	{
		return (float)Numerator / (float)Denom;						// gecastet wegen ganzzahliger Division, die hier nutzlos wäre
	}

	// Rechenoperationen

	/// 2 Brüche miteinander addieren
	Fraction Fraction::add(
	  const Fraction & others									///< der 2. Summand
	  ) const {
		long ggt1 = ggt(Denom, others.Denom);
		//~ long sum_num    = (Numerator * others.getDenom()) + (others.getNumerator() * Denom);	/// 1. Zähler mit Nenner des jeweils anderen Bruches erweitern und mit dessen Zähler addieren.
		//~ long main_denom = Denom * others.getDenom();			/// 2. Haupnenner bilden (=Nenner1 * Nenner2)
		long Mult1  = Denom / ggt1;
		long Mult2  = others.Denom / ggt1;
		long NumRes = Numerator * Mult2 + others.Numerator * Mult1;
		long DenRes = Denom * Mult2;	
		//~ Fraction Sum(sum_num, main_denom);
		//~ return Sum;
		return Fraction(NumRes, DenRes);
	}

	/// Brüche addieren per *Operatorenüberladung* (Also Bruch1 + Bruch2)
	Fraction Fraction::operator+(const Fraction & others) const
	{
		long ggt1 = ggt(Denom, others.Denom);
		//~ long sum_num    = (Numerator * others.getDenom()) + (others.getNumerator() * Denom);	/// 1. Zähler mit Nenner des jeweils anderen Bruches erweitern und mit dessen Zähler addieren.
		//~ long main_denom = Denom * others.getDenom();			/// 2. Haupnenner bilden (=Nenner1 * Nenner2)
		long Mult1  = Denom / ggt1;
		long Mult2  = others.Denom / ggt1;
		long NumRes = Numerator * Mult2 + others.Numerator * Mult1;
		long DenRes = Denom * Mult2;	
		//~ Fraction Sum(sum_num, main_denom);
		//~ return Sum;
		return Fraction(NumRes, DenRes);	
	}

	Fraction Fraction::substract(
	  const Fraction & others
	  ) const {

		/** Nur Übung macht den Meister, sagt man. ;-)
		 * Implementiere Diese Methode daher selbst!
		 * 
		 * Vielleicht hilft dir ein Blick in die Additionsmethode...
		 */

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

		Frac1 = Frac1.add(Frac2);
		//~ Frac3 = Frac3.multiply(Frac1);
		//~ Frac3 = Frac3.divide(Frac2);

		cout << "nachher:" << endl;
		cout << "Frac1=";
		Frac1.Display();
		cout << endl << "Frac2=";
		Frac2.Display();
		cout << endl << "Frac3=";
		Frac3.Display();
		cout << endl;

		cout << "...und nun per Operatorenüberladung:" << endl;
		Frac1 = Frac2+Frac3;
		cout << "Frac3=";
		Frac1.Display();
		cout << endl << "Als Dezimalbruch:" << Frac1.getValue() << endl;
	}
