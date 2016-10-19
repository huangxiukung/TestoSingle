/****************************************************************************
* Copyright: Testo AG, 79849 Lenzkirch, Postfach 1140
*****************************************************************************/
/**@file
@brief<b>Description: </b> Service module implementing the SACP protocol

set the module group for doxygen generation
\ingroup module_comservice
*****************************************************************************/
#ifndef __QT_WINFRAMECLASS_H__
#define __QT_WINFRAMECLASS_H__

/****************************************************************************
*  INCLUDES
*****************************************************************************/

#include<QFrame>
#include<QListWidget>
#include<QListView>
#include<QVBoxLayout>

class tszWinFrame : public QFrame
{
	Q_OBJECT
public:
    explicit tszWinFrame(QFrame *parent = 0);
	~tszWinFrame();

    void sleep(unsigned int msec);
private:

public:

};

#endif /* HEADER_GUARD */
