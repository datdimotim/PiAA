all: KMP.o cycShift.o
	g++ KMP.o -o KMP
	g++ cycShift.o -o cycShift
KMP.o: KMP.cpp
	g++ -c KMP.cpp -o KMP.o
cycShift.o: cycShift.cpp
	g++ -c cycShift.cpp -o cycShift.o