#include "./s21_Model.hpp"

using namespace s21;

Data_lf Model::resultCalculator(std::string expression, double x) {
  setExpression(expression, x);
  validator();
  if (!error1) expression_to_polish_notation();
  return getData();
}

/* -------------------------------------------------
          Проверка на введеные занчения
  return: true (ошибок не найдено)
          false (ошибки не найдено)
  unaryProcessing() - обработка
  --------------------------------------------------
*/
void Model::validator() {
  unaryProcessing();
  if (validatorList(expression_) == -1) error1 = true;
}

void Model::clearCalculater() {
  list.clear();
  support.clear();
  ready.clear();
  expression_.clear();
  data = 0;
  value_X = 0;
  error1 = false;
}

void Model::clearCredite() {
  error_credit = false;
  monthly_credite = 0;
  overpayment_credite = 0;
  total_credite = 0;
  monthle_pay_credit.clear();
}

void Model::clearDeposit() {
  error_deposit = false;
  all_percent = 0;
  sum_tax = 0;
  total_sum = 0;
  amount_profit = 0;
}
