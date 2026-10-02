#ifndef LOGICANALYZER_H
#define LOGICANALYZER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <ctime>

using namespace std;



class LogicAnalyzer
{
public:
    LogicAnalyzer();
    void addGUIAlert(const std::string &msg) {
        guiAlerts.push_back(msg);
    }

    // Getter so MainWindow can read alerts
    const std::vector<std::string>& getGUIAlerts() const {
        return guiAlerts;
    }

    // Data storage
    vector<string> timestamps;
    vector<string> sourceIPs;
    vector<string> destIPs;
    vector<int> ports;
    vector<string> actions;
    vector<string> usernames;
    vector<string> results;
    vector<string> keys;
    vector<vector<long>> times;
    vector<string> whitelistIPs;
    vector<string> uniqueIPs;
    vector<int> ipActionCount;

    int malformedCount = 0;
    int lineNumber = 0;

    // Thresholds (default)
    int bruteForceThreshold = 3;
    int bruteForceWindow = 60; // seconds

    int dosThreshold = 200;
    int dosWindow = 60;         // seconds

    int portScanPorts = 10;
    int portScanWindow = 60;    // seconds

    // Alert counters
    int dosAlerts = 0;
    int bruteAlerts = 0;
    int portAlerts = 0;

    // Methods
    time_t toSeconds(const string &timestamp);
    void detectDOS(ofstream &alerts, ostream &outAlerts = cout);
    void checkBruteForce(ofstream &alerts, ostream &outAlerts = cout);
    void portScanDetect(ofstream &alerts, ostream &outAlerts = cout);
    void loadWhitelist(const string &fileName);
    bool ipWhitelisted(const string &ip);
    string extractDate(const string &fileName);
    void loadLogFile(const string &filePath);
    void addWhitelistIP(const string &ip);
    void removeWhitelistIP(const string &ip);
    void saveWhitelist(const string &fileName);
private:
    std::vector<std::string> guiAlerts;
};


#endif // LOGICANALYZER_H
