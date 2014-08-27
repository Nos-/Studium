#ifndef MYADD_H
#define MYADD_H
 
#include <QWidget>
 
class Taschenrechner;										// Forward Deklaration

/// Die Klasse mit der Addierfunktionalität
class myAdd : public QWidget{
	Q_OBJECT
 
Taschenrechner *myTaschenrechner;							/// die Referenz auf das Taschenrechnerobjekt, zu dem die jeweilige myAdd-Instanz gehört
 
public:
	myAdd (Taschenrechner*);
	~myAdd();
private slots:
	void addAB(); 
};
 
#endif //MYADD_H
