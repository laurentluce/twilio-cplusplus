/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#ifndef TWILIOREST_H
#define TWILIOREST_H

namespace twilio {

  /** struct to contain the key and value for URL attributes or Body data */
  struct Var { string key; string value; };
  typedef struct Var Var;

  class Rest {
    public:
      /**
       * Constructor
       * @param id Twilio account SID
       * @param token Twilio account token
       */
      Rest(const string& id, const string& token)
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
      string request(const string& path, string method, vector<Var>& vars);

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
      string build_uri(const string& path);
      /**
       * HTTP GET request
       * @param url HTTP request URL
       * @param vars URL attributes
       * @return HTTP response
       */
      string get(string url, vector<Var>& vars);
      /**
       * HTTP POST request
       * @param url HTTP request URL
       * @param vars POST attributes
       * @return HTTP response
       */
      string post(string url, vector<Var>& vars);
      /**
       * HTTP PUT request
       * @param url HTTP request URL
       * @param filename File to read data from
       * @return HTTP response
      */
      string put(string url, const string& filename);
      /**
       * HTTP DELETE request
       * @param url HTTP request URL
       * @return HTTP response
      */
      string tdelete(string url);

  };

}

#endif
