/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#ifndef TWILIOREST_H
#define TWILIOREST_H

/** struct to contain the key and value for URL attributes or Body data */
struct Var { string key; string value; };
typedef struct Var Var;

class TwilioRest {
  public:
    /**
     * Constructor
     * @param id Twilio account SID
     * @param token Twilio account token
     */
    TwilioRest(string id, string token)
    {
       tid = id;
       ttoken = token;
    }

    /**
     * HTTP request
     * @param path URL path
     * @param method HTTP method: "GET", "POST", "PUT", "DELETE"
     * @param vars URL attributes or POST attributes
     * @return HTTP response
     */
    string Request(string path, string method, Var vars[]);

  private:
    /** Twilio account SID */
    string tid;
    /** Twilio account token */
    string ttoken;
    /** Response buffer */
    string tbuffer;
    /** Twilio API URL - set in cpp */
    static const string TWILIO_API_URL;

    /**
     * Prefix path with Twilio URL
     * @param path URL path
     * @return full URL
     */
    string Build_uri(string path);
    /**
     * HTTP GET request
     * @param url HTTP request URL
     * @param vars URL attributes
     * @return HTTP response
     */
    string Get(string url, Var vars[]);
    /**
     * HTTP POST request
     * @param url HTTP request URL
     * @param vars POST attributes
     * @return HTTP response
     */
    string Post(string url, Var vars[]);
};

#endif
