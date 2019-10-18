// -*-c++-*-

/*!
  \file options.cpp
  \brief application configuration class Source File.
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

#include <QSettings>
#include <QDir>

#include "options.h"

#ifdef HAVE_BOOST_PROGRAM_OPTIONS
#include <boost/program_options.hpp>
#endif

#include <iostream>
#include <cmath>
#include <cstdio>

#ifndef PACKAGE_NAME
#define PACKAGE_NAME "rcsslogplayer"
#endif
#ifndef VERSION
#define VERSION "unknown-version"
#endif

#define USE_MONITOR_CLIENT

const double Options::PITCH_LENGTH = 105.0;
const double Options::PITCH_WIDTH = 68.0;
const double Options::PITCH_HALF_LENGTH = Options::PITCH_LENGTH * 0.5;
const double Options::PITCH_HALF_WIDTH = Options::PITCH_WIDTH * 0.5;
const double Options::PITCH_MARGIN = 5.0;
const double Options::CENTER_CIRCLE_R = 9.15;
const double Options::PENALTY_AREA_LENGTH = 16.5;
const double Options::PENALTY_AREA_WIDTH = 40.32;
const double Options::PENALTY_CIRCLE_R = 9.15;
const double Options::PENALTY_SPOT_DIST = 11.0;
const double Options::GOAL_WIDTH = 14.02;
const double Options::GOAL_HALF_WIDTH = Options::GOAL_WIDTH * 0.5;
const double Options::GOAL_AREA_LENGTH = 5.5;
const double Options::GOAL_AREA_WIDTH = 18.32;
const double Options::GOAL_DEPTH = 2.44;
const double Options::CORNER_ARC_R = 1.0;
const double Options::GOAL_POST_RADIUS = 0.06;

const double Options::MIN_FIELD_SCALE = 1.0;
const double Options::MAX_FIELD_SCALE = 400.0;
const double Options::ZOOM_RATIO = 1.5;
const int Options::DEFAULT_TIMER_INTERVAL = 100;

/*-------------------------------------------------------------------*/
/*!
  singleton interface
*/
Options &
Options::instance()
{
    static Options s_instance;
    return s_instance;
}

/*-------------------------------------------------------------------*/
/*!

 */
Options::Options()
    : M_monitor_client_mode( false )
    , M_connect( false )
    , M_server_host( "127.0.0.1" )
    , M_server_port( 6000 )
    , M_client_version( 4 )
    , M_time_shift_replay( true )
    , M_minimum_mode( false )
    , M_monitor_path( "self" )
    , M_monitor_port( 6000 )
    , M_game_log_file( "" )
    , M_output_file( "" )
    , M_auto_quit_mode( false )
    , M_auto_quit_wait( 5 )
    , M_auto_loop_mode( false )
    , M_timer_interval( Options::DEFAULT_TIMER_INTERVAL )
      // window options
    , M_window_x( -1 )
    , M_window_y( -1 )
    , M_window_width( -1 )
    , M_window_height( -1 )
    , M_maximize( false )
    , M_full_screen( false )
    , M_canvas_width( -1 )
    , M_canvas_height( -1 )
    , M_hide_menu_bar( false )
    , M_hide_tool_bar( false )
    , M_hide_status_bar( false )
      // view options
    , M_anti_aliasing( true )
    , M_show_score_board( true )
    , M_show_keepaway_area( false )
    , M_show_team_graphic( true )
    , M_show_flag( false )
    , M_show_ball( true )
    , M_show_player( true )
    , M_show_player_number( true )
    , M_show_player_type( false )
    , M_show_view_area( false )
    , M_show_tackle_area( false )
    , M_show_stamina( false )
    , M_show_pointto( true )
    , M_show_card( true )
    , M_show_offside_line( false )
    , M_show_draw_info( true )
    , M_ball_size( 0.35 )
    , M_player_size( 0.0 )
    , M_grid_step( 0.0 )
    , M_show_grid_coord( false )
    , M_field_scale( 1.0 )
    , M_zoomed( false )
    , M_field_center( 0, 0 )
    , M_focus_type( FOCUS_POINT )
    , M_focus_point( 0.0, 0.0 )
    , M_selected_number( 0 )
    , M_player_select_type( SELECT_UNSELECT )
    , M_ball_trace_start( 0 )
    , M_ball_trace_end( 0 )
    , M_player_trace_start( 0 )
    , M_player_trace_end( 0 )
    , M_line_trace( true )
    , M_ball_vel_cycle( 0 )
{
    readSettings();
}

