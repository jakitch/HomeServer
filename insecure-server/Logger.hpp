



#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <map>

#define ALL 0
#define DEBUG 1
#define INFO 2
#define WARN 3
#define ERROR 4
#define FATAL 5
#define OFF 6 

using std::cout;
using std::endl;
using std::string;
using std::map;

class Logger {
    public:
        Logger(int level = INFO);
        void log(string, int level);
        int getLevel();
        string getLevelString();
        void setLevel(int);
    private: 
        int level;
};

#endif
