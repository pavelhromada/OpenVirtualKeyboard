#ifndef KEYBOARDSTYLE_H
#define KEYBOARDSTYLE_H

#include <QObject>
#include <QUrl>

class KeyboardStyle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl backgroundUrl READ backgroundUrl WRITE setBackgroundUrl NOTIFY backgroundUrlChanged)
    Q_PROPERTY(QUrl keyUrl READ keyUrl WRITE setKeyUrl NOTIFY keyUrlChanged)
    Q_PROPERTY(QUrl enterKeyUrl READ enterKeyUrl WRITE setEnterKeyUrl NOTIFY enterKeyUrlChanged)
    Q_PROPERTY(QUrl backspaceKeyUrl READ backspaceKeyUrl WRITE setBackspaceKeyUrl NOTIFY backspaceKeyUrlChanged)
    Q_PROPERTY(QUrl shiftKeyUrl READ shiftKeyUrl WRITE setShiftKeyUrl NOTIFY shiftKeyUrlChanged)
    Q_PROPERTY(QUrl spaceKeyUrl READ spaceKeyUrl WRITE setSpaceKeyUrl NOTIFY spaceKeyUrlChanged)
    Q_PROPERTY(QUrl hideKeyUrl READ hideKeyUrl WRITE setHideKeyUrl NOTIFY hideKeyUrlChanged)
    Q_PROPERTY(QUrl symbolKeyUrl READ symbolKeyUrl WRITE setSymbolKeyUrl NOTIFY symbolKeyUrlChanged)
    Q_PROPERTY(QUrl languageKeyUrl READ languageKeyUrl WRITE setLanguageKeyUrl NOTIFY languageKeyUrlChanged)
    Q_PROPERTY(QUrl nextPageKeyUrl READ nextPageKeyUrl WRITE setNextPageKeyUrl NOTIFY nextPageKeyUrlChanged)
    Q_PROPERTY(QUrl keyPreviewUrl READ keyPreviewUrl WRITE setKeyPreviewUrl NOTIFY keyPreviewUrlChanged)
    Q_PROPERTY(QUrl keyAlternativesPreviewUrl READ keyAlternativesPreviewUrl WRITE setKeyAlternativesPreviewUrl
               NOTIFY keyAlternativesPreviewUrlChanged)
    Q_PROPERTY(QUrl languageMenuUrl READ languageMenuUrl WRITE setLanguageMenuUrl NOTIFY languageMenuUrlChanged)
public:
    explicit KeyboardStyle( QObject* parent = nullptr );

    QUrl backgroundUrl() const;
    QUrl keyUrl() const;
    QUrl enterKeyUrl() const;
    QUrl backspaceKeyUrl() const;
    QUrl shiftKeyUrl() const;
    QUrl spaceKeyUrl() const;
    QUrl hideKeyUrl() const;
    QUrl symbolKeyUrl() const;
    QUrl languageKeyUrl() const;
    QUrl nextPageKeyUrl() const;
    QUrl keyPreviewUrl() const;
    QUrl keyAlternativesPreviewUrl() const;
    QUrl languageMenuUrl() const;

public slots:
    void setBackgroundUrl( const QUrl& backgroundUrl );
    void setKeyUrl( const QUrl& keyUrl );
    void setEnterKeyUrl( const QUrl& enterKeyUrl );
    void setBackspaceKeyUrl( const QUrl& backspaceKeyUrl );
    void setShiftKeyUrl( const QUrl& shiftKeyUrl );
    void setSpaceKeyUrl( const QUrl& spaceKeyUrl );
    void setHideKeyUrl( const QUrl& hideKeyUrl );
    void setSymbolKeyUrl( const QUrl& symbolKeyUrl );
    void setLanguageKeyUrl( const QUrl& languageKeyUrl );
    void setNextPageKeyUrl( const QUrl& nextPageKeyUrl );
    void setKeyPreviewUrl( const QUrl& keyPreviewUrl );
    void setKeyAlternativesPreviewUrl( const QUrl& keyAlternativesPreviewUrl );
    void setLanguageMenuUrl( const QUrl& languageMenuUrl );

signals:
    void backgroundUrlChanged();
    void keyUrlChanged();
    void enterKeyUrlChanged();
    void backspaceKeyUrlChanged();
    void shiftKeyUrlChanged();
    void spaceKeyUrlChanged();
    void hideKeyUrlChanged();
    void symbolKeyUrlChanged();
    void languageKeyUrlChanged();
    void nextPageKeyUrlChanged();
    void keyPreviewUrlChanged();
    void keyAlternativesPreviewUrlChanged();
    void languageMenuUrlChanged();

private:
    void loadStyleUrls();

    QUrl _backgroundUrl{"qrc:///ovk/qml/style/DefaultBackground.qml"};
    QUrl _keyUrl{"qrc:///ovk/qml/style/DefaultKeyDelegate.qml"};
    QUrl _enterKeyUrl{"qrc:///ovk/qml/style/DefaultEnterKeyDelegate.qml"};
    QUrl _backspaceKeyUrl{"qrc:///ovk/qml/style/DefaultBackspaceKeyDelegate.qml"};
    QUrl _shiftKeyUrl{"qrc:///ovk/qml/style/DefaultShiftKeyDelegate.qml"};
    QUrl _spaceKeyUrl{"qrc:///ovk/qml/style/DefaultSpaceKeyDelegate.qml"};
    QUrl _hideKeyUrl{"qrc:///ovk/qml/style/DefaultHideKeyDelegate.qml"};
    QUrl _symbolKeyUrl{"qrc:///ovk/qml/style/DefaultSymbolKeyDelegate.qml"};
    QUrl _languageKeyUrl{"qrc:///ovk/qml/style/DefaultLanguageKeyDelegate.qml"};
    QUrl _nextPageKeyUrl{"qrc:///ovk/qml/style/DefaultNextPageKeyDelegate.qml"};
    QUrl _keyPreview{"qrc:///ovk/qml/style/DefaultKeyPreviewDelegate.qml"};
    QUrl _keyAlternativesPreview{"qrc:///ovk/qml/style/DefaultKeyAlternativesPreviewDelegate.qml"};
    QUrl _languageMenuUrl{"qrc:///ovk/qml/style/DefaultLanguageMenu.qml"};
};

#endif // KEYBOARDSTYLE_H
