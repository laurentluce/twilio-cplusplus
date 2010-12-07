/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

//#include "beecrypt/c++/security/spec/SecretKeySpec.h"

using namespace std;

#include "Utils.h"

namespace twilio {
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
}



