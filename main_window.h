#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT;

public:
    MainWindow();

signals:
    void setParams(int x, int y);

private slots:
    void onApplyButtonClick();

private:
    QLineEdit m_xLineEdit;
    QLineEdit m_yLineEdit;
};

#endif // MAIN_WINDOW_H
