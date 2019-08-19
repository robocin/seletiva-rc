// -*-c++-*-

/*
 *Copyright:

 Copyright (C) Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3, or (at your option)
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

#include "role_center_back.h"

#include "bhv_chain_action.h"
#include "bhv_basic_offensive_kick.h"
#include "bhv_basic_move.h"

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>

#include <rcsc/common/logger.h>

using namespace rcsc;

const std::string RoleCenterBack::NAME( "CenterBack" );

/*-------------------------------------------------------------------*/
/*!

 */
namespace {
rcss::RegHolder role = SoccerRole::creators().autoReg( &RoleCenterBack::create,
                                                       RoleCenterBack::NAME );
}

/*-------------------------------------------------------------------*/
/*!

 */
bool
RoleCenterBack::execute( PlayerAgent * agent )
{
    /*          Seletiva Robocin - Desafio 2 - Comportamentos individuais
        Comportamentos individuais são chaves quando é preciso que o player realize 
        uma ação para uma determinada situação, tal como fazer a marcação de um outro 
        player adversário ou se posicionar na projeção da bola para fazer o bloqueio 
        do toque adversário. A partir da nossa base de código que será disponibilizada, 
        implemente um tipo de comportamento para o jogador de uma posição específica 
        (ex: atacante).
    */

    bool kickable = agent->world().self().isKickable();
    if ( agent->world().existKickableTeammate()
         && agent->world().teammatesFromBall().front()->distFromBall()
         < agent->world().ball().distFromSelf() )
    {
        kickable = false;
    }

    if ( kickable )
    {
        doKick( agent );
    }
    else
    {
        doMove( agent );
    }

    return true;
}

/*-------------------------------------------------------------------*/
/*!

 */
void
RoleCenterBack::doKick( PlayerAgent * agent )
{
    if ( Bhv_ChainAction().execute( agent ) )
    {
        dlog.addText( Logger::TEAM,
                      __FILE__": (execute) do chain action" );
        agent->debugClient().addMessage( "ChainAction" );
        return;
    }

    Bhv_BasicOffensiveKick().execute( agent );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
RoleCenterBack::doMove( PlayerAgent * agent )
{
    Bhv_BasicMove().execute( agent );
}
