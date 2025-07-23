.PHONY: r run m manual c clean

opt = 0
seed = 0
cnt = -1
dbg = 1

SANITIZER = -fsanitize=undefined,address
ifeq ($(dbg), 1)
CFLAGS = -include ../lib/debug/debug.hpp -g -std=c++17 -DLOCAL -D_GLIBCXX_NO_ASSERTIONS
else ifeq ($(dbg), 0)
CFLAGS = -g -std=c++17 -D_GLIBCXX_NO_ASSERTIONS
endif

r run: a.out safe.out tester
	@echo
	@./tester $(seed) $(cnt)

m manual: a.out safe.out tester
	watchexec -e inp "./a.out <a.inp >a.output; ./safe.out <a.inp >a.ans; diff a.output a.ans"

c clean:
	rm *.o
	rm a.out
	rm safe.out
	rm tester

ifeq ($(opt), 0)
a.out: a.o
	g++ $(SANITIZER) $< -o $@
safe.out: safe.o
	g++ $(SANITIZER) $< -o $@
tester: tester.o
	g++ $(SANITIZER) $< -o $@
else ifeq ($(opt), 2)
a.out: a2.o
	g++ $< -o $@
safe.out: safe2.o
	g++ $< -o $@
tester: tester2.o
	g++ $< -o $@
endif

%.o: %.cpp
	@g++ -include ../bits/stdc++.h $(CFLAGS) $(SANITIZER) $< -c -o $@

%2.o: %.cpp
	@g++ $(CFLAGS) -O2 $< -c -o $@
