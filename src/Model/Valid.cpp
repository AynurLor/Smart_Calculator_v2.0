#include "./s21_Model.hpp"

using namespace s21;

void Model::unaryProcessing() {
  size_t k = 0;
  std::string new_str;
  new_str.resize(255);
  for (size_t i = 0; i < expression_.length(); i++) {
    char token = expression_[i];
    if (token == '-') {
      if (i == 0) {
        new_str[k] = '0';
        k++;
      } else if (expression_[i - 1] == '(') {
        new_str[k] = '0';
        k++;
      }
    }
    new_str[k++] = token;
  }
  expression_ = new_str;
}

bool Model::is_function(char ch) {
  if (ch == 'c' || ch == 's' || ch == 't' || ch == 'a' || ch == 'c' ||
      ch == 'l' || ch == 'x')
    return true;
  return false;
}

int Model::validatorList(std::string str) {
  int ret = 0;
  int i = 0;
  int len_str = strlen(str.c_str());
  if (len_str > 256) {
    ret = -1;
  }
  while (i < len_str && len_str <= 256 && ret != -1) {
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
      if (str[i + 1] == '(') {
        ret = -1;
        break;
      }
      int j = i;
      int dot = 0;
      int count_dot = 0;
      while ((str[j] >= '0' && str[j] <= '9') || str[j] == '.') {
        if (str[j] == '.') {
          dot = dot + 1;
        } else if (dot > 1) {
          ret = -1;
          break;
        }
        if (dot == 1) {
          count_dot = count_dot + 1;
        } else if (count_dot > 7) {
          ret = -1;
          break;
        }
        j = j + 1;
      }
    } else if (is_operator(str[i])) {
      ret = check_list_2(str, ret, len_str, i);
    } else if (is_function(str[i])) {
      if (strncmp(str.c_str() + i, "cos(", 4) == 0) {
        i = i + 3;
      } else if (strncmp(str.c_str() + i, "sin(", 4) == 0) {
        i = i + 3;
      } else if (strncmp(str.c_str() + i, "tan(", 4) == 0) {
        i = i + 3;
      } else if (strncmp(str.c_str() + i, "acos(", 5) == 0) {
        i = i + 4;
      } else if (strncmp(str.c_str() + i, "asin(", 5) == 0) {
        i = i + 4;
      } else if (strncmp(str.c_str() + i, "atan(", 5) == 0) {
        i = i + 4;
      } else if (strncmp(str.c_str() + i, "sqrt(", 5) == 0) {
        i = i + 4;
      } else if (strncmp(str.c_str() + i, "ln(", 3) == 0) {
        i = i + 1;
      } else if (strncmp(str.c_str() + i, "log(", 4) == 0) {
        i = i + 3;
      } else if ('x' == str[i]) {
        ret = 0;
      } else {
        ret = -1;
      }
    } else {
      ret = -1;
      break;
    }
    i++;
  }
  if (str[strlen(str.c_str()) - 1] == '(') ret = -1;
  return (ret);
}

int Model::check_list_2(std::string str, int ret, int len_str, int i) {
  int count = 1;
  while (count) {
    if (str[0] == '*' || str[0] == '/' || str[0] == '%' || str[0] == '^' ||
        str[0] == ')') {
      ret = -1;
      break;
    }
    if (str[i] == '%' &&
        (isdigit(str[i + 1]) == 0 || isdigit(str[i - 1]) == 0)) {
      ret = -1;
      break;
    }
    if (str[len_str - 1] == '+' || str[len_str - 1] == '-' ||
        str[len_str - 1] == '*' || str[len_str - 1] == '/' ||
        str[len_str - 1] == '%' || str[len_str - 1] == '^' ||
        str[len_str - 1] == '(') {
      ret = -1;
      break;
    }
    if (str[i - 1] == '.' || str[i + 1] == '.') {
      ret = -1;
      break;
    }
    if (str[i] == '(' && str[i + 1] == ')') {
      ret = -1;
      break;
    }
    if (str[i + 1] == '\0') {
      break;
    }
    if (str[i] == '(' || str[i] == ')') {
      int brack_i = 0;
      int brack_j = 0;
      int j = 0;
      while (str[j] != '\0') {
        if (str[j] == '(') {
          brack_i = brack_i + 1;
        }
        if (str[j] == ')') {
          brack_j = brack_j + 1;
        }
        j++;
      }
      if (brack_i != brack_j) {
        ret = -1;
        break;
      }
    }
    if (str[i + 1] != '+' && str[i + 1] != '-' && str[i + 1] != '(' &&
        str[i + 1] != 'x' && !(str[i + 1] >= '0' && str[i + 1] <= '9')) {
      if (str[i + 1] != ')' && (str[i - 1] >= '0' && str[i - 1] <= '9')) {
        ret = 0;
      } else {
        if (str[strlen(str.c_str()) - 1] == '(') ret = -1;
      }
      break;
    }
    if (i >= 1 && !(is_brackets(str[i - 1])) && !(is_brackets(str[i]))) {
      if (is_operator(str[i - 1])) {
        ret = -1;
      }
    }
    count--;
  }
  return ret;
}

bool Model::is_operator(char ch) {
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||
      ch == '^' || ch == '(' || ch == ')' || ch == '+')
    return true;
  return false;
}

bool Model::is_brackets(char ch) {
  if (ch == '(' || ch == ')') return true;
  return false;
}
