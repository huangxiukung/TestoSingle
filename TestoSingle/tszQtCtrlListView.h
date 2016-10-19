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

typedef enum _elementType
{
    ELEMENT_TYPE_PNG = 0,
    ELEMENT_TYPE_TEXT,
    ELEMENT_TYPE_BTN,
    ELEMENT_TYPE_UNKNOW = 0xFF,
}elementType;

typedef enum _Command
{
    CMD_TYPE_ADD = 0,
    CMD_TYPE_DEL,
    CMD_TYPE_REPLACE,
    CMD_TYPE_UNKNOW = 0xFF,
}Command;

class tszQtCtrlListView:public QListView
{
public:
    tszQtCtrlListView(int width, int height);
    tszQtCtrlListView(int width, int height, QString stListViewBGPic, QString stItemBGPic);
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
    //many parameter
    bool ItemCreate(elementType enElementType,QString qtString,elementPos enPos);
    //bool ItemCreate(elementType enElementType,QString qtStr1, elementType enElementType, QString qtStr2);
    //bool ItemCreate(elementThreePosPermutation enSelect,QString qtStr1, QString qtStr2, QString qtStr3);
    //Select item and modify
    bool ItemSelectAdd(int u32Row,elementType enElementType,QString qtString,elementPos enPos);
    //size
    bool ItemSetHeight(int height);
    //if del, then stNewContent == NULL
    bool ItemModify(int u32Row,Command enCmd,QString stNewContent,elementPos enPos);
    //delete,
    bool ItemDelete(int u32Row);
    //get item Context
    bool ItemGetContext(int u32Row,elementType enElementType,QString &stContext,elementPos &enPos);
protected:
    void keyReleaseEvent(QKeyEvent *event);
    //ivan mark, communication with other app or frame
signals:
    //others app or frame can use this signals to call others function
    void GetSignals(void);
private:
   // void tszSetItemOption(int u32Row, QString &opt, QString &opt1, QString &opt2, Position2 cmd);
    void ItemZeroizeString(ListCtrlData &stListData);
    bool JudgeElementType(elementType &enElementType, QString &qtString);
    void sleep(int u32Msec);
private:
    QString m_ListViewBGPic;//ListView back ground picture
    QString m_ItemBGPic;//Item back ground picture
    tszQtCtrlModel *m_Model;
    tszQtCtrlDelegate *m_Delegate;
};

#endif /* HEADER_GUARD */
