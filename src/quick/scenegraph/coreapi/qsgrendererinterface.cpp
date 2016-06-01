/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQuick module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qsgrendererinterface.h"

QT_BEGIN_NAMESPACE

/*!
    \class QSGRendererInterface
    \brief An interface providing access to some of the graphics API specific internals
    of the scenegraph.
    \inmodule QtQuick
    \since 5.8

    Renderer interfaces allow accessing graphics API specific functionality in
    the scenegraph. Such internals are not typically exposed. However, when
    integrating custom rendering via QSGRenderNode for example, it may become
    necessary to query certain values, for instance the graphics device (e.g.
    the Direct3D or Vulkan device) that is used by the scenegraph.

    \note QSGRendererInterface is only available after the scenegraph is
    initialized. Additionally, there may be backend-specific limitations on
    when the functions can be called. The only way that is guaranteed to
    succeed is calling them when the rendering of a node (i.e. the preparation
    of the command list for the next frame) is active. In practice this
    typically means QSGRenderNode::render().
 */

/*!
    \enum QSGRenderNode::GraphicsApi
    \value Unknown An unknown graphics API is in use
    \value Software The Qt Quick 2D Renderer is in use
    \value OpenGL OpenGL ES 2.0 or higher
    \value Direct3D12 Direct3D 12
    \value Vulkan Vulkan
    \value Metal Metal
  */

/*!
    \enum QSGRenderNode::Resource
    \value Device The graphics device
    \value CommandQueue The graphics command queue used by the scenergaph
    \value CommandList The command list or buffer used by the scenegraph
 */

QSGRendererInterface::~QSGRendererInterface()
{
}

/*!
    \fn QSGRenderNode::GraphicsApi QSGRenderNode::graphicsApi() const

    Returns the graphics API that is in use by the Qt Quick scenegraph.

    \note This function can be called on any thread. However, the renderer
    interface's lifetime may be tied to the render thread and therefore calling
    this function from other threads during the process of application shutdown
    or QQuickWindow closing is likely to become invalid.
 */

/*!
    Queries a graphics \a resource. Returns null when the resource in question is
    not supported or not available.

    When successful, the returned pointer is either a direct pointer to an
    interface (and can be cast, for example, to \c{ID3D12Device *}) or a
    pointer to an opaque handle that needs to be dereferenced first (for
    example, \c{VkDevice dev = *static_cast<VkDevice *>(result)}). The latter
    is necessary since such handles may have sizes different from a pointer.

    \note This function must only be called on the render thread.
 */
void *QSGRendererInterface::getResource(Resource resource) const
{
    Q_UNUSED(resource);
    return nullptr;
}

/*!
    Queries a graphics resource. \a resource is a backend-specific key. This
    allows supporting any future resources that are not listed in the
    Resource enum.

    \note This function must only be called on the render thread.
 */
void *QSGRendererInterface::getResource(const char *resource) const
{
    Q_UNUSED(resource);
    return nullptr;
}

QT_END_NAMESPACE