CC=gcc
CFLAGS=-Wall -Wextra -O3
CLIBS=-lm -lSDL2main -lSDL2 -lpthread

main: create-build-dir
	${CC} -o build/raytracing src/*.c ${CFLAGS} ${CLIBS} -I.

debug: create-build-dir
	${CC} -g -o build/raytracing-debug src/*.c ${CFLAGS} ${CLIBS} -I.

analyze: create-build-dir
	${CC} -pg -o build/raytracing-analyze src/*.c ${CFLAGS} ${CLIBS} -I.
	build/raytracing-analyze
	gprof build/raytracing-analyze gmon.out > analysis.txt

test: create-build-dir
	${CC} -o build/linalg_tests src/vector.c src/matrix.c tests/linalg_tests.c -lm -lcheck -lsubunit -I.
	build/linalg_tests

create-build-dir:
	mkdir -p build

run: main
	build/raytracing

clean:
	rm -r build
	rm gmon.out
	rm analysis.txt
