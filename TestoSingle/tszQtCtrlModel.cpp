/***************************************************************************
* Copyright: Testo AG, 79849 Lenzkirch, Postfach 1140
***************************************************************************/

/***************************************************************************
*  INCLUDES
***************************************************************************/
/* fist include must be the header */
#include "tszQtCtrlModel.h"
#include <QListView>
#include <QPixmap>
#include <QDebug>
#include <QCursor>
#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>

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
tszQtCtrlModel::tszQtCtrlModel(uint32_t &width, QObject *parent)
{
    this->width = width-4;
    this->height = 50;
    flag = 0;
    m_ItemBG = "";
}

tszQtCtrlModel::~tszQtCtrlModel()
{
    if(m_Flag.size() != 0)
        m_Flag.clear();
    if(List.size() != 0)
        List.clear();
}

/* function is add ListView row */
int tszQtCtrlModel::rowCount(const QModelIndex &parent) const
{
    //qDebug()<<this->List.size()<<"rowCount";
    return this->List.size();
}

/* function is through struct judge the member wheather is NULL, to call function*/
QVariant tszQtCtrlModel::data(const QModelIndex &index, int role) const
{
    if ( (!index.isValid()) || (index.row() >= List.size()))
        return QVariant();

    switch (role) {
    case Qt::UserRole://256
        return SelectShowData(this->List[index.row()].stListCtrlLeftData);
    case Qt::UserRole+1:
        return SelectShowData(this->List[index.row()].stListCtrlMiddleData);
    case Qt::UserRole+2:
        return SelectShowData(this->List[index.row()].stListCtrlRightData);
    case Qt::UserRole+3:
        return m_Flag.at(index.row());
    case Qt::UserRole+4:
        return flag;
    case Qt::BackgroundColorRole:
        //set erery item background
        return QBrush(QPixmap(m_ItemBG));
    case  Qt::SizeHintRole://13
        return QSize(this->width,this->height);
    default:
        return QVariant();
    }
}

/* function is setData */
bool tszQtCtrlModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

        //stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

/* flag :when we click row or column , it make it can be edit */
Qt::ItemFlags tszQtCtrlModel::flags(const QModelIndex &index) const
{
    if (0 == index.column()) {
        return (QAbstractListModel::flags(index) | Qt::ItemIsEditable);
    } else {
        return QAbstractListModel::flags(index);
    }
}

