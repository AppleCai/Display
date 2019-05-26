#ifndef KEY_HPP
#define KEY_HPP
#include "head.hpp"

class key
{
public:
  //typedef std::shared_ptr<key> Ptr;
  key(display* disp);
  ~key(){};
  int KeyDetect();
  bool getJumpInfo();
  bool getTransCmd();
private:
  bool jump;
  bool status;
};

#endif
