/*
  @copyright Steve Keen 2013
  @author Russell Standish
  This file is part of Minsky.

  Minsky is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Minsky is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Minsky.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef STR_H
#define STR_H
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <memory>
#include <string.h>

namespace minsky
{
  /// utility function to create a string representation of a numeric type
  // works better than std::to_string
  template <class T> std::string str(T x) {
    std::ostringstream s;
    s<<x;
    return s.str();
  }

  // needed for remove_if below
  inline bool IsNotalnum(char x) {return !std::isalnum(x);}
  // strip non alphanum characters - eg signs
  inline void stripNonAlnum(std::string& x) {
    x.erase(std::remove_if(x.begin(), x.end(), IsNotalnum), x.end());
  } 

  // removes white space from beginning and end
  inline std::string trimWS(const std::string& s)
  {
    int start=0, end=s.length()-1;
    while (start<int(s.length()) && isspace(s[start])) ++start;
    while (end>=0 && isspace(s[end])) --end;
    if (end>=start)
      return s.substr(start,end-start+1);
    else
      return "";
  }

  /// strips characters that cause interpretation by TCL backslashes
  // are eliminated, and spaces are replaced by underscores, as they
  // cause problems
  inline std::string stripActive(const std::string& s) {
    std::string r;
    for (size_t i=0; i<s.length(); ++i)
      if (strchr("\\{}",s[i])==nullptr)
        {
          if (isspace(s[i]))
            r+='_';
          else
            r+=s[i];
        }
    if (r.empty()) return "_";
    return r;
  }

  /// arrange for a functional to be called on stack exit
  template <class F> struct OnStackExit
  {
    F f;
    OnStackExit(F f): f(f) {}
    ~OnStackExit() {f();}
  };

  /// generator function
  template <class F> OnStackExit<F> onStackExit(F f) {return OnStackExit<F>(f);}

  /// remove an element from a vector. V must be comparable to a T
  template <class T, class V>
  void remove(std::vector<T>& x, const V& v)
  {x.erase(std::remove(x.begin(),x.end(),v),x.end());}

  template <class T, class D>
  std::unique_ptr<T,D> uniqueDeleter(T* x, D d)
  {return std::unique_ptr<T,D>(x,d);}

  /// a wrapper around std::ofstream that checks the write succeeded,
  /// throwing an exception if not
  
}
#endif