/* function is change Index value */
bool tszQtCtrlModel::SetModelData(const QModelIndex &index, int row, const QString &changevalue)
{

    /* select listview row to change */
    //stringList.replace(row,changevalue);
    //List.at(row).tszGetDataList().at(1).option = changevalue;
    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::AddModelRow(const QModelIndex &index, const ListCtrlData &list)
{
    if(this->List.size() >= 4294967295)
        return false;
    /* add Listview Item */
    this->List.push_back(list);
    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::AddModelRow(const QModelIndex &index, const uint32_t &itemIndex, const ListCtrlData &list)
{
    if(this->List.size() >= 4294967295)
        return false;
    if(this->List.size() < itemIndex)
        return false;
    this->List.insert(List.begin()+itemIndex,list);
    emit dataChanged(index,index);
    return true;
}

//return to Delegate data
QVariant tszQtCtrlModel::SelectShowData(QString SelectOpt) const
{
    if(!SelectOpt.isEmpty())
    {
        if((SelectOpt.left(2)==":/")&&((SelectOpt.right(4)==".png")||(SelectOpt.right(4)==".jpg")))
        {
            QPixmap pixmap;
            pixmap.load(SelectOpt);
            return pixmap.scaled(40,40,Qt::KeepAspectRatioByExpanding, Qt::FastTransformation);

        }
        else
        {
            return SelectOpt;
        }
    }
    return QVariant();
}

bool tszQtCtrlModel::DeleteModelItem(const QModelIndex &index, int itemIndex)
{
    if(this->List.size() >= 4294967295)
        return false;
    if(this->List.size() < itemIndex)
        return false;

    this->List.erase(List.begin()+itemIndex);
    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::SetModelItem(const QModelIndex &index, uint32_t &itemIndex,
                                     elementPos &position, QString &string)
{
    if(this->List.size() >= 4294967295)
        return false;
    if(this->List.size() <= itemIndex)
        return false;

    if(position == ELEMENT_POS_LEFT)
    {
       this->List[itemIndex].stListCtrlLeftData = string;
    }
    else if(position == ELEMENT_POS_RIGHT)
    {
        this->List[itemIndex].stListCtrlRightData = string;
    }
    else
    {
       this->List[itemIndex].stListCtrlMiddleData = string;
    }
    //this is very important
    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::GetItemAttribute(uint32_t &row, elementType enElementType, QString &stContext, elementPos &enPos )
{
    if(this->List.size() <= row)
        return false;

    if(List.at(row).stListCtrlLeftData=="" && List.at(row).stListCtrlRightData==""&&List.at(row).stListCtrlMiddleData=="")
    {
        stContext = "";
        enPos = ELEMENT_POS_UNKNOW;
    }
    if(enElementType == ELEMENT_TYPE_PNG)
    {
        if((List.at(row).stListCtrlLeftData.left(2)==":/")&&((List.at(row).stListCtrlLeftData.right(4)==".png")||(List.at(row).stListCtrlLeftData.right(4)==".jpg"))
                && ((m_Flag.at(row)&4)==0))
        {
            stContext = List.at(row).stListCtrlLeftData;
            enPos = ELEMENT_POS_LEFT;
        }
        else if((List.at(row).stListCtrlRightData.left(2)==":/")&&((List.at(row).stListCtrlRightData.right(4)==".png")||(List.at(row).stListCtrlRightData.right(4)==".jpg"))
                && ((m_Flag.at(row)&1)==0))
        {
            stContext = List.at(row).stListCtrlRightData;
            enPos = ELEMENT_POS_RIGHT;
        }
        else if((List.at(row).stListCtrlMiddleData.left(2)==":/")&&((List.at(row).stListCtrlMiddleData.right(4)==".png")||(List.at(row).stListCtrlMiddleData.right(4)==".jpg"))
                && ((m_Flag.at(row)&2)==0))
        {
            stContext = List.at(row).stListCtrlMiddleData;
            enPos = ELEMENT_POS_MID;
        }
        else{
            stContext = "";
            enPos = ELEMENT_POS_UNKNOW;
        }
    }

    if(enElementType == ELEMENT_TYPE_TEXT)
    {
        if(!((List.at(row).stListCtrlLeftData.left(2)==":/")&&((List.at(row).stListCtrlLeftData.right(4)==".png")||(List.at(row).stListCtrlLeftData.right(4)==".jpg"))))
        {
            stContext = List.at(row).stListCtrlLeftData;
            enPos = ELEMENT_POS_LEFT;
        }
        else if(!((List.at(row).stListCtrlRightData.left(2)==":/")&&((List.at(row).stListCtrlRightData.right(4)==".png")||(List.at(row).stListCtrlRightData.right(4)==".jpg"))))
        {
            stContext = List.at(row).stListCtrlRightData;
            enPos = ELEMENT_POS_RIGHT;
        }
        else if(!((List.at(row).stListCtrlMiddleData.left(2)==":/")&&((List.at(row).stListCtrlMiddleData.right(4)==".png")||(List.at(row).stListCtrlMiddleData.right(4)==".jpg"))))
        {
            stContext = List.at(row).stListCtrlMiddleData;
            enPos = ELEMENT_POS_MID;
        }
        else {
            stContext = "";
            enPos = ELEMENT_POS_UNKNOW;
        }
    }

    if(enElementType == ELEMENT_TYPE_BTN)
    {
        if((List.at(row).stListCtrlLeftData.left(2)==":/")&&((List.at(row).stListCtrlLeftData.right(4)==".png")||(List.at(row).stListCtrlLeftData.right(4)==".jpg"))
                && ((m_Flag.at(row)&4)==4))
        {
            stContext = List.at(row).stListCtrlLeftData;
            enPos = ELEMENT_POS_LEFT;
        }
        else if((List.at(row).stListCtrlRightData.left(2)==":/")&&((List.at(row).stListCtrlRightData.right(4)==".png")||(List.at(row).stListCtrlRightData.right(4)==".jpg"))
                && ((m_Flag.at(row)&1)==1))
        {
            stContext = List.at(row).stListCtrlRightData;
            enPos = ELEMENT_POS_RIGHT;
        }
        else if((List.at(row).stListCtrlMiddleData.left(2)==":/")&&((List.at(row).stListCtrlMiddleData.right(4)==".png")||(List.at(row).stListCtrlMiddleData.right(4)==".jpg"))
                && ((m_Flag.at(row)&2)==2))
        {
            stContext = List.at(row).stListCtrlMiddleData;
            enPos = ELEMENT_POS_MID;
        }
        else{
            stContext = "";
            enPos = ELEMENT_POS_UNKNOW;
        }
    }


    return true;
}

void tszQtCtrlModel::SetViewItemHeight(uint32_t &height)
{
    this->height = height;
}

bool tszQtCtrlModel::GetButtonFlag(const QModelIndex &index, const uint8_t u8Number)
{
    if(u8Number > 7)
        return false;
    this->m_Flag.append(u8Number);

    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::GetButtonFlag(const QModelIndex &index, const uint8_t &number, const uint32_t &row)
{
    if(number > 7)
        return false;
    if(m_Flag.size() <= row)
        return false;
    this->m_Flag.insert(row, number);
    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::DeleteButtonFlag(const QModelIndex &index, const int &itemRow)
{
    if(this->m_Flag.size() <= itemRow)
        return false;
    this->m_Flag.removeAt(itemRow);

    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::ClearButtonFlag(const QModelIndex &index,uint32_t &u32Row, elementPos &enPos)
{
    if(this->m_Flag.size() <= u32Row)
        return false;

    uint32_t num = this->m_Flag.at(u32Row);
    qDebug()<<num;
    if(enPos == ELEMENT_POS_LEFT)
        num &= 3;
    else if(enPos == ELEMENT_POS_MID)
        num &= 5;
    else if(enPos == ELEMENT_POS_RIGHT)
        num &= 6;
    qDebug()<<num;
    this->m_Flag.replace(u32Row,num);
    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::ChangeButtonFlag(const QModelIndex &index, const int &changeIndex,
                                         Command enCmd, const int changeFlag)
{
    if(changeIndex >= this->m_Flag.size())
        return false;
    int num = this->m_Flag.at(changeIndex);
    if(enCmd==CMD_TYPE_ADD || enCmd==CMD_TYPE_REPLACE)
    {
        num |= changeFlag;
    }

    this->m_Flag.replace(changeIndex,num);

    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::SetDrawFoucsflag(const QModelIndex &index,uint8_t key, const int currentRow)
{
    //flag > 3 must clear, because it can let foucs in circle
    if(key == 2){
        flag ++;
    }else if(key == 1){
        flag --;
    }
    if(flag < 0 && (this->m_Flag.at(currentRow) == 7))
        flag = 2;

    if(flag > 2)
        flag = 0;
    if(key == 3)
        flag = 0;

    if(this->m_Flag.at(currentRow) == 3 || this->m_Flag.at(currentRow) == 5
            || this->m_Flag.at(currentRow) == 6)
    {
        this->flag %= 2;
    }
    else if(this->m_Flag.at(currentRow) == 7)
    {
        this->flag %= 3;
    }

    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::SetItemBackGround(const QModelIndex &index, const QString &stItemBGPic)
{
    this->m_ItemBG = stItemBGPic;

    emit dataChanged(index,index);
    return true;
}

void tszQtCtrlModel::GetItemBackGround(QString &string)
{
    string = this->m_ItemBG;
}

bool tszQtCtrlModel::JudgeButtonPos(uint32_t row)
{
    int num = this->m_Flag.at(row);
    if(num == 0)
        return false;
    return true;
}





