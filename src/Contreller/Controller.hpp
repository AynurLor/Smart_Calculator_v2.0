#ifndef SRC_CONTROLLER_HPP
#define SRC_CONTROLLER_HPP

#include "../Model/s21_Model.hpp"

namespace s21 {
class Controller {
 public:
  Controller() {}
  ~Controller() {}

 private:
  s21::Model model;

 public:
  void resultCredite(double total_sum, double period, double percent,
                     std::string type) {
    model.calculateCredit(total_sum, period, percent, type);
  }
  std::list<double> getMonthlyListCredite() {
    return model.getMonthlyListCredite();
  }
  double getMonthlyCredite() { return model.getMonthlyCredite(); }
  double getOverPaymentCredite() { return model.getOverPaymentCredite(); }
  double getTotalCredite() { return model.getTotalCredite(); }
  bool getErrorCredit() { return model.getErrorCredit(); }
  void clearCredite() { model.clearCredite(); }

  double Calculator(std::string expression, double x) {
    return model.resultCalculator(expression, x);
  }
  bool getErrorCalc() { return model.getError(); }
  void clearCalc() { model.clearCalculater(); }

  void resultDeposit(double deposit_amount, double placement_period,
                     double rate_of_exchange, int repayment_period,
                     int capitalization, double* partial_withdrawal,
                     double* interest_capitalisation) {
    model.calculateDeposit(deposit_amount, placement_period, rate_of_exchange,
                           repayment_period, capitalization, partial_withdrawal,
                           interest_capitalisation);
  }
  double getAllPercent() { return model.getAllPercent(); }
  double getsSumTax() { return model.getsSumTax(); }
  double getTotalSum() { return model.getTotalSum(); }
  bool getErrorDeposit() { return model.getErrorDeposit(); }
  double getAmountProfit() { return model.getAmountProfit(); }
  void clearDeposit() { model.clearDeposit(); }
};

}  // namespace s21

#endif  // SRC_CONTROLLER_HPP
