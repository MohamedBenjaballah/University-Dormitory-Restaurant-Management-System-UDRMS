#pragma once
#include <QMainWindow>
#include <QTabWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include "University.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    // Dormitory tab
    void onAddDormitory();
    void onRemoveDormitory();
    void onDormSelected(int row);

    // Room tab
    void onAddRoom();
    void onAssignStudent();
    void onRemoveStudent();

    // Restaurant tab
    void onSetBreakfast();
    void onSetLunch();
    void onSetDinner();
    void onServeMeal();
    void onResetDaily();

    // Toolbar
    void onSave();
    void onRefreshDisplay();

private:
    void buildUI();
    void buildDormTab(QTabWidget* tabs);
    void buildRoomTab(QTabWidget* tabs);
    void buildRestaurantTab(QTabWidget* tabs);
    void refreshDormList();
    void refreshRoomList(const QString& dormName);
    void log(const QString& msg);

    University        uni;
    QListWidget*      dormList   = nullptr;
    QListWidget*      roomList   = nullptr;
    QTextEdit*        logOutput  = nullptr;
    QLabel*           menuLabel  = nullptr;
    const std::string DATA_DIR   = "./data";
};
