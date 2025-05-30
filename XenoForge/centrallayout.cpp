#include "centrallayout.h"

QLabel* createIconLabel(const QString &path, QWidget *parent, QGridLayout *layout, int row, int col)
{
    QLabel *label = new QLabel(parent);

    QPixmap pix(path);
    if (!pix.isNull())
    {
        QPixmap scaled = pix.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        label->setPixmap(scaled);
    } else {label->setText("⚠️");}

    layout->addWidget(label, row, col);

    return label;
}
