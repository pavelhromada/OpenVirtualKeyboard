#ifndef KEYALTERNATIVESPREVIEW_H
#define KEYALTERNATIVESPREVIEW_H

#include <QQuickItem>
#include <QStringList>

class KeyAlternativesPreview : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal keyWidth READ keyWidth NOTIFY keyWidthChanged)
    Q_PROPERTY(qreal keyHeight READ keyHeight NOTIFY keyHeightChanged)
    Q_PROPERTY(QStringList alternatives READ alternatives NOTIFY alternativesChanged)
    Q_PROPERTY(QQuickItem* delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)
    Q_PROPERTY(int alternativeIndex READ alternativeIndex NOTIFY alternativeIndexChanged)
    Q_PROPERTY(bool uppercase READ uppercase WRITE setUppercase NOTIFY uppercaseChanged)
public:
    KeyAlternativesPreview();

    qreal keyWidth() const;
    void setKeyWidth( qreal keyWidth );

    qreal keyHeight() const;
    void setKeyHeight( qreal keyHeight );

    QStringList alternatives() const;
    void setAlternatives( const QStringList& alternatives );

    int alternativeIndex() const;
    void setAlternativeIndex( int alternativeIndex );

    QQuickItem* delegate() const;

    bool uppercase() const;

public slots:
    void setDelegate( QQuickItem* delegate );
    void setUppercase( bool uppercase );

signals:
    void keyWidthChanged();
    void keyHeightChanged();
    void alternativesChanged();
    void delegateChanged();
    void alternativeIndexChanged();
    void uppercaseChanged();

private:
    QStringList applyUppercase( const QStringList& alternatives );

    qreal       _keyWidth         = 0;
    qreal       _heyHeight        = 0;
    QStringList _alternatives;
    QQuickItem* _delegate         = nullptr;
    int         _alternativeIndex = 0;
    bool        _uppercase        = false;
};

#endif // KEYALTERNATIVESPREVIEW_H
