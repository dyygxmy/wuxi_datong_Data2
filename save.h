#ifndef SAVE_H
#define SAVE_H

#include <QDialog>

namespace Ui {
class Save;
}

class Save : public QDialog
{
    Q_OBJECT
    
public:
    explicit Save(QWidget *parent = 0);
    ~Save();
public:
signals:
    void sendSaveAdvancedState(bool);
    void sendSaveBaseinfo(bool);
    void sendDeSingle(bool);
    void sendSaveMasterSlaveState(bool);
    void sendCloseInput(bool);
    void sendShutDown(int);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Save *ui;
};

#endif // SAVE_H
