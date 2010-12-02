/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#include <iostream>
#include <string>

using namespace std;

#include "TwilioRest.h"

int main () {

  // Twilio REST API version
  const string API_VERSION = "2010-04-01";
  
  // Twilio AccountSid and AuthToken
  const string ACCOUNT_SID = "ACa8e1bcd8948d695aa731bcc128b772dd";
  const string ACCOUNT_TOKEN = "cd88c470c893f3db8d727f1eca6dba63";
  
  // Outgoing Caller ID previously validated with Twilio
  const string CALLER_ID = "NNNNNNNNNN";

  string response;

  TwilioRest t (ACCOUNT_SID, ACCOUNT_TOKEN);
  Var vars[4];

  try {
    
    // get completed calls XML
    vars[0].key = "Status";
    vars[0].value = "completed";
    response = t.Request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/Calls", "GET", vars);
    cout << response << endl;

    // send SMS
    vars[0].key = "To";
    vars[0].value = "650-430-4065";
    vars[1].key = "From";
    vars[1].value = "650-451-1116";
    vars[2].key = "Body";
    vars[2].value = "Hello, how are you?";
    vars[3].key = "";
    response = t.Request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/SMS/Messages", "POST", vars);
    cout << response << endl;

  }
  catch(char const* str) {
    cout << "Exception raised: " << str << endl;
  }


  return 0;
}
