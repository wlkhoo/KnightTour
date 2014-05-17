/*
	Copyright (C) 2008 by Wai Khoo

	AUTHOR:		Wai Khoo
	FILE: 		mainwindow.cpp
	CLASS:		MainWindow
	DETAILS:	The main GUI of the program; implementation of MainWindow
*/
#include "mainwindow.h"

/*
	Constructor
	Initialize all variables and set up layout
*/
MainWindow::MainWindow()
{
	createActions();
	createMenus();
	createToolBars();

	m_dispArea 		= new Display;

	QPushButton *startBut 	= new QPushButton(tr("Start"));
	QPushButton *stopBut	= new QPushButton(tr("Stop"));
	QPushButton *clearBut	= new QPushButton(tr("Clear"));

	m_textArea 		= new QTextEdit;
	m_textArea		->setReadOnly(true);
	m_textArea		->setFont(QFont("Courier", 8));

	QVBoxLayout *vLay 	= new QVBoxLayout;
	vLay			->addWidget(startBut);
	vLay			->addWidget(stopBut);
	vLay			->addWidget(clearBut);
	vLay			->addWidget(m_textArea);
	vLay			->setSpacing(10);

	QWidget *w 		= new QWidget;
	QHBoxLayout *hLay 	= new QHBoxLayout;
	hLay			->addWidget(m_dispArea);
	hLay			->setStretchFactor(m_dispArea, 1);
	hLay			->addLayout(vLay);

	w			->setLayout(hLay);

	connect(startBut, 	SIGNAL(clicked()), 	this, SLOT(start()));
	connect(stopBut,	SIGNAL(clicked()),	this, SLOT(stop()));
	connect(clearBut,	SIGNAL(clicked()),	this, SLOT(clear()));
	connect(m_dispArea,	SIGNAL(msg(QString)),	this, SLOT(message(QString)));

	qRegisterMetaType<QString>("QString");
	qRegisterMetaType< QVector< QVector<int> > >("QVector< QVector<int> >");

	connect(&m_knight,	SIGNAL(msg(QString)),	this, SLOT(message(QString)));
	connect(&m_knight,	SIGNAL(board(QVector< QVector<int> >, int)), m_dispArea, SLOT(receivedBoard(QVector< QVector<int> >, int)));
	connect(&m_knight,	SIGNAL(done()), 	this, SLOT(finished()));

	setWindowTitle(tr("Knight Tour"));
	setCentralWidget(w);
	message(tr("Ready...\n"));
}

/*
	Start a new instance.
	Reset board.
*/
void MainWindow::start()
{
	message(tr("Start\n"));
	setCursor(QCursor(Qt::BusyCursor));
	m_dispArea->clearBoard();
	m_knight.clear();
	m_knight.commence();
}

/*
	Stop the current instance
*/
void MainWindow::stop()
{
	m_knight.stop();
	setCursor(QCursor(Qt::ArrowCursor));
}

/*
	Clear the board and display
*/
void MainWindow::clear()
{
	m_knight.clear();
	m_dispArea->clearBoard();
}

/*
	A message display function
*/
void MainWindow::message(QString msg)
{
	m_textArea	->append(tr(">> %1").arg(msg));
	m_textArea	->update();
}

/*
	Menu action
	5x5 chessboard layout
*/
void MainWindow::layout5()
{
	m_knight.setSize(5);
	m_dispArea->setSize(5);
}

/*
	Menu action
	6x6 chessboard layout
*/
void MainWindow::layout6()
{
	m_knight.setSize(6);
	m_dispArea->setSize(6);
}

/*
	Menu action
	7x7 chessboard layout
*/
void MainWindow::layout7()
{
	m_knight.setSize(7);
	m_dispArea->setSize(7);
}

/*
	Knight has finished his tour.
*/
void MainWindow::finished()
{
	setCursor(QCursor(Qt::ArrowCursor));
}

/*
	Menu actions
	Initialization.
*/
void MainWindow::createActions()
{
	m_actGroup	= new QActionGroup(this);

	m_5x5		= new QAction(tr("5x5"), m_actGroup);
	m_5x5		->setStatusTip(tr("5x5 chessboard layout"));
	m_5x5		->setCheckable(true);
	m_5x5		->setChecked(true);

	m_6x6		= new QAction(tr("6x6"), m_actGroup);
	m_6x6		->setStatusTip(tr("6x6 chessboard layout"));
	m_6x6		->setCheckable(true);

	m_7x7		= new QAction(tr("7x7"), m_actGroup);
	m_7x7		->setStatusTip(tr("7x7 chessboard layout"));
	m_7x7		->setCheckable(true);

	m_actGroup	->setExclusive(true);
	m_actGroup	->setVisible(true);

	connect(m_5x5,	SIGNAL(triggered()), this, SLOT(layout5()));
	connect(m_6x6,	SIGNAL(triggered()), this, SLOT(layout6()));
	connect(m_7x7,	SIGNAL(triggered()), this, SLOT(layout7()));
}

/*
	Menu
	Initialization.
*/
void MainWindow::createMenus()
{
	m_menuBoard	= new QMenu(tr("&Board"), this);
	m_menuBoard	->addAction(m_5x5);
	m_menuBoard	->addAction(m_6x6);
	m_menuBoard	->addAction(m_7x7);

	menuBar()	->addMenu(m_menuBoard);
}

/*
	Toolbar
	Initialization.
*/
void MainWindow::createToolBars()
{
	m_toolBar	= addToolBar(tr("&Board"));
	m_toolBar	->addAction(m_5x5);
	m_toolBar	->addAction(m_6x6);
	m_toolBar	->addAction(m_7x7);
}
