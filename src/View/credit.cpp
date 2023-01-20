#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  setFixedSize(width(), height());
}

Credit::~Credit() { delete ui; }

void Credit::on_toolButton_32_clicked() {
  this->close();
  emit firstWindow();
}

void Credit::on_toolButton_33_clicked() { this->close(); }



void Credit::on_pushButton_result_credit_clicked() {
  double totaSum = 0, period = 0, percent = 0;

  totaSum = ui->total_sum->text().toDouble();
  period = ui->period->text().toInt();
  percent = ui->percent->text().toDouble();
  std::string type = "Differentiated";
  if (ui->type_credit->currentIndex() == 0) type = "Annuity";

  terminal.resultCredite(totaSum, period, percent, type);
  if (!terminal.getErrorCredit()) {
    ui->monthly_payment->setText(QString::number(terminal.getMonthlyCredite()));
    ui->overpayment->setText(QString::number(terminal.getOverPaymentCredite()));
    ui->total_payout->setText(QString::number(terminal.getTotalCredite()));
    tableCredite();
    (type == "Annuity") ? anuitet_calc() : diferic_calc();
  }
}

void Credit::tableCredite() {
  //    ui->tableWidget->setRowCount(ui->period->text().toInt());
  //    ui->tableWidget->setColumnCount(1);
  //    ui->tableWidget->setHorizontalHeaderLabels(QStringList()
  //                                               << "Сумма платежа, руб.");
  //    ui->tableWidget->setColumnWidth(1, 155);
  //    ui->tableWidget->setColumnWidth(1, 175);
  //    ui->tableWidget->setColumnWidth(3, 175);
  //    ui->tableWidget->setColumnWidth(4, 155);
}

void Credit::diferic_calc() {
  QStandardItemModel *model =
      new QStandardItemModel(ui->period->text().toInt(), 1, this);

  int row = 0;
  for (auto item : terminal.getMonthlyListCredite()) {
    for (auto col = 0; col != model->columnCount(); ++col) {
      QModelIndex index = model->index(row, col);
      model->setData(index, item);
    }
    row++;
  }
  model->setHeaderData(0, Qt::Horizontal, "Начисления %");
  ui->tableView->setModel(model);
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Credit::anuitet_calc() {
  QStandardItemModel *model =
      new QStandardItemModel(ui->period->text().toInt(), 1, this);

  int row = 0;
  for (int i = 0; i < model->rowCount(); i++) {
    for (auto col = 0; col != model->columnCount(); ++col) {
      QModelIndex index = model->index(row, col);
      model->setData(index, terminal.getMonthlyCredite());
    }
    row++;
  }
  model->setHeaderData(0, Qt::Horizontal, "Начисления %");
  ui->tableView->setModel(model);
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
