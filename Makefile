CFLAGS = -Wall -Werror -Wextra
all: clean calc

calc:
	gcc view.c controller.c model.c -o calc `pkg-config --cflags --libs gtk+-3.0`
	./calc
test:
	gcc test.c view.c model.c   -lcheck `pkg-config --cflags --libs gtk+-3.0`  -o Test
	./Test

gcov_report: 
	gcc -fprofile-arcs -ftest-coverage -lcheck model.c test.c -fprofile-arcs -ftest-coverage  `pkg-config --cflags --libs gtk+-3.0` -o Test
	./Test
	gcov  model.gcda
	gcov test.gcda
	lcov -t "calc" -o calc.info -c -d .
	genhtml -o report calc.info
	

clean:
	rm -f *.o Test *.out *.gcov *.gcda *.gcno *.info *.a
	rm -rf ./report
check:
	CK_FORK=no leaks --atExit -- ./Test

rebuild: clean all




