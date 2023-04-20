#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>

static enum Serverity { DEBUG, INFO, WARNING, ERROR};


static const char* logEnum2Strings[] = {
    "DEBUG",
    "INFO ",
    "WARN ",
    "ERROR",
};

/// <summary>add a serverity from the enum DEBUG,INFO,WARN,ERROR then the message {stuff} (its a string) </summary>
/// <param name="serverity">: enum on how servere the log is</param>
/// <param name="message">: the log detailed message </param>
#define CONSOLE(serverity, message) log_create(serverity, __FILE__, __LINE__ ,message)

static void addbrace(std::string& string)
{
    string.insert(0, 1, '[');
    string.append("]");
}

/// <summary>
/// Create a console log
/// </summary>
/// <param name="_serverity"> enum on how servere the log is</param>
/// <param name="_filename"> the file it came from</param>
/// <param name="_line_number"> the line the log came from</param>
/// <param name="_message"> the log detailed message </param>
static void log_create(Serverity _serverity, std::string _filename, int _line_number,std::string _message)
{
    //type initilisers
    std::string linenum;
    std::string filename;
    std::string serverity;

    // converts
    linenum = std::to_string(_line_number);
    serverity = logEnum2Strings[_serverity];

    // remove full file path of _filename
    auto last = _filename.find_last_of('\\') + 1;
    filename = _filename.substr(last);

    // add white space to end for uniform debugs
    filename.append((size_t)20 - std::min(20, int(filename.size())), ' ');

    // add leading 0s for uniform debugs
    if (_line_number < 100)
    {
        linenum.insert(0, _line_number < 10 ? 2 : 1, '0');
    }

    // add braces for clarity
    addbrace(serverity);
    addbrace(filename);
    addbrace(linenum);

    // uniform output
    //            type]  <<[filename]<< [line]  <<  :   <<" message" 
    //std::cout << _time;
    switch (_serverity)
    {
    case DEBUG:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        break;
    case INFO:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        break;
    case WARNING:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        break;
    case ERROR:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        break;
    default:
        break;
    }
    
    std::cout << serverity;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    std::cout << filename << linenum << ": " << _message << std::endl;
    
    
}


