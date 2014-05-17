/*
	Copyright (C) 2008 by Wai Khoo

	AUTHOR:		Wai Khoo
	FILE: 		knight.cpp
	CLASS:		Knight
	DETAILS:	The main algorithm of the program,
				which recursively call a function to solve the tour problem.
*/
#include "knight.h"
#include <ctime>

/*
	Constructor
	Start the timer and set the default board size to 5x5.
*/
Knight::Knight(QObject *parent)
	: QThread(parent)
{
	m_time.start();
	setSize(5);
}

/*
	Destructor
	Terminate current thread, safely
*/
Knight::~Knight()
{
	mutex.lock();
	cond.wakeOne();
	mutex.unlock();
	wait();
}

/*
	Set function
	set the board and result vectors' size.
*/
void Knight::setSize(int s)
{
	m_size = s;
	m_board.resize(m_size);
	m_result.resize(m_size);
	for (int i = 0; i < m_size; i++)
	{
		m_board[i].resize(m_size);
		m_result[i].resize(m_size);
	}
	clear();
}

/*
	Preparing this thread (called from mainwindow)
	Starting this thread with normal priority.
*/
void Knight::commence()
{
	QMutexLocker locker(&mutex);

	int range = m_size*m_size;

	srand((unsigned)time(0));
	int randInt = rand()%range;

	m_y = randInt / m_size;
	m_x = randInt % m_size;

	m_board[m_x][m_y] = 0;

	emit msg(tr("Initial position (%1, %2)").arg(m_x).arg(m_y));
	emit msg(tr("Computing..."));

	if(!isRunning())
		start(NormalPriority);
	else
		cond.wakeOne();
}

/*
	Clear the board and the result vectors.
*/
void Knight::clear()
{
	for (int i= 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			m_board[j][i] = -1;
			m_result[j][i] = -1;
		}
	}
}

/*
	Terminate the thread.
*/
void Knight::stop()
{
	terminate();
	wait();
	emit msg(tr("Stopped"));
}

/*
	Protected function
	Recursively call tour() to solve the problem and calculate how long it takes.
*/
void Knight::run()
{
	// Timing the algo
	m_time.restart();

	// Recursively call the function to solve the problem
	bool success = tour(m_board, m_x, m_y, 0);

	int passed = m_time.elapsed();
	double sec =  double(passed) / 1000.0; // Converting to seconds

	if(!success)
	{
		emit msg(tr("%1 seconds have elapsed\n  No solutions found").arg(sec));
		emit msg(tr("Ready...\n"));
	}
	else
	{
		emit msg(tr("Solution found in %1 seconds").arg(sec));
		animateResult();
	}
	emit done();
}

/*
	Recursive tour function
	Return true if all squares have been visited.
	Attempt to make a valid move,
		if a solution is found, return true;
		otherwise, backtrack.
*/
bool Knight::tour(QVector< QVector<int> > map, int x, int y, int imove)
{
	static const int move[8][2] = {2,-1, -2,-1, 2,1, -2,1, -1,-2, 1,-2, -1,2, 1,2};

	// Solution found
	if (imove == (m_size*m_size-1))
	{
		m_result = map;
		return true;
	}

	// Solution not found yet...make a move
	for (int i = 0; i < 8; i++)
	{
		int newX = x + move[i][0];
		int newY = y + move[i][1];

		// check for valid move
		if ( (newX >= 0) && (newY >= 0) && (newX < m_size) && (newY < m_size) && (map[newX][newY] == -1) )
		{
			QVector< QVector<int> > temp (map);
			temp[newX][newY] = imove + 1;
			if(tour(temp, newX, newY, imove+1)) // Solution found
				return true;
		}
	}
	return false;
}

/*
	Print the solution in the display area
*/
void Knight::printSolution(QVector< QVector<int> > result)
{
	QString text (tr("\n"));

	text.append(tr(" +"));
	for (int i = 0; i < m_size*m_size-1; i++)
		text.append(tr("-"));
	text.append(tr("+\n"));

	for (int i = 0; i < m_size; i++)
	{
		text.append(tr(" | "));
		for (int j = 0; j < m_size; j++)
			text.append(tr("%1 | ").arg(result[j][i], 2));
		text.append(tr("\n"));
	}

	text.append(tr(" +"));
	for (int i = 0; i < m_size*m_size-1; i++)
		text.append(tr("-"));
	text.append(tr("+\n"));

	emit msg(text);
	emit msg(tr("Ready...\n"));
}

/*
	Animate the result by setting each state to Display.
*/
void Knight::animateResult()
{
	emit msg(tr("Animating result now"));

	for (int i = 0; i < m_size*m_size; i++)
	{
		emit board(m_result, i);
		msleep(600);
	}
	printSolution(m_result);
}
