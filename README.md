# Network Security Log Analyzer

A C++/Qt6 desktop application that parses network log files (`.csv`), detects potential security threats using sliding-window thresholds, and exports structured reports.

---

## Features

* **Threat Detection Engine:**
  * **DoS Attacks:** Flags source IPs exceeding a set request volume within a given timeframe.
  * **Brute-Force Login Attempts:** Detects repeated failed logins (`LOGIN`, `FAIL`) per username/IP combination.
  * **Port Scanning:** Detects single IPs attempting to access multiple distinct destination ports within a short window.
* **Whitelist Support:** Whitelist trusted IPs on the fly or via `whitelist.txt` to suppress false positive alerts.
* **Log Parsing & Error Handling:** Validates log formatting, strips malformed rows, and logs errors to `rejects.txt`.
* **Alerts & Reports:** 
  * Saves flagged security events under `alerts/alerts_<date>.txt`.
  * Generates top-talker and top-target summary reports under `reports/report_<date>.csv`.

---

## Built With

* **Language:** C++17
* **GUI Framework:** Qt 6 (Widgets)
* **Build System:** CMake 3.16+

---

## Quick Start

1. **Download:** Download and unzip the `Project-Application` folder from the repository.
2. **Review Documentation:** Read through this `README.md` file for details on application features and expected log formats.
3. **Run:** Open the folder and launch `ProjectFinal.exe`.

### Expected Log File Format (`.csv`)

Your input log file should be formatted as follows:

```csv
Timestamp,SourceIP,DestIP,Port,Action,Username,Result
2025-03-01T10:22:14,192.168.1.5,10.0.0.1,80,LOGIN,admin,FAIL
