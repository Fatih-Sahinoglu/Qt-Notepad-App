# Qt-Notepad-App

A modern, lightweight, and user-centric text editor built with **C++** and the **Qt Framework**. This project goes beyond a basic Notepad clone by focusing on high-quality user experience, state persistence, and performance-aware UI behavior.

![Qt](https://img.shields.io/badge/Qt-217346?style=for-the-badge&logo=Qt&logoColor=white)
![C++](https://img.shields.io/badge/C++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/license-MIT-blue.svg?style=for-the-badge)

---

##  Features

###  File Management
- **Smart Operations:** New (resets editor & title), Open (.txt), Save, and Save As support.
- **Context-Aware:** Dynamic window title updates based on the active file name.
- **Auto-Load:** Automatically reopens the last worked file on startup.

###  Advanced Search (Finder)
- **Toggleable Panel:** Clean workspace with a hideable search frame.
- **Real-Time Navigation:** Find-as-you-type logic with "Next" and "Previous" buttons.
- **Circular Search:** Intelligent wrap-around behavior for continuous searching.

###  Smart Font & UI Control
- **Dynamic Zoom:** Change font size via `Ctrl + Mouse Wheel` or the dedicated **Sizer** panel.
- **Live Indicator:** Real-time font size (px) display with an auto-hide `QTimer` mechanism.
- **Dual Themes:** Full **Dark** and **Light** mode support with consistent UI styling.

###  Real-Time Analytics
- **Live Status Bar:** Tracks character count and word count (using optimized `simplified()` string logic) as you type.

---

##  Core Feature: Persistent Config System 

The application features a robust state management system. All user preferences are automatically stored in a `config.txt` file and restored upon launch:
- **UI State:** Theme (Dark/Light), Font Size, Toolbar Visibility, and Movability.
- **Session Data:** Remembers the last opened file path for instant resumption of work.

---

##  Technical Deep Dive

###  Architecture & OOP
Built using a modular **Object-Oriented** approach. Logic and UI interactions are strictly separated for maintainability, utilizing the powerful **Qt Signal-Slot** mechanism.

###  Performance Optimization (Debouncing)
To prevent excessive disk I/O, the app uses a **QTimer + Lambda** approach for zoom changes. It waits for the user to finish scaling before writing to the config file, ensuring a "buttery smooth" UI experience.

###  Notable Implementations
- **Custom Event Filtering:** Overridden `wheelEvent` for specialized zoom control.
- **Modern C++:** Extensive use of **Lambda expressions** for efficient, inline signal handling.
- **Modular Design:** Finder and Sizer panels are dynamically managed to keep the interface clutter-free.

---

##  Project Structure

| File / Folder | Description |
| :--- | :--- |
| **`main.cpp`** | Application entry point. |
| **`mainwindow.cpp`** | Core logic, event implementations, and signal-slot handling. |
| **`mainwindow.h`** | Class definitions, private variables, and method signatures. |
| **`mainwindow.ui`** | UI design file (Qt Designer) for the main editor. |
| **`resources.qrc`** | Resource file managing icon. |
| **`config.txt`** | (Auto-generated) Local storage for user preferences and persistence. |


---

##  Build & Run
Requirements: Qt Creator and a C++ Compiler (MSVC/MinGW).

Build: Open Notepad.pro in Qt Creator and press Ctrl + R.

Deployment: Use windeployqt for a standalone executable.

---

## Why This Project Matters
This is not just a Notepad clone. It demonstrates how thoughtful design decisions—like state persistence and small technical optimizations (timer-based saving)—can significantly improve the usability of even the simplest applications.

---

## Developer
**Fatih Şahinoğlu** - [GitHub](https://github.com/Fatih-Sahinoglu) | [LinkedIn](https://www.linkedin.com/in/fatih-şahinoğlu/)

## License
This project is licensed under the [MIT License](LICENSE).