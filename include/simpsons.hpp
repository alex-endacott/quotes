#ifndef SIMPSONS_H
#define SIMPSONS_H

#include"api.hpp"

class simpsons : public api
{
  public:
    simpsons();

    string getData();
};

#endif //SIMPSONS_H