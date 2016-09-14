/*
 * utilidades.cpp
 *
 *  Created on: 11 de ago. de 2016
 *      Author: ECERAMM
 */

#include <Utilidades.h>
#include <clocale>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <regex>
#include <dirent.h>
#include "../Json/json.h"

namespace utilidades {

  bool esMayuscula(char c) {
    std::setlocale(LC_ALL, localeSpanish);
    return std::isupper(c);
  }

  std::string removePuctuationFromText(const std::string &text) {
    std::string newText;
    std::setlocale(LC_ALL, localeSpanish);
    std::remove_copy_if(text.begin(), text.end(),
        std::back_inserter(newText),
        std::ptr_fun<int, int>(&std::ispunct)
    );
    return newText;
  }

  std::vector<std::string> splitTextInWords(const std::string& text) {
    std::istringstream linestream(text);
    std::string word;
    std::vector<std::string> words;
    while (linestream >> word) {
      words.push_back(word);
    }
    return words;
  }

  std::vector<std::string> obtenerNombreFicherosDesdeDirectorio(std::string &pathNews){
    DIR *pDIR;
    pDIR=opendir(pathNews.c_str());
    std::vector<std::string> ficheros;
    if(pDIR){
      struct dirent *entry;
      while((entry = readdir(pDIR))){
        std::string fileName(entry->d_name);
        if (fileName.compare(".") !=0
            && fileName.compare("..") != 0
            && isFormatoNombreFicheroCorrecto(fileName))
        {
          ficheros.push_back(pathNews+fileName);
        }
      }
      closedir(pDIR);
    }
    return ficheros;
  }

  bool isFormatoNombreFicheroCorrecto(std::string &fileName)
  {
    std::regex fileFormatSpanishTxt(spanishNewsFileNameFormat);
    if(std::regex_match(fileName,fileFormatSpanishTxt))
    {
      return true;
    }
    return false;
  }
}

