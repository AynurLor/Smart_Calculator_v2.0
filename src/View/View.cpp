#include "View.h"

#include "ui_View.h"

View::View(QWidget* parent) : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
  setFixedSize(width(), height());

  calculator_window = new Calculator();
  connect(calculator_window, &Calculator::firstWindow, this, &View::show);

  credit_window = new Credit();
  connect(credit_window, &Credit::firstWindow, this, &View::show);

  deposit_window = new Deposit();
  connect(deposit_window, &Deposit::firstWindow, this, &View::show);
}

View::~View() { delete ui; }

void View::on_toolButton_clicked() {
  calculator_window->show();
  this->close();
}

void View::on_toolButton_2_clicked() {
  credit_window->show();
  this->close();
}

void View::on_toolButton_3_clicked() {
  deposit_window->show();
  this->close();
}

void View::on_toolButton_5_clicked() { this->close(); }
