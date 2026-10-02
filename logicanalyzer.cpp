#include "logicanalyzer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

LogicAnalyzer::LogicAnalyzer() {}

// Convert timestamp to tm_sec (seconds since 1900)
// timestamp format: 2025-03-01T10:22:14
time_t LogicAnalyzer::toSeconds(const string &timestamp)
{
    struct tm t = {};
    int end = timestamp.find("-");
    t.tm_year = stoi(timestamp.substr(0, end)) - 1900;
    string temp = timestamp.substr(end + 1);

    end = temp.find("-");
    t.tm_mon = stoi(temp.substr(0, end)) - 1;
    temp = temp.substr(end + 1);

    end = temp.find("T");
    t.tm_mday = stoi(temp.substr(0, end));
    temp = temp.substr(end + 1);

    end = temp.find(":");
    t.tm_hour = stoi(temp.substr(0, end));
    temp = temp.substr(end + 1);

    end = temp.find(":");
    t.tm_min = stoi(temp.substr(0, end));
    temp = temp.substr(end + 1);

    t.tm_sec = stoi(temp);

    return mktime(&t);
}

// DOS detection
void LogicAnalyzer::detectDOS(ofstream &alerts, ostream &outAlerts)
{
    vector<string> uniqueSourceIPs;
    vector<queue<time_t>> IPWindows;

    for (size_t i = 0; i < sourceIPs.size(); ++i)
    {
        string IP = sourceIPs[i];
        time_t currentTime = toSeconds(timestamps[i]);

        // skips if ip is whitelisted
        if (ipWhitelisted(IP)) continue;

        int index = -1;
        for (size_t j = 0; j < uniqueSourceIPs.size(); ++j)
            if (uniqueSourceIPs[j] == IP) { index = j; break; }

        if (index == -1)
        {
            uniqueSourceIPs.push_back(IP);
            IPWindows.push_back(queue<time_t>());
            index = uniqueSourceIPs.size() - 1;
        }

        queue<time_t> &window = IPWindows[index];
        window.push(currentTime);

        while (!window.empty() && difftime(currentTime, window.front()) > dosWindow)
            window.pop();

        if (window.size() > (size_t)dosThreshold)
        {
            outAlerts << timestamps[i] << " - DOS alert, SourceIP: " << IP
                      << ", actions in " << dosWindow << "s: " << window.size() << "\n";
            alerts << timestamps[i] << " - DOS alert, SourceIP: " << IP
                      << ", actions in " << dosWindow << "s: " << window.size() << "\n";
            dosAlerts++;
            addGUIAlert("DoS detected from " + IP);

            while (!window.empty()) window.pop();
        }
    }
}

// Brute-force detection
void LogicAnalyzer::checkBruteForce(ofstream &alerts, ostream &outAlerts)
{
    for (size_t i = 0; i < sourceIPs.size(); ++i)
    {
        if (actions[i] != "LOGIN" || results[i] != "FAIL") continue;
        if (ipWhitelisted(sourceIPs[i])) continue;

        long t = toSeconds(timestamps[i]);
        string key = sourceIPs[i] + "|" + usernames[i];

        int index = -1;
        for (size_t j = 0; j < keys.size(); ++j)
            if (keys[j] == key) { index = j; break; }

        if (index == -1) { keys.push_back(key); times.push_back(vector<long>()); index = keys.size() - 1; }

        times[index].push_back(t);
        while (!times[index].empty() && times[index].front() < t - bruteForceWindow)
            times[index].erase(times[index].begin());

        if (times[index].size() >= (size_t)bruteForceThreshold)
        {
            outAlerts << timestamps[i] << " - Brute-force alert, SourceIP: " << sourceIPs[i]
                      << ", user: " << usernames[i]
                      << ", fails: " << times[index].size() << "\n";
            alerts << timestamps[i] << " - Brute-force alert, SourceIP: " << sourceIPs[i]
                      << ", user: " << usernames[i]
                      << ", fails: " << times[index].size() << "\n";
                        addGUIAlert("DoS detected from " + sourceIPs[i]);

            bruteAlerts++;
        }
    }
}

