// Includes - auf die Reihenfolge kommts an!
# include <stdio.h>
# include <stdlib.h>

//~ import java.io.IOException;
//~ import java.io.StreamTokenizer;
//~ import java.io.StringReader;
//~ import java.lang.Math;

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

class FormelparserMinimal {
    private:
		int lookahead;										///< Vorschau auf Typ des nächsten Tokens
		StreamTokenizer tokenizer;						///< Hilfsobjekt zur Aufsplittung der Eingabe in einzelne Token

		String tokenToString(int token);
		void next() throws IOException;
		void match(int expected) throws IOException;
		double parseExpr() throws IOException;
		double parseTerm() throws IOException;
		double parseFact() throws IOException;
		double parseTrig() throws IOException;

    public:
		int isValid;									///< Gibt an, ob der zuletzt geparste Ausdruck gültig gewesen ist
		double parseResult;								///< enthält das Ergebnis des zuletzt geparsten Ausdruckes \sa isValid()

		void FormelparserMinimal();
		double parse(String s) throws IOException;

//    public class ParseException extends Exception {}		//* Funktioniert leider nicht
};


// UNTERPROGRAMME

/// Hilfsfunktion für Debugausgaben
String tokenToString(int token) {
	if (token == StreamTokenizer.TT_NUMBER) { return "ZAHL ={" + tokenizer.nval + "}"; }
	else if (token == StreamTokenizer.TT_EOF) { return "EOF"; }
	else if (token == StreamTokenizer.TT_WORD) { return "WORT ={" + tokenizer.sval + "}"; }
	else { return "SONDERZEICHEN ={" + String.valueOf((char)token) + "}"; }
}

/// Liest das nächste Token ein
void next() throws IOException {
	lookahead = tokenizer.nextToken();    // kann sein: TT_EOF (Dateiende), TT_NUMBER (Zahl), TT_WORD (sonstiges)
}

/// Prüft, ob das nächste Token das erwartete ist
void match(int expected) throws IOException {
	if (lookahead != expected) {
		throw new IOException("Erwartet: '" + tokenToString(expected) + "', erhalten: '" + tokenToString(lookahead) + "'");    //* Exception auf spezifischere ParseException umbauen
	} else {
		next();
	}
}


/// Parst die Ableitungsregel: Expr -> Term (("+" | "-") Term)*
double parseExpr() throws IOException {
	double v, w;
	int op;
	
	System.out.print("\n#parseExpr:");
	v = parseTerm();
	while ((op = lookahead) == '+' || op == '-') {
		next();
		w = parseTerm();
		System.out.print(" " + v + " " + (char)op + " " + w + " ");
		if (op == '+') {
			v += w;
		} else if (op == '-') {
			v -= w;
		}
		System.out.print("= " + v + " ");
	}
	System.out.println("");
	return v;
}

/// Parst die Ableitungsregel: Term -> Fact (("*" | "/") Fact)*
double parseTerm() throws IOException {
	double v, w;
	int op;

	System.out.print("\n#parseTerm:");
	v = parseFact();
	while ((op = lookahead) == '*' || op == '/') {
//            System.out.print(" " + v + " " + (char)op + " ");
		next();
		w = parseTerm();
		System.out.print(" " + v + " " + (char)op + " " + w + " ");
		if (op == '*') {
			v *= w;
		} else if (op == '/') {
			v /= w;
		}
	}
	System.out.println("= " + v + " ");
	return v;
}

/// Parst die Ableitungsregel: Fact -> (("cos" | "sin" | "tan") Trig)* | Trig
double parseFact() throws IOException {
	double v, w;
	StringBuffer op = new StringBuffer();

	v = 0;
	if (lookahead == StreamTokenizer.TT_WORD) {
//			while (lookahead == StreamTokenizer.TT_WORD) {
			op.replace(0, 3, tokenizer.sval);
			if (op.toString().equals("cos") || op.toString().equals("sin") || op.toString().equals("tan")) {
				System.out.print("\n#parseFact: ");
				next();
				w = parseFact();
				System.out.print(op + " " + w + " ");
				if (op.toString().equals("cos")) {
					v = java.lang.Math.cos(w);
				} else if (op.toString().equals("sin")) {
					v = java.lang.Math.sin(w);
				} else if (op.toString().equals("tan")) {
					v = java.lang.Math.tan(w);
				}
			} else {
				throw new IOException("Unerwartetes Symbol: " + tokenToString(lookahead));
			}
//			}
	} else {
		v = parseTrig();
	}
	System.out.println("= " + v + " "); 
	return v;
}

/// Parst die Ableitungsregel: Trig -> "(" Expr ")" | Number
double parseTrig() throws IOException {
	double v = 0.0;

	System.out.print("\n#parseTrig: ");        
	if (lookahead == '(') {
		match('(');
		v = parseExpr();
		System.out.print(" ( " + v + " ) ");
		match(')');
	} else if (lookahead == StreamTokenizer.TT_NUMBER) {
		v = tokenizer.nval;
		next();
	} else {
		throw new IOException("Unerwartetes Symbol: " + tokenToString(lookahead));
	}
	System.out.println("=" + v + " ");
	return v;
}

/// Parst übergebenen Ausdruck und gibt dessen Ergebnis zurrück
double parse(String s) throws IOException {
	System.out.println("parse(" + s + ")");
	double v;
	StringReader r = new StringReader(s);
	tokenizer = new StreamTokenizer(r);
	tokenizer.ordinaryChar('/'); // Der Schrägstrich ist kein Kommentarzeichen

	next();
	v = parseExpr();
	if (lookahead != StreamTokenizer.TT_EOF) {
		isValid=FALSE;
		parseResult = 0;
		throw new IOException("Unerwartetes Symbol '" + (char)lookahead + "'");
	} else {
//            System.out.print("\nDer arithmetische Ausdruck ist in Ordnung und ergibt: " + v);
		isValid=TRUE;
		parseResult=v;
	}
	return v;
}


/// Initialisiert die Membervariablen
void FormelparserMinimal() {
	isValid = FALSE;
	parseResult = 0;
}



/// Ruft Parse() mit den Kommandozeilenparametern auf und meldet aufgetretene Fehler.
void main (String args[]) throws IOException {
	FormelparserMinimal fp = new FormelparserMinimal();
	double result;
	
	if (args.length < 1) {
		System.err.println("Verwendung: java Formelparser\"<Ausdruck>\"");
		System.err.println("Unterstützte Rechenoperationen: + - * / cos() sin() tan() einschließlich Klammern '()'.");
		return;											//* Hier sollte ein Fehlercode zurückgeben werden
	}
	
	try {
		System.out.println();
		result = fp.parse(args[0]);
		System.out.println();
		System.out.println(args[0] + " = " + Double.toString(result));
		
	} catch (IOException e1) {
		System.err.println("!!! Es ist ein Fehler aufgetreten: " + e1.getMessage() + " !!!");
		//* Hier sollte ein Fehlercode zurückgeben werden
	} finally {
//            System.out.println(args[0] + "=" + fp.parseResult + "; gültig: "+ fp.isValid);
		System.out.println();
	}
}
