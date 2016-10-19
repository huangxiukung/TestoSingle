/***************************************************************************
* Copyright: Testo AG, 79849 Lenzkirch, Postfach 1140
***************************************************************************/

/***************************************************************************
*  INCLUDES
***************************************************************************/
/* fist include must be the header */
#include "tszQtCtrlListView.h"
#include <QApplication>
#include <QKeyEvent>
#include <QTime>
/***************************************************************************
* DEFINES
***************************************************************************/
/* as few as posible */

/***************************************************************************
* MODULE GLOBALS
***************************************************************************/

/* some static variable */


/***************************************************************************
* LOCAL FUNCTION DECLARATIONS
***************************************************************************/

/* only static local functions are declared here */

/***************************************************************************
* FUNCTION IMPLEMENTATIONS
***************************************************************************/
tszQtCtrlListView::tszQtCtrlListView(int width, int height)
{
    this->setFixedWidth(width);
    this->setFixedHeight(height);
    //set model
    m_Model = new tszQtCtrlModel(width);
    this->setModel(m_Model);
    //set delegate
    this->setItemDelegateForRow(1, new tszQtCtrlDelegate());
    m_Delegate = new tszQtCtrlDelegate();
    this->setItemDelegate(m_Delegate);
}

tszQtCtrlListView::tszQtCtrlListView(int width, int height,QString stListViewBGPic,QString stItemBGPic)
{
    this->setFixedWidth(width);
    this->setFixedHeight(height);
    //set model
    m_Model = new tszQtCtrlModel(width);
    this->setModel(m_Model);
    //set delegate
    this->setItemDelegateForRow(1, new tszQtCtrlDelegate());
    m_Delegate = new tszQtCtrlDelegate();
    this->setItemDelegate(m_Delegate);
    //set Item background
    ItemSetBGPic(stItemBGPic);
    //set listview background
    ListViewSetBGPic(stListViewBGPic);
}

//Destructor
tszQtCtrlListView::~tszQtCtrlListView()
{
    if(m_Model != NULL)
        delete m_Model;
    if(m_Delegate != NULL)
        delete m_Delegate;
}

//set item background
void tszQtCtrlListView::ItemSetBGPic(QString stItemBGPic)
{
    m_Model->SetItemBackGround(m_Model->index(0,0,QModelIndex()),m_ItemBGPic);
    stItemBGPic = m_ItemBGPic;
}

//get item background information
void tszQtCtrlListView::ItemGetBGPic(QString &stItemBGPic)
{
    this->m_Model->GetItemBackGround(stItemBGPic);
}

//set listview background
void tszQtCtrlListView::ListViewSetBGPic(QString stListViewBGPic)
{
    QString m_String = QString("background-image: url(%1);").arg(stListViewBGPic);
    this->setStyleSheet(m_String);
    this->m_ListViewBGPic = stListViewBGPic;

}

//get listview background information
void tszQtCtrlListView::ListViewGetBGPic(QString &stListViewBGPic)
{
    stListViewBGPic = this->m_ListViewBGPic;
}

//default, can add a picture a text and a button
bool tszQtCtrlListView::ItemCreate(QString Picturepath, QString Text, QString Buttonpath)
{
    ListCtrlData List;
    List.stListCtrlLeftData = Picturepath;
    List.stListCtrlMiddleData = Text;
    List.stListCtrlRightData = Buttonpath;
    //button flag is use in judge whether have foucs
    if(!m_Model->GetButtonFlag(m_Model->index(0,0,QModelIndex()),1))
        return false;//0 0 1
    //add a row
    if(! m_Model->AddModelRow(m_Model->index(0,0,QModelIndex()), List))
        return false;
    return true;
}

bool tszQtCtrlListView::ItemCreate(elementType enElementType, QString qtString, elementPos enPos)
{
    if(qtString.isEmpty())
        return false;
    if(! JudgeElementType(enElementType,qtString))
        return false;

    ListCtrlData List;
    ItemZeroizeString(List);
    if(enPos == ELEMENT_POS_LEFT)
    {
        List.stListCtrlLeftData = qtString;
    }
    else if(enPos == ELEMENT_POS_RIGHT)
    {
        List.stListCtrlRightData = qtString;
    }
    else
    {
        List.stListCtrlMiddleData = qtString;
    }

    if(! m_Model->GetButtonFlag(m_Model->index(0,0,QModelIndex()),0))//0 0 0 no button
        return false;
    if(! m_Model->AddModelRow(m_Model->index(0,0,QModelIndex()), List))
        return false;

}
void tszQtCtrlListView::ItemZeroizeString(ListCtrlData &stListData)
{
    stListData.stListCtrlLeftData = "";
    stListData.stListCtrlMiddleData = "";
    stListData.stListCtrlRightData = "";
}

bool tszQtCtrlListView::JudgeElementType(elementType &enElementType, QString &qtString)
{
    if(enElementType == ELEMENT_TYPE_PNG || enElementType == ELEMENT_TYPE_BTN)
    {
        //picture and button must a picture path
        if((qtString.left(2)==":/")&&((qtString.right(4)==".png")||(qtString.right(4)==".jpg")))
            return true;
        //if not picture not will be done
        return false;
    }
    else
    {
        //if is a picture path ,nothing will be done
        if((qtString.left(2)==":/")&&((qtString.right(4)==".png")||(qtString.right(4)==".jpg")))
            return false;
        //text is not a picture path
        return true;
    }
}

void tszQtCtrlListView::keyReleaseEvent(QKeyEvent *event) {

    QModelIndex currIndex = this->currentIndex();

    switch (event->key()) {
    case Qt::Key_0:
        if(currIndex.row() == 3||currIndex.row() == 1 ||currIndex.row() == 2||currIndex.row() == 0)
        {

        }
        break;
    case Qt::Key_Left:
        m_Model->SetDrawFoucsflag(m_Model->index(0,0,QModelIndex()),currIndex.row());
        break;
    case Qt::Key_Right:
        m_Model->SetDrawFoucsflag(m_Model->index(0,0,QModelIndex()),currIndex.row());
        break;
    default:
        break;
    }
}

void tszQtCtrlListView::sleep(int u32Msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(u32Msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

bool tszQtCtrlListView::ItemDelete(int u32Row)
{
    if(m_Model->DeleteModelItem(m_Model->index(0,0,QModelIndex()),u32Row))
    {
       m_Model->DeleteButtonFlag(m_Model->index(0,0,QModelIndex()),u32Row);
       return true;
    }
    else
    {
        return false;
    }
}

 bool tszQtCtrlListView::ItemGetContext(int u32Row,elementType enElementType,QString &stContext,elementPos &enPos)
 {
    //m_Model->GetItemAttribute(u32Row);
 }