// Port scanning detection
void LogicAnalyzer::portScanDetect(ofstream &alerts, ostream &outAlerts)
{
    vector<string> uniqueSourceIPs;
    // stores distinct ports accessed by each ip
    vector<vector<int>> portHistory;
    vector<vector<time_t>> portTimestamps;

    for (size_t i = 0; i < sourceIPs.size(); ++i)
    {
        string IP = sourceIPs[i];
        time_t currentTime = toSeconds(timestamps[i]);
        int port = ports[i];

        if (ipWhitelisted(IP)) continue;

        int index = -1;
        for (size_t j = 0; j < uniqueSourceIPs.size(); ++j)
            if (uniqueSourceIPs[j] == IP) { index = j; break; }

        if (index == -1)
        {
            uniqueSourceIPs.push_back(IP);
            portHistory.push_back(vector<int>());
            portTimestamps.push_back(vector<time_t>());
            index = uniqueSourceIPs.size() - 1;
        }

        vector<int> &ipPorts = portHistory[index];
        vector<time_t> &ipTimes = portTimestamps[index];

        for (size_t j = 0; j < ipTimes.size(); )
        {
            if (difftime(currentTime, ipTimes[j]) > portScanWindow)
            {
                ipPorts.erase(ipPorts.begin() + j);
                ipTimes.erase(ipTimes.begin() + j);
            }
            else ++j;
        }

        if (find(ipPorts.begin(), ipPorts.end(), port) == ipPorts.end())
        {
            ipPorts.push_back(port);
            ipTimes.push_back(currentTime);
        }

        if (ipPorts.size() >= (size_t)portScanPorts)
        {
            outAlerts << timestamps[i] << " - Port scan alert, SourceIP: " << IP
                      << ", distinct ports in " << portScanWindow << "s: " << ipPorts.size() << "\n";
            alerts << timestamps[i] << " - Port scan alert, SourceIP: " << IP
                      << ", distinct ports in " << portScanWindow << "s: " << ipPorts.size() << "\n";
            addGUIAlert("DoS detected from " + IP);

            portAlerts++;
        }
    }
}

// Whitelist
void LogicAnalyzer::loadWhitelist(const string &fileName)
{
    ifstream file(fileName);
    if (!file.is_open()) return;
    string ip;
    while (getline(file, ip)) if (!ip.empty()) whitelistIPs.push_back(ip);
    file.close();
}

bool LogicAnalyzer::ipWhitelisted(const string &ip)
{
    return find(whitelistIPs.begin(), whitelistIPs.end(), ip) != whitelistIPs.end();
}

void LogicAnalyzer::addWhitelistIP(const string &ip)
{
    if (!ipWhitelisted(ip)) whitelistIPs.push_back(ip);
}

void LogicAnalyzer::removeWhitelistIP(const string &ip)
{
    whitelistIPs.erase(remove(whitelistIPs.begin(), whitelistIPs.end(), ip), whitelistIPs.end());
}

void LogicAnalyzer::saveWhitelist(const string &fileName)
{
    ofstream file(fileName);
    for (auto &ip : whitelistIPs) file << ip << "\n";
    file.close();
}

// Extract date from filename
// File format: logs_2025-03-01.csv
string LogicAnalyzer::extractDate(const string &fileName)
{
    int start = fileName.find('_');
    int end = fileName.rfind('.');
    if (start == string::npos || end == string::npos) return "";
    return fileName.substr(start + 1, end - start - 1);
}

// Load log file
void LogicAnalyzer::loadLogFile(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open()) return;
    std::ofstream rejects("rejects.txt");

    string line;
    lineNumber = 0;
    malformedCount = 0;

    while (getline(file, line))
    {
        lineNumber++;
        if (line.empty()) continue;

        stringstream ss(line);
        vector<string> fields;
        string token;
        while (getline(ss, token, ',')) fields.push_back(token);

        if (fields.size() != 7)
        {
            rejects << "Line " << lineNumber << ": [" << line << "] - Invalid format" << endl;
            malformedCount++;
            continue;
        }

        string timestamp = fields[0];
        string srcIP = fields[1];
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
        timestamps.push_back(timestamp);
        sourceIPs.push_back(srcIP);
        destIPs.push_back(destIP);
        ports.push_back(port);
        actions.push_back(action);
        usernames.push_back(username);
        results.push_back(result);

        int index = -1;
        for (size_t j = 0; j < uniqueIPs.size(); ++j)
            if (uniqueIPs[j] == srcIP) index = j;

        if (index == -1) { uniqueIPs.push_back(srcIP); ipActionCount.push_back(1); }
        else ipActionCount[index]++;
    }

    file.close();
}
