#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <bitset>
#include <string>
using namespace std;

#include <QMessageBox>
#include <QDebug>

#include "MyQShortings.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->setWindowTitle("Converter");

	auto viewDetailedFoo = [this](){
		int fromBase=GetBase(ui->rBntFrom2, ui->rBntFrom10, ui->rBntFrom16);
		auto details = Details(ui->leFrom->text().remove(' '), fromBase);
		ui->leFromDetailed2->setText(details.forBin);
		ui->leFromDetailed10->setText(details.forDec);
		ui->leFromDetailed16->setText(details.forHex);
	};

	connect(ui->leFrom,     &QLineEdit::textChanged, this, viewDetailedFoo);
	connect(ui->rBntFrom2,  &QRadioButton::clicked,  this, viewDetailedFoo);
	connect(ui->rBntFrom10, &QRadioButton::clicked,  this, viewDetailedFoo);
	connect(ui->rBntFrom16, &QRadioButton::clicked,  this, viewDetailedFoo);

	connect(ui->leFrom,     &QLineEdit::textChanged, this, &MainWindow::SlotConvert);
	connect(ui->rBntFrom2,  &QRadioButton::clicked,  this, &MainWindow::SlotConvert);
	connect(ui->rBntFrom10, &QRadioButton::clicked,  this, &MainWindow::SlotConvert);
	connect(ui->rBntFrom16, &QRadioButton::clicked,  this, &MainWindow::SlotConvert);
	connect(ui->rBntTo2,    &QRadioButton::clicked,  this, &MainWindow::SlotConvert);
	connect(ui->rBntTo10,   &QRadioButton::clicked,  this, &MainWindow::SlotConvert);
	connect(ui->rBntTo16,   &QRadioButton::clicked,  this, &MainWindow::SlotConvert);
}

MainWindow::~MainWindow()
{
	delete ui;
}

MainWindow::DetailsRes MainWindow::Details(QString value, int base)
{
	if(base != 2 && base != 10 && base != 16) return DetailsRes("wrong base","wrong base", "wrong base");

	int newBase = 16;
	value = QSn(value.toULongLong(nullptr,base), newBase);

	int byteLen = 2;
	while(value.size() % byteLen != 0) value.prepend('0');

	DetailsRes res("bin:  ", "dec:  ", "hex:  ");

	for(int i=0; i<value.size(); i+=byteLen)
	{
		QString byte = value.mid(i, byteLen);
		QString convertedByte2 = QSn(byte.toUShort(nullptr, newBase), 2).rightJustified(8,'0');
		QString convertedByte10 = QSn(byte.toUShort(nullptr, newBase), 10).rightJustified(3,'0');
		QString convertedByte16 = QSn(byte.toUShort(nullptr, newBase), 16).rightJustified(2,'0');

		res.forBin += convertedByte2 + "  ";
		res.forDec += convertedByte10 + "  ";
		res.forHex += convertedByte16 + "  ";
	}

	return res;
}

int MainWindow::GetBase(QRadioButton *rBnt2, QRadioButton *rBnt10, QRadioButton *rBnt16)
{
	if(rBnt2->isChecked()) return 2;
	if(rBnt10->isChecked()) return 10;
	if(rBnt16->isChecked()) return 16;
	QMbError("can't define base, return -1");
	return -1;
}

void MainWindow::SlotConvert()
{
	QString src=ui->leFrom->text();

	src.remove(' ');

	int fromBase=GetBase(ui->rBntFrom2, ui->rBntFrom10, ui->rBntFrom16);

	bool ok;
	long long srcLL {src.toLongLong(&ok,fromBase)};
	if(!ok) { ui->leTo->setText("Error converting src"); return; }

	int toBase=GetBase(ui->rBntTo2, ui->rBntTo10, ui->rBntTo16);

	ui->leTo->setText(QString::number(srcLL,toBase));
}
