#include "WindowConverter.h"
#include "ui_mainwindow.h"

#include <bitset>
#include <string>

#include <QMessageBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QTimer>

#include "MyQShortings.h"
#include "MyQWidget.h"

WindowConverter::WindowConverter(QWidget *parent)
	: QWidget(parent)
{
	this->setWindowTitle("Converter");

	rBntFrom2 = new QRadioButton("2");
	rBntFrom10 = new QRadioButton("10");
	rBntFrom16 = new QRadioButton("16");
	rBntTo2 = new QRadioButton("2");
	rBntTo10 = new QRadioButton("10");
	rBntTo16 = new QRadioButton("16");

	rBntFrom2->setChecked(true);
	rBntTo10->setChecked(true);

	leFrom = new QLineEdit;
	leFromDetailed2 = new QLineEdit;
	leFromDetailed10 = new QLineEdit;
	leFromDetailed16 = new QLineEdit;
	leTo = new QLineEdit;

	textEditForNotes = new QTextEdit;

	auto vloMain = new QVBoxLayout(this);

	std::vector<QWidget*> courierNew { leFrom, leFromDetailed2, leFromDetailed10, leFromDetailed16, leTo,
									   textEditForNotes };
	for(auto &w:courierNew) MyQWidget::SetFontFamily(w, "Courier new");

	std::vector<QWidget*> extraSize { leFrom, leTo, textEditForNotes };
	QTimer::singleShot(0,[extraSize](){ for(auto &w:extraSize) MyQWidget::IncreaseFontPointSize(w, 6); });

	auto grBoxFrom = new QGroupBox("From");
	vloMain->addWidget(grBoxFrom);

	auto hloGrBoxFrom = new QHBoxLayout(grBoxFrom);

	hloGrBoxFrom->addWidget(rBntFrom2);
	hloGrBoxFrom->addWidget(rBntFrom10);
	hloGrBoxFrom->addWidget(rBntFrom16);
	hloGrBoxFrom->addStretch();

	auto vloFrom = new QVBoxLayout;
	vloFrom->setContentsMargins(0,0,0,0);
	vloFrom->setSpacing(1);
	vloMain->addLayout(vloFrom);

	vloFrom->addWidget(leFrom);
	vloFrom->addWidget(leFromDetailed2);
	vloFrom->addWidget(leFromDetailed10);
	vloFrom->addWidget(leFromDetailed16);

	auto grBoxTo = new QGroupBox("To");
	vloMain->addWidget(grBoxTo);

	auto hloGrBoxTo = new QHBoxLayout(grBoxTo);

	hloGrBoxTo->addWidget(rBntTo2);
	hloGrBoxTo->addWidget(rBntTo10);
	hloGrBoxTo->addWidget(rBntTo16);
	hloGrBoxTo->addStretch();

	vloMain->addWidget(leTo);

	vloMain->addWidget(new QLabel("For notes:"));
	vloMain->addWidget(textEditForNotes);

	//vloMain->addStretch();

	auto viewDetailedFoo = [this](){
		int fromBase=GetBase(rBntFrom2, rBntFrom10, rBntFrom16);
		auto details = Details(leFrom->text().remove(' '), fromBase);
		leFromDetailed2->setText(details.forBin);
		leFromDetailed10->setText(details.forDec);
		leFromDetailed16->setText(details.forHex);
	};

	QTimer::singleShot(0,[this](){ resize(height()*1.4,height()); });

	connect(leFrom,     &QLineEdit::textChanged, this, viewDetailedFoo);
	connect(rBntFrom2,  &QRadioButton::clicked,  this, viewDetailedFoo);
	connect(rBntFrom10, &QRadioButton::clicked,  this, viewDetailedFoo);
	connect(rBntFrom16, &QRadioButton::clicked,  this, viewDetailedFoo);

	connect(leFrom,     &QLineEdit::textChanged, this, &WindowConverter::SlotConvert);
	connect(rBntFrom2,  &QRadioButton::clicked,  this, &WindowConverter::SlotConvert);
	connect(rBntFrom10, &QRadioButton::clicked,  this, &WindowConverter::SlotConvert);
	connect(rBntFrom16, &QRadioButton::clicked,  this, &WindowConverter::SlotConvert);
	connect(rBntTo2,    &QRadioButton::clicked,  this, &WindowConverter::SlotConvert);
	connect(rBntTo10,   &QRadioButton::clicked,  this, &WindowConverter::SlotConvert);
	connect(rBntTo16,   &QRadioButton::clicked,  this, &WindowConverter::SlotConvert);
}

WindowConverter::~WindowConverter()
{

}

WindowConverter::DetailsRes WindowConverter::Details(QString value, int base)
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

int WindowConverter::GetBase(QRadioButton *rBnt2, QRadioButton *rBnt10, QRadioButton *rBnt16)
{
	if(rBnt2->isChecked()) return 2;
	if(rBnt10->isChecked()) return 10;
	if(rBnt16->isChecked()) return 16;
	QMbError("can't define base, return -1");
	return -1;
}

void WindowConverter::SlotConvert()
{
	QString src=leFrom->text();

	src.remove(' ');

	int fromBase=GetBase(rBntFrom2, rBntFrom10, rBntFrom16);

	bool ok;
	long long srcLL {src.toLongLong(&ok,fromBase)};
	if(!ok) { leTo->setText("Error converting src"); return; }

	int toBase=GetBase(rBntTo2, rBntTo10, rBntTo16);

	leTo->setText(QString::number(srcLL,toBase));
}
