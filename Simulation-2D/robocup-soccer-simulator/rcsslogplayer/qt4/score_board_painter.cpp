// -*-c++-*-

/*!
  \file score_board_painter.cpp
  \brief score board painter class Source File.
*/

/*
 *Copyright:

 Copyright (C) The RoboCup Soccer Server Maintenance Group.
 Hidehisa Akiyama

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

#include <QtGui>

#include "score_board_painter.h"

#include "main_data.h"
#include "options.h"

#include <iostream>

/*-------------------------------------------------------------------*/
/*!

*/
ScoreBoardPainter::ScoreBoardPainter( const MainData & main_data )
    : M_main_data( main_data )
    , M_pen( QColor( 255, 255, 255 ), 0, Qt::SolidLine )
    , M_brush( QColor( 0, 0, 0 ), Qt::SolidPattern )
    , M_font( "6x13bold", 11, QFont::Bold )
    , M_mini_pen( QColor( 0, 0, 0 ), 0, Qt::SolidLine )
    , M_mini_brush( QColor( 255, 255, 255 ), Qt::SolidPattern )
    , M_mini_font( "6x13bold", 11, QFont::Bold )
{
    M_font.setPointSize( 11 );
    M_font.setBold( true );
    //M_font.setStyleHint( QFont::System, QFont::PreferBitmap );
    M_font.setBold( true );
    M_font.setFixedPitch( true );

    readSettings();
}

