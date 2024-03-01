#pragma  once
#include<string>

std::string to_lower(std::string text){

  for (size_t i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i]);
    }
  return text;

}

std::string to_upper(std::string text){

  for (size_t i = 0; i < text.length(); i++) {
        text[i] = toupper(text[i]);
    }
  return text;

}
