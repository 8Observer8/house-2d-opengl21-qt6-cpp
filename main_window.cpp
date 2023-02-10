#include "main_window.h"

#include <QtCore/QSize>
#include <QtGui/QFont>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QVBoxLayout>

#include "opengl_widget.h"
#include <iostream>

MainWindow::MainWindow()
{
    setWindowTitle("OpenGL21 Qt6 C++");
    setFixedSize(QSize(312, 400));

    QLabel *coordLabel = new QLabel("Введите координаты домика:");
    coordLabel->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    m_xLineEdit.setText("75");
    m_yLineEdit.setText("100");

    QLabel *xLabel = new QLabel("x:");
    QLabel *yLabel = new QLabel("y:");
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(xLabel);
    hbox->addWidget(&m_xLineEdit);
    hbox->addWidget(yLabel);
    hbox->addWidget(&m_yLineEdit);

    QPushButton *applyButton = new QPushButton("Применить");
    applyButton->setFixedSize(QSize(100, 30));
    connect(applyButton, &QPushButton::clicked, this,
        &MainWindow::onApplyButtonClick);
    QHBoxLayout *applyButtonLayout = new QHBoxLayout();
    applyButtonLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    applyButtonLayout->addWidget(applyButton);

    OpenGLWidget *openGLWidget = new OpenGLWidget();

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(coordLabel);
    vbox->addLayout(hbox);
    vbox->addLayout(applyButtonLayout);
    vbox->addWidget(openGLWidget);
    setLayout(vbox);

    QFont font("serif", 11);
    coordLabel->setFont(font);
    m_xLineEdit.setFont(font);
    m_yLineEdit.setFont(font);
    xLabel->setFont(font);
    yLabel->setFont(font);
    applyButton->setFont(font);

    connect(this, &MainWindow::setParams, openGLWidget,
        &OpenGLWidget::setParamsSlot);

    int x = m_xLineEdit.text().toInt();
    int y = m_yLineEdit.text().toInt();
    emit setParams(x, y);
}

void MainWindow::onApplyButtonClick()
{
    int x = m_xLineEdit.text().toInt();
    int y = m_yLineEdit.text().toInt();
    emit setParams(x, y);
}
