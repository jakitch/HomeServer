#include <iostream>
#include <vector> 
#include <functional>
#include "Logger.hpp"


using std::string;
using std::vector;
using std::cerr;
using std::endl;
using std::function;

struct HostAndPort{
    string hostname;
    int port;
};

struct cmdlineArg {
    string longhand;
    string shorthand;
    void* action;
};

bool matchCommand(const string, const string, const string);
HostAndPort* handleArguments(const vector<string>*);
void addHostName(vector<string>, HostAndPort*);

vector<cmdlineArg> initArgs() {
    auto args = new vector<cmdlineArg>;

    //hostname argument
    auto hostnameArg = new cmdlineArg;
    hostnameArg->longhand = "-host";
    hostnameArg->shorthand = "-h";
    hostnameArg->action = &[](vector<string>* arguments, int targetIndex, HostAndPort* hostAndPort) {
        hostAndPort->hostname = arguments->at(targetIndex); 
    }
}
int main(const int argc, const char* argv[]) {

    Logger* logger = new Logger(OFF);
    logger->log("Hello, you are gay!", ALL);
    logger->log("Hello, you are gay!", DEBUG);
    logger->log("Hello, you are gay!", INFO);
    logger->log("Hello, you are gay!", WARN);
    logger->log("Hello, you are gay!", ERROR);
    logger->log("Hello, you are gay!", FATAL);
    logger->log("Hello, you are gay!", OFF);

    if (argc < 2) {
        cerr << "Missing hostname and port" << endl;
        exit(EXIT_FAILURE);
    }
    auto arguments = new vector<string>;
    for (int ii = 1; ii < argc; ii++) {
        arguments->push_back(string(argv[ii]));
    }
    HostAndPort* hostAndPort = handleArguments(arguments);
    exit(EXIT_SUCCESS);
}


HostAndPort* handleArguments(const vector<string>* arguments) {

    const vector longhand = {"-host", "-port", "-log"};
    const vector shorthand = {"-h", "-p", "-l"};
    const vector<void*> executeCommand;
    
    const int numKnownCommands = 3;

    HostAndPort* hostAndPort = new HostAndPort;
    int index = 0;
    bool skip = false;

    for(auto const &arg: *arguments) {
        if (skip) {
            skip = false;
            continue;
        }
        try {
            for(int ii = 0; ii < numKnownCommands; ii++) {
                if(matchCommand(arg, longhand.at(ii), shorthand.at(ii))) {
                    string value = arguments->at(index+1);
                    if(value.at(0) != '-') {
                        //(action.at(ii))(arguments, hostAndPort);
                        skip = true;
                    }
                    else
                        throw (arg);
                }
            }
            cerr << "Unknown argument: '" << arg << "'" << endl;
            exit(EXIT_FAILURE);

        } catch (const std::out_of_range& e) {
            cerr << "Missing argument for '" << arg << "'" << endl;
            exit(EXIT_FAILURE);
        } catch (const string incompleteArg) {
            cerr << "Missing argument for '" << incompleteArg << "'" << endl;
            exit(EXIT_FAILURE);
        }
        index++;
    }
    return hostAndPort;
}

bool matchCommand(const string argument, const string longhand, const string shorthand) {
    if (argument.compare(longhand) == 0 || argument.compare(shorthand) == 0)
        return true;
    else
        return false;
}

void addHostName(vector<string>* arguments, HostAndPort*) {

}
