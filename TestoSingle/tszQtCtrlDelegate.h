/****************************************************************************
* Copyright: Testo AG, 79849 Lenzkirch, Postfach 1140
*****************************************************************************/
/**@file
@brief<b>Description: </b> Service module implementing the SACP protocol

set the module group for doxygen generation
\ingroup module_comservice
*****************************************************************************/
#ifndef __QT_TSZQTCTRLDELEGATECLASS_H__
#define __QT_TSZQTCTRLDELEGATECLASS_H__

/****************************************************************************
*  INCLUDES
*****************************************************************************/
#include <QItemDelegate>

/* QItemDelegate: Inheriting this class is better, reducing the amount of code */
class tszQtCtrlDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit tszQtCtrlDelegate(QObject *parent = 0);
    ~tszQtCtrlDelegate();

public:
    void paint ( QPainter * painter,
                 const QStyleOptionViewItem & option,
                 const QModelIndex & index ) const;
//    QSize sizeHint ( const QStyleOptionViewItem & option,
//                     const QModelIndex & index ) const;

    QWidget * createEditor ( QWidget * parent,
                           const QStyleOptionViewItem & option,
                           const QModelIndex & index ) const ;

    void setEditorData ( QWidget * editor,
                       const QModelIndex & index ) const ;

    void setModelData ( QWidget * editor,
                      QAbstractItemModel * model,
                      const QModelIndex & index ) const  ;

    void updateEditorGeometry ( QWidget * editor,
                              const QStyleOptionViewItem & option,
                              const QModelIndex & index ) const ;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index);
public:

private:
};

#endif /* HEADER_GUARD */
