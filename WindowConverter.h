#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QRadioButton>
#include <QTextEdit>

#include "declare_struct.h"

class WindowConverter : public QWidget
{
	Q_OBJECT
public:
	WindowConverter(QWidget *parent = nullptr);
	~WindowConverter();

private:

	declare_struct_3_fields_move(DetailsRes, QString, forBin, QString, forDec, QString, forHex);
	DetailsRes Details(QString value, int base);
	int GetBase(QRadioButton *rBnt2, QRadioButton *rBnt10, QRadioButton *rBnt16);

	void SlotConvert();

	QRadioButton *rBntFrom2;
	QRadioButton *rBntFrom10;
	QRadioButton *rBntFrom16;
	QRadioButton *rBntTo2;
	QRadioButton *rBntTo10;
	QRadioButton *rBntTo16;

	QLineEdit *leFrom;
	QLineEdit *leFromDetailed2;
	QLineEdit *leFromDetailed10;
	QLineEdit *leFromDetailed16;
	QLineEdit *leTo;

	QTextEdit *textEditForNotes;
};
#endif // MAINWINDOW_H
