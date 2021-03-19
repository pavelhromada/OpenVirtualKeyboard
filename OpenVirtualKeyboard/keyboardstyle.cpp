/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

#include <QFile>
#include "keyboardstyle.h"
#include "utils.h"
#include "loggingcategory.h"

static const char* BACKGROUND_COMPONENT_NAME      = "Background.qml";
static const char* KEY_COMPONENT_NAME             = "Key.qml";
static const char* ENTER_KEY_COMPONENT_NAME       = "EnterKey.qml";
static const char* BACKSPACE_KEY_COMPONENT_NAME   = "BackspaceKey.qml";
static const char* SHIFT_KEY_COMPONENT_NAME       = "ShiftKey.qml";
static const char* SPACE_KEY_COMPONENT_NAME       = "SpaceKey.qml";
static const char* HIDE_KEY_COMPONENT_NAME        = "HideKey.qml";
static const char* SYMBOL_KEY_COMPONENT_NAME      = "SymbolKey.qml";
static const char* LANGUAGE_KEY_COMPONENT_NAME    = "LanguageKey.qml";
static const char* NEXT_KEY_COMPONENT_NAME        = "NextPageKey.qml";
static const char* KEY_PREVIEW_COMPONENT_NAME     = "KeyPreview.qml";
static const char* KEY_ALT_PREVIEW_COMPONENT_NAME = "KeyAlternativesPreview.qml";
static const char* LANGUAGE_MENU_COMPONENT_NAME   = "LanguageMenu.qml";

KeyboardStyle::KeyboardStyle( QObject* parent )
    : QObject( parent )
{
    loadStyleUrls();
}

QUrl KeyboardStyle::backgroundUrl() const
{
    return _backgroundUrl;
}

QUrl KeyboardStyle::keyUrl() const
{
    return _keyUrl;
}

QUrl KeyboardStyle::enterKeyUrl() const
{
    return _enterKeyUrl;
}

QUrl KeyboardStyle::backspaceKeyUrl() const
{
    return _backspaceKeyUrl;
}

QUrl KeyboardStyle::shiftKeyUrl() const
{
    return _shiftKeyUrl;
}

QUrl KeyboardStyle::spaceKeyUrl() const
{
    return _spaceKeyUrl;
}

QUrl KeyboardStyle::hideKeyUrl() const
{
    return _hideKeyUrl;
}

QUrl KeyboardStyle::symbolKeyUrl() const
{
    return _symbolKeyUrl;
}

QUrl KeyboardStyle::languageKeyUrl() const
{
    return _languageKeyUrl;
}

QUrl KeyboardStyle::nextPageKeyUrl() const
{
    return _nextPageKeyUrl;
}

QUrl KeyboardStyle::keyPreviewUrl() const
{
    return _keyPreview;
}

QUrl KeyboardStyle::keyAlternativesPreviewUrl() const
{
    return _keyAlternativesPreview;
}

QUrl KeyboardStyle::languageMenuUrl() const
{
    return _languageMenuUrl;
}

void KeyboardStyle::setBackgroundUrl( const QUrl& backgroundUrl )
{
    if ( _backgroundUrl == backgroundUrl )
        return;

    _backgroundUrl = backgroundUrl;
    emit backgroundUrlChanged();
}

void KeyboardStyle::setKeyUrl( const QUrl& keyUrl )
{
    if ( _keyUrl == keyUrl )
        return;

    _keyUrl = keyUrl;
    emit keyUrlChanged();
}

void KeyboardStyle::setEnterKeyUrl( const QUrl& enterKeyUrl )
{
    if ( _enterKeyUrl == enterKeyUrl )
        return;

    _enterKeyUrl = enterKeyUrl;
    emit enterKeyUrlChanged();
}

void KeyboardStyle::setBackspaceKeyUrl( const QUrl& backspaceKeyUrl )
{
    if ( _backspaceKeyUrl == backspaceKeyUrl )
        return;

    _backspaceKeyUrl = backspaceKeyUrl;
    emit backspaceKeyUrlChanged();
}

void KeyboardStyle::setShiftKeyUrl( const QUrl& shiftKeyUrl )
{
    if ( _shiftKeyUrl == shiftKeyUrl )
        return;

    _shiftKeyUrl = shiftKeyUrl;
    emit shiftKeyUrlChanged();
}

