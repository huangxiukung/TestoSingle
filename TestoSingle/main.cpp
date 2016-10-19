/***************************************************************************
* Copyright: Testo AG, 79849 Lenzkirch, Postfach 1140
***************************************************************************/

/***************************************************************************
*  INCLUDES
***************************************************************************/
/* fist include must be the header */
#include "tszWinFrame.h"
#include "tszQtCtrlListView.h"
#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>

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
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    tszWinFrame *w = new tszWinFrame();
    tszQtCtrlListView *tszListview = new tszQtCtrlListView(360,480);
    QVBoxLayout *m_pLayout = new QVBoxLayout();
    m_pLayout->addWidget(tszListview);

//    listview->setListViewSize(w,h);

//    listview->CreateItem(w,h);

//    listview->setItemSize(w,h);

//    listview->InsertItem(item index,"\image\background.png","setting", "btn");

//    listview->InsertItem(item index,ParM,);
//    listview->InsertItem(item index,ParM,);
//    listview->InsertItem(item index,ParM,);
    //listview->tszSetItemSize(360,90);
/***************************************************************************
     *这个的功能是将一个具有实际内存的BUTTON放到LISTVIEW的对应行中，故这样的button是
     * 是可以实实在在的关联信号与槽的*/
    /*
    QIcon icon(":/head/qq.png");
     //设置按钮的图标
    QPushButton *btn = new QPushButton(listview);
    btn->setIcon(icon);
    btn->setGeometry(300,10,40,40);
***************************************************************************/

/***************************************************************************
//    参考代码如下：
//    QStandardItemModel *model = new QStandardItemModel(ui->listView);
//    ui->listView->setModel(model);
//    for(int i = 0; i < 5; i++) {
//    QStandardItem *item = new QStandardItem(QString::number(i));
//    model->appendRow(item);
//    QModelIndex index = model->indexFromItem(item);
//    QCheckBox *box = new QCheckBox( ui->listView);
//    box->setCheckable(true);
//    box->setCheckState(Qt::Unchecked);
//    box->setText("ssss");
//    ui->listView->setIndexWidget(index, box);
***************************************************************************/
/**************************************************************************
    tszItemset_T x;
    x.string = ":/head/5.jpg";
    x.position = Left;

    tszItemset_T y;
    y.string = ":/head/2.jpg";
    y.position = Right;

    tszItemset_T z;
    z.string = ":/head/1.jpg";
    z.position = Middle;
***************************************************************************/
    QString x = ":/head/5.jpg";
    QString y = ":/head/1.jpg";
    QString z = ":/head/3.jpg";
    //set every item's height
//    listview->tszSetItemSize(50);
    for(int i=0; i<100; i++)
    {
//        listview->tszInsertItem(0,":/head/qq.png","Hello","World");
//        listview->tszInsertItem(1,":/head/qq.png","Hello","World");

//        listview->tszappend(x,y,z,ONE);
//        listview->tszappend(z,y,TWO);
//        listview->tszappend(x,z,THREE);
//        listview->tszappend(x,z,FOUR);

        //default
//        listview->tszappend(2,":/head/9.jpg","how are you",":/head/1.jpg");
//        listview->tszSetItem(15,BUTTON,":/head/qq.png",Middle);
//        listview->tszSetItem(15,BUTTON,":/head/9.jpg",Left);
    }

//    void MainWindow::keyReleaseEvent(QKeyEvent *event) {
//    #if 0
//        if (event->key() == Qt::Key_Down) {
//            ui->fm1->setVisible(false);
//            ui->fm2->setVisible(true);
//            myflashlist->setVisible(true);
//           // event->accept();
//           // update();
//        }
//        if (event->key() == Qt::Key_Up) {
//            ui->fm1->setVisible(true);
//            ui->fm2->setVisible(false);
//            myflashlist->setVisible(false);
//           // event->accept();
//           // update();
//            return;
//        }
//    #endif
//    }



//     tszItemset_T set1;
//     set1.position = Left;
//     tszItemset_T set2;
//     set2.position = Right;
//     tszItemset_T set3;
//     set3.position = Middle;

//     tszItemset_T set4;
//     set4.position = Left;
//     set4.string = ":/head/8.jpg";

    // listview->tszSetItem(1,Middle);
    //qDebug()<<listview->model()->rowCount();

    //listview->tszDeleteItem(1,3);
    //listview->tszDeleteItem(2);
    w->setLayout(m_pLayout);
    w->show();
//    这部分数据的改变必须用线程来做，不然会变的非常的卡
//    while(1)
//    {
//        int progress = rand()%100;

//        set1.string = QString::number(progress);
//        set2.string = QString::number(progress);
//        set3.string = QString::number(progress);
//        w->sleep(1);//depend on data transmission speed
//        listview->tszSetItem(1,set2);

//        listview->tszSetItem(2,set1);
//        listview->tszSetItem(2,set2);

//        listview->tszSetItem(3,set1);
//        listview->tszSetItem(3,set2);
//        listview->tszSetItem(3,set3);

//        listview->tszSetItem(4,set4);
//    }
       return a.exec();
}
