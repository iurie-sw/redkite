/**
 * File name: RkTimer.h
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

#include "RkTimer.h"
#include "RkEventQueue.h"
#include "RkLog.h"

#include <chrono>

RkTimer::RkTimer(int interval, RkEventQueue* queue)
        : timerInterval{interval}
        , timerStarted{false}
        , lastTime{-1}
        , eventQueue{queue}
{
        if (!eventQueue)
                RK_LOG_INFO("null");
        if (eventQueue)
                eventQueue->subscribeTimer(this);
}

RkTimer::~RkTimer()
{
        if (eventQueue)
                eventQueue->unsubscribeTimer(this);
}

void RkTimer::start()
{
        RK_LOG_INFO("called");
        timerStarted = true;
        lastTime = getCurrentTime();
}

bool RkTimer::started() const
{
        return timerStarted;
}

void RkTimer::stop()
{
        RK_LOG_INFO("called");
        timerStarted = false;
}

int RkTimer::interval() const
{
        return timerInterval;
}

void RkTimer::setInterval(int val)
{
        timerInterval = val;
}

bool RkTimer::isTimeout() const
{
        if (lastTime < 0 || timerInterval < 0)
                return false;

        if (getCurrentTime() - lastTime > timerInterval)
                return true;
        return false;
}

int RkTimer::getCurrentTime() const
{
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void RkTimer::callTimeout()
{
        timeout();
        lastTime = getCurrentTime();
}