void KeyboardStyle::setSpaceKeyUrl( const QUrl& spaceKeyUrl )
{
    if ( _spaceKeyUrl == spaceKeyUrl )
        return;

    _spaceKeyUrl = spaceKeyUrl;
    emit spaceKeyUrlChanged();
}

void KeyboardStyle::setHideKeyUrl( const QUrl& hideKeyUrl )
{
    if ( _hideKeyUrl == hideKeyUrl )
        return;

    _hideKeyUrl = hideKeyUrl;
    emit hideKeyUrlChanged();
}

void KeyboardStyle::setSymbolKeyUrl( const QUrl& symbolKeyUrl )
{
    if ( _symbolKeyUrl == symbolKeyUrl )
        return;

    _symbolKeyUrl = symbolKeyUrl;
    emit symbolKeyUrlChanged();
}

void KeyboardStyle::setLanguageKeyUrl( const QUrl& languageKeyUrl )
{
    if ( _languageKeyUrl == languageKeyUrl )
        return;

    _languageKeyUrl = languageKeyUrl;
    emit languageKeyUrlChanged();
}

void KeyboardStyle::setNextPageKeyUrl( const QUrl& nextPageKeyUrl )
{
    if ( _nextPageKeyUrl == nextPageKeyUrl )
        return;

    _nextPageKeyUrl = nextPageKeyUrl;
    emit nextPageKeyUrlChanged();
}

void KeyboardStyle::setKeyPreviewUrl( const QUrl& keyPreview )
{
    if (_keyPreview == keyPreview)
        return;

    _keyPreview = keyPreview;
    emit keyPreviewUrlChanged();
}

void KeyboardStyle::setKeyAlternativesPreviewUrl( const QUrl& keyAlternativesPreview )
{
    if (_keyAlternativesPreview == keyAlternativesPreview)
        return;

    _keyAlternativesPreview = keyAlternativesPreview;
    emit keyAlternativesPreviewUrlChanged();
}

void KeyboardStyle::setLanguageMenuUrl( const QUrl& languageMenuUrl )
{
    if (_languageMenuUrl == languageMenuUrl)
        return;

    _languageMenuUrl = languageMenuUrl;
    emit languageMenuUrlChanged();
}

void KeyboardStyle::loadStyleUrls()
{
    const auto stylesPath = ovk::stylesAbsolutePath();
    if (stylesPath.isEmpty()) {
        qCDebug(logOvk) << "default keyboard styles will be used";
        return;
    }

    auto component = stylesPath + BACKGROUND_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'background' will be loaded from:" << component;
        setBackgroundUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + KEY_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'default key' will be loaded from:" << component;
        setKeyUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + ENTER_KEY_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'enter key' will be loaded from:" << component;
        setEnterKeyUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + BACKSPACE_KEY_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'backspace key' will be loaded from:" << component;
        setBackspaceKeyUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + SHIFT_KEY_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'shift key' will be loaded from:" << component;
        setShiftKeyUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + SPACE_KEY_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'space key' will be loaded from:" << component;
        setSpaceKeyUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + HIDE_KEY_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'hide key' will be loaded from:" << component;
        setHideKeyUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + SYMBOL_KEY_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'symbol key' will be loaded from:" << component;
        setSymbolKeyUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + LANGUAGE_KEY_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'language key' will be loaded from:" << component;
        setLanguageKeyUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + NEXT_KEY_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'next page key' will be loaded from:" << component;
        setNextPageKeyUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + KEY_PREVIEW_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'key preview' will be loaded from:" << component;
        setKeyPreviewUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + KEY_ALT_PREVIEW_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'key alternative preview' will be loaded from:" << component;
        setKeyAlternativesPreviewUrl( QUrl::fromLocalFile( component ));
    }

    component = stylesPath + LANGUAGE_MENU_COMPONENT_NAME;
    if (QFile::exists( component )) {
        qCDebug(logOvk) << "keyboard 'language menu' will be loaded from:" << component;
        setLanguageMenuUrl( QUrl::fromLocalFile( component ));
    }
}
