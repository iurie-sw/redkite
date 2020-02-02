/**
 * File name: Button.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2020 Iurie Nistor <http://geontime.com>
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

#include "RkMain.h"
#include "RkWidget.h"
#include "RkPainter.h"
#include "RkEvent.h"

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    auto widget = new PainterExample(&app);
    widget->setTitle("Button Example");
    widget->setSize(350, 350);
    widget->show();

    auto button = new RkButton(widget);
    button->setPosition(10, 10);
    button->setPressedImage(RkImage(48, 48, pressed_button));
    button->unpressedImage(RkImage(48, 48, unpressed_button));
    button->show();

    return app.exec();
}