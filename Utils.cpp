/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

#include "Utils.h"
#include "Rest.h"
#include "crypto/HMAC_SHA1.h"
#include "crypto/Base64.h"

namespace twilio {
  /**
    * Check if expectedSignature matches url + params base64 encoded hash
    * @param expectedSignature signature to compare to 
    * @param url URL to build hash on
    * @param params POST params
  */
  bool Utils::validateRequest(const string& expectedSignature, const string& url, vector<Var>& params)
  {
    string u = url;

    // sort params alphabetically
    sort(params.begin(), params.end());
  
    // add params to url  
    for(unsigned int i = 0; i < params.size(); i++)
    {
      u += params[i].key + params[i].value;
    }

    unsigned int len = ttoken.length();
    CHMAC_SHA1 HMAC_SHA1;
    BYTE* digest = new BYTE[20];
    HMAC_SHA1.HMAC_SHA1((BYTE*)(u.c_str()), u.length(), (BYTE*)(ttoken.c_str()), len, digest);
    
    string digest_enc;
    digest_enc = base64_encode(digest, len);
    cout << expectedSignature.c_str() << endl;
    cout << digest_enc << endl;
    if(memcmp(expectedSignature.c_str(), digest_enc.c_str(), len) == 0)
      return true;
    else
      return false;
  }

  /**
    * Replace all occurences of needle in haystack by replacement
    * @param haystack string to search in
    * @param needle string to search for
    * @param replacement string to replace with
  */
  string replaceAll(const string& haystack, const string& needle, const string& replacement) {
    if (needle.empty()) {
      return haystack;
    }
    string result;
    for (string::const_iterator substart = haystack.begin(), subend; ; ) {
      subend = search(substart, haystack.end(), needle.begin(), needle.end());
      copy(substart, subend, back_inserter(result));
      if (subend == haystack.end()) {
        break;
      }
      copy(replacement.begin(), replacement.end(), back_inserter(result));
      substart = subend + needle.size();
    }
    return result;
  }

  /**
   * Convert integer to string
   * @param i integer to convert
   * @return string
  */
  string intToStr(int i)
  {
    stringstream out;
    out << i;
    return out.str();
  }
 
  /**
   * '<' operator to compare 2 Var structure based on their key string
   * @param a Var 1
   * @param b Var 1
   * @return < result
  */
  bool operator<(const Var& a, const Var& b) {
        return a.key < b.key;
  }

}



