#include "Logger.hpp"

map<int,string> levelStrings = {
    {ALL, "ALL"},
    {DEBUG, "DEBUG"},
    {INFO, "INFO"},
    {WARN, "WARN"},
    {ERROR, "ERROR"},
    {FATAL, "FATAL"},
    {OFF, "OFF"}
};

Logger::Logger(int level) {
    this->level = level;
}
void Logger::log(string message, int level) {
    if (level >= this->level)
        cout << "[" << levelStrings[level] << "]: " << message << endl;
}
int Logger::getLevel() {
    return this->level;
}
std::string Logger::getLevelString() {
    return levelStrings[this->level];
}
void Logger::setLevel(int level) {
    this->level = level;
}


