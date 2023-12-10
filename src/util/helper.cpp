#include"helper.h"

std::string Helper::remove_last_char(std::string str){
  int length = str.length();
  if(length <=0) return "";
  return str.substr(0, length-1);
}
