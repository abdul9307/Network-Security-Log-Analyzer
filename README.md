# Network Security Log Analyzer & Threat Detection System

A C++ and Qt6 Graphical User Interface (GUI) application designed to parse network security log files, perform real-time security threat analysis (DoS, Brute-Force, Port Scanning), manage IP whitelists, dynamically configure detection thresholds, and export security reports.

---

## Key Features

- **Multi-Vector Threat Detection Engine:**
  - **Denial of Service (DoS):** Tracks action spikes per source IP within configurable sliding time windows.
  - **Brute-Force Detection:** Monitors failed login attempts target-by-target within specified time limits.
  - **Port Scanning Detection:** Identifies distinct destination port access attempts originating from single source IPs.
- **Whitelist Management:** Exclude trusted IP addresses dynamically or via persistent storage (`whitelist.txt`).
- **Interactive Qt Interface:** Easily inspect log files, update detection window thresholds on the fly, and view generated security alerts directly in the GUI.
- **Automated Report & Alert Generation:**
  - Saves date-stamped threat detection alerts in the `/alerts` directory.
  - Exports top source talkers and top target destination ports to CSV format in the `/reports` directory.
  - Records malformed or invalid log file lines into `rejects.txt`.

---

## Technical Architecture

* **Language:** C++17
* **GUI Framework:** Qt6 (Widgets module)
* **Build System:** CMake (3.16+)
* **Core Components:**
  - `LogicAnalyzer`: Core threat detection logic, sliding-window algorithms, time conversions, and CSV parsing.
  - `MainWindow`: Main Qt graphical dashboard handling button events, dialog inputs, and UI text updates.
  - `ThresholdConfigDialog`: Custom Qt dialog for threshold parameter updates.

---

## Getting Started
1. **Download the Application:** Download and extract the `Project-Application` folder from the repository. This folder contains all necessary dependencies and runtime files required to run the application.
2. **Review Documentation:** Read through this `README.md` file for details on application features and expected log formats.
3. **Launch the Application:** Navigate into the `Project-Application` folder and double-click `ProjectFinal.exe` to start the program.
