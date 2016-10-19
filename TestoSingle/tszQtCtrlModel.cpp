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
tszQtCtrlModel::tszQtCtrlModel(int &width, QObject *parent)
{
    this->width = width;
    this->height = 50;
    flag = 0;
    m_ItemBG = "";
}

tszQtCtrlModel::~tszQtCtrlModel()
{

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
    qDebug()<<role<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
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
    qDebug()<<"ffffffffffffffffffffffffffffffffffsetData..........";
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
    qDebug()<<"flags..........";

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

bool tszQtCtrlModel::AddModelRow(const QModelIndex &index, int &itemIndex, const ListCtrlData &list)
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
    if(this->List.size() < itemIndex || itemIndex < 1)
        return false;

    this->List.erase(List.begin()+itemIndex-1);
    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::DeleteModelItem(const QModelIndex &index, int itemIndex1, int itemIndex2)
{
    if(this->List.size() >= 4294967295)
        return false;
    if(this->List.size() < itemIndex1 ||this->List.size() < itemIndex2
            || itemIndex1 < 1 || itemIndex2 < 1)
        return false;
    this->List.erase(List.begin()+itemIndex1-1);
    this->List.erase(List.begin()+itemIndex2-1);
    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::SetModelItem(const QModelIndex &index, int &itemIndex,
                                     elementPos &position, QString &string)
{
    if(this->List.size() >= 4294967295)
        return false;
    //this->List[index.row()].first
    if(itemIndex < 0|| this->List.size() <= itemIndex)
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

bool tszQtCtrlModel::GetItemAttribute(int &row, int enElementType, QString &stContext, QString &enPos )
{
//    tszGetAttri_T back;
//    back.pic = 0;
//    back.text = 0;
//    back.button = 0;
//    if(itemIndex >= List.size())
//        return back;
//    //get in this row how many button
//    while(this->m_Flag.at(itemIndex)&(this->m_Flag.at(itemIndex)-1))
//    {
//        back.button ++;
//    }

//    if((this->List.at(itemIndex).stListCtrlLeftData.left(2) == ":/")
//            &&((this->List.at(itemIndex).stListCtrlLeftData.right(4)==".png" )
//               ||(this->List.at(itemIndex).stListCtrlLeftData.right(4)==".jpg" )))
//    {
//        back.pic ++;
//    }
//    else
//    {
//        back.text ++;
//    }

//    if((this->List.at(itemIndex).stListCtrlRightData.left(2) == ":/")
//            &&((this->List.at(itemIndex).stListCtrlRightData.right(4)==".png" )
//               ||(this->List.at(itemIndex).stListCtrlRightData.right(4)==".jpg" )))
//    {
//        back.pic ++;
//    }
//    else
//    {
//        back.text ++;
//    }

//    if((this->List.at(itemIndex).stListCtrlMiddleData.left(2) == ":/")
//            &&((this->List.at(itemIndex).stListCtrlMiddleData.right(4)==".png" )
//               ||(this->List.at(itemIndex).stListCtrlMiddleData.right(4)==".jpg" )))
//    {
//        back.pic ++;
//    }
//    else
//    {
//        back.text ++;
//    }

//    back.pic = back.pic - back.button;

//    return back;

}

void tszQtCtrlModel::SetViewItemHeight(int &height)
{
    this->height = height;
}

bool tszQtCtrlModel::GetButtonFlag(const QModelIndex &index, const int number)
{
    if(number > 7 || number < 0)
        return false;
    //qDebug()<<List.size()<<"s.........................i.............z........e";
    this->m_Flag.append(number);

    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::GetButtonFlag(const QModelIndex &index, const int number, const int row)
{
    if(number > 7 || number < 0)
        return false;
    this->m_Flag.insert(row, number);
    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::DeleteButtonFlag(const QModelIndex &index, const int &itemRow)
{
    if(this->m_Flag.size() >= itemRow)
        return false;
    this->m_Flag.removeAt(itemRow);

    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::ChangeButtonFlag(const QModelIndex &index, const int &changeIndex,
                                         const int type, const int changeFlag)
{
    if(changeIndex >= this->m_Flag.size())
        return false;
    int num = this->m_Flag.at(changeIndex);
    if(type == 0)
    {
        num |= changeFlag;
    }
    else
    {
        num &= changeFlag;
    }

    this->m_Flag.replace(changeIndex,num);

    emit dataChanged(index,index);
    return true;
}

bool tszQtCtrlModel::SetDrawFoucsflag(const QModelIndex &index, const int currentRow)
{
    //flag > 3 must clear, because it can let foucs in circle
    if(this->flag == 3)
        this->flag = 0;

    if(this->m_Flag.at(currentRow) == 3 || this->m_Flag.at(currentRow) == 5
            || this->m_Flag.at(currentRow) == 6)
    {
        this->flag ++;
        this->flag %= 2;
    }
    else if(this->m_Flag.at(currentRow) == 7)
    {
        this->flag ++;
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







