#ifndef MYSUB_H
#define MYSUB_H
 
#include <QWidget>
 
class Taschenrechner;										// Forward Deklaration

/// Die Klasse mit der Subierfunktionalität
class mySub : public QWidget{
	Q_OBJECT
 
Taschenrechner *myTaschenrechner;							/// die Referenz auf das Taschenrechnerobjekt, zu dem die jeweilige mySub-Instanz gehört
 
public:
	mySub (Taschenrechner*);
	~mySub();
private slots:
	void subAB(); 
};
 
#endif //MYSUB_H
