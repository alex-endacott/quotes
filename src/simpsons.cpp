#include"../include/simpsons.hpp"

simpsons::simpsons()
{
  this->url = "thesimpsonsquoteapi.glitch.me";
  this->subfolder = "/quotes";
}

string simpsons::getData()
{
  string str = this->call();
  json j_arr = json::parse(str);
  json j = j_arr[0];
  std::string character = j["character"];
  std::string quote = j["quote"];
  std::string output = "\"" + quote + "\"\n" + "- " + character + "\n"; 
  return output;
}