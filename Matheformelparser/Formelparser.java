// import java.util.*;
import java.io.IOException;
import java.io.StreamTokenizer;
import java.io.StringReader;
import java.lang.Math;


/** Formelparser.java - ein Parser zum Auswerten arithmetischer Ausdrücke mittels Recursive-Descent-Parser, der auch rechnet
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
 * Expr -> Term (("+" | "-") Term)*
 * Term -> Fact (("*" | "/") Fact)*
 * Fact -> ("cos" | "sin" | "tan") Trig | Trig
 * Trig -> "(" Expr ")" | Number
 *
 * Aufgrund der verwendeten StreamTokenizer- Klasse sind Leerzeichen nach einigen Operatoren nötig aber auch Klammern können helfen.
 * * Minuszeichen vor Zahlen werden ansonsten als deren Vorzeichen angesehen. 
 * * Operatoren, die aus Buchstaben bestehen, werden sonst nicht richtig ausgewertet.
 * * Unäre Operatoren (z.B. sin) sollten mit Klammern verwendet werden
 * 
 * ### Legende zur Programmausgabe ###
 * 
 * Zur besseren Nachvollziehbarkeit des Programmablaufs lasse ich mir einige Debugausgaben anzeigen. Anhand dieser kann man gut die Struktur des entstehenden Parsebaumes erkennen. Hier nun ein (hoffentlich) selbsterklärendes Beispiel:
 * 
 * >Funktionsname(Übergabeparameter)
 * #Funktionsname: {Zwischenergebnis}
 * <Funktionsname= {Rückgabewert}
 */


public class Formelparser {
    private int lookahead;									/// Vorschau auf das nächste Token (TT_NUMBER, TT_EOF, TT_WORD)
    private StreamTokenizer tokenizer;						/// Hilfsobjekt zur Aufsplittung der Eingabe in einzelne Token
    int level = 0;											/// Verschachtelungstiefe (für Darstellung)

//    public class ParseException extends Exception {}		//* Funktioniert leider nicht

	/// Hilfsfunktion zur eingerückten Textausgabe (Einrückung ist proportional zu level)
	private void printIndented(String text) {
		String indentation = "";		
		for (int i=0; i<=level; i++) { indentation += "  "; }	//* elegantere Lösung finden
		System.out.println(indentation + text);
	}
    
//    private static String tokenToString(int token) {		//* im ursprünglichen Beispiel war diese Methode 'static', keine Ahnung warum
    private String tokenToString(int token) {
//		printIndented(">tokenToString(...)");
        if (token == StreamTokenizer.TT_NUMBER) { /* printIndented(">tokenToString(ZAHL); token={" + tokenizer.nval + "}"); printIndented("<tokenToString='ZAHL'"); */ return "ZAHL ={" + tokenizer.nval + "}"; }
        else if (token == StreamTokenizer.TT_EOF) { /* printIndented(">tokenToString(EOF)"); printIndented("<tokenToString='EOF'"); */ return "EOF"; }
        else if (token == StreamTokenizer.TT_WORD) { /* printIndented(">tokenToString(WORT); token={" + tokenizer.sval + "}"); printIndented("<tokenToString='WORT'"); */ return "WORT ={" + tokenizer.sval + "}"; }
        else { /* printIndented(">tokenToString(" + token + "); token={" + tokenizer.nval + "}"); printIndented("<tokenToString='" + String.valueOf((char)token) + "'"); */ return "SONDERZEICHEN ={" + String.valueOf((char)token) + "}"; }
    }
    
    private void next() throws IOException {
		level += 0; printIndented(">next()");
        lookahead = tokenizer.nextToken();    // kann sein: TT_EOF (Dateiende), TT_NUMBER (Zahl), TT_WORD (sonstiges)
        printIndented("<next; \tlookahead=" + tokenToString(lookahead)); level += 0;
    }
    
    private void match(int expected) throws IOException {
		printIndented(">match(" + expected + ")");
        if (lookahead != expected) {
            throw new IOException("Erwartet: '" + tokenToString(expected) + "', erhalten: '" + tokenToString(lookahead) + "'");    //* Exception auf spezifischere ParseException umbauen
        } else {
            next();
        }
        printIndented("<match");
    }