/*-------------------------------------------------------------------*/
/*!

*/
ScoreBoardPainter::~ScoreBoardPainter()
{
    writeSettings();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
ScoreBoardPainter::readSettings()
{
#ifndef Q_WS_WIN
    QSettings settings( QDir::homePath() + "/.rcsslogplayer",
                        QSettings::IniFormat );
#else
    QSettings settings( QDir::currentPath() + "/rcsslogplayer.ini",
                        QSettings::IniFormat );
#endif

    settings.beginGroup( "ScoreBoardPainter" );

    QVariant val;

    val = settings.value( "score_board_pen" );
    if ( val.isValid() ) M_pen.setColor( val.toString() );

    val = settings.value( "score_board_brush" );
    if ( val.isValid() ) M_brush.setColor( val.toString() );

    val = settings.value( "score_board_font" );
    if ( val.isValid() ) M_font.fromString( val.toString() );

    val = settings.value( "mini_score_board_pen" );
    if ( val.isValid() ) M_mini_pen.setColor( val.toString() );

    val = settings.value( "mini_score_board_brush" );
    if ( val.isValid() ) M_mini_brush.setColor( val.toString() );

    val = settings.value( "mini_score_board_font" );
    if ( val.isValid() ) M_mini_font.fromString( val.toString() );

    settings.endGroup();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
ScoreBoardPainter::writeSettings()
{
#ifndef Q_WS_WIN
    QSettings settings( QDir::homePath() + "/.rcsslogplayer",
                        QSettings::IniFormat );
#else
    QSettings settings( QDir::currentPath() + "/rcsslogplayer.ini",
                        QSettings::IniFormat );
#endif

    settings.beginGroup( "ScoreBoardPainter" );

    settings.setValue( "score_board_pen", M_pen.color().name() );
    settings.setValue( "score_board_brush", M_brush.color().name() );
    settings.setValue( "score_board_font", M_font.toString() );

    settings.setValue( "mini_score_board_pen", M_mini_pen.color().name() );
    settings.setValue( "mini_score_board_brush", M_mini_brush.color().name() );
    settings.setValue( "mini_score_board_font", M_mini_font.toString() );

    settings.endGroup();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ScoreBoardPainter::draw( QPainter & painter )
{
    static const std::string s_playmode_strings[] = PLAYMODE_STRINGS;

    const Options & opt = Options::instance();

    if ( ! opt.showScoreBoard()
         && ! opt.minimumMode() )
    {
        return;
    }

    DispConstPtr disp = M_main_data.getDispInfo( M_main_data.index() );

    if ( ! disp )
    {
        return;
    }

    const int current_time = disp->show_.time_;

    const rcss::rcg::TeamT & team_l = disp->team_[0];
    const rcss::rcg::TeamT & team_r = disp->team_[1];

    const rcss::rcg::PlayMode pmode = disp->pmode_;

    const std::vector< std::pair< int, rcss::rcg::PlayMode > > & pen_scores_l
        = M_main_data.dispHolder().penaltyScoresLeft();
    const std::vector< std::pair< int, rcss::rcg::PlayMode > > & pen_scores_r
        = M_main_data.dispHolder().penaltyScoresRight();

    bool show_pen_score = true;

    if ( pen_scores_l.empty()
         && pen_scores_r.empty() )
    {
        show_pen_score = false;
    }
    else if ( ( ! pen_scores_l.empty()
                && current_time < pen_scores_l.front().first )
              && ( ! pen_scores_r.empty()
                   && current_time < pen_scores_r.front().first )
              && pmode != rcss::rcg::PM_PenaltySetup_Left
              && pmode != rcss::rcg::PM_PenaltySetup_Right
              && pmode != rcss::rcg::PM_PenaltyReady_Left
              && pmode != rcss::rcg::PM_PenaltyReady_Right
              && pmode != rcss::rcg::PM_PenaltyTaken_Left
              && pmode != rcss::rcg::PM_PenaltyTaken_Right )
    {
        show_pen_score = false;
    }


    QString main_buf;

    if ( ! show_pen_score )
    {
        if ( opt.minimumMode() )
        {
            main_buf.sprintf( " %-15s %2d\n %-15s %2d\n %19s %6d    ",
                              ( team_l.name_.empty() || team_l.name_ == "null" )
                              ? ""
                              : team_l.name_.c_str(),
                              team_l.score_,
                              ( team_r.name_.empty() || team_r.name_ == "null" )
                              ? ""
                              : team_r.name_.c_str(),
                              team_r.score_,
                              s_playmode_strings[pmode].c_str(),
                              current_time );
        }
        else
        {
            main_buf.sprintf( " %10s %d:%d %-10s %19s %6d    ",
                              ( team_l.name_.empty() || team_l.name_ == "null" )
                              ? ""
                              : team_l.name_.c_str(),
                              team_l.score_,
                              team_r.score_,
                              ( team_r.name_.empty() || team_r.name_ == "null" )
                              ? ""
                              : team_r.name_.c_str(),
                              s_playmode_strings[pmode].c_str(),
                              current_time );
        }
    }
    else
    {
        std::string left_penalty; left_penalty.reserve( 10 );
        std::string right_penalty; right_penalty.reserve( 10 );

        for ( std::vector< std::pair< int, rcss::rcg::PlayMode > >::const_iterator it = pen_scores_l.begin();
              it != pen_scores_l.end();
              ++it )
        {
            if ( it->first > current_time ) break;

            if ( it->second == rcss::rcg::PM_PenaltyScore_Left
                 || it->second == rcss::rcg::PM_PenaltyScore_Right )
            {
                left_penalty += 'o';
            }
            else if ( it->second == rcss::rcg::PM_PenaltyMiss_Left
                      || it->second == rcss::rcg::PM_PenaltyMiss_Right )
            {
                left_penalty += 'x';
            }
        }

        for ( std::vector< std::pair< int, rcss::rcg::PlayMode > >::const_iterator it = pen_scores_r.begin();
              it != pen_scores_r.end();
              ++it )
        {
            if ( it->first > current_time ) break;

            if ( it->second == rcss::rcg::PM_PenaltyScore_Left
                 || it->second == rcss::rcg::PM_PenaltyScore_Right )
            {
                right_penalty += 'o';
            }
            else if ( it->second == rcss::rcg::PM_PenaltyMiss_Left
                      || it->second == rcss::rcg::PM_PenaltyMiss_Right )
            {
                right_penalty += 'x';
            }
        }

        if ( opt.minimumMode() )
        {
            main_buf.sprintf( " %-15s %2d |%-5s|\n %-15s %2d |%-5s|\n %19s %6d",
                              ( team_l.name_.empty() || team_l.name_ == "null" )
                              ? ""
                              : team_l.name_.c_str(),
                              team_l.score_,
                              left_penalty.c_str(),
                              ( team_r.name_.empty() || team_r.name_ == "null" )
                              ? ""
                              : team_r.name_.c_str(),
                              team_r.score_,
                              right_penalty.c_str(),
                              s_playmode_strings[pmode].c_str(),
                              current_time );
        }
        else
        {
            main_buf.sprintf( " %10s %d:%d |%-5s:%-5s| %-10s %19s %6d",
                              ( team_l.name_.empty() || team_l.name_ == "null" )
                              ? ""
                              : team_l.name_.c_str(),
                              team_l.score_, team_r.score_,
                              left_penalty.c_str(),
                              right_penalty.c_str(),
                              ( team_r.name_.empty() || team_r.name_ == "null" )
                              ? ""
                              : team_r.name_.c_str(),
                              s_playmode_strings[pmode].c_str(),
                              current_time );
        }
    }

    QRect rect;
    if ( opt.minimumMode() )
    {
        painter.setFont( M_mini_font );

        rect = painter.window();

        painter.fillRect( rect, M_mini_brush );
        painter.setPen( M_mini_pen );
        painter.setBrush( Qt::NoBrush );
    }
    else
    {
        painter.setFont( M_font );

        QRect bounding_rect = painter.fontMetrics().boundingRect( main_buf );
        rect.setLeft( 0 );
        rect.setTop( painter.window().bottom() - bounding_rect.height() + 1 );
        rect.setWidth( bounding_rect.width() );
        rect.setHeight( bounding_rect.height() );

        painter.fillRect( rect, M_brush );
        painter.setPen( M_pen );
        painter.setBrush( Qt::NoBrush );
    }

    painter.drawText( rect,
                      Qt::AlignVCenter,
                      main_buf );
}
