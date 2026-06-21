#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QGroupBox>
#include <QSplitter>
#include <stdexcept>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), uni("ENSIA University") {
    uni.loadAll(DATA_DIR);
    buildUI();
    refreshDormList();
    setWindowTitle("UDRMS — University Dormitory & Restaurant Manager");
    resize(960, 640);
}

MainWindow::~MainWindow() {
    uni.saveAll(DATA_DIR);
}

// ── UI construction ───────────────────────────────────────────────────────────

void MainWindow::buildUI() {
    QToolBar* tb = addToolBar("Main");
    tb->setMovable(false);
    QAction* saveAct    = tb->addAction("💾 Save");
    QAction* refreshAct = tb->addAction("🔄 Refresh");
    connect(saveAct,    &QAction::triggered, this, &MainWindow::onSave);
    connect(refreshAct, &QAction::triggered, this, &MainWindow::onRefreshDisplay);

    QWidget*     central = new QWidget(this);
    QVBoxLayout* vlay    = new QVBoxLayout(central);
    QTabWidget*  tabs    = new QTabWidget;

    buildDormTab(tabs);
    buildRoomTab(tabs);
    buildRestaurantTab(tabs);

    logOutput = new QTextEdit;
    logOutput->setReadOnly(true);
    logOutput->setMaximumHeight(120);
    logOutput->setPlaceholderText("Activity log…");

    vlay->addWidget(tabs);
    vlay->addWidget(logOutput);
    setCentralWidget(central);
}

void MainWindow::buildDormTab(QTabWidget* tabs) {
    QWidget*     w    = new QWidget;
    QHBoxLayout* hlay = new QHBoxLayout(w);

    dormList = new QListWidget;
    connect(dormList, &QListWidget::currentRowChanged, this, &MainWindow::onDormSelected);

    QGroupBox*   gb    = new QGroupBox("Actions");
    QVBoxLayout* vlay  = new QVBoxLayout(gb);
    auto mkBtn = [&](const QString& label) {
        auto* b = new QPushButton(label); vlay->addWidget(b); return b;
    };
    connect(mkBtn("Add dormitory"),    &QPushButton::clicked, this, &MainWindow::onAddDormitory);
    connect(mkBtn("Remove dormitory"), &QPushButton::clicked, this, &MainWindow::onRemoveDormitory);
    vlay->addStretch();

    hlay->addWidget(dormList, 2);
    hlay->addWidget(gb, 1);
    tabs->addTab(w, "Dormitories");
}

void MainWindow::buildRoomTab(QTabWidget* tabs) {
    QWidget*     w    = new QWidget;
    QHBoxLayout* hlay = new QHBoxLayout(w);

    roomList = new QListWidget;

    QGroupBox*   gb   = new QGroupBox("Actions");
    QVBoxLayout* vlay = new QVBoxLayout(gb);
    auto mkBtn = [&](const QString& label) {
        auto* b = new QPushButton(label); vlay->addWidget(b); return b;
    };
    connect(mkBtn("Add room"),             &QPushButton::clicked, this, &MainWindow::onAddRoom);
    connect(mkBtn("Assign student"),       &QPushButton::clicked, this, &MainWindow::onAssignStudent);
    connect(mkBtn("Remove student"),       &QPushButton::clicked, this, &MainWindow::onRemoveStudent);
    vlay->addStretch();

    hlay->addWidget(roomList, 2);
    hlay->addWidget(gb, 1);
    tabs->addTab(w, "Rooms");
}

