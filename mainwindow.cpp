#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QWheelEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Zoom Indicator Setup
    zoomlabel = new QLabel(this);
    zoomlabel->setObjectName("zoomIndicator");
    zoomlabel->setAlignment(Qt::AlignCenter);
    zoomlabel->setFixedSize(50,30);
    zoomlabel->hide();

    //Wait 1 second to hide and save
    zoomtimer = new QTimer(this);
    zoomtimer->setSingleShot(true);
    connect(zoomtimer, &QTimer::timeout, this, [this](){
        zoomlabel->hide();
        saveConfig();
    });

    //Initial Ui State
    this->setWindowIcon(QIcon("://icon.png"));
    ui->statusbar->showMessage("Characters: 0 | Words: 0");
    ui->Searchframe->hide();
    ui->Fontframe->hide();

    loadConfig(); //Restore settings on startup
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveConfig()
{
    QFile file("config.txt");
    if(file.open(QFile::WriteOnly | QFile::Text)){
        QTextStream out(&file);
        out << (isDark ? "1" : "0") << "\n";
        out << ui->textEdit->font().pointSize() << "\n";
        out << (ui->toolBar->isVisible() ? "1" : "0") << "\n";
        out << (ui->toolBar->isMovable() ? "1" : "0") << "\n";
        out << file_path <<"\n";
        file.flush();
        file.close();
    }
}

void MainWindow::loadConfig()
{
    QFile file("config.txt");
    this->setWindowTitle("Notepad");

    if(!file.exists()){ //if config doesn't exist create a default one
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&file);
            out << "1\n15\n1\n1\n\n";
            file.close();
        }

        this->setStyleSheet(darkmode);
        isDark = true;
        ui->Sizer->setValue(15);
        return;

    }else{
        if(file.open(QFile::ReadOnly | QFile::Text)){
            QTextStream in(&file);

            isDark = (in.readLine() == "1");
            this->setStyleSheet(isDark ? darkmode : lightmode);

            int size = in.readLine().toInt();
            QFont f = ui->textEdit->font();
            f.setPointSize(size);
            ui->textEdit->setFont(f);
            ui->Sizer->setValue(size);

            ui->toolBar->setVisible(in.readLine() == "1");

            ui->toolBar->setMovable(in.readLine() == "1");

            QString last_path = in.readLine();
            if(!last_path.isEmpty()){
                QFile getfile(last_path);
                if (getfile.open(QFile::ReadOnly | QFile::Text)){
                    QTextStream contentIn(&getfile);
                    ui->textEdit->setText(contentIn.readAll());
                    getfile.close();

                    file_path = last_path;
                    QFileInfo info(file_path);
                    this->setWindowTitle("Notepad - " + info.fileName());

                }
            }
            file.close();
        }
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    // Check if Ctrl key is pressed while mouse wheel scroll
    if (event->modifiers() & Qt::ControlModifier) {

        // angleDelta().y() > 0 means wheel scrolled forward (up)
        if (event->angleDelta().y() > 0) {
            ui->textEdit->zoomIn(1); // Increase font size 1
        }
        // Wheel scrolled backward (down)
        else {
            ui->textEdit->zoomOut(1); // Decrease font size 1
        }

        showzoomIndicator(); //Show size of font
        // Job is done don't look others
        event->accept();
    }
    // Otherwise, default behaviour
    else {
        QMainWindow::wheelEvent(event);
    }
}

// FILE MENU ACTİONS
void MainWindow::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->clear();
    this->setWindowTitle("Notepad");
    saveConfig();
}

void MainWindow::on_actionOpen_triggered()
{
    QString filter = "Text Files (*.txt)";
    file_path = QFileDialog::getOpenFileName(this,"Choose a file",QDir::homePath(),filter);

    if(file_path.isEmpty()) return;

    QFile file(file_path);
    if (file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
        QFileInfo info(file_path);
        this->setWindowTitle("Notepad - " + info.fileName());
        saveConfig();

    }
}

void MainWindow::on_actionSave_triggered()
{
    if(file_path.isEmpty()) {
        on_actionSave_as_triggered();
        return;}

    QFile file(file_path);
    if (file.open(QFile::WriteOnly | QFile::Text)){
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.flush();
        file.close();
        QFileInfo info(file_path);
        QMessageBox::information(this,"Successfully Saved",info.fileName()+" is saved");
        saveConfig();
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,"Save As",QDir::homePath());
    if(path.isEmpty()) return;

    if(!path.endsWith(".txt",Qt::CaseInsensitive)) path += ".txt";

    file_path = path;
    on_actionSave_triggered();
}

// EDIT MENU ACTİONS
void MainWindow::on_actionCopy_triggered() { ui->textEdit->copy(); }
void MainWindow::on_actionPaste_triggered() { ui->textEdit->paste(); }
void MainWindow::on_actionCut_triggered() { ui->textEdit->cut(); }
void MainWindow::on_actionRedo_triggered() { ui->textEdit->redo(); }
void MainWindow::on_actionUndo_triggered() { ui->textEdit->undo(); }
void MainWindow::on_actionSelect_All_triggered() { ui->textEdit->selectAll(); }

