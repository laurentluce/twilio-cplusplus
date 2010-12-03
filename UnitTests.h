/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "cxxtest/TestSuite.h"
#include "TwilioRest.h"
#include "TwilioTwiML.h"

class TwilioTestSuite : public CxxTest::TestSuite
{
    public:
      void testRest(void)
      {
        string response;
        vector<Var> vars;
        Var var;
        TwilioRest t (ACCOUNT_SID, ACCOUNT_TOKEN);

        // completed calls
        vars.clear();
        var.key = "Status";
        var.value = "completed";
        vars.push_back(var);
        response = t.request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/Calls", "GET", vars);
        TS_ASSERT(true);
        
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
        TS_ASSERT(true);
      }

      void testTwiML(void)
      {
        // Say, Dial and Play
        TwiMLResponse response;
        Say say ("Hello, how are you?");
        say.setLoop(5);
        say.setVoice("woman");
        response.append(say);
        TS_ASSERT(response.toXML() == "<Response><Say loop=\"5\" voice=\"woman\"><![CDATA[Hello, how are you?]]></Say></Response>");
      } 

    private:
      static const string API_VERSION;
      static const string ACCOUNT_SID;
      static const string ACCOUNT_TOKEN;
      static const string CALLER_ID;
};

const string TwilioTestSuite::API_VERSION = "2010-04-01";
const string TwilioTestSuite::ACCOUNT_SID = "SID";
const string TwilioTestSuite::ACCOUNT_TOKEN = "TOKEN";
const string TwilioTestSuite::CALLER_ID = "NNNNNNNNNN";

