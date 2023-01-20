#ifndef CREDIT_H
#define CREDIT_H

//#include <QAudioOutput>
#include <QDialog>
//#include <QDir>
//#include <QMediaPlayer>
#include <QStandardItemModel>

#include "../Contreller/Controller.hpp"
#include "../Model/s21_Model.hpp"

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT
 signals:
  void firstWindow();

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_toolButton_32_clicked();

  void on_toolButton_33_clicked();
  // void on_toolButton_6_clicked();

  void on_pushButton_result_credit_clicked();

 private:
  Ui::Credit *ui;
  s21::Controller terminal;
//  QString pathFile1(QString name);
//  void isError();
  void tableCredite();
  void anuitet_calc();
  void diferic_calc();
  //    s21::Controller terminal;
};

#endif  // CREDIT_H
