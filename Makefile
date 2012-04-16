ex1:	symbol.cpp symbol.h source.cpp source.h binarizer.cpp binarizer.h  main1.cpp
	g++ symbol.cpp source.cpp main1.cpp binarizer.cpp -o modulo1 -DMODULO1=1

ex2: symbol.cpp symbol.h source.cpp source.h binarizer.cpp binarizer.h main2.cpp
	g++ symbol.cpp source.cpp main2.cpp binarizer.cpp -o modulo2 -DMODULO2=1

ex3: symbol.cpp symbol.h source.cpp source.h binarizer.cpp binarizer.h main3.cpp
	g++ symbol.cpp source.cpp binarizer.cpp main3.cpp -o modulo3

ex4: symbol.cpp symbol.h source.cpp source.h binarizer.cpp binarizer.h main4.cpp
	g++ symbol.cpp source.cpp main4.cpp binarizer.cpp -o modulo4
