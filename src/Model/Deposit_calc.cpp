#include "./s21_Model.hpp"

using namespace s21;

void Model::calculateDeposit(double deposit_amount, double placement_period,
                             double rate_of_exchange, int repayment_period,
                             int capitalization, double* partial_withdrawal,
                             double* interest_capitalisation) {
  clearDeposit();
  double new_deposit_amount = deposit_amount;
  int times_of_payment = placement_period / repayment_period;
  double placement_period_in_years = placement_period / 12.0;
  double new_rate_of_exchange =
      rate_of_exchange * placement_period_in_years / times_of_payment;

  double exchange = 1 + new_rate_of_exchange / 100;
  int movie = placement_period / times_of_payment;
  double total_partial_withdrawal = 0.0;
  double total_interest_capitalisation = 0.0;

  for (Data_d i = 0; i < placement_period; i++) {
    if (partial_withdrawal[i] != 0.0) {
      new_deposit_amount += partial_withdrawal[i];
      total_partial_withdrawal += partial_withdrawal[i];
    }
    if (interest_capitalisation[i] != 0.0) {
      if (interest_capitalisation[i] > new_deposit_amount) {
        error_deposit = true;
      } else {
        new_deposit_amount -= interest_capitalisation[i];
        total_interest_capitalisation += interest_capitalisation[i];
      }
    }
    if (i % movie == 0) {
      new_deposit_amount = new_deposit_amount * exchange;
    }
  }

  if (capitalization == 1) {
    all_percent = ((new_deposit_amount - total_partial_withdrawal +
                    total_interest_capitalisation) /
                       deposit_amount -
                   1) *
                  100 / placement_period_in_years;
    total_sum = new_deposit_amount;
    amount_profit = new_deposit_amount - deposit_amount;
    deposit_tax();
  } else {
    all_percent = rate_of_exchange;
    total_sum = deposit_amount;
    amount_profit = deposit_amount * (all_percent / 100.0);
    deposit_tax();
  }
}

void Model::deposit_tax() {
  double result_tax = 0;
  double profit = amount_profit;

  double limits = 1000000 * 0.08;
  if (profit > limits) {
    result_tax = (profit - limits) * 0.13;
    sum_tax = result_tax;
  } else
    sum_tax = 0.0;
}
