/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

#ifndef KEYBOARDLAYOUTSPROVIDER_H
#define KEYBOARDLAYOUTSPROVIDER_H

#include <QObject>
#include <QJsonArray>
#include <QMap>
#include "keyboardlayoutmodel.h"
#include "keyboardlayouttype.h"

struct LayoutData
{
    QJsonArray alphabet;
    QJsonArray symbols;
    QJsonArray dial;
    QJsonArray numbers;
    QJsonArray digits;
};

class KeyboardLayoutsProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList layoutsList READ layoutsList NOTIFY layoutsListChanged)
    Q_PROPERTY(QString selectedLayout READ selectedLayout NOTIFY selectedLayoutChanged)
    Q_PROPERTY(int selectedLayoutIndex READ selectedLayoutIndex WRITE setSelectedLayoutIndex
               NOTIFY selectedLayoutIndexChanged)
    Q_PROPERTY(int layoutsCount READ layoutsCount NOTIFY layoutsCountChanged)
    Q_PROPERTY(KeyboardLayoutModel* alphabetModel READ alphabetModel NOTIFY alphabetModelChanged)
    Q_PROPERTY(KeyboardLayoutModel* symbolsModel READ symbolsModel NOTIFY symbolsModelChanged)
    Q_PROPERTY(KeyboardLayoutModel* dialModel READ dialModel NOTIFY dialModelChanged)
    Q_PROPERTY(KeyboardLayoutModel* numbersModel READ numbersModel NOTIFY numbersModelChanged)
    Q_PROPERTY(KeyboardLayoutModel* digitsModel READ digitsModel NOTIFY digitsModelChanged)

public:
    KeyboardLayoutsProvider();

    QStringList layoutsList() const;
    QString selectedLayout() const;
    KeyboardLayoutModel* alphabetModel() const;
    KeyboardLayoutModel* symbolsModel() const;
    KeyboardLayoutModel* dialModel() const;
    KeyboardLayoutModel* numbersModel() const;
    KeyboardLayoutModel* digitsModel() const;
    void incrementPageForLayoutType( KeyboardLayoutType::Type layoutType );
    int selectedLayoutIndex() const;
    int layoutsCount() const;

public slots:
    void setSelectedLayoutIndex( int index );

signals:
    void layoutsListChanged();
    void alphabetModelChanged();
    void symbolsModelChanged();
    void dialModelChanged();
    void numbersModelChanged();
    void digitsModelChanged();
    void selectedLayoutChanged();
    void selectedLayoutIndexChanged();
    void layoutsCountChanged();

private:
    void loadDefaultLayout();
    void loadCustomLayouts();
    void applySystemLocaleLayout();
    QJsonArray loadLayoutData( const QString& layoutFilename );

    KeyboardLayoutModel       _alphabetModel;
    KeyboardLayoutModel       _symbolsModel;
    KeyboardLayoutModel       _dialModel;
    KeyboardLayoutModel       _numbersModel;
    KeyboardLayoutModel       _digitsModel;
    QMap<QString, LayoutData> _layoutData;
    int                       _selectedLayoutIndex = -1;
};

#endif // KEYBOARDLAYOUTSPROVIDER_H
