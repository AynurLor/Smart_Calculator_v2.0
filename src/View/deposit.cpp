#include "deposit.h"

#include "ui_deposit.h"

Deposit::Deposit(QWidget* parent) : QDialog(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);
  setFixedSize(width(), height());
  ui->rate_of_payment->addItem("Раз в месяц");
  ui->rate_of_payment->addItem("Раз в три месяца");
  ui->rate_of_payment->addItem("Раз в полгода");
  ui->rate_of_payment->addItem("Раз в год");
  ui->pop_time->addItem("Разовое");
  ui->pop_time->addItem("Раз в месяц");
  ui->pop_time->addItem("Раз в три месяца");
  ui->pop_time->addItem("Раз в год");
  ui->withdrawal_time->addItem("Разовое");
  ui->withdrawal_time->addItem("Раз в месяц");
  ui->withdrawal_time->addItem("Раз в три месяца");
  ui->withdrawal_time->addItem("Раз в год");
  ui->time->addItem("месяцев");
  ui->time->addItem("лет");
  ui->pop_time->setVisible(0);
  ui->pop_num->setVisible(0);
  ui->withdrawal_time->setVisible(0);
  ui->withdrawal->setVisible(0);
  ui->checkBox->animateClick();
}

Deposit::~Deposit() { delete ui; }

void Deposit::on_toolButton_menuCredit_clicked() {
  this->close();
  emit firstWindow();
}

void Deposit::on_toolButton_exitCredit_clicked() { this->close(); }

void Deposit::on_pushButton_calculate_deposit_clicked() {
  s21::Controller terminalDeposit;

  double deposit_amount = ui->amount_money->text().toDouble();
  double rate_of_exchange = ui->rate_of_exchange->text().toDouble();
  double partial_withdrawal_list[1000] = {};
  double list_of_interest_capitalisation[1000] = {};
  int placement_period = 0;
  int repayment_period = 0;
  double capitalization = 0;
  int period = 0;
  switch (ui->pop_time->currentIndex()) {
    case 0:
      partial_withdrawal_list[0] = ui->pop_num->text().toDouble();
      for (int i = 1; i < ui->time_replament->text().toInt(); i++)
        partial_withdrawal_list[i] = 0;
      break;
    case 1:
      for (int i = 0; i < ui->time_replament->text().toInt(); i++) {
        partial_withdrawal_list[i] = ui->pop_num->text().toDouble();
      }
      break;
    case 2:
      partial_withdrawal_list[ui->time_replament->text().toInt()] =
          ui->pop_num->text().toDouble();
      for (int i = 0; i < ui->time_replament->text().toInt(); i++) {
        if (period == 3) {
          partial_withdrawal_list[i] = ui->pop_num->text().toDouble();
          period = 0;
        } else {
          partial_withdrawal_list[i] = 0;
        }
        period += 1;
      }
      break;
    case 3:
      for (int i = 0; i < ui->time_replament->text().toInt(); i++) {
        if (period == 12) {
          partial_withdrawal_list[i] = ui->pop_num->text().toDouble();
          period = 0;
        } else {
          partial_withdrawal_list[i] = 0;
        }
        period += 1;
      }
      break;
    default:
      break;
  }
  switch (ui->withdrawal_time->currentIndex()) {
    case 0:
      list_of_interest_capitalisation[0] = ui->withdrawal->text().toDouble();
      for (int i = 1; i < ui->time_replament->text().toInt(); i++)
        list_of_interest_capitalisation[i] = 0;
      break;
    case 1:
      for (int i = 0; i < ui->time_replament->text().toInt(); i++) {
        list_of_interest_capitalisation[i] = ui->withdrawal->text().toDouble();
      }
      break;
    case 2:
      list_of_interest_capitalisation[ui->time_replament->text().toInt()] =
          ui->withdrawal->text().toDouble();
      for (int i = 0; i < ui->time_replament->text().toInt(); i++) {
        if (period == 3) {
          list_of_interest_capitalisation[i] =
              ui->withdrawal->text().toDouble();
          period = 0;
        } else {
          list_of_interest_capitalisation[i] = 0;
        }
        period += 1;
      }
      break;
    case 3:
      for (int i = 0; i < ui->time_replament->text().toInt(); i++) {
        if (period == 12) {
          list_of_interest_capitalisation[i] =
              ui->withdrawal->text().toDouble();
          period = 0;
        } else {
          list_of_interest_capitalisation[i] = 0;
        }
        period += 1;
      }
      break;
    default:
      break;
  }

  if (ui->time->currentIndex() == 0)
    placement_period = ui->time_replament->text().toInt();
  else if (ui->time->currentIndex() == 1)
    placement_period = ui->time_replament->text().toInt() * 12;

  int currect_index_rate_of_payment = ui->rate_of_payment->currentIndex();
  if (currect_index_rate_of_payment == 0) {
    repayment_period = 1;
  } else if (currect_index_rate_of_payment == 1) {
    repayment_period = 3;
  } else if (currect_index_rate_of_payment == 2) {
    repayment_period = 6;
  } else if (currect_index_rate_of_payment == 3) {
    repayment_period = 12;
  }

  if (ui->checkBox->checkState()) {
    capitalization = 1;
  } else {
    capitalization = 0;
  }

  terminalDeposit.resultDeposit(
      deposit_amount, placement_period, rate_of_exchange, repayment_period,
      capitalization, partial_withdrawal_list, list_of_interest_capitalisation);

  QString total_money = QString::number(terminalDeposit.getTotalSum());
  QString total_percent = QString::number(terminalDeposit.getAllPercent());
  QString total_tax = QString::number(terminalDeposit.getsSumTax());
  QString total_amount_profit =
      QString::number(terminalDeposit.getAmountProfit());

  ui->label_total_money->setText(total_money + " руб.");
  ui->label_total_percent->setText(total_percent + " %");
  ui->label_total_tax->setText(total_tax + " руб.");
  ui->label_amount_profit->setText(total_amount_profit + " руб.");
}

void Deposit::on_Button_pop_clicked() {
  ui->pop_time->setVisible(1);
  ui->pop_num->setVisible(1);
}

void Deposit::on_Button_with_clicked() {
  ui->withdrawal_time->setVisible(1);
  ui->withdrawal->setVisible(1);
}

