#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

#include "calculator.h"
#include "credit.h"
#include "deposit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private slots:

  void on_toolButton_clicked();
  void on_toolButton_2_clicked();
  void on_toolButton_3_clicked();
  void on_toolButton_5_clicked();

 private:
  Ui::View *ui;
  Credit *credit_window;
  Deposit *deposit_window;
  Calculator *calculator_window;
};
#endif  // VIEW_H
