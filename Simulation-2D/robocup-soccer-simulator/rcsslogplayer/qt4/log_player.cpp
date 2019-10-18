// -*-c++-*-

/*!
  \file log_player.cpp
  \brief log player class Header File.
*/

/*
 *Copyright:

 Copyright (C) The RoboCup Soccer Server Maintenance Group.
 Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2, or (at your option)
 any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this code; see the file COPYING.  If not, write to
 the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <QApplication>
#include <QTimer>

#include "main_data.h"
#include "log_player.h"
#include "options.h"

#include <iostream>

/*-------------------------------------------------------------------*/
/*!

*/
LogPlayer::LogPlayer( MainData & main_data,
                      QObject * parent )
    : QObject( parent )
    , M_main_data( main_data )
    , M_timer( new QTimer( this ) )
    , M_forward( true )
    , M_live_mode( false )
{
    connect( M_timer, SIGNAL( timeout() ),
             this, SLOT( handleTimer() ) );
}

/*-------------------------------------------------------------------*/
/*!

*/
LogPlayer::~LogPlayer()
{

}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::handleTimer()
{
    if ( M_forward )
    {
        stepForwardImpl();
    }
    else
    {
        stepBackImpl();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
LogPlayer::isLiveMode() const
{
    return M_live_mode;
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::stepBackImpl()
{
    if ( M_main_data.setIndexStepBack() )
    {
        emit updated();
    }
    else
    {
        M_timer->stop();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::stepForwardImpl()
{
    if ( M_main_data.setIndexStepForward() )
    {
        emit updated();
    }
    else
    {
        M_timer->stop();

        if ( Options::instance().autoQuitMode() )
        {
            int wait_msec = ( Options::instance().autoQuitWait() > 0
                              ? Options::instance().autoQuitWait() * 1000
                              : 100 );
            QTimer::singleShot( wait_msec,
                                qApp, SLOT( quit() ) );
        }
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::stepBack()
{
    M_live_mode = false;
    M_forward = false;
    M_timer->stop();

    stepBackImpl();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::stepForward()
{
    M_live_mode = false;
    M_forward = true;
    M_timer->stop();

    stepForwardImpl();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::playOrStop()
{
    M_live_mode = false;

    if ( M_timer->isActive() )
    {
        M_timer->stop();
    }
    else if ( M_forward )
    {
        playForward();
    }
    else
    {
        playBack();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::stop()
{
    M_live_mode = false;
    M_timer->stop();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::playBack()
{
    M_live_mode = false;
    M_forward = false;

    if ( ! M_timer->isActive()
         || M_timer->interval() != Options::instance().timerInterval() )
    {
        M_timer->start( Options::instance().timerInterval() );
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::playForward()
{
    M_live_mode = false;
    M_forward = true;

    if ( ! M_timer->isActive()
         || M_timer->interval() != Options::instance().timerInterval() )
    {
        M_timer->start( Options::instance().timerInterval() );
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::accelerateBack()
{
    int interval = 0;
    if ( M_forward
         || ! M_timer->isActive() )
    {
        interval = Options::instance().timerInterval() / 2;
    }
    else
    {
        interval = M_timer->interval() / 2;
        if ( interval < 10 ) interval = 10;
    }

    M_live_mode = false;
    M_forward = false;
    M_timer->start( interval );
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::accelerateForward()
{
    int interval = 0;
    if ( ! M_forward
        || ! M_timer->isActive() )
    {
        interval = Options::instance().timerInterval() / 2;
    }
    else
    {
        interval = M_timer->interval() / 2;
        if ( interval < 10 ) interval = 10;
    }

    M_live_mode = false;
    M_forward = true;
    M_timer->start( interval );
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::goToPrevScore()
{
    M_live_mode = false;

    const DispHolder & holder = M_main_data.dispHolder();

    const std::size_t cur_idx = M_main_data.index();
    std::vector< std::size_t >::const_reverse_iterator rend = holder.scoreChangedIndex().rend();
    for ( std::vector< std::size_t >::const_reverse_iterator it = holder.scoreChangedIndex().rbegin();
          it != rend;
          ++it )
    {
        if ( *it < cur_idx )
        {
            std::size_t new_idx = *it;
            new_idx -= ( new_idx < 50 ? new_idx : 50 );
            goToIndex( new_idx );
            return;
        }
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::goToNextScore()
{
    M_live_mode = false;

    const DispHolder & holder = M_main_data.dispHolder();

    const std::size_t cur_idx = M_main_data.index();
    std::vector< std::size_t >::const_iterator end = holder.scoreChangedIndex().end();
    for ( std::vector< std::size_t >::const_iterator it = holder.scoreChangedIndex().begin();
          it != end;
          ++it )
    {
        if ( 50 < *it && cur_idx < *it - 50 )
        {
            std::size_t new_idx = *it;
            new_idx -= ( new_idx < 50 ? 0 : 50 );
            goToIndex( new_idx );
            return;
        }
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::goToFirst()
{
    if ( M_main_data.setIndexFirst() )
    {
        M_live_mode = false;
        M_timer->stop();

        emit updated();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::goToLast()
{
    if ( M_main_data.setIndexLast() )
    {
        M_live_mode = false;
        M_timer->stop();

        emit updated();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::decelerate()
{
    if ( M_timer->isActive() )
    {
        int interval = M_timer->interval() * 2;
        if ( 5000 < interval ) interval = 5000;
        M_timer->start( interval );
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::accelerate()
{
    if ( M_timer->isActive() )
    {
        int interval = M_timer->interval() / 2;
        if ( interval < 5 ) interval = 5;
        M_timer->start( interval );
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::goToIndex( int index )
{
    if ( M_main_data.setIndex( index ) )
    {
        M_live_mode = false;
        //M_timer->stop();

        emit updated();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::goToCycle( int cycle )
{
    if ( M_main_data.setCycle( cycle ) )
    {
        M_live_mode = false;
        //M_timer->stop();

        emit updated();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::showLive()
{
    if ( M_main_data.setIndexLast() )
    {
        M_timer->stop();

        emit updated();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
LogPlayer::setLiveMode()
{
    M_main_data.setIndexLast();
    M_live_mode = true;
    M_timer->stop();

    //emit updated();
}
