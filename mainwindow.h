#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // Overriding wheelEvent for custom Ctrl + Mouse Wheel zoom behavior
    void wheelEvent(QWheelEvent *event) override;

private slots:
    //File Operations
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();


    //Edit Operations
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionCut_triggered();
    void on_actionRedo_triggered();
    void on_actionUndo_triggered();
    void on_actionSelect_All_triggered();

    //Text status System
    void on_textEdit_textChanged();

    //Search Text System
    void on_actionFind_triggered();
    void on_Finder_textChanged(const QString &arg1);
    void on_btnNext_clicked();
    void on_btnPrev_clicked();
    void on_btnClose_clicked();

    //Ui and Theme Management
    void on_actionLock_Unlock_triggered(bool checked);
    void on_actionShow_Hide_triggered(bool checked);
    void on_actionSwitch_Theme_triggered();
    void on_actionAbout_triggered();

    //Text size System
    void showzoomIndicator();
    void on_Sizer_valueChanged(int arg1);
    void on_actionFont_Size_triggered();
    void on_btnclosefont_clicked();

    //Config System
    void saveConfig();
    void loadConfig();

private:
    Ui::MainWindow *ui;

    QString file_path; // Tracks the currently opened file path
    bool isDark = true; // Current theme state (Dark or Light)

    // UI Stylesheets
    QString darkmode = R"(QMainWindow, QWidget#centralwidget, QFrame#Searchframe {
    background-color: #2b2b2b;
    color: #ffffff;
}

QMenuBar {
    background-color: #2b2b2b;
    color: #ffffff;
    border-bottom: 1px solid #3d3d3d;
}

QMenuBar::item:selected {
    background-color: #444444;
    border-radius: 4px;
}

QTextEdit {
    background-color: #1e1e1e;
    color: #dcdcdc;
    border: none;
}

QLineEdit#Finder {
    background-color: #3c3f41;
    color: white;
    border: 1px solid #555;
    border-radius: 4px;
}

QPushButton#btnPrev, QPushButton#btnNext {
    border-right: 1px solid #3d3d3d;
    background-color: transparent;
    color: #aaaaaa;
    font-size: 14pt;
    font-weight: bold;
    min-width: 35px;
    margin-right: 2px;
}

QPushButton#btnClose {
    background-color: transparent;
    color: #aaaaaa;
    font-size: 14pt;
}
QPushButton#btnclosefont {
    background-color: transparent;
    color: #aaaaaa;
    font-size: 11pt;
}

QPushButton#btnPrev:hover, QPushButton#btnNext:hover {
    background-color: #444444;
    color: white;
}

QPushButton#btnClose:hover, QPushButton#btnclosefont:hover {
    background-color: #c42b1c;
    color: white;
}

QLabel#zoomIndicator {
    background-color: rgba(50, 50, 50, 180); /* Gri ve şeffaf */
    color: white;
    border-radius: 8px;
    font-weight: bold;
})";

    QString lightmode = R"(
QMainWindow, QWidget#centralwidget, QFrame#Searchframe {
    background-color: #ffffff;
    color: #1a1a1a;
}

QMenuBar {
    background-color: #ffffff;
    color: #1a1a1a;
    border-bottom: 1px solid #e0e0e0;
}

QMenuBar::item:selected {
    background-color: #f0f0f0;
    border-radius: 4px;
}

QTextEdit {
    background-color: #ffffff;
    color: #1a1a1a;
    border: none;
}

QLineEdit#Finder {
    background-color: #f8f8f8;
    color: #1a1a1a;
    border: 1px solid #dcdcdc;
    border-radius: 4px;
    padding: 2px 5px;
}

QPushButton#btnPrev, QPushButton#btnNext {
    background-color: transparent;
    color: #555555;
    border: none;
    border-right: 1px solid #e0e0e0;
    font-size: 13pt;
    min-width: 35px;
}

QPushButton#btnClose {
    background-color: transparent;
    color: #555555;
    border: none;
    font-size: 13pt;
    min-width: 35px;
    padding: 2px 10px;
}

QPushButton#btnPrev:hover, QPushButton#btnNext:hover {
    background-color: #eeeeee;
    color: #000000;
}

QPushButton#btnClose:hover {
    background-color: #e81123;
    color: white;
}

QStatusBar {
    background-color: #f3f3f3;
    color: #666666;
    border-top: 1px solid #e0e0e0;
}

QToolBar {
    background-color: #e0e0e0;
    border-bottom: 1px solid #ccc;
}

QLabel#zoomIndicator {
    background-color: rgba(50, 50, 50, 180);
    color: white;
    border-radius: 8px;
    font-weight: bold;
})";
    // Visual feedback for font scaling
    QLabel *zoomlabel;
    QTimer *zoomtimer;
};


#endif // MAINWINDOW_H
