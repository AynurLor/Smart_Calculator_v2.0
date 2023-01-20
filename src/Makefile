OS := $(shell uname -s)
CC = g++
FLAG = 
FLAG_C = -c 
CL_11 = -std=c++17 -Wall -Wextra -Werror
PR_NAME = s21_smartcalc
ALL_FILE_CC = ./Model/s21_Model.cpp ./Model/Credit_calc.cpp ./Model/Deposit_calc.cpp ./Model/Stack.cpp ./Model/Valid.cpp
ALL_FILE_H = ./Model/s21_Model.hpp ./Contreller/Controller.hpp
ALL_FILE_O = s21_Model.o Credit_calc.o Deposit_calc.o Stack.o Valid.o

ifeq ($(OS), Darwin)
	FLAGS_PLATFORM = -lgtest
else
	FLAGS_PLATFORM = -lgtest -lsubunit -lrt -lm -lpthread -g
endif

all: clean $(PR_NAME).a install

temp_test:
	@$(CC) $(PR_NAME).cpp
	@./a.out

$(PR_NAME).a:
	@$(CC) $(FLAG_C) $(ALL_FILE_CC) $(ALL_FILE_H)
	@ar rcs $(PR_NAME).a $(ALL_FILE_O) 

test: $(PR_NAME).a
	@$(CC) $(CL_11) ./tests.cpp $(ALL_FILE_CC) -o tests.o -lgtest
	@./tests.o

gcov_report:
	@$(CC) --coverage $(ALL_FILE) ./tests.cpp $(ALL_FILE_CC) $(FLAGS_PLATFORM) -o gov_report.o
	@./gov_report.o
	@lcov -t $(PR_NAME)_tests -o $(PR_NAME)_tests.info -c -d .
	@genhtml -o report $(PR_NAME)_tests.info
	@open ./report/index.html

install:
	@make clean
	@mkdir build
	@cd View && qmake && make && make clean && rm Makefile && cd ../ && mv View/View.app build/

uninstall:
	@rm -rf build*

dvi:
	open readme.html

dist:
	@rm -rf Archive_SmartCalc_v2.0/
	@mkdir Archive_SmartCalc_v2.0/
	@mkdir Archive_SmartCalc_v2.0/src
	@mv build/View.app Archive_SmartCalc_v2.0/src/
	@tar cvzf Archive_SmartCalc_v2.0.tgz Archive_SmartCalc_v2.0/
	@rm -rf Archive_SmartCalc_v2.0/

clean:
	@rm -f *.a
	@rm -f *.o
	@rm -f *.out
	@rm -f *.gcda
	@rm -f *.gcdo
	@rm -f *.gcno
	@rm -f *.info
	@rm -f *.info
	@rm -f ./*/*.gch
	@rm -rf build
	@rm -rf *tgz
	@rm -rf *.dSYM
	@rm -f RESULT_VALGRIND.txt
	@rm -rf report

leaks: test
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./tests.o

check:
	@cp ../materials/linters/.clang-format ./
	@cd View && clang-format -i ./*.cpp ./*.h
	cd View && clang-format -n ./*.cpp ./*.h
	@cd Model && clang-format -i ./*.cpp ./*.hpp
	cd Model && clang-format -n ./*.cpp ./*.hpp
	@cd Contreller && clang-format -i ./Controller.hpp
	cd Contreller && clang-format -n ./Controller.hpp
	@rm -rf .clang-format