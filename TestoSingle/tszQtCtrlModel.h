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

typedef enum _elementType
{
    ELEMENT_TYPE_PNG = 0,
    ELEMENT_TYPE_TEXT,
    ELEMENT_TYPE_BTN,
    ELEMENT_TYPE_UNKNOW = 0xFF,
}elementType;

typedef enum _elementPos
{
    ELEMENT_POS_LEFT = 0,
    ELEMENT_POS_MID,
    ELEMENT_POS_RIGHT,
    ELEMENT_POS_UNKNOW = 0xFF,
}elementPos;

typedef enum _Command
{
    CMD_TYPE_ADD = 0,
    CMD_TYPE_REPLACE,
    CMD_TYPE_UNKNOW = 0xFF,
}Command;

typedef std::vector<ListCtrlData> tszDataInfoVec;

class tszQtCtrlModel : public QAbstractListModel
{
    Q_OBJECT
public:
    tszQtCtrlModel(uint32_t &width, QObject *parent = 0);
    ~tszQtCtrlModel();
public:
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole ) const ;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool SetModelData(const QModelIndex &index, int row, const QString &changevalue);
    bool AddModelRow(const QModelIndex &index, const ListCtrlData &list);
    bool AddModelRow(const QModelIndex &index, const uint32_t &itemIndex, const ListCtrlData &list);

    bool SetModelItem(const QModelIndex &index, uint32_t &itemIndex, elementPos &position, QString &string);
    bool DeleteModelItem(const QModelIndex &index, int itemIndex);
    bool GetItemAttribute(uint32_t &row, elementType enElementType, QString &stContext, elementPos &enPos );
    void SetViewItemHeight(uint32_t &height);

    bool GetButtonFlag(const QModelIndex &index, const uint8_t u8Number);
    bool GetButtonFlag(const QModelIndex &index,const uint8_t &number,const uint32_t &row);
    bool DeleteButtonFlag(const QModelIndex &index,const int &itemRow);
    bool ClearButtonFlag(const QModelIndex &index, uint32_t &u32Row, elementPos &enPos);
    bool ChangeButtonFlag(const QModelIndex &index, const int &changeIndex,
                             Command enCmd, const int changeFlag);
    bool SetDrawFoucsflag(const QModelIndex &index, uint8_t key, const int currentRow);
    bool SetItemBackGround(const QModelIndex &index, const QString &stItemBGPic);
    void GetItemBackGround(QString &string);
    bool JudgeButtonPos(uint32_t row);
private:
    QVariant SelectShowData(QString SelectOpt) const;
signals:


private:
    tszDataInfoVec List;
    uint32_t width;
    uint32_t height;
    int flag;
    QString m_ItemBG;
    QList<uint8_t> m_Flag;//0-7 mark item wheather have button, 0 0 0 、0 0 1、...
};

#endif  /* HEADER_GUARD */
