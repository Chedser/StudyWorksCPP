#ifndef IOMANAGER_H
#define IOMANAGER_H


#include <iostream>
#include <fstream>

using std::string;
using std::ifstream;

namespace Morozov {
/* Вспомогательный класс для работы с файлами */    
class IOManager {

    public:  
     
        static string GetManual();
        static bool FileExists(string fileName);
        static  bool FileIsEmpty(string fileName);
       static bool IsDigit(string str);

    };

};
#endif


