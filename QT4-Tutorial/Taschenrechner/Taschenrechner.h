#ifndef TASCHENRECHNER_H
#define TASCHENRECHNER_H
 
#include "ui_Taschenrechner.h"

/// Die Taschenrechnerklasse bzw. das Programmfenster
class Taschenrechner : public QMainWindow, public Ui::MainWindow{
	Q_OBJECT
 
public:
	Taschenrechner (QMainWindow *parent = 0);
	~Taschenrechner();
private slots:
	void showAdd();
	void showSub();
};
 
#endif //TASCHENRECHNER_H
