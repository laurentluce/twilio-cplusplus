/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "cxxtest/TestSuite.h"
#include "Utils.h"
#include "Rest.h"
#include "TwiML.h"

using namespace twilio;

class TwilioTestSuite : public CxxTest::TestSuite
{
    public:
      void testRest(void)
      {
        string response;
        vector<Var> vars;
        Var var;
        Rest t (ACCOUNT_SID, ACCOUNT_TOKEN);

        // completed calls
        vars.clear();
        var.key = "Status";
        var.value = "completed";
        vars.push_back(var);
        response = t.request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/Calls", "GET", vars);
        TS_ASSERT(response.find("RestException") == string::npos);
       
        // make a call
        vars.clear();
        var.key = "To";
        var.value = "xxx-xxx-xxxx";
        vars.push_back(var);
        var.key = "From";
        var.value = "xxx-xxx-xxxx";
        vars.push_back(var);
        var.key = "Url";
        var.value = "http://xxxx";
        vars.push_back(var);
        response = t.request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/Calls", "POST", vars);
        TS_ASSERT(response.find("RestException") == string::npos);
 
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
        TS_ASSERT(response.find("RestException") == string::npos);
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
        
        // Gather, redirect
        TwiMLResponse response2;
        Gather gather;
        gather.setNumDigits(10);
        Say say2 ("Press 1");
        Redirect redirect;
        gather.append(say2);
        response2.append(gather);
        response2.append(redirect);
        TS_ASSERT(response2.toXML() == "<Response><Gather numDigits=\"10\"><Say><![CDATA[Press 1]]></Say></Gather><Redirect></Redirect></Response>");
      }

      void testUtils(void)
      {
        vector<Var> vars;
        Var var;

        // Twilio Utils
        Utils u (ACCOUNT_SID, ACCOUNT_TOKEN);

        // validate request signature
        vars.clear();
        var.key = "Status";
        var.value = "completed";
        vars.push_back(var);
        TS_ASSERT(u.validateRequest("mGgsPkZZfTGohCMY6yey2aWAAuU=", "/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/Calls", vars));
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

