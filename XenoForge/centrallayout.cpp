#include "centrallayout.h"

QLabel* createIconLabel(const QString &path, QWidget *parent, QGridLayout *layout, int row, int col, bool scale)
{
    QLabel *label = new QLabel(parent);

    QPixmap pix(path);
    if (!pix.isNull() & scale == true)
    {
        QPixmap scaled = pix.scaled(300, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        label->setPixmap(scaled);
    } else {label->setPixmap(pix);}

    layout->addWidget(label, row, col);

    return label;
}