    /// Expr -> Term (("+" | "-") Term)*
    private double parseExpr() throws IOException {
		level += 1; printIndented(">parseExpr()");
        double v, w;
        int op;
        
        v = parseTerm();
        printIndented("#parseExpr: {" + v + "}");
        while ((op = lookahead) == '+' || op == '-') {
            printIndented("#parseExpr: {" + v + "}{" + (char)op + "}");
            next();
            w = parseTerm();
            printIndented("#parseExpr: {" + v + "}{" + (char)op + "}{" + w + "}");
            if (op == '+') {
				v += w;
			} else if (op == '-') {
				v -= w;
			}
        }
        printIndented("<parseExpr= {" + v + "}"); level -= 1;
        return v;
    }
    
    /// Term -> Fact (("*" | "/") Fact)*
    private double parseTerm() throws IOException {
		level += 1; printIndented(">parseTerm()");
        double v, w;
        int op;

        v = parseFact();
        printIndented("#parseTerm: {" + v + "}");
        while ((op = lookahead) == '*' || op == '/') {
            printIndented("#parseTerm: {" + v + "}{" + (char)op + "}");
            next();
            w = parseTerm();
            printIndented("#parseTerm: {" + v + "}{" + (char)op + "}{" + w + "}");
            if (op == '*') {
				v *= w;
			} else if (op == '/') {
				v /= w;
			}
        }
        printIndented("<parseTerm= {" + v + "}"); level -= 1;
        return v;
    }

	/// Fact -> ("cos" | "sin" | "tan") Trig | Trig
    private double parseFact() throws IOException {
		level += 1; printIndented(">parseFact()");
        double v, w;
        StringBuffer op = new StringBuffer();

        v = 0;
		if (lookahead == StreamTokenizer.TT_WORD) {
//			while (lookahead == StreamTokenizer.TT_WORD) {
				op.replace(0, 3, tokenizer.sval);
				if (op.toString().equals("cos") || op.toString().equals("sin") || op.toString().equals("tan")) {
					printIndented("#parseFact: {" + op.toString() + "}");
					next();
					w = parseTrig();
					printIndented("#parseFact: {" + op + "}{" + w + "}");
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
        printIndented("<parseFact= {" + v + "}"); level -= 1;
        return v;
    }

    /// Trig -> "(" Expr ")" | Number
    private double parseTrig() throws IOException {
		level += 1; printIndented(">parseTrig()");
        double v = 0.0;
        
        if (lookahead == '(') {
            match('(');
            v = parseExpr();
			printIndented("#parseTrig: ( {" + v + "} ) ");
            match(')');
        } else if (lookahead == StreamTokenizer.TT_NUMBER) {
			v = tokenizer.nval;
            next();
        } else {
            throw new IOException("Unerwartetes Symbol: " + tokenToString(lookahead));
        }
        printIndented("<parseTrig= {" + v + "}"); level -= 1;
        return v;
    }
    
    public double parse(String s) throws IOException {
		level += 1; printIndented(">parse(" + s + ")");
		double v;
        StringReader r = new StringReader(s);
        tokenizer = new StreamTokenizer(r);
        tokenizer.ordinaryChar('/'); // Der Schrägstrich ist kein Kommentarzeichen

        next();
        v = parseExpr();
        if (lookahead != StreamTokenizer.TT_EOF) {
            throw new IOException("Unerwartetes Symbol '" + (char)lookahead + "'");
        } else {
            printIndented("Der arithmetische Ausdruck ist in Ordnung und ergibt: " + v);
        }
        printIndented("<parse= {" + v + "}"); level -= 1; 
        return v;
    }

    
    public static void main (String args[]) throws IOException {
        Formelparser fp = new Formelparser();
        double result;
        
        if (args.length < 1) {
            System.err.println("Verwendung: java Formelparser\"<Ausdruck>\"");
            return;											//* Hier sollte ein Fehlercode zurückgeben werden
        }
        
        try {
            result = fp.parse(args[0]);
            System.out.println();
            System.out.println(args[0] + "=" + Double.toString(result));
            
        } catch (IOException e1) {
            System.err.println("!!! Es ist ein Fehler aufgetreten: " + e1.getMessage() + " !!!");
            //* Hier sollte ein Fehlercode zurückgeben werden
        } finally {
			System.out.println();
		}
    }
}

