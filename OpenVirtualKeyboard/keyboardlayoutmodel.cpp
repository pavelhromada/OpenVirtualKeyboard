#include "keyboardlayoutmodel.h"
#include <QJsonObject>

QJsonArray KeyboardLayoutModel::pages() const
{
    return _pages;
}

int KeyboardLayoutModel::currentPage() const
{
    return _currentPage;
}

void KeyboardLayoutModel::setPages( const QJsonArray& pagesData )
{
    _pages = pagesData;

    if (_currentPage < _pages.size())
        emit currentPageChanged();
    else
        setCurrentPage( 0 );

    emit pagesChanged();
    notifyStretchChanged();
}

qreal KeyboardLayoutModel::adaptedStretchRow1() const
{
    return calculateStretchForRow( 0 );
}

qreal KeyboardLayoutModel::adaptedStretchRow2() const
{
    return calculateStretchForRow( 1 );
}

qreal KeyboardLayoutModel::adaptedStretchRow3() const
{
    return calculateStretchForRow( 2 );
}

qreal KeyboardLayoutModel::adaptedStretchRow4() const
{
    return calculateStretchForRow( 3 );
}

void KeyboardLayoutModel::setCurrentPage( int page )
{
    if (_pages.size() > 0)
        page = page % _pages.size();

    if (page == _currentPage)
        return;

    _currentPage = page;
    notifyStretchChanged();
    emit currentPageChanged();
}

qreal KeyboardLayoutModel::calculateStretchForRow( int rowIndex ) const
{
    if (_currentPage < 0 || _currentPage >= _pages.size() || _pages.empty())
        return 1;

    const auto page = _pages.at( _currentPage ).toArray();

    if (rowIndex < 0 || rowIndex >= page.size())
        return 1;

    const auto row = page.at( rowIndex ).toArray();
    qreal sumStretch = 0;

    for (auto&& key : row) {
        const auto keyObject = key.toObject();
        sumStretch += keyObject.contains( QLatin1String( "stretch" ))
            ? keyObject[QLatin1String( "stretch" )].toDouble()
            : 1.0;
    }

    return row.size() / sumStretch;
}

void KeyboardLayoutModel::notifyStretchChanged()
{
    emit adaptedStretchRow1Changed();
    emit adaptedStretchRow2Changed();
    emit adaptedStretchRow3Changed();
    emit adaptedStretchRow4Changed();
}
