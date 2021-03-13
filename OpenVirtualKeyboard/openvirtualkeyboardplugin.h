#ifndef OPENVIRTUALKEYBOARDTPLUGIN_H
#define OPENVIRTUALKEYBOARDTPLUGIN_H

#include <qpa/qplatforminputcontextplugin_p.h>

class OpenVirtualKeyboardPlugin : public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "OpenVirtualKeyboard.json")

private:
    QPlatformInputContext* create( const QString& key, const QStringList& paramList ) override;
};

#endif // OPENVIRTUALKEYBOARDTPLUGIN_H
