#include "calculator.h"

#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Calculator)

{
  ui->setupUi(this);
  setFixedSize(width(), height());
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_openBracket, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_closeBracket, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_remove, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
}

Calculator::~Calculator() { delete ui; }

void Calculator::digits_numbers() {
  QString new_label;
  QToolButton *button = (QToolButton *)sender();

  if (button == ui->pushButton_sin || button == ui->pushButton_cos ||
      button == ui->pushButton_tan || button == ui->pushButton_asin ||
      button == ui->pushButton_acos || button == ui->pushButton_atan ||
      button == ui->pushButton_ln || button == ui->pushButton_log) {
    new_label = (ui->show_result->text() + button->text()) + '(';

  } else if (button == ui->pushButton_openBracket) {
    new_label = (ui->show_result->text() + "(");

  } else if (button == ui->pushButton_closeBracket) {
    new_label = (ui->show_result->text() + ")");

  } else if (button == ui->pushButton_remove) {
    new_label = "";

  } else if (button == ui->pushButton_mod) {
    new_label = ui->show_result->text() + "mod";
  } else if (button == ui->pushButton_sqrt) {
    new_label = (ui->show_result->text() + "sqrt(");
  } else if (button == ui->pushButton_x) {
    new_label = (ui->show_result->text() + "x");
  } else {
    new_label = (ui->show_result->text() + button->text());
  }

  ui->show_result->setText(new_label);
}

void Calculator::on_pushButton_result_clicked() {
  terminal.clearCalc();
  std::string str_string;
  double result = 0;
  str_string = ui->show_result->text().toStdString();
  result = terminal.Calculator(str_string, 0);
  if (terminal.getErrorCalc() == false)
    ui->show_result->setText(QString::number(result)), result = 0;
  str_string.clear();

}

void Calculator::on_clear_clicked() {
  terminal.clearCalc();
  std::string str = ui->show_result->text().toStdString();
  if (!str.empty()) {
    str.erase(str.size() - 1);
  }
  QString tmp;
  if (str.empty()) {
  } else {
    tmp = QString::fromStdString(str);
  }
  ui->show_result->setText(tmp);
}

void Calculator::on_pushButton_graph_clicked() {
  ui->graphWidget->clearGraphs();
  x.clear();
  y.clear();
  std::string str = ui->show_result->text().toStdString();

  if (!str.empty()) {
    xBegin_ = ui->horizontalSlider->sliderPosition();
    if (xBegin_ == 0) {
      xBegin_ = -10;
    }
    xEnd_ = ui->horizontalSlider_3->sliderPosition();
    if (xEnd_ == 0) {
      xEnd_ = 10;
    }
    s21::Controller test;
    Y_ = test.Calculator(str, X_);
    double y_min = 0;
    double y_max = 0;
    h_ = 0.005 * (fabs(xBegin_) + fabs(xEnd_));
    int f = 1;

    for (double x1 = xBegin_; x1 <= xEnd_ && f == 1; x1 += h_) {
      ;
      Y_ = test.Calculator(str, x1);
      f = 1;
      x.push_back(x1);
      y.push_back(Y_);
      if (Y_ > y_max) y_max = Y_ * 1.1;
      if (Y_ < y_min) y_min = Y_ * 1.1;
      test.clearCalc();
    }

    QPen pen;
    pen.setWidth(pen.width() + 1);
    pen.setColor(QColor(255, 0, 0));

    ui->graphWidget->xAxis->setRange(xBegin_, xEnd_);
    ui->graphWidget->yAxis->setRange(y_min, y_max);

    ui->graphWidget->addGraph()->setPen(pen);
    ui->graphWidget->graph(0)->addData(x, y);
    ui->graphWidget->replot();
  }
}

void Calculator::on_pushButton_32_clicked() {
  terminal.clearCalc();
  this->close();
  emit firstWindow();
}

void Calculator::on_pushButton_33_clicked() { this->close(); }

