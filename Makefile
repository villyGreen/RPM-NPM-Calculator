CFLAGS = -Wall -Werror -Wextra
all: clean calc

calc:
	gcc view.c controller.c model.c -o calc `pkg-config --cflags --libs gtk+-3.0`
	./calc

clean:
	rm -f *.o calc

rebuild: clean all



