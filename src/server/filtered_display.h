// Copyright 2017  David Edmundson <davidedmundson@kde.org>
// SPDX-FileCopyrightText: 2022 Martin Gräßlin <mgraesslin@kde.org>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef KWAYLAND_SERVER_FILTERED_DISPLAY_H
#define KWAYLAND_SERVER_FILTERED_DISPLAY_H

#include "global.h"
#include "display.h"

#include <KWayland/Server/kwaylandserver_export.h>

namespace KWayland
{
namespace Server
{

/**
* Server Implementation that allows one to restrict which globals are available to which clients
*
* Users of this class must implement the virtual @method allowInterface method.
*
* @since 5.FIXME
*/
class KWAYLANDSERVER_EXPORT FilteredDisplay : public Display
{
    Q_OBJECT
public:
    FilteredDisplay(QObject *parent);
    ~FilteredDisplay();

/**
* Return whether the @arg client can see the interface with the given @arg interfaceName
*
* When false will not see these globals for a given interface in the registry,
* and any manual attempts to bind will fail
*
* @return true if the client should be able to access the global with the following interfaceName
*/
    virtual bool allowInterface(ClientConnection *client, const QByteArray &interfaceName) = 0;
private:
    class Private;
    QScopedPointer<Private> d;
};

}
}

#endif
