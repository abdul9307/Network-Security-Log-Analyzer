#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

vector<string> timestamps;
vector<string> sourceIPs;
vector<string> destIPs;
vector<int> ports;
vector<string> actions;
vector<string> usernames;
vector<string> results;

int main()
{
    string filePath;
    cout << "Enter csv file path: ";
    getline(cin, filePath);
    ifstream filein(filePath);
    ofstream rejects("rejects.txt");
    
    if (!filein.is_open())
    {
        cout << "Error: Cannot open file" << endl;
        return 1;
    }

    string line;
    int lineNumber = 0;
    int malformedCount = 0;

    while (getline(filein, line))
    {
        lineNumber++;
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string token;
        vector<string> fields;
        
        while (getline(ss,token, ','))
        {
            fields.push_back(token);
        }

        if (fields.size() != 7) 
        {
            rejects << "Line " << lineNumber << ": [" << line << "] - Invalid number of fields" << endl;
            malformedCount ++;
            continue;
        }

        string timestamp = fields[0];
        string sourceIP = fields[1];
        string destIP = fields[2];
        string portStr = fields[3];
        string action = fields[4];
        string username = fields[5];
        string result = fields[6];

        int port;
        try
        {
            port = stoi(portStr);

        }
        catch(const std::exception& e)
        {
            rejects << "Line " << lineNumber << ": [" << line << "] - Invalid port" << endl;
            malformedCount ++;
            continue;
        }
        
        if (port < 0 || port > 65535)
        {
            rejects << "Line " << lineNumber << ": [" << line << "] - Invalid port" << endl;
            malformedCount ++;
            continue;
        }

        if (action != "LOGIN")
        {
            rejects << "Line " << lineNumber << ": [" << line << "] - Invalid action" << endl;
            malformedCount ++;
            continue;
        }

        if (result != "FAIL" && result != "SUCCESS")
        {
            rejects << "Line " << lineNumber << ": [" << line << "] - Invalid result" << endl;
            malformedCount ++;
            continue;
        }

        timestamps.push_back(timestamp);
        sourceIPs.push_back(sourceIP);
        destIPs.push_back(destIP);
        ports.push_back(port);
        actions.push_back(action);
        usernames.push_back(username);
        results.push_back(result);
    }

    filein.close();
    rejects.close();

    cout << "Log loading complete" << endl;
    cout << "Valid entries: " << timestamps.size() << endl;
    cout << "Rejected entries: " << malformedCount << endl;
    return 0;
    
}

