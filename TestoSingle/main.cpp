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
    qDebug()<<"test";
    tszWinFrame *w = new tszWinFrame();
    tszQtCtrlListView *tszListview = new tszQtCtrlListView(360,480);
    QVBoxLayout *m_pLayout = new QVBoxLayout();
    m_pLayout->addWidget(tszListview);
    w->setLayout(m_pLayout);
    w->show();

    QString m_TestStr ;
    //set every item's height
    tszListview->ItemSetHeight(50);
    //item background will cover listview background,must Note one of them
    //item background
    tszListview->ItemSetBGPic(":/head/9.jpg");
    //listview background
    tszListview->ListViewSetBGPic(":/head/9.jpg");
    //get item background
    tszListview->ItemGetBGPic(m_TestStr);
    qDebug()<<"item background"+m_TestStr;
    //get listview background
    tszListview->ListViewGetBGPic(m_TestStr);
    qDebug()<<"listview background"+m_TestStr;
    element par1;
    par1.enElementname = ":/head/1.jpg";
    par1.enElementpos =  ELEMENT_POS_LEFT;
    par1.enElementtype = ELEMENT_TYPE_BTN;

    element par2;
    par2.enElementname = ":/head/2.jpg";
    par2.enElementpos =  ELEMENT_POS_RIGHT;
    par2.enElementtype = ELEMENT_TYPE_BTN;

    element par3;
    par3.enElementname = ":/head/3.jpg";
    par3.enElementpos =  ELEMENT_POS_MID;
    par3.enElementtype = ELEMENT_TYPE_BTN;

    QString stContext;
    elementPos pos;

    for(int i=0; i<1; i++)
    {
        //create test
        tszListview->ItemCreate(":/head/9.jpg","hello",":/head/1.jpg");
        tszListview->ItemCreate(ELEMENT_TYPE_PNG,":/head/1.jpg",ELEMENT_POS_LEFT);
        tszListview->ItemCreate(ELEMENT_TYPE_TEXT,"head",ELEMENT_POS_RIGHT);
        tszListview->ItemCreate(ELEMENT_TYPE_BTN,":/head/1.jpg",ELEMENT_POS_MID);
        tszListview->ItemCreate(par1,par2);
        tszListview->ItemCreate(par1,par2,par3);
        tszListview->ItemModify(0,ELEMENT_POS_RIGHT);
        tszListview->ItemModify(1,CMD_TYPE_ADD,ELEMENT_TYPE_PNG,":/head/1.jpg",ELEMENT_POS_MID);
        //test Get rid of the notes
        tszListview->ItemSelectAdd(0,ELEMENT_TYPE_BTN,":/head/2.jpg",ELEMENT_POS_MID);
        tszListview->ItemSelectAdd(0,par1,par2);
        tszListview->ItemSelectAdd(0,par1,par2,par3);
        tszListview->ItemDelete(0);
        tszListview->ItemDelete(0);
        tszListview->ItemDelete(0);
        tszListview->ItemGetContext(0,ELEMENT_TYPE_TEXT,stContext,pos);
        qDebug()<<"stContext is"<<stContext<<"position is"<<pos;
    }

    //    This part need used thread to do, or it will be very card
        while(0)
        {
            int progress = rand()%100;
            w->sleep(1);//depend on data transmission speed
            tszListview->ItemModify(0,CMD_TYPE_REPLACE,ELEMENT_TYPE_TEXT,QString::number(progress),ELEMENT_POS_MID);
            tszListview->ItemModify(1,CMD_TYPE_REPLACE,ELEMENT_TYPE_TEXT,QString::number(progress),ELEMENT_POS_RIGHT);
            tszListview->ItemModify(2,CMD_TYPE_REPLACE,ELEMENT_TYPE_TEXT,QString::number(progress),ELEMENT_POS_LEFT);
        }

       return a.exec();
}
