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
#include <QMessageBox>
#include <QMainWindow>
#include <QDebug>
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
tszQtCtrlListView::tszQtCtrlListView(uint32_t width, uint32_t height)
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
    //register eventtype
    m_ListViewEvent = static_cast<QEvent::Type>(QEvent::registerEventType(-1));
}

tszQtCtrlListView::tszQtCtrlListView(uint32_t width, uint32_t height,QString stListViewBGPic,QString stItemBGPic)
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
    {
       delete m_Model;
    }

    if(m_Delegate != NULL)
        delete m_Delegate;
}

//set item background
void tszQtCtrlListView::ItemSetBGPic(QString stItemBGPic)
{
    m_Model->SetItemBackGround(m_Model->index(0,0,QModelIndex()),stItemBGPic);
    m_ItemBGPic = stItemBGPic;
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

//one parameter
bool tszQtCtrlListView::ItemCreate(elementType enElementType, QString qtString, elementPos enPos)
{
    if(qtString.isEmpty())
        return false;
    //judge user input element type whether correct
    if(! JudgeElementType(enElementType,qtString))
        return false;
    //create a ListCtrlData
    ListCtrlData List;
    ItemZeroizeString(List);
    ListCtrlDataAssignment(enPos, List, qtString);
    //create a button flag, must Initial value
    uint8_t btnFlag = 0;
    UpdateBtnFlag(btnFlag, enElementType,enPos);

    if(! m_Model->GetButtonFlag(m_Model->index(0,0,QModelIndex()),btnFlag))
        return false;
    if(! m_Model->AddModelRow(m_Model->index(0,0,QModelIndex()), List))
        return false;
    return true;
}

bool tszQtCtrlListView::ItemCreate(element enElement1, element enElement2)
{
    //judge two element's position ,Return error of the same
    if(enElement1.enElementpos == enElement2.enElementpos)
        return false;
    //judge user input element type whether correct
    if(! JudgeElementType(enElement1.enElementtype,enElement1.enElementname))
        return false;
    if(! JudgeElementType(enElement2.enElementtype,enElement2.enElementname))
        return false;
    //create a ListCtrlData
    ListCtrlData List;
    ItemZeroizeString(List);
    ListCtrlDataAssignment(enElement1.enElementpos, List, enElement1.enElementname);
    ListCtrlDataAssignment(enElement2.enElementpos, List, enElement2.enElementname);
    //create a button flag, must Initial value
    uint8_t btnFlag = 0;
    UpdateBtnFlag(btnFlag, enElement1.enElementtype, enElement1.enElementpos);
    UpdateBtnFlag(btnFlag, enElement2.enElementtype, enElement2.enElementpos);
    //add flag and a Item
    if(! m_Model->GetButtonFlag(m_Model->index(0,0,QModelIndex()),btnFlag))//0 0 0 no button
        return false;
    if(! m_Model->AddModelRow(m_Model->index(0,0,QModelIndex()), List))
        return false;

    return true;
}

bool tszQtCtrlListView::ItemCreate(element enElement1, element enElement2, element enElement3)
{
    //judge Three element's position ,Return error of the same
    if(enElement1.enElementpos==enElement2.enElementpos || enElement1.enElementpos==enElement3.enElementpos
            || enElement2.enElementpos==enElement3.enElementpos )
        return false;
    //judge user input element type whether correct
    if(! JudgeElementType(enElement1.enElementtype,enElement1.enElementname))
        return false;
    if(! JudgeElementType(enElement2.enElementtype,enElement2.enElementname))
        return false;
    if(! JudgeElementType(enElement3.enElementtype,enElement3.enElementname))
        return false;
    //create a ListCtrlData
    ListCtrlData List;
    ItemZeroizeString(List);
    ListCtrlDataAssignment(enElement1.enElementpos, List, enElement1.enElementname);
    ListCtrlDataAssignment(enElement2.enElementpos, List, enElement2.enElementname);
    ListCtrlDataAssignment(enElement3.enElementpos, List, enElement3.enElementname);
    //create a button flag, must Initial value
    uint8_t btnFlag = 0;
    UpdateBtnFlag(btnFlag, enElement1.enElementtype, enElement1.enElementpos);
    UpdateBtnFlag(btnFlag, enElement2.enElementtype, enElement2.enElementpos);
    UpdateBtnFlag(btnFlag, enElement3.enElementtype, enElement3.enElementpos);
    //add flag and a Item
    if(! m_Model->GetButtonFlag(m_Model->index(0,0,QModelIndex()),btnFlag))//0 0 0 no button
        return false;
    if(! m_Model->AddModelRow(m_Model->index(0,0,QModelIndex()), List))
        return false;

    return true;
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
        //if not picture ,not will be done
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

//data assignment
void tszQtCtrlListView::ListCtrlDataAssignment(elementPos &enPos, ListCtrlData &List ,QString qtString)
{
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
}

bool tszQtCtrlListView::UpdateBtnFlag(uint8_t &btnFlag,elementType &enElementtype, elementPos &enPos)
{
    if(btnFlag > 7)
        return false;
    if(enElementtype == ELEMENT_TYPE_BTN)
    {
        if(enPos == ELEMENT_POS_LEFT){
            btnFlag |= 4;
        }
        else if(enPos == ELEMENT_POS_RIGHT){
            btnFlag |= 1;
        }
        else {
            btnFlag |= 2;
        }
    }

    return true;
}

//key event
void tszQtCtrlListView::keyReleaseEvent(QKeyEvent *event) {

    QModelIndex currIndex = this->currentIndex();

    switch (event->key()) {
    case Qt::Key_0:
        if(m_Model->JudgeButtonPos(currentIndex().row()))
        {
            QMainWindow *win = new QMainWindow();
            QMessageBox::information(win, "Error Message", "Error SetFont");
        }
        break;
    case Qt::Key_Left:
        m_Model->SetDrawFoucsflag(m_Model->index(0,0,QModelIndex()),1,currIndex.row());
        break;
    case Qt::Key_Right:
        m_Model->SetDrawFoucsflag(m_Model->index(0,0,QModelIndex()),2,currIndex.row());
        break;
    case Qt::Key_Up:
        m_Model->SetDrawFoucsflag(m_Model->index(0,0,QModelIndex()),3,currIndex.row());
        break;
    case Qt::Key_Down:
        m_Model->SetDrawFoucsflag(m_Model->index(0,0,QModelIndex()),3,currIndex.row());
        break;
    default:
        break;
    }
}

void tszQtCtrlListView::sleep(uint32_t u32Msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(u32Msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

 bool tszQtCtrlListView::ItemSelectAdd(uint32_t u32Row,elementType enElementType,QString qtString,elementPos enPos)
 {
     if(! JudgeElementType(enElementType,qtString))
         return false;
     //create a ListCtrlData
     ListCtrlData List;
     ItemZeroizeString(List);
     ListCtrlDataAssignment(enPos, List, qtString);
     //create a button flag, must Initial value
     uint8_t btnFlag = 0;
     UpdateBtnFlag(btnFlag, enElementType, enPos);
     //add flag and a Item
     if(! m_Model->GetButtonFlag(m_Model->index(0,0,QModelIndex()),btnFlag, u32Row))//0 0 0 no button
         return false;
     if(! m_Model->AddModelRow(m_Model->index(0,0,QModelIndex()), u32Row, List))
         return false;
     return true;
 }

bool tszQtCtrlListView::ItemSelectAdd(uint32_t u32Row, element enElement1, element enElement2)
{
     //judge two element's position ,Return error of the same
     if(enElement1.enElementpos == enElement2.enElementpos)
         return false;
     //judge user input element type whether correct
     if(! JudgeElementType(enElement1.enElementtype,enElement1.enElementname))
         return false;
     if(! JudgeElementType(enElement2.enElementtype,enElement2.enElementname))
         return false;
     //create a ListCtrlData
     ListCtrlData List;
     ItemZeroizeString(List);
     ListCtrlDataAssignment(enElement1.enElementpos, List, enElement1.enElementname);
     ListCtrlDataAssignment(enElement2.enElementpos, List, enElement2.enElementname);
     //create a button flag, must Initial value
     uint8_t btnFlag = 0;
     UpdateBtnFlag(btnFlag, enElement1.enElementtype, enElement1.enElementpos);
     UpdateBtnFlag(btnFlag, enElement2.enElementtype, enElement2.enElementpos);
     //add flag and a Item
     if(! m_Model->GetButtonFlag(m_Model->index(0,0,QModelIndex()),btnFlag, u32Row))//0 0 0 no button
         return false;
     if(! m_Model->AddModelRow(m_Model->index(0,0,QModelIndex()), u32Row, List))
         return false;
     return true;
}

bool tszQtCtrlListView::ItemSelectAdd(uint32_t u32Row, element enElement1, element enElement2, element enElement3)
{
    //judge Three element's position ,Return error of the same
    if(enElement1.enElementpos==enElement2.enElementpos || enElement1.enElementpos==enElement3.enElementpos
            || enElement2.enElementpos==enElement3.enElementpos )
        return false;
    //judge user input element type whether correct
    if(! JudgeElementType(enElement1.enElementtype,enElement1.enElementname))
        return false;
    if(! JudgeElementType(enElement2.enElementtype,enElement2.enElementname))
        return false;
    if(! JudgeElementType(enElement3.enElementtype,enElement3.enElementname))
        return false;
    //create a ListCtrlData
    ListCtrlData List;
    ItemZeroizeString(List);
    ListCtrlDataAssignment(enElement1.enElementpos, List, enElement1.enElementname);
    ListCtrlDataAssignment(enElement2.enElementpos, List, enElement2.enElementname);
    ListCtrlDataAssignment(enElement3.enElementpos, List, enElement3.enElementname);
    //create a button flag, must Initial value
    uint8_t btnFlag = 0;
    UpdateBtnFlag(btnFlag, enElement1.enElementtype, enElement1.enElementpos);
    UpdateBtnFlag(btnFlag, enElement2.enElementtype, enElement2.enElementpos);
    UpdateBtnFlag(btnFlag, enElement3.enElementtype, enElement3.enElementpos);
    //add flag and a Item
    //add flag and a Item
    if(! m_Model->GetButtonFlag(m_Model->index(0,0,QModelIndex()),btnFlag, u32Row))//0 0 0 no button
        return false;
    if(! m_Model->AddModelRow(m_Model->index(0,0,QModelIndex()), u32Row, List))
        return false;
    return true;
}
//default height is 50
bool tszQtCtrlListView::ItemSetHeight(uint32_t height)
{
    if(height < 50)
        return false;
    m_Model->SetViewItemHeight(height);
    return true;
}

bool tszQtCtrlListView::ItemModify(uint32_t u32Row,Command enCmd,elementType enType,QString stNewContent,elementPos enPos)
{
    if(stNewContent.isEmpty())
        return false;
    if(! JudgeElementType(enType,stNewContent))
        return false;
    //create a button flag, must Initial value
    uint8_t btnFlag = 0;
    UpdateBtnFlag(btnFlag, enType, enPos);
    //change btn flag
    if(! m_Model->ChangeButtonFlag(m_Model->index(0,0,QModelIndex()),u32Row, enCmd,btnFlag))
            return false;
    //modify
    m_Model->SetModelItem(m_Model->index(0,0,QModelIndex()), u32Row, enPos, stNewContent);

    return true;
}

bool tszQtCtrlListView::ItemModify(uint32_t u32ClearRow,elementPos enPos)
{
    //change btn flag
    QString m_Clear = "";
    if(! m_Model->ClearButtonFlag(m_Model->index(0,0,QModelIndex()),u32ClearRow, enPos))
            return false;
    //modify
    m_Model->SetModelItem(m_Model->index(0,0,QModelIndex()), u32ClearRow, enPos, m_Clear);

    return true;
}
//delete a item
bool tszQtCtrlListView::ItemDelete(uint32_t u32Row)
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

bool tszQtCtrlListView::ItemGetContext(uint32_t u32Row, elementType enElementType, QString &stContext, elementPos &enPos)
{
    if(!(m_Model->GetItemAttribute(u32Row, enElementType, stContext, enPos)))
     return false;
    return true;
}
bool tszQtCtrlListView::event(QEvent* e)
{
    if(e->type() == m_ListViewEvent){
            QMainWindow * win = new QMainWindow();
            QMessageBox::warning(win, tr("event"), tr("myEvent1"), QMessageBox::Yes); return true;
    }

    return QWidget::event(e);
}




