/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#ifndef TWILIOTWIML_H
#define TWILIOTWIML_H

/** struct to contain the key and value for URL attributes or Body data */
struct Var { string key; string value; };
typedef struct Var Var;

class TwilioVerb {
  public:
    /**
     * Constructor
     * @param tag TwiML tag
     * @param body TwiML tag body
     */
    TwilioVerb(string tag, string body)
    {
       ttag = ttag;
       tbody = body;
    }

    static const string V_SAY;
    static const string V_PLAY;
    static const string V_GATHER;
    static const string V_RECORD;
    static const string V_PAUSE;
    static const string V_HANGUP;
    static const string V_DIAL;
    static const string V_NUMBER;
    static const string V_REDIRECT;
    static const string V_RESPONSE;
    static const string V_CONFERENCE;
    static const string V_SMS;
    static const string V_REJECT;

  private:
    /** tag */
    string ttag;
    /** tag body */
    string tbody;
    /** attributes */
    vector<Var> attributes;
    /** children */
    vector<TwilioVerb> children;
    /** allowed verbs */
    vector<string> allowedVerbs;

    /**
     * Append a children verb
     * @param verb Twilio verb
     * @return verb
     */
    TwilioVerb append(TwilioVerb verb);
    
    /**
      * Get verb body
      * @return verb body
    */
    string getBody();

    /**
      * Get verb tag
      * @return verb tag
    */
    string getTag();
    
    /**
      * Get verb children
      * @return vector of verbs
    */
    vector<TwilioVerb> getChildren();

    /**
      * Get verb attributes
      * @return vector of attributes
    */
    vector<Var> getAttributes();
    
    /**
      * Return verb xml based on tag, body, attributes and its children
      * @return verb xml
    */
    string toXML();

};

#endif
