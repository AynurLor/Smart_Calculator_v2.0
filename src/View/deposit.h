#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>

#include "../Contreller/Controller.hpp"
#include "../Model/s21_Model.hpp"

namespace Ui {
class Deposit;
}

class Deposit : public QDialog {
  Q_OBJECT

 signals:
  void firstWindow();

 public:
  explicit Deposit(QWidget *parent = nullptr);
  ~Deposit();

 private slots:
  void on_toolButton_menuCredit_clicked();
  void on_toolButton_exitCredit_clicked();
  void on_pushButton_calculate_deposit_clicked();
  void on_Button_pop_clicked();
  void on_Button_with_clicked();

 private:
  Ui::Deposit *ui;
};

#endif  // DEPOSIT_H
