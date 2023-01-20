#ifndef SRC_S21_MODEL_HPP
#define SRC_S21_MODEL_HPP

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <list>

#define CORRECT 0
#define INCORRECT 1

#define ERROR 0;
#define OK 1;

using namespace std;

typedef double Data_lf;
typedef int Data_d;

/*     value_type_t - нужен для того чтобы       */
/*     записывать тип символа или переменной     */
/*     в структуру s21_Stack_t                   */
typedef enum {
  Number,
  Point,
  X,
  Add,
  Sub,
  Mul,
  Div,
  Mod,
  Pow,
  Cos,
  Sin,
  Tan,
  Acos,
  Asin,
  Atan,
  Sqrt,
  Ln,
  Log,
  OpenBracket,
  CloseBracket
} value_type_t;

/*     priority_t - нужен для определения       */
/*     приотритета 1 лексемы                    */
typedef enum {
  SHORT,
  MIDDLE,
  UNARY,
  HIGH,
  BRACKET,
} priority_t;

typedef struct Node {
  double value;
  priority_t priority;
  value_type_t type_t;
} s21_Stack_t;

namespace s21 {
class Model {
  /*   ------   attribute for polish notation  ------    */
 private:
  std::list<s21_Stack_t> list;
  std::list<s21_Stack_t> support;
  std::list<s21_Stack_t> ready;
  std::string expression_;
  double data;
  double value_X;

  /*   ------   attribute for credite calc  ------    */
 private:
  bool error1, error_credit, error_deposit;
  double monthly_credite;
  double overpayment_credite;
  double total_credite;
  std::list<double> monthle_pay_credit;

  /*   ------   attribute for deposit calc  ------    */
 private:
  double all_percent;
  double sum_tax;
  double total_sum;
  double amount_profit;

 public:
  double getData() { return data; }
  bool getError() { return error1; }
  std::string& getExpression() { return expression_; }
  void setExpression(std::string other, double value) {
    expression_ = other, value_X = value;
  }

  std::list<double> getMonthlyListCredite() { return monthle_pay_credit; }
  double getMonthlyCredite() { return monthly_credite; }
  double getOverPaymentCredite() { return overpayment_credite; }
  double getTotalCredite() { return total_credite; }
  bool getErrorCredit() { return error_credit; }

  double getAllPercent() { return all_percent; }
  double getsSumTax() { return sum_tax; }
  double getTotalSum() { return total_sum; }
  bool getErrorDeposit() { return error_deposit; }
  double getAmountProfit() { return amount_profit; }

  void clearCalculater();
  void clearCredite();
  void clearDeposit();

  Data_lf resultCalculator(std::string expression, double x);

  /*  ------ Вычисление Credit calc     ------    */
  void calculateCredit(double total_sum, double period, double percent,
                       string type);

  /*  ------ Вычисление Deposit calc     ------    */
  void calculateDeposit(double deposit_amount, double period, double percent,
                        int repayment_period, int capitalization,
                        double* partial_withdrawal,
                        double* interest_capitalisation);

 private:
  /*  ------ Проверка на валидность ввода ------  */
  void unaryProcessing();
  void validator();

  bool is_operator(char ch);
  bool is_brackets(char ch);
  bool is_function(char ch);
  int check_list_2(std::string str, int ret, int len_str, int i);
  int validatorList(std::string str);

  /*  ------ Расчет  выражения          ------   */
  void pushNumber(std::string str, int* d, int* i);
  void mergeStack();
  int get_priority(int token);
  void expression_to_polish_notation();

  /*  ------ Вычисление выражение       ------    */
  void calculate_expression();
  double s21_arithmetic(double a, double b, value_type_t operation);
  double s21_trigonometry(double a, value_type_t operation);

  /*  ------ Доп. функции       ------    */
  bool checkCredit(double total_sum, double period, double percent);
  void deposit_tax();
};

}  // namespace s21

#endif  // SRC_S21_MODEL_H