//Update Char and Word numbers
void MainWindow::on_textEdit_textChanged(){
    QString text = ui->textEdit->toPlainText();
    int chars = text.length();
    int words = 0;

    QString cleaner_text = text.simplified();
    if(!cleaner_text.isEmpty()){
        words = cleaner_text.split(' ').count();
    }
    ui->statusbar->showMessage(QString("Characters: %1 | Words: %2").arg(chars).arg(words));
}

//About part with custom messagebox
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox inf(this);

    inf.setWindowTitle("Informations");
    QString bio = "<h3>Qt Notepad v1.0</h3>"
                  "<p><b>Developer:</b> Fatih Şahinoğlu</p>"
                  "<p>This project was developed as part of the C++ and Qt framework learning process.</p>"
                  "<p>Check out my projects on "
                  "<a href='https://github.com/Fatih-Sahinoglu'>GitHub</a> | "
                  "<a href='https://www.linkedin.com/in/fatih-şahinoğlu/'>Linkedin</a></p>"
                  "<hr>"
                  "<p><b>Geliştirici:</b> Fatih Şahinoğlu</p>"
                  "<p>Bu proje, C++ ve Qt framework öğrenim sürecinin bir parçası olarak geliştirilmiştir.</p>"
                  "<p>Diğer Projelerimi görmek için  "
                  "<a href='https://github.com/Fatih-Sahinoglu'>GitHub</a> | "
                  "<a href='https://www.linkedin.com/in/fatih-şahinoğlu/'>Linkedin</a></p>"
                  "<hr>"
                  ;
    inf.setText(bio);
    inf.setIcon(QMessageBox::Information);

    inf.exec();

}


// SEARCH (FIND) SYSTEM
void MainWindow::on_actionFind_triggered()
{
    if(!ui->Searchframe->isVisible()){
    ui->Searchframe->show();
    ui->Finder->setFocus(); //To write without clicking lineedit(finder)
    }
    else{
        ui->Searchframe->hide();
        // Clear selection when closing finder
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.clearSelection();
        ui->textEdit->setTextCursor(cursor);
    }
}

void MainWindow::on_Finder_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()) {

        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.clearSelection();
        ui->textEdit->setTextCursor(cursor);
        return;
    }
    ui->textEdit->find(arg1);

    // Wrap around search (restart from beginning if not found)
    if (!ui->textEdit->find(arg1)) {
        ui->textEdit->moveCursor(QTextCursor::Start);
        ui->textEdit->find(arg1);
    }
}

void MainWindow::on_btnNext_clicked()
{
    QString search = ui->Finder->text();
    if (search.isEmpty()) return;

    bool found = ui->textEdit->find(search);
    if(!found){
        ui->textEdit->moveCursor(QTextCursor::Start);
        ui->textEdit->find(search);
    }
}

void MainWindow::on_btnPrev_clicked()
{
    QString search = ui->Finder->text();
    if (search.isEmpty()) return;

    bool found = ui->textEdit->find(search, QTextDocument::FindBackward);
    if(!found){
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->textEdit->find(search, QTextDocument::FindBackward);
    }
}

void MainWindow::on_btnClose_clicked()
{
    ui->Searchframe->hide();

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.clearSelection();
    ui->textEdit->setTextCursor(cursor);
}


// UI and THEME MANAGEMENT
void MainWindow::on_actionLock_Unlock_triggered(bool checked)
{
    bool status = ui->toolBar->isMovable();
    ui->toolBar->setMovable(!status);
    saveConfig();
}

void MainWindow::on_actionShow_Hide_triggered(bool checked)
{
    bool status = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!status);
    saveConfig();
}


void MainWindow::on_actionSwitch_Theme_triggered()
{
    if(isDark) {
        this->setStyleSheet(lightmode);
        isDark = false;
    }else {
        this->setStyleSheet(darkmode);
        isDark = true;
    }
    saveConfig();
}

//TEXT SIZE SYSTEM
void MainWindow::showzoomIndicator()
{
    zoomlabel->setText(QString::number(ui->textEdit->font().pointSize())+ "\npx");
    short x = ui->textEdit->x() + ui->textEdit->width() - 70;
    short y = ui->textEdit->y() + 70;
    zoomlabel->move(x,y);

    zoomlabel->raise();
    zoomlabel->show();

    ui->Sizer->setValue(ui->textEdit->font().pointSize());

    zoomtimer->start(1000);
}

void MainWindow::on_Sizer_valueChanged(int arg1)
{
    QFont font = ui->textEdit->font();
    font.setPointSize(arg1);
    ui->textEdit->setFont(font);
    saveConfig();
}

void MainWindow::on_actionFont_Size_triggered()
{
    if(!ui->Fontframe->isVisible()){
        ui->Fontframe->show();
        ui->Sizer->setFocus();
    }else ui->Fontframe->hide();
}

void MainWindow::on_btnclosefont_clicked()
{
    ui->Fontframe->hide();
}
