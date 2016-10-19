/****************************************************************************
* Copyright: Testo AG, 79849 Lenzkirch, Postfach 1140
*****************************************************************************/
/**@file
@brief<b>Description: </b> Service module implementing the SACP protocol

set the module group for doxygen generation
\ingroup module_comservice
*****************************************************************************/
#ifndef __QT_TSZQTCTRLMODELCLASS_H__
#define __QT_TSZQTCTRLMODELCLASS_H__

/****************************************************************************
*  INCLUDES
*****************************************************************************/
#include<QAbstractListModel>
#include <vector>

/* every Item position's context */
typedef struct _tszListCtrlData
{
    QString stListCtrlLeftData;
    QString stListCtrlMiddleData;
    QString stListCtrlRightData;
}ListCtrlData;

typedef enum _elementPos
{
    ELEMENT_POS_LEFT = 0,
    ELEMENT_POS_RIGHT,
    ELEMENT_POS_MID,
    ELEMENT_POS_UNKNOW = 0xFF,
}elementPos;

typedef std::vector<ListCtrlData> tszDataInfoVec;

class tszQtCtrlModel : public QAbstractListModel
{
    Q_OBJECT
public:
    tszQtCtrlModel(int &width, QObject *parent = 0);
    ~tszQtCtrlModel();
public:
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole ) const ;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool SetModelData(const QModelIndex &index, int row, const QString &changevalue);
    bool AddModelRow(const QModelIndex &index, const ListCtrlData &list);
    bool AddModelRow(const QModelIndex &index, int &itemIndex, const ListCtrlData &list);

    bool SetModelItem(const QModelIndex &index, int &itemIndex, elementPos &position, QString &string);
    bool DeleteModelItem(const QModelIndex &index, int itemIndex);
    bool DeleteModelItem(const QModelIndex &index, int itemIndex1, int itemIndex2);
    bool GetItemAttribute(int &row, int enElementType,QString &stContext,QString &enPos );
    void SetViewItemHeight(int &height);

    bool GetButtonFlag(const QModelIndex &index,const int number);
    bool GetButtonFlag(const QModelIndex &index,const int number,const int row);
    bool DeleteButtonFlag(const QModelIndex &index,const int &itemRow);
    bool ChangeButtonFlag(const QModelIndex &index,const int &changeIndex,
                             const int type,const int changeFlag);
    bool SetDrawFoucsflag(const QModelIndex &index, const int currentRow);
    bool SetItemBackGround(const QModelIndex &index, const QString &stItemBGPic);
    void GetItemBackGround(QString &string);

private:
    QVariant SelectShowData(QString SelectOpt) const;
signals:


private:
    tszDataInfoVec List;
    int width;
    int height;
    int flag;
    QString m_ItemBG;
    QList<int> m_Flag;//0-7 mark item wheather have button, 0 0 0 、0 0 1、...
};

#endif  /* HEADER_GUARD */
