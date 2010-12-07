/*
 * Twilio REST C++
 * Author: Laurent Luce
*/

#ifndef TWILIOUTILS_H
#define TWILIOUTILS_H

namespace twilio
{
  class Utils {
    public:
      /**
       * Constructor
       */
      Utils()
      {
      }
     
  };

  /**
    * Replace all occurences of needle in haystack by replacement
    * @param haystack string to search in
    * @param needle string to search for
    * @param replacement string to replace with
  */
  string replaceAll(const string& haystack, const string& needle, const string& replacement);

  /**
   * Convert integer to string
   * @param i integer to convert
   * @return string
  */
  string intToStr(int i);
}

#endif
