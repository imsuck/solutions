SANITIZER = -fsanitize=undefined,address
CFLAGS = -include ../lib/debug/debug.hpp -g -std=c++17 -DLOCAL -D_GLIBCXX_NO_ASSERTIONS

build: a.o safe.o tester.o
	g++ $(SANITIZER) a.o -o a.out
	g++ $(SANITIZER) safe.o -o safe.out
	g++ $(SANITIZER) tester.o -o tester

build2: a2.o safe2.o tester2.o
	g++ a2.o -o a.out
	g++ safe2.o -o safe.out
	g++ tester2.o -o tester

seed = 1
cnt = -1
run: a.out safe.out tester
	./tester $(seed) $(cnt)

rerun: build run

manual:
	watchexec -e inp "./a.out <a.inp >a.output; ./safe.out <a.inp >a.ans; diff a.output a.ans"

clean:
	rm *.o
	rm a.out
	rm safe.out
	rm tester

a.o: a.cpp
	@g++ -include ../bits/stdc++.h $(CFLAGS) $(SANITIZER) a.cpp -c -o a.o

safe.o: safe.cpp
	@g++ -include ../bits/stdc++.h $(CFLAGS) $(SANITIZER) safe.cpp -c -o safe.o

tester.o: tester.cpp
	@g++ -include ../bits/stdc++.h $(CFLAGS) $(SANITIZER) tester.cpp -c -o tester.o

a2.o: a.cpp
	@g++ -include ../bits/stdc++.h $(CFLAGS) a.cpp -c -o a2.o

safe2.o: safe.cpp
	@g++ -include ../bits/stdc++.h $(CFLAGS) safe.cpp -c -o safe2.o

tester2.o: tester.cpp
	@g++ -include ../bits/stdc++.h $(CFLAGS) tester.cpp -c -o tester2.o
