/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

#ifndef KEYBOARDLAYOUTMODEL_H
#define KEYBOARDLAYOUTMODEL_H

#include <QObject>
#include <QJsonArray>

class KeyboardLayoutModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonArray pages READ pages NOTIFY pagesChanged)
    Q_PROPERTY(int currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(qreal adaptedStretchRow1 READ adaptedStretchRow1 NOTIFY adaptedStretchRow1Changed)
    Q_PROPERTY(qreal adaptedStretchRow2 READ adaptedStretchRow2 NOTIFY adaptedStretchRow2Changed)
    Q_PROPERTY(qreal adaptedStretchRow3 READ adaptedStretchRow3 NOTIFY adaptedStretchRow3Changed)
    Q_PROPERTY(qreal adaptedStretchRow4 READ adaptedStretchRow4 NOTIFY adaptedStretchRow4Changed)

public:
    QJsonArray pages() const;
    int currentPage() const;

    void setPages( const QJsonArray& pagesData );

    qreal adaptedStretchRow1() const;
    qreal adaptedStretchRow2() const;
    qreal adaptedStretchRow3() const;
    qreal adaptedStretchRow4() const;

public slots:
    void setCurrentPage( int page );

signals:
    void pagesChanged();
    void currentPageChanged();
    void adaptedStretchRow1Changed();
    void adaptedStretchRow2Changed();
    void adaptedStretchRow3Changed();
    void adaptedStretchRow4Changed();

private:
    qreal calculateStretchForRow( int rowIndex ) const;
    void notifyStretchChanged();

    QJsonArray _pages;
    int        _currentPage = 0;
};

#endif // KEYBOARDLAYOUTMODEL_H
