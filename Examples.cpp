/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "TwilioRest.h"
#include "TwilioTwiML.h"

int main () {

  // Twilio REST API version
  const string API_VERSION = "2010-04-01";
  
  // Twilio AccountSid and AuthToken
  const string ACCOUNT_SID = "SID";
  const string ACCOUNT_TOKEN = "TOKEN";
  
  // Outgoing Caller ID previously validated with Twilio
  const string CALLER_ID = "NNNNNNNNNN";

  string response;

  vector<Var> vars;
  Var var;

  try {
    
    TwilioRest t (ACCOUNT_SID, ACCOUNT_TOKEN);

    // get completed calls XML
    vars.clear();
    var.key = "Status";
    var.value = "completed";
    vars.push_back(var);
    response = t.request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/Calls", "GET", vars);
    cout << response << endl;

    // send SMS
    vars.clear();
    var.key = "To";
    var.value = "xxx-xxx-xxxx";
    vars.push_back(var);
    var.key = "From";
    var.value = "xxx-xxx-xxxx";
    vars.push_back(var);
    var.key = "Body";
    var.value = "Hello, how are you?";
    vars.push_back(var);
    response = t.request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/SMS/Messages", "POST", vars);
    cout << response << endl;

    // TwiML

    // Say, Dial and Play
    TwiMLResponse response;
    Say say ("Hello, how are you?");
    say.setLoop(5);
    say.setVoice("woman");
    response.append(say);
    cout << response.toXML() << endl;

  }
  catch(char const* str) {
    cout << "Exception raised: " << str << endl;
  }

  return 0;
}
