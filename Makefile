all: lib
 
examples: Rest.o TwiML.o Examples.o Utils.o
	g++ -o examples Rest.o TwiML.o Utils.o Examples.o -lcurl 

lib: Rest.o TwiML.o Utils.o
	ar rcs twilio-cplusplus.a Rest.o TwiML.o Utils.o

Rest.o: Rest.cpp
	      g++ -Wall -c -o Rest.o Rest.cpp

TwiML.o: TwiML.cpp
	      g++ -Wall -c -o TwiML.o TwiML.cpp

Utils.o: Utils.cpp
	      g++ -Wall -c -o Utils.o Utils.cpp

Examples.o: Examples.cpp
	      g++ -Wall -c -o Examples.o Examples.cpp

unittests: runner
	./runner

runner: runner.cpp
	g++ -Wall -I./ -o $@ Rest.o TwiML.o Utils.o -lcurl $^

runner.cpp: UnitTests.h
	./cxxtestgen.py -o $@ --error-printer $^
