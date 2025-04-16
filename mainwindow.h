#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QRadioButton>

#include "declare_struct.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	declare_struct_3_fields_move(DetailsRes, QString, forBin, QString, forDec, QString, forHex);
	DetailsRes Details(QString value, int base);
	int GetBase(QRadioButton *rBnt2, QRadioButton *rBnt10, QRadioButton *rBnt16);

private slots:
	void on_pushButton_clicked();

private:
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
