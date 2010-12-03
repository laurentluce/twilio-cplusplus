/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "TwilioTwiML.h"

/**
  * Append a children verb
  * @param verb Twilio verb
  * @return verb
*/
TwilioVerb TwilioVerb::append(TwilioVerb verb)
{
  vector<string>::iterator result;
  result = find(allowedVerbs.begin(), allowedVerbs.end(), verb.getTag());
  if(result == allowedVerbs.end())
  {
    throw "This is not a supported verb";
  }
  else
  {
    children.push_back(verb);
    return verb;
  }
}

/**
  * Get verb body
  * @return verb body
*/
string TwilioVerb::getBody()
{
  return tbody;
}

/**
  * Get verb tag
  * @return verb tag
*/
string TwilioVerb::getTag()
{
  return ttag;
}

/**
  * Get verb children
  * @return vector of verbs
*/
vector<TwilioVerb> TwilioVerb::getChildren()
{
  return children;
}

/**
  * Get verb attributes
  * @return vector of attributes
*/
vector<Var> TwilioVerb::getAttributes()
{
  return attributes;
}

/**
  * Return verb xml based on tag, body, attributes and its children
  * @return verb xml
*/
string TwilioVerb::toXML()
{
  string xml = "<" + ttag;
  for (unsigned int i = 0; i < attributes.size(); i++)
  {
    xml += " " + attributes[i].key + "=\"" + attributes[i].value + "\"";
  }
  
  xml += ">";
  
  // TODO:
  //if(tbody.length() > 0)
  //  xml += "<![CDATA[" + tbody.replaceAll("]]>",
  //          "]]>]]><![CDATA[")+ "]]>";
  for (unsigned int i = 0; i < children.size(); i++)
  {
    xml += children[i].toXML();
  }
  
  return xml += "</" + ttag + ">";
}

const string TwilioVerb::V_SAY = "Say";
const string TwilioVerb::V_PLAY = "Play";
const string TwilioVerb::V_GATHER = "Gather";
const string TwilioVerb::V_RECORD = "Record";
const string TwilioVerb::V_PAUSE = "Pause";
const string TwilioVerb::V_HANGUP = "Hangup";
const string TwilioVerb::V_DIAL = "Dial";
const string TwilioVerb::V_NUMBER = "Number";
const string TwilioVerb::V_REDIRECT = "Redirect";
const string TwilioVerb::V_RESPONSE = "Response";
const string TwilioVerb::V_CONFERENCE = "Conference";
const string TwilioVerb::V_SMS = "Sms";
const string TwilioVerb::V_REJECT = "Reject";


