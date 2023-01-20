#include <list>

#include "./Model/s21_Model.hpp"
#include "gtest/gtest.h"

TEST(Test, calc_test_plus) {
  double result = 0.0;
  double answer = 1.25 + 3.45;
  std::string strline = "1.25+3.45";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  // test.terminal(strline, 0.0, &result);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_minus) {
  double result = 0.0;
  double answer = 0.003 - 15.34;
  std::string strline = "0.003-15.34";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_mult) {
  double result = 0.0;
  double answer = 0.25 * 5;
  std::string strline = "0.25*5";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_div) {
  double result = 0.0;
  double answer = 0.2 / 5;
  std::string strline = "0.2/5";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_mod) {
  double result = 0.0;
  double answer = fmod(60, 3.5);
  std::string strline = "60%3.5";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_pow) {
  double result = 0.0;
  double answer = pow(5, 3.45);
  std::string strline = "5^3.45";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_brackets) {
  double result = 0.0;
  double answer = sin(0.3 * 0.6);
  std::string strline = "sin(0.3*0.6)";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_cos) {
  double result = 0.0;
  double answer = cos(0.6 - 0.1);
  std::string strline = "cos(0.6-0.1)";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_tan) {
  double result = 0.0;
  double answer = tan(0.8 / 2);
  std::string strline = "tan(0.8/2)";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_sqrt) {
  double result = 0.0;
  double answer = sqrt(97.3456);
  std::string strline = "sqrt(97.3456)";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_ln) {
  double result = 0.0;
  double answer = log(2.5 + 99);
  std::string strline = "ln(2.5+99)";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_log) {
  double result = 0.0;
  double answer = log10(1.8 + 256.34);
  std::string strline = "log(1.8+256.34)";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_asin) {
  double result = 0.0;
  double answer = asin(0.34);
  std::string strline = "asin(0.34)";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_acos) {
  double result = 0.0;
  double answer = acos(-0.83);
  std::string strline = "acos(-0.83)";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_atan) {
  double result = 0.0;
  double answer = atan(-0.669);
  std::string strline = "atan(-0.669)";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_1) {
  double result = 0.0;
  double answer = 1 - 1;
  std::string strline = "1-1";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_2) {
  double result = 0.0;
  double answer = 1 - 2 - 3;
  std::string strline = "1-2-3";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_3) {
  double result = 0.0;
  double answer = 4 * (-5) + 2.01 / sin(0.01);
  std::string strline = "4*(-5)+2.01/sin(0.01)";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_4) {
  double result = 0.0;
  double answer = sin(0.1);
  std::string strline = "sin(0.1)";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_test_5) {
  double result = 0;
  double answer = cos(sin(tan(-0.005)));
  std::string strline = "cos(sin(tan(-0.005)))";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
  test.clearCalculater();
}

TEST(Test, calc_test_big) {
  double result = 0;
  double answer = log10(32 + 1) * 7 / 11 * 432 * (sin(2) * 12 - 45 + 4) / 2;
  std::string strline = "log(32+1)*7/11*432*(sin(2)*12-45+4)/2";
  s21::Model test;
  result = test.resultCalculator(strline, 0);
  ASSERT_EQ(answer, result);
}

TEST(Test, calc_credit) {
  s21::Model test;
  double all_sum_credit = 105504;
  test.calculateCredit(100000, 12, 10, "Annuity");
  ASSERT_EQ(all_sum_credit, test.getTotalCredite());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
