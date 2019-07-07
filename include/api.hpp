#ifndef API_H
#define API_H

#include<iostream>
#include"json.hpp"

using std::string;
using json = nlohmann::json;

class api
{
  protected:
    string url;
    string subfolder;

  public:
    string getUrl(){return this->url;}
    string getSubFolder(){return this->subfolder;}
    string call();
    virtual string getData() = 0;
};

#endif //API_H