#include <math.h>

#include "./s21_Model.hpp"

using namespace s21;

void Model::expression_to_polish_notation() {
  int index_cur_str = 0, priority = -1;
  std::string str = expression_;
  std::string currect_string = str;

  for (auto i = 0; (unsigned)i < (str.size() - 1); i++) {
    priority = get_priority(str[i]);

    if (priority == Number) {
      pushNumber(currect_string, &index_cur_str, &i);
    }

    else if (priority == Sub) {
      ready.push_back({0, SHORT, Sub});
    } else if (priority == Add) {
      ready.push_back({0, SHORT, Add});
    } else if (priority == Mul) {
      ready.push_back({0, MIDDLE, Mul});
    } else if (priority == Div) {
      ready.push_back({0, MIDDLE, Div});
    } else if (priority == Mod) {
      ready.push_back({0, MIDDLE, Mod});
    } else if (priority == X) {
      list.push_back({value_X, (priority_t)5, Number});
    } else if (priority == Cos) {
      ready.push_back({0, HIGH, Cos}), i += 2;
    } else if (priority == Tan) {
      ready.push_back({0, HIGH, Tan}), i += 2;
    } else if (priority == Pow) {
      ready.push_back({0, HIGH, Pow});
    } else if (priority == OpenBracket) {
      ready.push_back({0, BRACKET, OpenBracket});
    } else if (priority == CloseBracket) {
      ready.push_back({0, BRACKET, CloseBracket});
    }

    else if (priority == Sin) {
      if (strncmp(str.c_str() + i, "sin", 3) == 0)
        ready.push_back({0, HIGH, Sin}), i += 2;
      else if (strncmp(str.c_str() + i, "sqrt", 4) == 0)
        ready.push_back({0, HIGH, Sqrt}), i += 3;
    }

    else if (priority == Acos) {
      if (strncmp(str.c_str() + i, "acos", 4) == 0) {
        ready.push_back({0, HIGH, Acos});
      } else if (strncmp(str.c_str() + i, "asin", 4) == 0) {
        ready.push_back({0, HIGH, Asin});
      } else if (strncmp(str.c_str() + i, "atan", 4) == 0) {
        ready.push_back({0, HIGH, Atan});
      }
      i += 3;
    }

    else if (priority == Ln) {
      if (strncmp(str.c_str() + i, "ln", 2) == 0)
        ready.push_back({0, HIGH, Ln}), i += 1;
      else if (strncmp(str.c_str() + i, "log", 3) == 0)
        ready.push_back({0, HIGH, Log}), i += 2;
    }
    mergeStack();
  }
  while (!support.empty()) {
    list.push_back(support.back());
    support.pop_back();
    calculate_expression();
  }
  if (!list.empty()) {
    data = list.back().value;
    list.pop_back();
    list.clear();
  }
}

/*  Идентификация символа  */
int Model::get_priority(int token) {
  int f_result = -1;
  if (token == '*')
    f_result = Mul;
  else if (token == '/')
    f_result = Div;
  else if (token == 'x')
    f_result = X;
  else if (token == '%')
    f_result = Mod;
  else if (token == '+')
    f_result = Add;
  else if (token == '-')
    f_result = Sub;
  else if (token == '(')
    f_result = OpenBracket;
  else if (token == ')')
    f_result = CloseBracket;
  else if (isdigit(token) != 0)
    f_result = Number;
  else if (token == '.')
    f_result = Point;
  else if (token == 's')
    f_result = Sin;
  else if (token == 'c')
    f_result = Cos;
  else if (token == 't')
    f_result = Tan;
  else if (token == 'a')
    f_result = Acos;
  else if (token == 'l')
    f_result = Ln;
  else if (token == '^')
    f_result = Pow;
  return f_result;
}

void Model::pushNumber(std::string str, int* d, int* i) {
  int index_cur_str = 0, priority = -1;
  std::string currect_string = str;
  priority = get_priority(str[*i]);
  while (priority == 0 || priority == 1) {
    currect_string[index_cur_str] = str[*i];
    priority = get_priority(str[*i]);
    ++index_cur_str, ++*i;
  }
  if (currect_string[0] != '\0') {
    s21_Stack_t tmp = {atof(currect_string.c_str()), (priority_t)5, Number};
    list.push_back(tmp);
    *d = 0;
  }
  *i -= 2;
}
void Model::mergeStack() {
  if (!ready.empty()) {
    if (ready.back().type_t == CloseBracket) {
      while (support.back().type_t != OpenBracket) {
        list.push_back(support.back());
        support.pop_back();
        calculate_expression();
      }
      support.pop_back();
      ready.pop_back();
    } else if (support.empty()) {
      support.push_back(ready.back());
      ready.pop_back();
    } else if (ready.back().type_t == OpenBracket ||
               support.back().type_t == OpenBracket) {
      support.push_back(ready.back());
      ready.pop_back();
    } else if (ready.back().priority <= support.back().priority &&
               ready.back().type_t != CloseBracket) {
      while (ready.back().priority <= support.back().priority &&
             !support.empty() && support.back().type_t != OpenBracket) {
        list.push_back(support.back());
        support.pop_back();
        calculate_expression();
      }
      support.push_back(ready.back());
      ready.pop_back();
    } else if (ready.back().priority > support.back().priority) {
      support.push_back(ready.back());
      ready.pop_back();
    }
  }
}

/*  вычисление польской нотации */
void Model::calculate_expression() {
  value_type_t operation = Number;
  double a = 0, b = 0, result = 0;

  if (!list.empty()) {
    operation = list.back().type_t;
    if (operation > 0) {
      if (operation < 9) {
        operation = list.back().type_t;
        list.pop_back();
        if (list.back().type_t == 0) a = list.back().value, list.pop_back();
        if (list.back().type_t == 0) b = list.back().value, list.pop_back();
        result = s21_arithmetic(b, a, operation);
      } else if (operation >= 9 && operation <= 17) {
        operation = list.back().type_t;
        list.pop_back();
        if (list.back().type_t == 0) a = list.back().value, list.pop_back();
        result = s21_trigonometry(a, operation);
      }
      list.push_back({result, (priority_t)5, Number});
    }
  }
}

double Model::s21_arithmetic(double a, double b, value_type_t operation) {
  double res = 0;
  switch (operation) {
    case Add:
      res = a + b;
      break;
    case Sub:
      res = a - b;
      break;
    case Div:
      if (b != 0 || b != 0.0)
        res = a / b;
      else
        error1 = true;
      break;
    case Mul:
      res = a * b;
      break;
    case Pow:
      res = pow(a, b);
      break;
    case Mod:
      res = fmod(a, b);
      break;
    default:
      break;
  }
  return res;
}

double Model::s21_trigonometry(double a, value_type_t operation) {
  double res = 0;
  switch (operation) {
    case Sin:
      res = sin(a);
      break;
    case Cos:
      res = cos(a);
      break;
    case Tan:
      res = tan(a);
      break;
    case Asin:
      res = asin(a);
      break;
    case Acos:
      res = acos(a);
      break;
    case Atan:
      res = atan(a);
      break;
    case Sqrt:
      res = sqrt(a);
      break;
    case Ln:
      res = log(a);
      break;
    case Log:
      res = log10(a);
      break;
    default:
      break;
  }
  return res;
}
