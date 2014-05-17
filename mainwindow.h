/*
	Copyright (C) 2008 by Wai Khoo

	AUTHOR:		Wai Khoo
	FILE: 		mainwindow.h
	CLASS:		MainWindow
	DETAILS:	The main GUI of the program.
*/
#ifndef         	MAINWINDOW_H
#define         	MAINWINDOW_H

#include 		"display.h"
#include		"knight.h"

class MainWindow : public QMainWindow
{
        		Q_OBJECT

public:
			MainWindow	();

private slots:
	void		start		();
	void		stop		();
	void		clear		();
	void		message		(QString);
	void		layout5		();
	void		layout6		();
	void		layout7		();
	void		finished	();

private:
	void		createActions	();
	void		createMenus	();
	void		createToolBars	();

	Display		*m_dispArea;
	QTextEdit	*m_textArea;
	Knight		m_knight;

	QMenu		*m_menuBoard;

	QAction		*m_5x5;
	QAction		*m_6x6;
	QAction		*m_7x7;

	QToolBar	*m_toolBar;

	QActionGroup	*m_actGroup;
};
#endif
