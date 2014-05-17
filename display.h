/*
	Copyright (C) 2008 by Wai Khoo

	AUTHOR:		Wai Khoo
	FILE: 		display.h
	CLASS:		Display
	DETAILS:	Secondary GUI of the program, which handles the chessboard.
			The program solve the problem first and then simulate the tour;
				showing each move is time-consuming and require a lot of resources.
*/
#ifndef         	DISPLAY_H
#define         	DISPLAY_H

#define			MAX	64

#include		<QtGui>

class Display : public QWidget
{
			Q_OBJECT

public:
			Display		(QWidget *parent = 0, Qt::WFlags f = 0);
	void		clearBoard	();
	void		setSize		(int);

signals:
	void 		msg		(QString);

public slots:
	void		receivedBoard	(QVector< QVector<int> >, int);

private:
	QLabel		*m_tile[MAX];
	QPixmap		*m_whiteKnight;
	QPixmap		*m_blackKnight;
	QGridLayout	*m_lay;

	int		m_size;
};
#endif
