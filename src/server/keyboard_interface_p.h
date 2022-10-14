// Copyright 2016  Martin Gräßlin <mgraesslin@kde.org>
// SPDX-FileCopyrightText: 2022 Martin Gräßlin <mgraesslin@kde.org>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef WAYLAND_SERVER_KEYBOARD_INTERFACE_P_H
#define WAYLAND_SERVER_KEYBOARD_INTERFACE_P_H
#include "keyboard_interface.h"
#include "resource_p.h"

#include <QPointer>

namespace KWayland
{
namespace Server
{

class KeyboardInterface::Private : public Resource::Private
{
public:
    Private(SeatInterface *s, wl_resource *parentResource, KeyboardInterface *q);
    void sendKeymap(int fd, quint32 size);
    void sendModifiers();
    void sendModifiers(quint32 depressed, quint32 latched, quint32 locked, quint32 group, quint32 serial);

    void focusChildSurface(const QPointer<SurfaceInterface> &childSurface, quint32 serial);
    void sendLeave(SurfaceInterface *surface, quint32 serial);
    void sendEnter(SurfaceInterface *surface, quint32 serial);

    SeatInterface *seat;
    SurfaceInterface *focusedSurface = nullptr;
    QPointer<SurfaceInterface> focusedChildSurface;
    QMetaObject::Connection destroyConnection;

private:
    static const struct wl_keyboard_interface s_interface;
};

}
}

#endif
