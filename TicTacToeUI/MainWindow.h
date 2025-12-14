#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "ui_MainWindow.h"
#include "GameViewModel.h"
#include "BoardWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void OnGameStateChanged(GameState newState);
    void OnCurrentPlayerChanged(Symbol newPlayer);
    void OnResetButtonClicked();

private:
    Ui::MainWindowClass* ui;

    GameViewModel* m_viewModel;
    BoardWidget* m_boardWidget;
    QLabel* m_statusLabel;
    QPushButton* m_resetButton;

    void SetupUI();
    void ConnectSignals();
    void UpdateStatusLabel();
};