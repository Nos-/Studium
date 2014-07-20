// Includes - auf die Reihenfolge kommts an!
#include <iostream>
#include <cstring>
#include <typeinfo>
#include <cmath>

//~ import java.io.IOException;
//~ import java.io.StreamTokenizer;
//~ import java.io.StringReader;
//~ import java.lang.Math;

using namespace std;

#define FALSE 0
#define TRUE  1

/** Formelparser.cpp - Portierung des gleichnamigen Java-Programms: ein Parser zum Auswerten arithmetischer Ausdrücke mittels Recursive-Descent-Parser, der auch rechnet.
 *
 * @author Copyright 2014 Norman nospam.schwirz at freenet.de
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 * ### Funktionsweise ###
 *
 * Der gegebene Ausdruck wird mittels folgender Grammatik geparst:
 *
 * 1. Expr -> Term (("+" | "-") Term)*
 * 2. Term -> Fact (("*" | "/") Fact)*
 * 3. Fact -> (("cos" | "sin" | "tan") Trig)* | Trig
 * 4. Trig -> "(" Expr ")" | Number
 * 5. Number ...
 *
 * Bte sämtliche Operatoren und Operanden durch Leerzeichen trennen!
 * Also z.B.: 1 + 2 * -3
 */

// GLOBALE DEKLARATIONEN

class Formelparser {
    private:
		int lookahead;										///< Vorschau auf Typ des nächsten Tokens
		StreamTokenizer tokenizer;						///< Hilfsobjekt zur Aufsplittung der Eingabe in einzelne Token

		string tokenToString(int token);
		void next();
		void match(int expected);
		double parseExpr();
		double parseTerm();
		double parseFact();
		double parseTrig();

    public:
		int isValid;									///< Gibt an, ob der zuletzt geparste Ausdruck gültig gewesen ist
		double parseResult;								///< enthält das Ergebnis des zuletzt geparsten Ausdruckes \sa isValid()

		Formelparser();
		double parse(string s);

//    public class ParseException extends Exception {}		//* Funktioniert leider nicht
};


// UNTERPROGRAMME

/// Hilfsfunktion für Debugausgaben
string Formelparser::tokenToString(int token) {
	if (token == StreamTokenizer.TT_NUMBER) { return "ZAHL ={" + tokenizer.nval + "}"; }
	else if (token == StreamTokenizer.TT_EOF) { return "EOF"; }
	else if (token == StreamTokenizer.TT_WORD) { return "WORT ={" + tokenizer.sval + "}"; }
	else { return "SONDERZEICHEN ={" + string.valueOf((char)token) + "}"; }
}

/// Liest das nächste Token ein
void Formelparser::next() {
	lookahead = tokenizer.nextToken();    // kann sein: TT_EOF (Dateiende), TT_NUMBER (Zahl), TT_WORD (sonstiges)
}

/// Prüft, ob das nächste Token das erwartete ist
void Formelparser::match(int expected) {
	if (lookahead != expected) {
		throw "Erwartet: '" + tokenToString(expected) + "', erhalten: '" + tokenToString(lookahead) + "'";    //* Exception auf spezifischere ParseException umbauen
	} else {
		next();
	}
}


/// Parst die Ableitungsregel: Expr -> Term (("+" | "-") Term)*
double Formelparser::parseExpr() {
	double v, w;
	int op;
	
	cout << endl<<"#parseExpr:";
	v = parseTerm();
	while ((op = lookahead) == '+' || op == '-') {
		next();
		w = parseTerm();
		cout << " " << v << " " << op << " " << w << " ";
		if (op == '+') {
			v += w;
		} else if (op == '-') {
			v -= w;
		}
		cout << "= " << v << " ";
	}
	cout<<endl;
	return v;
}

