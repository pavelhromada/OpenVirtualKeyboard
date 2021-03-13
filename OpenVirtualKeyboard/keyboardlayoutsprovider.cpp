#include <QDir>
#include <QJsonDocument>
#include <QFile>
#include <QLocale>

#include "keyboardlayoutsprovider.h"
#include "keyboardlayoutmodel.h"
#include "loggingcategory.h"
#include "utils.h"

const QString ALPHABET_FILENAME = QStringLiteral("alphabet.json");
const QString SYMBOLS_FILENAME = QStringLiteral("symbols.json");
const QString DIGITS_FILENAME = QStringLiteral("digits.json");
const QString NUMBERS_FILENAME = QStringLiteral("numbers.json");
const QString DIAL_FILENAME = QStringLiteral("dial.json");

KeyboardLayoutsProvider::KeyboardLayoutsProvider()
{
    loadDefaultLayout();
    loadCustomLayouts();
    applySystemLocaleLayout();
    emit layoutsCountChanged();
}

KeyboardLayoutModel* KeyboardLayoutsProvider::alphabetModel() const
{
    return const_cast<KeyboardLayoutModel*>( &_alphabetModel );
}

KeyboardLayoutModel* KeyboardLayoutsProvider::symbolsModel() const
{
    return const_cast<KeyboardLayoutModel*>( &_symbolsModel );
}

KeyboardLayoutModel* KeyboardLayoutsProvider::dialModel() const
{
    return const_cast<KeyboardLayoutModel*>( &_dialModel );
}

KeyboardLayoutModel* KeyboardLayoutsProvider::numbersModel() const
{
    return const_cast<KeyboardLayoutModel*>( &_numbersModel );
}

KeyboardLayoutModel* KeyboardLayoutsProvider::digitsModel() const
{
    return const_cast<KeyboardLayoutModel*>( &_digitsModel );
}

void KeyboardLayoutsProvider::incrementPageForLayoutType( KeyboardLayoutType::Type layoutType )
{
    switch (layoutType) {
        case KeyboardLayoutType::Alphabet:
            _alphabetModel.setCurrentPage( _alphabetModel.currentPage() + 1 );
            break;
        case KeyboardLayoutType::Symbols:
            _symbolsModel.setCurrentPage( _symbolsModel.currentPage() + 1 );
            break;
        case KeyboardLayoutType::Dial:
            _dialModel.setCurrentPage( _dialModel.currentPage() + 1 );
            break;
        case KeyboardLayoutType::Numbers:
            _numbersModel.setCurrentPage( _numbersModel.currentPage() + 1 );
            break;
        case KeyboardLayoutType::Digits:
            _digitsModel.setCurrentPage( _digitsModel.currentPage() + 1 );
            break;
    }
}

int KeyboardLayoutsProvider::selectedLayoutIndex() const
{
    return _selectedLayoutIndex;
}

int KeyboardLayoutsProvider::layoutsCount() const
{
    return _layoutData.size();
}

void KeyboardLayoutsProvider::setSelectedLayoutIndex( int index )
{
    if (_selectedLayoutIndex == index)
        return;

    const auto layouts = layoutsList();

    if (index >= layouts.size() || index < 0)
        return;

    const auto& layout = _layoutData[ layouts.at( index )];

    _alphabetModel.setPages( layout.alphabet );
    _symbolsModel.setPages( layout.symbols );
    _dialModel.setPages( layout.dial );
    _numbersModel.setPages( layout.numbers );
    _digitsModel.setPages( layout.digits );

    _selectedLayoutIndex = index;
    emit selectedLayoutIndexChanged();
    emit selectedLayoutChanged();
}

QString KeyboardLayoutsProvider::selectedLayout() const
{
    return layoutsList()[ _selectedLayoutIndex ];
}

