#include "include/views/MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
    , m_viewModel(new GameViewModel(this))
    , m_boardWidget(nullptr)
    , m_statusLabel(nullptr)
    , m_resetButton(nullptr)
{
    ui->setupUi(this);
    SetupUI();
    ConnectSignals();

    setWindowTitle("Tic Tac Toe");
    setFixedSize(400, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetupUI()
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    m_statusLabel = new QLabel(this);
    m_statusLabel->setAlignment(Qt::AlignCenter);
    QFont labelFont = m_statusLabel->font();
    labelFont.setPointSize(16);
    labelFont.setBold(true);
    m_statusLabel->setFont(labelFont);
    m_statusLabel->setStyleSheet(
        "QLabel {"
        "   color: #2196F3;"
        "   padding: 10px;"
        "   background-color: #f0f0f0;"
        "   border-radius: 8px;"
        "}"
    );
    UpdateStatusLabel();

    m_boardWidget = new BoardWidget(m_viewModel, this);
    m_boardWidget->setStyleSheet(
        "BoardWidget {"
        "   background-color: #ffffff;"
        "}"
    );

    m_resetButton = new QPushButton("New Game", this);
    m_resetButton->setFixedHeight(40);
    QFont buttonFont = m_resetButton->font();
    buttonFont.setPointSize(12);
    buttonFont.setBold(true);
    m_resetButton->setFont(buttonFont);
    m_resetButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #3d8b40;"
        "}"
    );

    mainLayout->addWidget(m_statusLabel);
    mainLayout->addWidget(m_boardWidget, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_resetButton);
    mainLayout->addStretch();

    setCentralWidget(centralWidget);
}

void MainWindow::ConnectSignals()
{
    connect(m_viewModel, &GameViewModel::GameStateChanged,
        this, &MainWindow::OnGameStateChanged);

    connect(m_viewModel, &GameViewModel::CurrentPlayerChanged,
        this, &MainWindow::OnCurrentPlayerChanged);

    connect(m_resetButton, &QPushButton::clicked,
        this, &MainWindow::OnResetButtonClicked);
}

void MainWindow::OnGameStateChanged(GameState newState)
{
    UpdateStatusLabel();
}

void MainWindow::OnCurrentPlayerChanged(Symbol newPlayer)
{
    UpdateStatusLabel();
}

void MainWindow::OnResetButtonClicked()
{
    m_viewModel->ResetGame();
    UpdateStatusLabel();
}

void MainWindow::UpdateStatusLabel()
{
    m_statusLabel->setText(m_viewModel->GetGameStateString());

    GameState state = m_viewModel->GetGameState();
    QString color;

    switch (state)
    {
    case GameState::WaitingForMove:
        color = "#2196F3"; 
        break;
    case GameState::XWins:
        color = "#4CAF50"; 
        break;
    case GameState::OWins:
        color = "#FF9800";
        break;
    case GameState::Draw:
        color = "#9E9E9E";
        break;
    }

    m_statusLabel->setStyleSheet(QString(
        "QLabel {"
        "   color: %1;"
        "   padding: 10px;"
        "   background-color: #f0f0f0;"
        "   border-radius: 8px;"
        "}"
    ).arg(color));
}