#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QTimer>
#include <QVector>
#include <QtMath>
#include <limits>

#include "../Contreller/Controller.hpp"
#include "../Model/s21_Model.hpp"
#include "qcustomplot.h"

namespace Ui {
class Calculator;
}

class Calculator : public QDialog {
  Q_OBJECT
 signals:
  void firstWindow();

 public:
  explicit Calculator(QWidget *parent = nullptr);
  ~Calculator();

 private slots:

  void digits_numbers();
  void on_pushButton_result_clicked();
  void on_clear_clicked();
  void on_pushButton_graph_clicked();
  void on_pushButton_32_clicked();
  void on_pushButton_33_clicked();

 private:
  Ui::Calculator *ui;
  double xBegin_;
  double xEnd_;
  double h_;
  int N_;
  int count_;
  double X_ = 0.0;
  double Y_ = 0.0;
  bool error = 0;
  QVector<double> x, y;
  s21::Controller terminal;

};

#endif  // CALCULATOR_H
