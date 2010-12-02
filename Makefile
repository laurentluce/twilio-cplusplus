all: twilio

twilio: TwilioRest.o Examples.o
	g++ -o twilio TwilioRest.o Examples.o -lcurl 

TwilioRest.o: TwilioRest.cpp
	      g++ -Wall -c -o TwilioRest.o TwilioRest.cpp

Examples.o: Examples.cpp
	      g++ -Wall -c -o Examples.o Examples.cpp
