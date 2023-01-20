#include "./s21_Model.hpp"

using namespace s21;

bool Model::checkCredit(double total_sum, double period, double percent) {
  bool result = false;
  if (total_sum < 0 || period < 0 || percent < 0) {
    result = true;
  }
  return result;
}

void Model::calculateCredit(double total_sum, double period, double percent,
                            std::string type) {
  error_credit = checkCredit(total_sum, period, percent);

  if (!error_credit) {
    clearCredite();
    if (type == "Annuity") {
      double procently = percent / (100 * 12);
      monthly_credite =
          round(total_sum * (procently / (1 - pow(1 + procently, -period))));
      total_credite = monthly_credite * period;
      overpayment_credite = total_credite - total_sum;

    } else if (type == "Differentiated") {
      total_credite = 0.0;
      monthly_credite = total_sum / period;
      double mon_payment = 0.0;
      for (int i = 0; i < period; i++) {
        mon_payment = monthly_credite +
                      (total_sum - monthly_credite * i) * (percent / 100) / 12;
        monthle_pay_credit.push_back(mon_payment);
        total_credite += mon_payment;
      }
      monthly_credite = monthle_pay_credit.back();
      overpayment_credite = total_credite - total_sum;
    }
  }
}
