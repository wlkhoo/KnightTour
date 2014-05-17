/*
	Copyright (C) 2008 by Wai Khoo

	AUTHOR:		Wai Khoo
	FILE: 		knight.h
	CLASS:		Knight
	DETAILS:	The main algorithm of the program,
				which recursively call a function to solve the tour problem.
*/
#ifndef 			KNIGHT_H
#define 			KNIGHT_H

#include 			<QMutex>
#include 			<QThread>
#include 			<QWaitCondition>
#include 			<QVector>
#include			<QTime>

class Knight : public QThread
{
				Q_OBJECT

public:
				Knight		(QObject *parent = 0);
				~Knight		();
	void			commence	();
	void			clear		();
	void			stop		();
	void			setSize		(int);

signals:
	void			msg		(QString);
	void			board		(QVector< QVector<int> >, int);
	void			done		();

protected:
	void			run		();

private:
	bool			tour		(QVector< QVector<int> >, int, int, int);
	void			printSolution	(QVector< QVector<int> >);
	void			animateResult	();

	QMutex			mutex;
	QWaitCondition		cond;

	QVector< QVector<int> >	m_board;
	QVector< QVector<int> >	m_result;

	QTime			m_time;

	int			m_x;
	int			m_y;
	int 			m_size;
};
#endif