void MainWindow::buildRestaurantTab(QTabWidget* tabs) {
    QWidget*     w    = new QWidget;
    QHBoxLayout* hlay = new QHBoxLayout(w);

    menuLabel = new QLabel("Select a dormitory first.");
    menuLabel->setWordWrap(true);
    menuLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    QGroupBox*   gb   = new QGroupBox("Actions");
    QVBoxLayout* vlay = new QVBoxLayout(gb);
    auto mkBtn = [&](const QString& label) {
        auto* b = new QPushButton(label); vlay->addWidget(b); return b;
    };
    connect(mkBtn("Set breakfast"),    &QPushButton::clicked, this, &MainWindow::onSetBreakfast);
    connect(mkBtn("Set lunch"),        &QPushButton::clicked, this, &MainWindow::onSetLunch);
    connect(mkBtn("Set dinner"),       &QPushButton::clicked, this, &MainWindow::onSetDinner);
    connect(mkBtn("Serve meal"),       &QPushButton::clicked, this, &MainWindow::onServeMeal);
    connect(mkBtn("Reset daily count"),&QPushButton::clicked, this, &MainWindow::onResetDaily);
    vlay->addStretch();

    hlay->addWidget(menuLabel, 2);
    hlay->addWidget(gb, 1);
    tabs->addTab(w, "Restaurant");
}

// ── Helpers ───────────────────────────────────────────────────────────────────

void MainWindow::refreshDormList() {
    dormList->clear();
    for (const auto& d : uni.getDormitories())
        dormList->addItem(QString::fromStdString(d.getName()));
}

void MainWindow::refreshRoomList(const QString& dormName) {
    roomList->clear();
    auto* d = uni.findDormitory(dormName.toStdString());
    if (!d) return;
    for (const auto& r : d->getRooms())
        roomList->addItem(QString("Room %1  [%2/%3]")
                          .arg(r.getRoomNumber())
                          .arg(r.getOccupancy())
                          .arg(r.getCapacity()));
}

void MainWindow::log(const QString& msg) {
    logOutput->append(msg);
}

QString currentDorm(QListWidget* list) {
    auto* item = list->currentItem();
    return item ? item->text() : QString();
}

// ── Slots ─────────────────────────────────────────────────────────────────────

