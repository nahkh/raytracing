CC=gcc
CFLAGS=-Wall -Wextra


main:
	${CC} -o build/raytracing src/*.c ${CFLAGS} -lm -lSDL2main -lSDL2 -I.

test:
	${CC} -o build/linalg_tests src/vector.c src/matrix.c tests/linalg_tests.c -lm -lcheck -lsubunit -I.
	build/linalg_tests

run: main
	build/raytracing

clean:
	rm build/*