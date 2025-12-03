#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QRadioButton>
#include <QTextEdit>
#include <QCheckBox>

#include "declare_struct.h"
#include "MyQDifferent.h"

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
	void SloOpenNewConverter();

	QRadioButton *rBntFrom2;
	QRadioButton *rBntFrom10;
	QRadioButton *rBntFrom16;
	QRadioButton *rBntTo2;
	QRadioButton *rBntTo10;
	QRadioButton *rBntTo16;

	QCheckBox *chBoxUpperCase;

	QLineEdit *leFrom;
	QLineEdit *leFromDetailed2;
	QLineEdit *leFromDetailed10;
	QLineEdit *leFromDetailed16;
	QLineEdit *leTo;

	QTextEdit *textEditForNotes;

	QString filesPath = MyQDifferent::ExePath()+"/files";
	QString settigsFile = filesPath+"/settings.ini";
};
#endif // MAINWINDOW_H
