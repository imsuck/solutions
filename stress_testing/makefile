build: a.cpp safe.cpp tester.cpp
	g++ -include ../bits/stdc++.h -include ../lib/debug/debug.hpp -std=c++17 -DLOCAL -fsanitize=undefined,address -g a.cpp -o a.out
	g++ -include ../bits/stdc++.h -include ../lib/debug/debug.hpp -std=c++17 -DLOCAL -fsanitize=undefined,address -g safe.cpp -o safe.out
	g++ -include ../bits/stdc++.h -std=c++17 -DLOCAL -fsanitize=undefined,address -g tester.cpp -o tester

seed = 1
cnt = -1
run: a.out safe.out tester
	./tester $(seed) $(cnt)
