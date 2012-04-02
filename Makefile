ex1:	symbol.cpp symbol.h source.cpp source.h main1.cpp
	g++ symbol.cpp source.cpp main1.cpp -o lector

ex2: symbol.cpp symbol.h source.cpp source.h hufftree.cpp hufftree.h main2.cpp
	g++ symbol.cpp source.cpp hufftree.cpp main2.cpp -o arbol
