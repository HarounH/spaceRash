#ifndef HTTP_SERVER2_HEADER_HPP
#define HTTP_SERVER2_HEADER_HPP

#include <string>

namespace server {

struct header
{
  std::string name;
  std::string value;
};

}


#endif // HTTP_SERVER2_HEADER_HPP