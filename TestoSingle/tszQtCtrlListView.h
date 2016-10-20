/****************************************************************************
* Copyright: Testo AG, 79849 Lenzkirch, Postfach 1140
*****************************************************************************/
/**@file
@brief<b>Description: </b> Service module implementing the SACP protocol

set the module group for doxygen generation
\ingroup module_comservice
*****************************************************************************/
#ifndef __QT_TSZQTCTRLCREAT_H__
#define __QT_TSZQTCTRLCREAT_H__

/****************************************************************************
*  INCLUDES
*****************************************************************************/
#include "tszQtCtrlDelegate.h"
#include "tszQtCtrlModel.h"
#include <QString>
#include <QListView>
#include <QEvent>

typedef struct _element
{
    elementType enElementtype;
    QString enElementname;
    elementPos enElementpos;
}element;

class tszQtCtrlListView:public QListView
{
public:
    tszQtCtrlListView(uint32_t width, uint32_t height);
    tszQtCtrlListView(uint32_t width, uint32_t height, QString stListViewBGPic, QString stItemBGPic);
    ~tszQtCtrlListView();
public:
    //item or listview background
    void ItemSetBGPic(QString stItemBGPic);
    void ItemGetBGPic(QString &stItemBGPic);
    void ListViewSetBGPic(QString stListViewBGPic);
    void ListViewGetBGPic(QString &stListViewBGPic);
    //create item
    //default
    bool ItemCreate(QString Picturepath, QString Text, QString Buttonpath);
    //different parameter
    //one parameter
    bool ItemCreate(elementType enElementType, QString qtString, elementPos enPos);
    //two parmeter
    bool ItemCreate(element enElement1, element enElement2);
    //three parmeter
    bool ItemCreate(element enElement1, element enElement2, element enElement3);
    //Select item and modify
    bool ItemSelectAdd(uint32_t u32Row,elementType enElementType,QString qtString,elementPos enPos);
    bool ItemSelectAdd(uint32_t u32Row, element enElement1, element enElement2);
    bool ItemSelectAdd(uint32_t u32Row, element enElement1, element enElement2, element enElement3);
    //size
    bool ItemSetHeight(uint32_t height);
    //if del, then stNewContent == NULL
    bool ItemModify(uint32_t u32Row,Command enCmd,elementType enType,QString stNewContent,elementPos enPos);
    bool ItemModify(uint32_t u32ClearRow,elementPos enPos);
    //delete,
    bool ItemDelete(uint32_t u32Row);
    //get item Context
    bool ItemGetContext(uint32_t u32Row,elementType enElementType,QString &stContext,elementPos &enPos);
public:
    bool event(QEvent* e);
protected:
    void keyReleaseEvent(QKeyEvent *event);
    //ivan mark, communication with other app or frame

signals:
    //emit
    //others app or frame can use this signals to call others function
    void GetSignals(QString signalType);
private:
   // void tszSetItemOption(int u32Row, QString &opt, QString &opt1, QString &opt2, Position2 cmd);
    void ItemZeroizeString(ListCtrlData &stListData);
    bool JudgeElementType(elementType &enElementType, QString &qtString);
    void ListCtrlDataAssignment(elementPos &enPos, ListCtrlData &List, QString qtString);
    bool UpdateBtnFlag(uint8_t &btnFlag, elementType &enElementtype, elementPos &enPos);
    void sleep(uint32_t u32Msec);
private:
    QString m_ListViewBGPic;//ListView back ground picture
    QString m_ItemBGPic;//Item back ground picture
    tszQtCtrlModel *m_Model;
    tszQtCtrlDelegate *m_Delegate;
    QEvent::Type m_ListViewEvent;
};

#endif /* HEADER_GUARD */
