/**
 * File name: RkWidgetImpl.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor (http://quamplex.com/redkite)
 *
 * This file is part of Redkite.
 *
 * Redkite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "RkWidgetImpl.h"
#include "RkEvent.h"
#include "RkPlatform.h"

#ifdef RK_WIN_OS
#elif RK_MAC_OS
#else
#include <RkWindowX.h>
#undef KeyPress
#undef KeyRelease
#undef Paint
#endif // RK_WIN_OS

RkWidget::RkWidgetImpl::RkWidgetImpl(RkWidget* interface, RkWidget* parent)
        : inf_ptr{interface}
        , parentWidget{parent}
        , platformWindow{!parent ? std::make_unique<RkWindowX>() : std::make_unique<RkWindowX>(parent->nativeWindowInfo())}
        , widgetClosed{false}
{
}

RkWidget::RkWidgetImpl::RkWidgetImpl(RkWidget* interface, const RkNativeWindowInfo &parent)
        : inf_ptr{interface}
        , parentWidget{nullptr}
        , platformWindow{std::make_unique<RkWindowX>(parent)}
        , widgetClosed{false}
{
}

void RkWidget::RkWidgetImpl::show()
{
        platformWindow->show();
}

void RkWidget::RkWidgetImpl::setTitle(const std::string &title)
{
        widgetTitle = title;
        platformWindow->setTitle(widgetTitle);
}

const std::string& RkWidget::RkWidgetImpl::title() const
{
        return widgetTitle;
}

std::shared_ptr<RkNativeWindowInfo> RkWidget::RkWidgetImpl::nativeWindowInfo() const
{
        return platformWindow->nativeWindowInfo();
}

bool RkWidget::RkWidgetImpl::isClose() const
{
        return widgetClosed;
}

RkWindowId RkWidget::RkWidgetImpl::id() const
{
        return platformWindow->id();
}

void RkWidget::RkWidgetImpl::processEvent(const std::shared_ptr<RkEvent> &event)
{
        switch (event->type())
        {
        case RkEvent::Type::Paint:
                inf_ptr->paintEvent(std::dynamic_pointer_cast<RkPaintEvent>(event));
                break;
        case RkEvent::Type::KeyPress:
                inf_ptr->keyPressEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                break;
        case RkEvent::Type::KeyRelease:
                inf_ptr->keyReleaseEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                break;
        case RkEvent::Type::MouseButtonPress:
                inf_ptr->mouseButtonPressEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                break;
        case RkEvent::Type::MouseButtonRelease:
                inf_ptr->mouseButtonReleaseEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                break;
        case RkEvent::Type::Resize:
                inf_ptr->resizeEvent(std::dynamic_pointer_cast<RkResizeEvent>(event));
                break;
        case RkEvent::Type::Close:
                widgetClosed = true;
                inf_ptr->closeEvent(std::dynamic_pointer_cast<RkCloseEvent>(event));
                break;
        default:
                break;
        }
}

RkWidget* RkWidget::RkWidgetImpl::parent() const
{
        return parentWidget;
}

RkWidget* RkWidget::RkWidgetImpl::child(const RkWindowId &id) const
{
}

void RkWidget::RkWidgetImpl::addChild(const RkWidget* child)
{
        if (child)
                widgetChildren->push_back(child);
}

void RkWidget::RkWidgetImpl::setSize(const std::pair<int, int> &size)
{
        if (size.first > 1 && size.second > 1)
                platformWIndow->setSize(widgetSize);
}

std::pair<int, int> RkWidget::RkWidgetImpl::size() const
{
        return  platformWIndow->size();
}

void RkWidget::RkWidgetImpl::setPosition(const std::pair<int, int> &position)
{
        platformWindow->setPosition(position);
}

std::pair<int, int> RkWidget::RkWidgetImpl::position() const
{
        return platformWindow->position();
}

void RkWidget::RkWidgetImpl::setBackgroundColor(int r, int g, int b)
{
}
//void setBackgroundColor(std::tuple<int, int, int, int> &color);
//RkColor backgroundColor() const;
//d::tuple<int, int, int, int> backgroundColor() const;