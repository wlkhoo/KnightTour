/*
	Copyright (C) 2008 by Wai Khoo

	AUTHOR:		Wai Khoo
	FILE: 		display.cpp
	CLASS:		Display
	DETAILS:	Secondary GUI of the program, which handles the chessboard.
			The program solve the problem first and then simulate the tour;
				showing each move is time-consuming and require a lot of resources.
*/
#include	"display.h"

/*
	Constructor
	Initialize variables
*/
Display::Display(QWidget *parent, Qt::WFlags f)
	: QWidget(parent, f)
{
	m_lay 			= new QGridLayout(this);

	for (int i = 0; i < MAX; i++)
		m_tile[i]	= new QLabel(this);

	setSize(5);
}

/*
	Set function
	set the board to be SxS layout.
*/
void Display::setSize(int s)
{
	m_size 		= s;

	m_whiteKnight	= new QPixmap(":/images/wn.png");
	m_blackKnight	= new QPixmap(":/images/bn.png");

	*m_whiteKnight	= m_whiteKnight->scaled(QSize(width()/m_size, height()/m_size), Qt::KeepAspectRatio);
	*m_blackKnight	= m_blackKnight->scaled(QSize(width()/m_size, height()/m_size), Qt::KeepAspectRatio);


	for (int i = 0; i < MAX; i++)
	{
		m_lay		->removeWidget(m_tile[i]);
		m_tile[i]	->setVisible(false);
	}

	clearBoard();

	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{	// Setting up chessboard pattern
			if ((i%2) == 0)
			{
				if ((j%2) == 0)
					m_tile[i*m_size+j]	->setPalette(QPalette(QColor(Qt::white)));
				else
					m_tile[i*m_size+j]	->setPalette(QPalette(QColor(Qt::darkGray)));
			}
			else
			{
				if ((j%2) == 0)
					m_tile[i*m_size+j]	->setPalette(QPalette(QColor(Qt::darkGray)));
				else
					m_tile[i*m_size+j]	->setPalette(QPalette(QColor(Qt::white)));
			}

			m_tile[i*m_size+j]			->setBackgroundRole(QPalette::Window);
			m_tile[i*m_size+j]			->setAutoFillBackground(true);
			m_tile[i*m_size+j]			->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			m_tile[i*m_size+j]			->setVisible(true);

			m_lay					->addWidget(m_tile[i*m_size+j], i, j);
		}
	}

	setLayout(m_lay);
	update();
}

/*
	Clear the board
*/
void Display::clearBoard()
{
	for (int i = 0; i < m_size*m_size; i++)
		m_tile[i]->clear();
}

/*
	Receive Knight moves and display it.
	Current position is displayed with white knight; visited position is displayed with black knight
*/
void Display::receivedBoard(QVector< QVector<int> > board, int current)
{
	int val;
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			val = board[j][i];
			if (val == current)
				m_tile[j+i*m_size] -> setPixmap(*m_whiteKnight);
			else if (val == current-1)
				m_tile[j+i*m_size] -> setPixmap(*m_blackKnight);
		}
	}
}