void KeyboardLayoutsProvider::loadDefaultLayout()
{
    auto& data    = _layoutData[ "en_US" ];
    data.alphabet = loadLayoutData( ":/ovk/qml/layouts/" + ALPHABET_FILENAME );
    data.symbols  = loadLayoutData( ":/ovk/qml/layouts/" + SYMBOLS_FILENAME );
    data.dial     = loadLayoutData( ":/ovk/qml/layouts/" + DIAL_FILENAME );
    data.numbers  = loadLayoutData( ":/ovk/qml/layouts/" + NUMBERS_FILENAME );
    data.digits   = loadLayoutData( ":/ovk/qml/layouts/" + DIGITS_FILENAME );
}

void KeyboardLayoutsProvider::loadCustomLayouts()
{
    const auto  layoutsPath = ovk::layoutsAbsolutePath();
    const QDir  layouts( layoutsPath );

    if (layoutsPath.isEmpty() || !layouts.exists()) {
        qCDebug(logOvk) << "custom layouts not found, only default en_US will be available";
        return;
    }

    QStringList layoutFilesFilter {
        ALPHABET_FILENAME, SYMBOLS_FILENAME, DIGITS_FILENAME, NUMBERS_FILENAME, DIAL_FILENAME
    };

    const auto& fallback     = _layoutData[ "en_US" ];
    const auto  layoutsDirs  = layouts.entryList( QDir::Dirs | QDir::NoDot | QDir::NoDotDot );

    if (!layoutsDirs.isEmpty())
        qCDebug( logOvk ).noquote() << "trying to load custom layouts:" << layoutsDirs.join( ", " );

    const auto asignLayout = [this]( const QString&     fileName,
                                     const QString&     layoutDir,
                                     const QStringList& foundFiles,
                                     const QJsonArray&  fallback ) {
        if (foundFiles.contains( fileName )) {
            qCDebug(logOvk).noquote() << ".. loading file" << fileName;
            return loadLayoutData( layoutDir + fileName );
        } else {
            qCDebug(logOvk).noquote() << ".. providing fallback of" << fileName;
            return fallback;
        }
    };

    for (auto&& layoutDirName : layoutsDirs) {
        const QDir layoutDir( layoutsPath + layoutDirName );
        const auto layoutFiles = layoutDir.entryList( layoutFilesFilter );

        if (layoutFiles.isEmpty())
            continue;        

        const auto dirPath = layoutDir.absolutePath() + QDir::separator();
        auto&      data    = _layoutData[layoutDirName];

        qCDebug( logOvk ).noquote() << "trying to load layout files from:" << dirPath;

        data.alphabet = asignLayout( ALPHABET_FILENAME, dirPath, layoutFiles, fallback.alphabet );
        data.symbols  = asignLayout( SYMBOLS_FILENAME,  dirPath, layoutFiles, fallback.symbols  );
        data.dial     = asignLayout( DIAL_FILENAME,     dirPath, layoutFiles, fallback.dial     );
        data.numbers  = asignLayout( NUMBERS_FILENAME,  dirPath, layoutFiles, fallback.numbers  );
        data.digits   = asignLayout( DIGITS_FILENAME,   dirPath, layoutFiles, fallback.digits   );
    }
}

void KeyboardLayoutsProvider::applySystemLocaleLayout()
{
    QLocale defaultLocale; // takes locale set by QLocale::setDefault() or system's locale, if
                           // setDefault() was not called by application

    auto lang          = defaultLocale.name();
    lang               = _layoutData.contains( lang ) ? lang : "en_US";
    const auto layouts = layoutsList();
    qCDebug(logOvk).noquote() << "Applying default keyboard layout:" << lang;
    setSelectedLayoutIndex( layouts.indexOf( lang ));
}

QJsonArray KeyboardLayoutsProvider::loadLayoutData( const QString& layoutFilename )
{
    QFile layoutFile( layoutFilename );

    if (!layoutFile.open( QIODevice::ReadOnly | QIODevice::Text ))
        return QJsonArray();

    return QJsonDocument::fromJson( layoutFile.readAll() ).array();
}

QStringList KeyboardLayoutsProvider::layoutsList() const
{
    return _layoutData.keys();
}