void MainWindow::onAddDormitory() {
    bool ok;
    QString n   = QInputDialog::getText(this, "Add Dormitory", "Name:", QLineEdit::Normal, "", &ok);
    if (!ok || n.isEmpty()) return;
    int cap = QInputDialog::getInt(this, "Add Dormitory", "Capacity:", 50, 1, 2000, 1, &ok);
    if (!ok) return;
    try {
        uni.addDormitory(n.toStdString(), cap);
        refreshDormList();
        log("Added dormitory: " + n);
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onRemoveDormitory() {
    QString n = currentDorm(dormList);
    if (n.isEmpty()) return;
    if (QMessageBox::question(this, "Confirm", "Remove " + n + "?") != QMessageBox::Yes) return;
    try {
        uni.removeDormitory(n.toStdString());
        refreshDormList();
        log("Removed dormitory: " + n);
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onDormSelected(int row) {
    if (row < 0) return;
    QString dn = dormList->item(row)->text();
    refreshRoomList(dn);
    // Update restaurant menu display
    auto* d = uni.findDormitory(dn.toStdString());
    if (!d) return;
    const auto& m = d->getRestaurant().getMenu();
    menuLabel->setText(
        QString("<b>%1 Restaurant</b><br>"
                "<b>Breakfast:</b> %2<br>"
                "<b>Lunch:</b> %3<br>"
                "<b>Dinner:</b> %4<br>"
                "<b>Meals served today:</b> %5")
        .arg(dn)
        .arg(QString::fromStdString(m.getMeal(MealType::BREAKFAST)))
        .arg(QString::fromStdString(m.getMeal(MealType::LUNCH)))
        .arg(QString::fromStdString(m.getMeal(MealType::DINNER)))
        .arg(d->getRestaurant().getMealsServed()));
}

void MainWindow::onAddRoom() {
    QString dn = currentDorm(dormList);
    if (dn.isEmpty()) { QMessageBox::information(this, "Info", "Select a dormitory first."); return; }
    bool ok;
    int num = QInputDialog::getInt(this, "Add Room", "Room number:", 101, 1, 9999, 1, &ok);
    if (!ok) return;
    int cap = QInputDialog::getInt(this, "Add Room", "Capacity:", 2, 1, 20, 1, &ok);
    if (!ok) return;
    try {
        uni.findDormitory(dn.toStdString())->addRoom(num, cap);
        refreshRoomList(dn);
        log("Added room " + QString::number(num) + " to " + dn);
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onAssignStudent() {
    QString dn = currentDorm(dormList);
    if (dn.isEmpty()) { QMessageBox::information(this, "Info", "Select a dormitory first."); return; }
    bool ok;
    QString id   = QInputDialog::getText(this, "Assign Student", "Student ID:",   QLineEdit::Normal, "", &ok); if (!ok) return;
    QString name = QInputDialog::getText(this, "Assign Student", "Full name:",    QLineEdit::Normal, "", &ok); if (!ok) return;
    int year     = QInputDialog::getInt  (this, "Assign Student", "Academic year:", 1, 1, 6, 1, &ok);           if (!ok) return;
    int room     = QInputDialog::getInt  (this, "Assign Student", "Room number:",   101, 1, 9999, 1, &ok);      if (!ok) return;
    try {
        uni.assignStudentToRoom(dn.toStdString(), Student(id.toStdString(), name.toStdString(), year), room);
        refreshRoomList(dn);
        log("Assigned " + id + " to room " + QString::number(room));
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onRemoveStudent() {
    QString dn = currentDorm(dormList);
    if (dn.isEmpty()) return;
    bool ok;
    QString id = QInputDialog::getText(this, "Remove Student", "Student ID:", QLineEdit::Normal, "", &ok); if (!ok) return;
    int room   = QInputDialog::getInt (this, "Remove Student", "Room number:", 101, 1, 9999, 1, &ok);     if (!ok) return;
    try {
        uni.removeStudent(dn.toStdString(), id.toStdString(), room);
        refreshRoomList(dn);
        log("Removed student " + id);
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onSetBreakfast() {
    QString dn = currentDorm(dormList); if (dn.isEmpty()) return;
    bool ok;
    QString items = QInputDialog::getText(this, "Set Breakfast", "Items:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    uni.findDormitory(dn.toStdString())->getRestaurant().setMenu(MealType::BREAKFAST, items.toStdString());
    onDormSelected(dormList->currentRow());
    log("Updated breakfast for " + dn);
}

void MainWindow::onSetLunch() {
    QString dn = currentDorm(dormList); if (dn.isEmpty()) return;
    bool ok;
    QString items = QInputDialog::getText(this, "Set Lunch", "Items:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    uni.findDormitory(dn.toStdString())->getRestaurant().setMenu(MealType::LUNCH, items.toStdString());
    onDormSelected(dormList->currentRow());
    log("Updated lunch for " + dn);
}

void MainWindow::onSetDinner() {
    QString dn = currentDorm(dormList); if (dn.isEmpty()) return;
    bool ok;
    QString items = QInputDialog::getText(this, "Set Dinner", "Items:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    uni.findDormitory(dn.toStdString())->getRestaurant().setMenu(MealType::DINNER, items.toStdString());
    onDormSelected(dormList->currentRow());
    log("Updated dinner for " + dn);
}

void MainWindow::onServeMeal() {
    QString dn = currentDorm(dormList); if (dn.isEmpty()) return;
    bool ok;
    QString id = QInputDialog::getText(this, "Serve Meal", "Student ID:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    auto* d = uni.findDormitory(dn.toStdString());
    if (!d) return;
    bool served = d->getRestaurant().serveMeal(id.toStdString());
    log(served ? "Meal served to " + id : "Student " + id + " already served today.");
    onDormSelected(dormList->currentRow());
}

void MainWindow::onResetDaily() {
    QString dn = currentDorm(dormList); if (dn.isEmpty()) return;
    uni.findDormitory(dn.toStdString())->getRestaurant().resetDailyCount();
    onDormSelected(dormList->currentRow());
    log("Daily meal count reset for " + dn);
}

void MainWindow::onSave() {
    uni.saveAll(DATA_DIR);
    log("Data saved.");
}

void MainWindow::onRefreshDisplay() {
    refreshDormList();
    log("Display refreshed.");
}
