/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#include <iostream>
#include <string>
#include <algorithm>

#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

using namespace std;

#include "TwilioRest.h"

/**
 * HTTP request
 * @param path URL path
 * @param method HTTP method: "GET", "POST", "PUT", "DELETE"
 * @param vars URL attributes or POST attributes
 * @return HTTP response
 */
string TwilioRest::Request(string path, string method, Var vars[])
{
  string response;
    
  if (path.length() <= 0)
    throw "Path is empty";
    
  transform(method.begin(), method.end(), method.begin(), ::toupper);

  if ((method != "GET" && method != "POST"
        && method != "PUT" && method != "DELETE"))
  {
    throw "Invalid method parameter";
  }
    
  string url = Build_uri(path);
  if(method == "GET")
  {
    response = Get(url, vars);
  }
  else if(method == "POST")
  {
    response = Post(url, vars);
  }
  
  return response;
}

/**
 * Curl write function
 * @param data data received from server
 * @param size data size is size * nmemb
 * @param nmemb data size is size * nmemb
 * @param buffer
 */
static int writer(char *data, size_t size, size_t nmemb, string *buffer)
{
  int result = 0;
  if (buffer != NULL)
  {
    buffer->append(data, size * nmemb);
    result = size * nmemb;
  }
  return result;
}

/**
 * HTTP GET request
 * @param url HTTP request URL
 * @param vars URL attributes or POST attributes
 * @return HTTP response
 */
string TwilioRest::Get(string url, Var vars[])
{
  string query = "";
  
  int i = 0;
  while(vars[i].key != "")
  {
    query += "&" + vars[i].key + "=" + vars[i].value;
    i++;
  }
    
  if (query.length() > 0)
    url = url + "?" + query.substr(1);

  CURL *curl;
  CURLcode res;
     
  curl = curl_easy_init();
  if(curl) {
    //url = curl_easy_escape(curl, url.c_str(), url.length());
    cout << url << endl;
    string sAuth = tid + ":" + ttoken;
    cout << sAuth << endl;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
    curl_easy_setopt(curl, CURLOPT_USERPWD, sAuth.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tbuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res == CURLE_OK)
      return tbuffer;
  }
  
  return "";
}
/**
 * HTTP POST request
 * @param url HTTP request URL
 * @param vars POST attributes
 * @return HTTP response
*/
string TwilioRest::Post(string url, Var vars[])
{
  CURL *curl;
  CURLcode res;
    
  struct curl_httppost *formpost = NULL;
  struct curl_httppost *lastptr = NULL;
  struct curl_slist *headerlist = NULL;
  static const char buf[] = "Expect:";

  curl_global_init(CURL_GLOBAL_ALL);

  // Post data
  int i = 0;
  while(vars[i].key != "")
  {
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, vars[i].key.c_str(),
                 CURLFORM_COPYCONTENTS, vars[i].value.c_str(),
                 CURLFORM_END);
    i++;
  }

  curl = curl_easy_init();
  headerlist = curl_slist_append(headerlist, buf);

  if(curl) {
    cout << url << endl;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    string sAuth = tid + ":" + ttoken;
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
    curl_easy_setopt(curl, CURLOPT_USERPWD, sAuth.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tbuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_formfree(formpost);
    curl_slist_free_all (headerlist);
    if (res == CURLE_OK)
      return tbuffer;
  }
  
  return "";
}

/**
 * Prefix path with Twilio URL
 * @param path URL path
 * @return full URL
 */
string TwilioRest::Build_uri(string path)
{
  if (path[0] == '/')
    return TWILIO_API_URL + path;
        else
    return TWILIO_API_URL + "/" + path;
}
 
const string TwilioRest::TWILIO_API_URL = "https://api.twilio.com";


