#ifndef KEYPREVIEW_H
#define KEYPREVIEW_H

#include <QQuickItem>

class KeyPreview : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)
    Q_PROPERTY(qreal keyWidth READ keyWidth NOTIFY keyWidthChanged)
    Q_PROPERTY(qreal keyHeight READ keyHeight NOTIFY keyHeightChanged)
    Q_PROPERTY(QString keyText READ keyText NOTIFY keyTextChanged)
public:
    KeyPreview();

    QQuickItem* delegate() const;

    qreal keyWidth() const;
    void setKeyWidth( qreal keyWidth );

    qreal keyHeight() const;
    void setKeyHeight( qreal keyHeight );

    QString keyText() const;
    void setKeyText( const QString& keyText );

public slots:
    void setDelegate( QQuickItem* delegate );

signals:
    void delegateChanged();
    void keyWidthChanged();
    void keyHeightChanged();
    void keyTextChanged();

private:
    QQuickItem* _delegate  = nullptr;
    qreal       _keyWidth  = 0;
    qreal       _keyHeight = 0;
    QString     _keyText;
};

#endif // KEYPREVIEW_H