/*-------------------------------------------------------------------*/
/*!

 */
Options::~Options()
{
    writeSettings();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::readSettings()
{
#ifndef Q_WS_WIN
    QSettings settings( QDir::homePath() + "/.rcsslogplayer",
                        QSettings::IniFormat );
#else
    QSettings settings( QDir::currentPath() + "/rcsslogplayer.ini",
                        QSettings::IniFormat );
#endif

    settings.beginGroup( "Global" );

    QVariant val;

//     val = settings.value( "game_log_file" );
//     if ( val.isValid() ) M_game_log_file = val.toString().toStdString();

//     val = settings.value( "connect" );
//     if ( val.isValid() ) M_connect  = val.toBool();

//     val = settings.value( "server-host" );
//     if ( val.isValid() ) M_server_host = val.toString().toStdString();

//     val = settings.value( "server-port" );
//     if ( val.isValid() ) M_server_port = val.toInt();

//     val = settings.value( "client-version" );
//     if ( val.isValid() ) M_client_version = val.toInt();

    val = settings.value( "monitor_port" );
    if ( val.isValid() ) M_monitor_port = val.toInt();

    val = settings.value( "auto_quit_mode" );
    if ( val.isValid() ) M_auto_quit_mode = val.toBool();

    val = settings.value( "auto_quit_wait" );
    if ( val.isValid() ) M_auto_quit_wait = val.toInt();

    val = settings.value( "auto_loop_mode" );
    if ( val.isValid() ) M_auto_loop_mode = val.toBool();

    val = settings.value( "timer_interval" );
    if ( val.isValid() ) M_timer_interval = val.toInt();

    val = settings.value( "window_width" );
    if ( val.isValid() ) M_window_width = val.toInt();

    val = settings.value( "window_height" );
    if ( val.isValid() ) M_window_height = val.toInt();

    val = settings.value( "window_x" );
    if ( val.isValid() ) M_window_x = val.toInt();

    val = settings.value( "window_y" );
    if ( val.isValid() ) M_window_y = val.toInt();

//     val = settings.value( "canvas_width" );
//     if ( val.isValid() ) M_canvas_width = val.toInt();

//     val = settings.value( "canvas_height" );
//     if ( val.isValid() ) M_canvas_height = val.toInt();

    val = settings.value( "maximize" );
    if ( val.isValid() ) M_maximize = val.toBool();

    val = settings.value( "full_screen" );
    if ( val.isValid() ) M_full_screen = val.toBool();

    val = settings.value( "hide_menu_bar" );
    if ( val.isValid() ) M_hide_menu_bar = val.toBool();

    val = settings.value( "hide_tool_bar" );
    if ( val.isValid() ) M_hide_tool_bar = val.toBool();

    val = settings.value( "hide_status_bar" );
    if ( val.isValid() ) M_hide_status_bar = val.toBool();

    val = settings.value( "anti_aliasing" );
    if ( val.isValid() ) M_anti_aliasing = val.toBool();

    val = settings.value( "show_score_board" );
    if ( val.isValid() ) M_show_score_board = val.toBool();

    val = settings.value( "show_keepaway_area" );
    if ( val.isValid() ) M_show_keepaway_area = val.toBool();

    val = settings.value( "show_team_graphic" );
    if ( val.isValid() ) M_show_team_graphic = val.toBool();

    val = settings.value( "show_draw_info" );
    if ( val.isValid() ) M_show_draw_info = val.toBool();

    val = settings.value( "show_ball" );
    if ( val.isValid() ) M_show_ball = val.toBool();

    val = settings.value( "show_player" );
    if ( val.isValid() ) M_show_player = val.toBool();

    val = settings.value( "show_player_number" );
    if ( val.isValid() ) M_show_player_number = val.toBool();

    val = settings.value( "show_player_type" );
    if ( val.isValid() ) M_show_player_type = val.toBool();

    val = settings.value( "show_view_area" );
    if ( val.isValid() ) M_show_view_area = val.toBool();

    val = settings.value( "show_catch_area" );
    if ( val.isValid() ) M_show_catch_area = val.toBool();

    val = settings.value( "show_tackle_area" );
    if ( val.isValid() ) M_show_tackle_area = val.toBool();

    val = settings.value( "show_kick_accel_area" );
    if ( val.isValid() ) M_show_kick_accel_area = val.toBool();

    val = settings.value( "show_stamina" );
    if ( val.isValid() ) M_show_stamina = val.toBool();

    val = settings.value( "show_pointto" );
    if ( val.isValid() ) M_show_pointto = val.toBool();

    val = settings.value( "show_card" );
    if ( val.isValid() ) M_show_card = val.toBool();

    val = settings.value( "ball_size", M_ball_size );
    if ( val.isValid() ) M_ball_size = val.toDouble();

    val = settings.value( "player_size", M_player_size );
    if ( val.isValid() ) M_player_size = val.toDouble();

    val = settings.value( "show_grid_coord", M_show_grid_coord );
    if ( val.isValid() ) M_show_grid_coord = val.toBool();

    val = settings.value( "grid_step", M_grid_step );
    if ( val.isValid() ) M_grid_step = val.toDouble();

    val = settings.value( "show_flag", M_show_flag );
    if ( val.isValid() ) M_show_flag = val.toBool();

    val = settings.value( "show_offside_line", M_show_offside_line );
    if ( val.isValid() ) M_show_offside_line = val.toBool();

    settings.endGroup();
}

/*-----------------------------------------------------------------*/
/*!

 */
void
Options::writeSettings()
{
#ifndef Q_WS_WIN
    QSettings settings( QDir::homePath() + "/.rcsslogplayer",
                        QSettings::IniFormat );
#else
    QSettings settings( QDir::currentPath() + "/rcsslogplayer.ini",
                        QSettings::IniFormat );
#endif

    settings.beginGroup( "Global" );

//     settings.setValue( "game_log_file", QString::fromStdString( M_game_log_file ) );

//     settings.setValue( "connect", M_connect );
//     settings.setValue( "server-host", QString::fromStdString( M_server_host ) );
//     settings.setValue( "server-port", M_server_port );
//     settings.setValue( "client-version", M_client_version );

//     settings.setValue( "minimum_mode", M_minimum_mode );
    settings.setValue( "monitor_port", M_monitor_port );
    settings.setValue( "auto_quit_mode", M_auto_quit_mode );
    settings.setValue( "auto_quit_wait", M_auto_quit_wait );
    settings.setValue( "auto_loop_mode", M_auto_loop_mode );
    settings.setValue( "timer_interval", M_timer_interval );
//     settings.setValue( "window_width", M_window_width );
//     settings.setValue( "window_height", M_window_height );
//     settings.setValue( "window_x", M_window_x );
//     settings.setValue( "window_y", M_window_y );
//     settings.setValue( "canvas_width", M_canvas_width );
//     settings.setValue( "canvas_height", M_canvas_height );
//     settings.setValue( "maximize", M_maximize );
//     settings.setValue( "full_screen", M_full_screen );
//     settings.setValue( "hide_menu_bar", M_hide_menu_bar );
//     settings.setValue( "hide_tool_bar", M_hide_tool_bar );
//     settings.setValue( "hide_status_bar", M_hide_status_bar );
    settings.setValue( "anti_aliasing", M_anti_aliasing );
    settings.setValue( "show_score_board", M_show_score_board );
    settings.setValue( "show_keepaway_area", M_show_keepaway_area );
    settings.setValue( "show_team_graphic", M_show_team_graphic );
    settings.setValue( "show_draw_info", M_show_draw_info );
    settings.setValue( "show_ball", M_show_ball );
    settings.setValue( "show_player", M_show_player );
    settings.setValue( "show_player_number", M_show_player_number );
    settings.setValue( "show_player_type", M_show_player_type );
    settings.setValue( "show_view_area", M_show_view_area );
    settings.setValue( "show_catch_area", M_show_catch_area );
    settings.setValue( "show_tackle_area", M_show_tackle_area );
    settings.setValue( "show_kick_accel_area", M_show_kick_accel_area );
    settings.setValue( "show_stamina", M_show_stamina );
    settings.setValue( "show_pointto", M_show_pointto );
    settings.setValue( "show_card", M_show_card );
    settings.setValue( "ball_size", M_ball_size );
    settings.setValue( "player_size", M_player_size );
    settings.setValue( "show_grid_coord", M_show_grid_coord );
    settings.setValue( "grid_step", M_grid_step );
    settings.setValue( "show_flag", M_show_flag );
    settings.setValue( "show_offside_line", M_show_offside_line );

    settings.endGroup();
}

/*-------------------------------------------------------------------*/
/*!

 */
bool
Options::parseCmdLine( int argc,
                       char ** argv )
{
#ifdef HAVE_BOOST_PROGRAM_OPTIONS
    namespace po = boost::program_options;

    std::string geometry;
//     std::string canvas_size;

    po::options_description visibles( "Allowed options:" );

    visibles.add_options()
        ( "help,h",
          "print this message." )
        ( "version,v",
          "print version information." )
        // monitor options
#ifdef USE_MONITOR_CLIENT
        ( "connect,c",
          po::bool_switch( &M_connect ),
          "start as a soccer monitor." )
        ( "server-host",
          po::value< std::string >( &M_server_host )->default_value( "127.0.0.1", "127.0.0.1" ),
          "set host name to connect to rcssserver." )
        ( "server-port",
          po::value< int >( &M_server_port )->default_value( 6000, "6000" ),
          "set port number to connect as the monitor client." )
        ( "client-version",
          po::value< int >( &M_client_version )->default_value( 4, "4" ),
          "set a monitor client protocol version." )
//         ( "time-shift-replay",
//           po::value< bool >( &M_time_shift_replay )->default_value( true, "on" ),
//           "enable time shift replay mode." )
#endif
        // logplayer options
        ( "minimum-mode",
          po::bool_switch( &M_minimum_mode )->default_value( M_minimum_mode ),
          "start logplayer with minimum mode." )
        ( "monitor-path,m",
          po::value< std::string >( &M_monitor_path )->default_value( "self", "self" ),
          "set the path to the monitor client invoked by rcsslogplayer." )
        ( "monitor-port",
          po::value< int >( &M_monitor_port )->default_value( 6000, "6000" ),
          "set a port number to wait monitor client connections." )
//         ( "output-file",
//           po::value< std::string >( &M_output_file )->default_value( "", "" ),
//           "set the output file path." )
        ( "auto-quit-mode",
          po::value< bool >( &M_auto_quit_mode )->default_value( false, "off" ),
          "enable automatic quit mode." )
        ( "auto-quit-wait",
          po::value< int >( &M_auto_quit_wait )->default_value( 5, "5" ),
          "set a wait period for the automatic quit mode." )
        ( "auto-loop-mode",
          po::value< bool >( &M_auto_loop_mode )->default_value( false, "off" ),
          "enable automatic replay loop mode." )
        ( "timer-interval",
          po::value< int >( &M_timer_interval )->default_value( DEFAULT_TIMER_INTERVAL ),
          "set the logplayer timer interval." )
        // window options
        ( "geometry",
          po::value< std::string >( &geometry )->default_value( "" ),
          "specifies the window geometry ([WxH][+X+Y]). e.g. --geometry=1024x768+1+1" )
//         ( "canvas-size",
//           po::value< std::string >( &canvas_size )->default_value( "" ),
//           "specifies the canvas size(WxH). e.g. --canvas-size=1024x768" )
        ( "maximize",
          po::bool_switch( &M_maximize )->default_value( M_maximize ),
          "start with a maximized window." )
        ( "full-screen",
          po::bool_switch( &M_full_screen )->default_value( M_full_screen ),
          "start with a full screen window." )
        ( "hide-menu-bar",
          po::bool_switch( &M_hide_menu_bar )->default_value( M_hide_menu_bar ),
          "start without a menu bar." )
        ( "hide-tool-bar",
          po::bool_switch( &M_hide_tool_bar )->default_value( M_hide_tool_bar ),
          "start without a tool bar." )
        ( "hide-status-bar",
          po::bool_switch( &M_hide_status_bar )->default_value( M_hide_status_bar ),
          "start without a status bar." )
        // view options
        ( "anti-aliasing",
          po::value< bool >( &M_anti_aliasing )->default_value( true, "on" ),
          "show anti-aliased objects." )
        ( "show-score-board",
          po::value< bool >( &M_show_score_board )->default_value( true, "on" ),
          "show score board." )
        ( "show-keepaway-area",
          po::value< bool >( &M_show_keepaway_area )->default_value( false, "off" ),
          "show keepaway area." )
        ( "show-team-graphic",
          po::value< bool >( &M_show_team_graphic )->default_value( true, "on" ),
          "show team graphic." )
        ( "show-draw-info",
          po::value< bool >( &M_show_draw_info )->default_value( true, "on" ),
          "show team draw information." )
        ( "show-ball",
          po::value< bool >( &M_show_ball )->default_value( true, "on" ),
          "show ball." )
        ( "show-player",
          po::value< bool >( &M_show_player )->default_value( true, "on" ),
          "show players." )
        ( "show-player-number",
          po::value< bool >( &M_show_player_number )->default_value( true, "on" ),
          "show player\'s uniform number." )
        ( "show-player-type",
          po::value< bool >( &M_show_player_type )->default_value( false, "off" ),
          "show player\'s heterogeneous type ID." )
        ( "show-view-area",
          po::value< bool >( &M_show_view_area )->default_value( false, "off" ),
          "show player\'s view area." )
        ( "show-catch-area",
          po::value< bool >( &M_show_catch_area )->default_value( false, "off" ),
          "show player\'s catch area." )
        ( "show-tackle-area",
          po::value< bool >( &M_show_tackle_area )->default_value( false, "off" ),
          "show player\'s tackle area." )
        ( "show-kick-accel-area",
          po::value< bool >( &M_show_kick_accel_area )->default_value( false, "off" ),
          "show player\'s kick acceleration area." )
        ( "show-stamina",
          po::value< bool >( &M_show_stamina )->default_value( false, "off" ),
          "show player\'s stamina." )
        ( "show-stamina-capacity",
          po::value< bool >( &M_show_stamina_capacity )->default_value( false, "off" ),
          "show player\'s stamina capacity." )
        ( "show-pointto",
          po::value< bool >( &M_show_pointto )->default_value( false, "off" ),
          "show player\'s pointing to point." )
        ( "show-card",
          po::value< bool >( &M_show_card )->default_value( true, "on" ),
          "show player\'s card status." )
        ( "ball-size",
          po::value< double >( &M_ball_size )->default_value( 0.35, "0.35" ),
          "set a ball radius in enlarge mode." )
        ( "player-size",
          po::value< double >( &M_player_size )->default_value( 0.0, "0.0" ),
          "set a fixed player radius in enlarge mode." )
        ( "show-grid-coord",
          po::value< bool >( &M_show_grid_coord )->default_value( false, "off" ),
          "show grid line coordinate value." )
        ( "grid-step",
          po::value< double >( &M_grid_step )->default_value( 0.0, "0.0" ),
          "set a grid step size." )
        ( "show-flag",
          po::value< bool >( &M_show_flag )->default_value( false, "off" ),
          "show landmark flags." )
        ( "show-offside-line",
          po::value< bool >( &M_show_offside_line )->default_value( false, "off" ),
          "show offside lines." )
        ;

    po::options_description invisibles( "Invisibles" );
    invisibles.add_options()
        ( "game-log-file",
          po::value< std::string >( &M_game_log_file )->default_value( "" ),
          "set the path to Game Log file(.rcg) to be opened.")
        ;

    po::positional_options_description pdesc;
    pdesc.add( "game-log-file", 1 );

    po::options_description all_desc( "All options:" );
    all_desc.add( visibles ).add( invisibles );


    bool help = false;
    bool version = false;
    try
    {
        po::variables_map vm;
        po::command_line_parser parser( argc, argv );
        parser.options( all_desc ).positional( pdesc );
        po::store( parser.run(), vm );
        po::notify( vm );

        help = vm.count( "help" );
        version = vm.count( "version" );
    }
    catch ( std::exception & e )
    {
        std::cerr << e.what() << std::endl;
        help = true;
    }

    if ( version )
    {
        std::cout << PACKAGE_NAME << " Version " << VERSION
                  << std::endl;
        if ( ! help )
        {
            return false;
        }
    }

    if ( help )
    {
        std::cout << "Usage: " << PACKAGE_NAME
                  << " [options ... ] [<GameLogFile>]\n";
        std::cout << visibles << std::endl;
        return false;
    }

    if ( M_timer_interval < 0 )
    {
        std::cerr << "Illegal timer interval " << M_timer_interval
                  << ". set default value." << std::endl;
        M_timer_interval = DEFAULT_TIMER_INTERVAL;
    }

    if ( M_timer_interval < 5 )
    {
        std::cerr << "Too small timer interval " << M_timer_interval
                  << ".  replaced by 5." << std::endl;
        M_timer_interval = 5;
    }

    if ( M_timer_interval > 5000 )
    {
        std::cerr << "Too huge timer interval " << M_timer_interval
                  << ".  replaced by 5000." << std::endl;
        M_timer_interval = 5000;
    }

    if ( ! geometry.empty() )
    {
        int w = -1, h = -1;
        int x = -1, y = -1;

        int num = std::sscanf( geometry.c_str(),
                               " %d x %d %d %d " ,
                               &w, &h, &x, &y );
        //std::cerr << "geometry = " << geometry
        //          << "  param_num=" << num
        //          << " width=" << w << " height=" << h
        //          << " x=" << x << " y=" << y
        //          << std::endl;
        if ( num == 4 || num == 2 )
        {
            if ( w <= 0 || h <= 0 )
            {
                std::cerr << "Illegal window size [" << geometry
                          << "]" << std::endl;
            }
            else
            {
                M_window_width = w;
                M_window_height = h;
                M_window_x = x;
                M_window_y = y;
            }
        }
        else if ( std::sscanf( geometry.c_str(),
                               " %d %d " ,
                               &x, &y ) == 2 )
        {
            //std::cerr << "only pos = "
            //          << " x=" << x
            //          << " y=" << y
            //          << std::endl;
            M_window_x = x;
            M_window_y = y;
        }
        else
        {
            std::cerr << "Illegal geometry format [" << geometry
                      << "]" << std::endl;
        }
    }

//     if ( ! canvas_size.empty() )
//     {
//         int w = -1, h = -1;
//         if ( std::sscanf( canvas_size.c_str(),
//                           " %d x %d ",
//                           &w, &h ) == 2
//              && w > 1
//              && h > 1 )
//         {
//             M_canvas_width = w;
//             M_canvas_height = h;
//         }
//         else
//         {
//             std::cerr << "Illegal canvas size format [" << canvas_size
//                       << "]" << std::endl;
//         }
//     }
#endif
    return true;
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::setFieldScale( const double & value )
{
    if ( std::fabs( M_field_scale - value ) > 0.01 )
    {
        M_field_scale = std::max( MIN_FIELD_SCALE, std::min( value, MAX_FIELD_SCALE ) );
        M_zoomed = true;
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::zoomIn()
{
    M_zoomed = true;
    M_field_scale *= ZOOM_RATIO;
    if ( M_field_scale > MAX_FIELD_SCALE )
    {
        M_field_scale = MAX_FIELD_SCALE;
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::zoomOut()
{
    M_zoomed = true;
    M_field_scale /= ZOOM_RATIO;
    if ( M_field_scale < MIN_FIELD_SCALE )
    {
        M_field_scale = MIN_FIELD_SCALE;
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::unzoom()
{
    if ( M_zoomed
         || focusType() != Options::FOCUS_POINT
         || focusPoint().x() != 0.0
         || focusPoint().y() != 0.0 )
    {
        M_focus_type = Options::FOCUS_POINT;
        M_focus_point.setX( 0.0 );
        M_focus_point.setY( 0.0 );
        M_zoomed = false;

        int temp_width = M_canvas_width;
        M_canvas_width += 1;
        updateFieldSize( temp_width, M_canvas_height );
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::updateFieldSize( const int canvas_width,
                          const int canvas_height )
{
    if ( M_canvas_width != canvas_width
         || M_canvas_height != canvas_height )
    {
        M_canvas_width = canvas_width;
        M_canvas_height = canvas_height;

        // adjust field scale to window size.
        if ( ! zoomed() )
        {
            double total_pitch_l = ( PITCH_LENGTH
                                     + PITCH_MARGIN * 2.0
                                     + 1.0 );
            double total_pitch_w = ( PITCH_WIDTH
                                     + PITCH_MARGIN * 2.0
                                     + 1.0 );

            M_field_scale = static_cast< double >( canvas_width ) / total_pitch_l;

            // automatically adjust a field scale
            if ( total_pitch_w * fieldScale() > canvas_height )
            {
                M_field_scale = static_cast< double >( canvas_height ) / total_pitch_w;
            }

            // check the scale threshold
            if ( fieldScale() < MIN_FIELD_SCALE )
            {
                M_field_scale = MIN_FIELD_SCALE;
            }

            M_field_scale = rint( M_field_scale * 100.0 ) / 100.0;
        }
    }

    M_field_center.setX( canvas_width/2 - scale( focusPoint().x() ) );
    M_field_center.setY( canvas_height/2 - scale( focusPoint().y() ) );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::setFocusPoint( const int screen_x,
                        const int screen_y )
{
    M_focus_type = Options::FOCUS_POINT;

    M_focus_point.setX( fieldX( screen_x ) );
    M_focus_point.setY( fieldY( screen_y ) );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::unselectPlayer()
{
    M_player_select_type = Options::SELECT_UNSELECT;
    setSelectedNumber( rcss::rcg::NEUTRAL, 0 );
    M_focus_type = Options::FOCUS_POINT;
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::setPlayerSelectType( const Options::PlayerSelectType type )
{
    if ( type != Options::SELECT_FIX
         && type == M_player_select_type )
    {
        unselectPlayer();
    }
    else
    {
        M_player_select_type = type;
    }
}
