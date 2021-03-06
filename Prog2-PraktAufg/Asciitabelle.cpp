//#include <stdio.h>
#include <iostream>
//#include <ctype.h>

using namespace std;

int main()
{
  int    i,j;

  cout << "Content-Type: text/html";
  cout << "\n\n";
  /*cout <<("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2//EN\">");*/
  cout << "<html><head><title>CGI-Script - ASCII Codetabelle</title></head>\n";
  cout << "<body><h2><hr>\n";
  cout << "<pre>\n";

  for (i=0; i<4; i++) cout <<"|dec hex Char ";
  cout << "|\n";
  for (i=0; i<32; i ++)
  {
    cout <<"\n| ";
    for (j=0; j < 128; j += 128/4)
    {
      cout <<i+j;
      if (isgraph(j+i)) cout << " " << char(j+i) << " | ";
      else cout <<"  .  | ";
    }
  }
  cout <<"</pre><hr>";
  cout <<"<a href=\"http://www.....de/~beck/a.beck.html\">A. Beck</A> <p>";
  cout <<"</body>\n";
  cout <<"</html>\n";
  return 0;
}



//#include <iostream>
//#include <iomanip>

//using namespace std;


////~ Beispielausgabe der Aufgabenstellung:
////~
////~ Content-Type: text/html
////~ 
////~ <html><head><title>CGI-Script - ASCII Codetabelle</title></head>
////~ 
////~ <body><h2><hr>
////~ 
////~ <pre>
////~ 
////~ |dec hex Char |dec hex Char |dec hex Char |dec hex Char |
////~ 
////~ |   0  0   .  |  32 20   .  |  64 40   @  |  96 60   `  |
////~ |   1  1   .  |  33 21   !  |  65 41   A  |  97 61   a  |
////~ |   2  2   .  |  34 22   "  |  66 42   B  |  98 62   b  |
////~ |   3  3   .  |  35 23   #  |  67 43   C  |  99 63   c  |
////~ |   4  4   .  |  36 24   $  |  68 44   D  | 100 64   d  |
////~ |   5  5   .  |  37 25   %  |  69 45   E  | 101 65   e  |
////~ |   6  6   .  |  38 26   &  |  70 46   F  | 102 66   f  |
////~ |   7  7   .  |  39 27   '  |  71 47   G  | 103 67   g  |
////~ |   8  8   .  |  40 28   (  |  72 48   H  | 104 68   h  |
////~ |   9  9   .  |  41 29   )  |  73 49   I  | 105 69   i  |
////~ |  10  A   .  |  42 2A   *  |  74 4A   J  | 106 6A   j  |
////~ |  11  B   .  |  43 2B   +  |  75 4B   K  | 107 6B   k  |
////~ |  12  C   .  |  44 2C   ,  |  76 4C   L  | 108 6C   l  |
////~ |  13  D   .  |  45 2D   -  |  77 4D   M  | 109 6D   m  |
////~ |  14  E   .  |  46 2E   .  |  78 4E   N  | 110 6E   n  |
////~ |  15  F   .  |  47 2F   /  |  79 4F   O  | 111 6F   o  |
////~ |  16 10   .  |  48 30   0  |  80 50   P  | 112 70   p  |
////~ |  17 11   .  |  49 31   1  |  81 51   Q  | 113 71   q  |
////~ |  18 12   .  |  50 32   2  |  82 52   R  | 114 72   r  |
////~ |  19 13   .  |  51 33   3  |  83 53   S  | 115 73   s  |
////~ |  20 14   .  |  52 34   4  |  84 54   T  | 116 74   t  |
////~ |  21 15   .  |  53 35   5  |  85 55   U  | 117 75   u  |
////~ |  22 16   .  |  54 36   6  |  86 56   V  | 118 76   v  |
////~ |  23 17   .  |  55 37   7  |  87 57   W  | 119 77   w  |
////~ |  24 18   .  |  56 38   8  |  88 58   X  | 120 78   x  |
////~ |  25 19   .  |  57 39   9  |  89 59   Y  | 121 79   y  |
////~ |  26 1A   .  |  58 3A   :  |  90 5A   Z  | 122 7A   z  |
////~ |  27 1B   .  |  59 3B   ;  |  91 5B   [  | 123 7B   {  |
////~ |  28 1C   .  |  60 3C   <  |  92 5C   \  | 124 7C   |  |
////~ |  29 1D   .  |  61 3D   =  |  93 5D   ]  | 125 7D   }  |
////~ |  30 1E   .  |  62 3E   >  |  94 5E   ^  | 126 7E   ~  |
////~ |  31 1F   .  |  63 3F   ?  |  95 5F   _  | 127 7F   .  | </pre><hr>
////~ <a href="http://www.informatik.htw-dresden.de/~beck/a.beck.html">A. Beck</A> <p>
////~ </body>
////~ 
////~ </html>

//int main () {
	//int i, j;
	//char c;
	
	//cout << "Content-Type: text/html"<<endl;
	//cout << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2//EN\">"<<endl;
	//cout << "<html><head><title>ASCII Codetabelle per CGI-Script</title></head>"<<endl;
	//cout << "<body>";
	//cout << "<h2>ASCII Codetabelle per CGI-Script</h2>"<<endl;

	//cout << "<p><pre>";
	//cout << "|dec hex Char |dec hex Char |dec hex Char |dec hex Char |"<<endl;
	//for (j=0; j < 64; j=j+1) {
		//for (i=0; i < 256; i=i+64) {
			//c = char(j+i);
			//cout<<setw(3)<<right<<dec<<j+i<<setw(3)<<right<<hex<<j+i<<" ";
			//if (isgraph(c)) {
				//cout<<c;
			//} else {
				//cout << ".";
			//}
			//cout <<" |";
		//}
		//cout << "<br>"<<endl;
	//}
	
	//cout << "</pre><hr>"<<endl;

	//cout << "<a href=\"http://www.informatik.htw-dresden.de/~beck/C/cgi.html\">Zur Aufgabenstellung</a> </p>"<<endl;
	//cout << "</body></html>\n"<<endl;
	
	//return 0;
//}
