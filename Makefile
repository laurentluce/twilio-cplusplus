all: lib
 
examples: Rest.o TwiML.o Examples.o Utils.o HMAC_SHA1.o SHA1.o Base64.o
	g++ -o examples Rest.o TwiML.o Utils.o Examples.o HMAC_SHA1.o SHA1.o Base64.o -lcurl 

lib: Rest.o TwiML.o Utils.o HMAC_SHA1.o SHA1.o Base64.o
	ar rcs twilio-cplusplus.a Rest.o TwiML.o Utils.o HMAC_SHA1.o SHA1.o Base64.o

Rest.o: Rest.cpp
	      g++ -Wall -c -o Rest.o Rest.cpp

TwiML.o: TwiML.cpp
	      g++ -Wall -c -o TwiML.o TwiML.cpp

Utils.o: Utils.cpp
	      g++ -c -o Utils.o Utils.cpp

Examples.o: Examples.cpp
	      g++ -Wall -c -o Examples.o Examples.cpp

HMAC_SHA1.o: crypto/HMAC_SHA1.cpp
	      g++ -c -o HMAC_SHA1.o crypto/HMAC_SHA1.cpp

SHA1.o: crypto/SHA1.cpp
	      g++ -c -o SHA1.o crypto/SHA1.cpp

Base64.o: crypto/SHA1.cpp
	      g++ -c -o Base64.o crypto/Base64.cpp

unittests: runner
	./runner

runner: runner.cpp
	g++ -Wall -I./ -o $@ Rest.o TwiML.o Utils.o HMAC_SHA1.o SHA1.o Base64.o -lcurl $^

runner.cpp: UnitTests.h
	./cxxtestgen.py -o $@ --error-printer $^
