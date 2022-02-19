CFLAGS = -Wall -Werror -Wextra
all: clean calc

calc:
	gcc view.c controller.c model.c  `pkg-config --cflags --libs gtk+-3.0` -o calc
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

install:
	gcc view.c controller.c model.c  `pkg-config --cflags --libs gtk+-3.0` -o calc
	mkdir -p app
	install ./calc app
	install mystyle.css ~/

uninstall:
	rm -rf app
	rm calc

dvi:
	open documentation.html

clean:
	rm -f *.o Test calc *.out *.gcov *.gcda *.gcno *.info *.a
	rm -rf ./report
	rm -rf app
check:
	cppcheck *.h *.c
	CK_FORK=no leaks --atExit -- ./Test

