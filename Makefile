all: twilio

twilio: TwilioRest.o TwilioTwiML.o Examples.o
	g++ -o twilio TwilioRest.o Examples.o TwilioTwiML.o -lcurl 

TwilioRest.o: TwilioRest.cpp
	      g++ -Wall -c -o TwilioRest.o TwilioRest.cpp

TwilioTwiML.o: TwilioTwiML.cpp
	      g++ -Wall -c -o TwilioTwiML.o TwilioTwiML.cpp

Examples.o: Examples.cpp
	      g++ -Wall -c -o Examples.o Examples.cpp
