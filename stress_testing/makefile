build: a.cpp safe.cpp tester.cpp
	g++ -include ../bits/stdc++.h -include ../lib/debug/debug.hpp -std=c++17 -DLOCAL -fsanitize=undefined,address -g a.cpp -o a.out
	g++ -include ../bits/stdc++.h -include ../lib/debug/debug.hpp -std=c++17 -DLOCAL -fsanitize=undefined,address -g safe.cpp -o safe.out
	g++ -include ../bits/stdc++.h -std=c++17 -DLOCAL -fsanitize=undefined,address -g tester.cpp -o tester

build2: a.cpp safe.cpp tester.cpp
	g++ -O2 -include ../lib/debug/debug.hpp -std=c++17 -DLOCAL -fsanitize=undefined,address -g a.cpp -o a.out
	g++ -O2 -include ../lib/debug/debug.hpp -std=c++17 -DLOCAL -fsanitize=undefined,address -g safe.cpp -o safe.out
	g++ -O2 -std=c++17 -DLOCAL -fsanitize=undefined,address -g tester.cpp -o tester

seed = 1
cnt = -1
run: a.out safe.out tester
	./tester $(seed) $(cnt)

rerun: build run

manual:
	watchexec -e inp "./a.out <a.inp >a.output; ./safe.out <a.inp >a.ans; diff a.output a.ans"
