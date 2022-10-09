#include "inputevents.h"
#include "GlobalVarible.h"
#include <QDebug>
InputEvents::InputEvents(QObject *parent) :
    QObject(parent)
{
    numcount = 0;
    issingle = false;
    keyvalue = 0;
    m_thread.start();
    this->moveToThread(&m_thread);
}

void InputEvents::InputEventStart()
{

    connect(&m_timer,SIGNAL(timeout()),this,SLOT(mtimerarrve3()));
    const char *dev_name;
    dev_name = "/dev/input/event0";
    while(1)
    {
        keys_fd = open(dev_name, O_RDWR, 0);
        if (keys_fd < 0)
        {
            continue;
        }
        else
        {
            break;
        }

    }
    if (fcntl(keys_fd, F_SETFL, O_NONBLOCK) < 0)
        printf("Unable set to NONBLOCK mode");
   m_timer.start(100);





}

void InputEvents::mtimerarrve3()
{
//    qDebug()<<"point[mtimerarrve3_0]:";
   //qDebug() << "JHGKJHGHHHHHHHHHHHHHHHHHG1 " << ISWARNING;
    if(!ISWARNING)
    {
  //qDebug() << "JHGKJHGHHHHHHHHHHHHHHHHHG2";
 // qDebug() << "JHGKJHGHHHHHHHHHHHHHHHHHG1 " << ISWARNING;
    if(read(keys_fd,&t,sizeof(t))==sizeof(t))
    {

       // qDebug() << "JJJJJJJJLJKKKKKKKKKKKKKKKKKKKKKKKcode" << t.code;
       //qDebug() << "JJJJJJJJLJKKKKKKKKKKKKKKKKKKKKKKKvalue" << t.value;

        if(t.type == EV_KEY)
            if(t.value==0 || t.value==1)
            {
                switch(t.code)
                {
                case 114:   //钥匙
                   // qDebug() << "JJJJJJJJLJKKKKKKKKKKKKKKKKKKKKKKK" << t.value;
                    keyvalue = t.value;

                        if(t.value == 1)
                        {
                            numcount++;
                            if(numcount == 20)//长拧处理，20个循环都拧着
                            {
                              emit sendconfigwarning(false);//跳过所有
                              numcount = 0;
                            }

                        }
                        else if(t.value == 0)//拧一下处理
                        {
                            numcount = 0;
                            //qDebug() << "uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu44";
                            if(SYSS == "ING")
                            {
                               emit sendconfigwarning(true);//跳过一个
                            }

                        }

                    //printf("key114 %s\n",(t.value)?"Pressed":"Released");
                    break;

                case 115:   //电池
                    if(!battery)
                    {
                        if(t.value == 0)
                            emit sendbatterysta(true);
                        else
                            emit sendbatterysta(false);
                        break;
                    }

                case 116:
                   // printf("key116 %s\n",(t.value)?"Pressed":"Released");
                    break;

                default:
                    break;
                }
            }
    }
    else
    {
        // qDebug() << "JJJJJJJJLJKKKKKKKKKKKKKKKKKKKKKKKeyvalue" << keyvalue;
        if(keyvalue)
        {
            numcount++;
            // qDebug() << "JJJJJJJJLJKKKKKKKKKKKKKKKKKKKKKKKeyvalue" << numcount;
            if(numcount == 20)
            {
               if(SYSS == "ING")
              emit sendconfigwarning(false);
              numcount = 0;
              keyvalue = 0;
            }

        }

    }
    }
    else
    {
        read(keys_fd,&t,sizeof(t));
    }


//    qDebug()<<"point[mtimerarrve3_1]:";
}