/// Parst die Ableitungsregel: Term -> Fact (("*" | "/") Fact)*
double Formelparser::parseTerm() {
	double v, w;
	int op;

	cout << endl<<"#parseTerm:";
	v = parseFact();
	while ((op = lookahead) == '*' || op == '/') {
//            cout << " " << v << " " << (char)op << " ";
		next();
		w = parseTerm();
		cout << " " << v << " " << op << " " << w << " ";
		if (op == '*') {
			v *= w;
		} else if (op == '/') {
			v /= w;
		}
	}
	cout<<endl<<"= " << v << " ";
	return v;
}

/// Parst die Ableitungsregel: Fact -> (("c" | "s" | "t") Trig)* | Trig
double Formelparser::parseFact() {
	double v, w;
	StringBuffer op = new StringBuffer();

	v = 0;
	if (lookahead == StreamTokenizer.TT_WORD) {
//			while (lookahead == StreamTokenizer.TT_WORD) {
			op.replace(0, 3, tokenizer.sval);
			if (op='c' || op='s' || op='t') {	//* Stringvergleich
				cout << endl<<"#parseFact: ";
				next();
				w = parseFact();
				cout << op << " " << w << " ";
				if (op='c') {
					v = cos(w);
				} else if (op='s') {
					v = sin(w);
				} else if (op='t') {
					v = tan(w);
				}
			} else {
				throw "Unerwartetes Symbol: " + tokenToString(lookahead);
			}
//			}
	} else {
		v = parseTrig();
	}
	cout<<endl<<"= " << v << " "; 
	return v;
}

/// Parst die Ableitungsregel: Trig -> "(" Expr ")" | Number
double Formelparser::parseTrig() {
	double v = 0.0;

	cout << endl<<"#parseTrig: ";        
	if (lookahead == '(') {
		match('(');
		v = parseExpr();
		cout << " ( " << v << " ) ";
		match(')');
	} else if (lookahead == StreamTokenizer.TT_NUMBER) {
		v = tokenizer.nval;
		next();
	} else {
		throw "Unerwartetes Symbol: " + tokenToString(lookahead);
	}
	cout<<endl<<"=" << v << " ";
	return v;
}

/// Parst übergebenen Ausdruck und gibt dessen Ergebnis zurrück
double Formelparser::parse(string s) {
	cout<<endl<<"parse(" << s << ")";
	double v;
	StringReader r = new StringReader(s);
	tokenizer = new StreamTokenizer(r);
	tokenizer.ordinaryChar('/'); // Der Schrägstrich ist kein Kommentarzeichen

	next();
	v = parseExpr();
	if (lookahead != StreamTokenizer.TT_EOF) {
		isValid=FALSE;
		parseResult = 0;
		throw "Unerwartetes Symbol '" + (char)lookahead + "'";
	} else {
//            cout << endl<<"Der arithmetische Ausdruck ist in Ordnung und ergibt: " << v;
		isValid=TRUE;
		parseResult=v;
	}
	return v;
}


/// Initialisiert die Membervariablen
Formelparser::Formelparser() {
	isValid = FALSE;
	parseResult = 0;
}



/// Ruft Parse() mit den Kommandozeilenparametern auf und meldet aufgetretene Fehler.
int main (int argc, char* argv[]) {
	Formelparser fp = new Formelparser();
	double result;
	
	if (argc <= 1) {
		cerr << endl << "Verwendung: Formelparser.out\"<Ausdruck>\"";
		cerr << endl << "Unterstützte Rechenoperationen: + - * / cos() sin() tan() einschließlich Klammern '()'.";
		return 1;											//* Hier sollte ein Fehlercode zurückgeben werden
	}
	
	try {
		cout<<endl;
		result = fp.parse(argv[0]);
		cout<<endl;
		cout<<endl<<argv[0] << " = " << result;
		return 0;
		
	} catch (const char* p) {
		cerr << endl << "!!! Es ist ein Fehler aufgetreten: " << p << " !!!";
		return 2;	//* Hier sollte ein Fehlercode zurückgeben werden
	}
}
