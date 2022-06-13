CC=gcc
CFLAGS=-Wall -Wextra -O3

main: create-build-dir
	${CC} -o build/raytracing src/*.c ${CFLAGS} -lm -lSDL2main -lSDL2 -I.

debug: create-build-dir
	${CC} -g -o build/raytracing-debug src/*.c ${CFLAGS} -lm -lSDL2main -lSDL2 -I.

test: create-build-dir
	${CC} -o build/linalg_tests src/vector.c src/matrix.c tests/linalg_tests.c -lm -lcheck -lsubunit -I.
	build/linalg_tests

create-build-dir:
	mkdir -p build

run: main
	build/raytracing

clean:
	rm -r build