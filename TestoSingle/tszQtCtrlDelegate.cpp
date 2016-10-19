/***************************************************************************
* Copyright: Testo AG, 79849 Lenzkirch, Postfach 1140
***************************************************************************/

/***************************************************************************
*  INCLUDES
***************************************************************************/
/* fist include must be the header */
#include "tszQtCtrlDelegate.h"
#include <QStyledItemDelegate>
#include <QTimeEdit>
#include <QPainter>
#include <QApplication>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include <QMainWindow>

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
/*
* set data changes:
* createEditor->updateEditorGeometry->setEditorData->
* ->setModelData->updateEditorGeometry->setEditorData
*/
/* only static local functions are declared here */

/***************************************************************************
* FUNCTION IMPLEMENTATIONS
***************************************************************************/
tszQtCtrlDelegate::tszQtCtrlDelegate(QObject *parent)
{

}

tszQtCtrlDelegate::~tszQtCtrlDelegate()
{
}

void tszQtCtrlDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option,
                                const QModelIndex & index ) const
{
    QStyleOptionViewItem opt = setOptions(index, option);
    // prepare
    painter->save();

    //text from Model data
    const QString& text = index.data(Qt::UserRole).toString();
    const QString& text1 = index.data(Qt::UserRole+1).toString();
    const QString& text2 = index.data(Qt::UserRole+2).toString();
    const int& num = index.data(Qt::UserRole+3).toInt();
    const int& flag = index.data(Qt::UserRole+4).toInt();
    // get the rectangles and position
    QFontMetrics fm(painter->font());
    QRect displayRect = QRect(opt.rect.topLeft()+QPoint(0,20),QSize(fm.width(text),fm.height()));
    QRect displayRect1 = QRect(opt.rect.topLeft()+QPoint(140,20),QSize(fm.width(text1),fm.height()));
    QRect displayRect2 = QRect(opt.rect.topRight()+QPoint(-100,20),QSize(fm.width(text2),fm.height()));
    QRect Left = QRect(opt.rect.topLeft()+QPoint(10,5), QSize(40,40));
    QRect Middle = QRect(opt.rect.topLeft()+QPoint(140,5), QSize(40,40));
    //QRect Middle = QRect(opt.rect.topRight()-QPoint(100,-20), QSize(20,20));
    QRect Right = QRect(opt.rect.topRight()-QPoint(100,-5), QSize(40,40));

    //picture
    const QPixmap& pixmap = qvariant_cast<QPixmap>(index.data(Qt::UserRole));
    const QPixmap& pixmap1 = qvariant_cast<QPixmap>(index.data(Qt::UserRole+1));
    const QPixmap& pixmap2 = qvariant_cast<QPixmap>(index.data(Qt::UserRole+2));

    //draw from rectangles, text, picture
    //draw Background
    drawBackground(painter, opt, index);
    //draw text
    painter->drawText(displayRect, text);
    painter->drawText(displayRect1, text1);
    painter->drawText(displayRect2, text2);
    //draw picture
    painter->drawPixmap(Left, pixmap);
    painter->drawPixmap(Middle, pixmap1);
    painter->drawPixmap(Right, pixmap2);

    //Focus
    switch (num) {
    case 0://000
        break;
    case 1://001
        drawFocus(painter, opt, Right);
        break;
    case 2://010
        drawFocus(painter, opt, Middle);
        break;
    case 3://011
        if(flag == 0)
        {
           drawFocus(painter, opt, Middle);
        }
        else
        {
            drawFocus(painter, opt, Right);
        }
        break;
    case 4://100
        drawFocus(painter, opt, Left);
        break;
    case 5://101
        if(flag == 0)
        {
            drawFocus(painter, opt, Left);
        }
        else
        {
            drawFocus(painter, opt, Right);
        }
        //drawFocus(painter, opt, Middle);
        break;
    case 6://110
        if(flag == 0)
        {
            drawFocus(painter, opt, Left);
        }
        else
        {
            drawFocus(painter, opt, Middle);
        }
        break;
    default://111
        if(flag == 0)
        {
            drawFocus(painter, opt, Left);
        }
        else if(flag == 1)
        {
            drawFocus(painter, opt, Middle);
        }
        else
        {
            drawFocus(painter, opt, Right);
        }
        break;
    }
    // done
    painter->restore();

}

/* function can set option value, it is set every option's width and heigh show in listview */
//QSize tszQtCtrlDelegate::sizeHint(const QStyleOptionViewItem &option,
//                              const QModelIndex &index) const
//{
//    return option.rect.size();
//}

/* createEditor */
QWidget * tszQtCtrlDelegate::createEditor ( QWidget * parent, const QStyleOptionViewItem & option,
                                            const QModelIndex & index ) const
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

/* function is set Model's data */
void tszQtCtrlDelegate::setModelData ( QWidget * editor, QAbstractItemModel * model,
                                       const QModelIndex & index ) const
{
    QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor) ;
    /* complete date changes */
    model->setData(index, qVariantFromValue(textEdit->text()));
}

/* setEditorData must read Model's data */
void tszQtCtrlDelegate::setEditorData ( QWidget * editor, const QModelIndex & index ) const
{
    const QString& text = index.data(Qt::UserRole).toString();
    QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor) ;
    textEdit->setText(text);
}

/* once list element be edit, paint not done, so must be call updateEditorGeometry function */
void tszQtCtrlDelegate::updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option,
                                               const QModelIndex & index ) const
{
    QRect decorationRect = QRect(option.rect.topLeft(), QSize(80,80));
    QRect displayRect = QRect(decorationRect.topRight()+QPoint(20,30),QSize(150,25));
    editor->setGeometry(displayRect);
}

/* wherever the mouse click, this function will be call, once press ,twice release */
bool tszQtCtrlDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                             const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {

        qDebug()<<"editorEvent"<<QCursor::pos().rx()<<QCursor::pos().ry();
          /* test */
          if(QCursor::pos().rx()>= 300&&QCursor::pos().rx() <= 780
                  &&QCursor::pos().ry() >=100&&QCursor::pos().ry() <= 390)
          {
//              QMainWindow *win = new QMainWindow();
//              QMessageBox::information(win, "Error Message", "Error SetFont");
          }
    }
}


