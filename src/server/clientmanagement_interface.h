/********************************************************************
Copyright 2020  wugang <wugang@uniontech.com>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) version 3, or any
later version accepted by the membership of KDE e.V. (or its
successor approved by the membership of KDE e.V.), which shall
act as a proxy defined in Section 6 of version 3 of the license.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/
#ifndef WAYLAND_SERVER_CLIENT_MANAGEMENT_INTERFACE_H
#define WAYLAND_SERVER_CLIENT_MANAGEMENT_INTERFACE_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QVector>
#include <QImage>

#include <KWayland/Server/kwaylandserver_export.h>
#include "global.h"
#include "surface_interface.h"

struct wl_resource;

namespace KWayland
{
namespace Server
{

class Display;

/** @class ClientManagementInterface
 *
 *
 * @see ClientManagementInterface
 * @since 5.5
 */
class KWAYLANDSERVER_EXPORT ClientManagementInterface : public Global
{
    Q_OBJECT
public:
    virtual ~ClientManagementInterface();

    struct WindowState {
        int32_t pid;
        int32_t windowId;
        char resourceName[256];
        struct Geometry {
            int32_t x;
            int32_t y;
            int32_t width;
            int32_t height;
        } geometry;
        bool isMinimized;
        bool isFullScreen;
        bool isActive;
    };

    static ClientManagementInterface *get(wl_resource *native);
    void setWindowStates(QList<WindowState*> &windowStates);

    void sendWindowCaptionImage(int windowId, wl_resource *buffer, QImage image);
    void sendWindowCaption(int windowId, wl_resource *buffer, SurfaceInterface* surface);

Q_SIGNALS:
    void windowStatesRequest();
    void windowStatesChanged();

    void captureWindowImageRequest(int windowId, wl_resource *buffer);

private:
    friend class Display;
    explicit ClientManagementInterface(Display *display, QObject *parent = nullptr);
    class Private;
    Private *d_func() const;
};

}
}

#endif
