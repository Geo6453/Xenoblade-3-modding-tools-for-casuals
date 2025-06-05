#ifndef CENTRALLAYOUT_H
#define CENTRALLAYOUT_H

#include <QLabel>
#include <QGridLayout>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include <Qt>

QLabel* createIconLabel(const QString &path, QWidget *parent, QGridLayout *layout, int row, int col, bool scale = true);

class centralLayout : public QWidget
{
    Q_OBJECT

    public:

    signals:

};

#endif // CENTRALLAYOUT_H
