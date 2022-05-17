#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_BobIsInTheSaloon,
  Msg_DrunkardWin,
  Msg_BobWin
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";
  
  case 2:

    return "BobIsInTheSaloon";

  case 3:

      return "DrunkardWin";

  case 4:

      return "BobWin";

  default:

    return "Not recognized!";
  }
}

#endif