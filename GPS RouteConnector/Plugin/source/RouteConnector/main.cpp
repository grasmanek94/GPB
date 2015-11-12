/*
		ROUTER PLUGIN
		- GPS ADDITION TO SA-MP
		- Made By Gamer_Z a.k.a. grasmanek94 , Rafal Grasman

		October-2011

		contact: gzx@live.nl

		http://gpb.googlecode.com/
*/

//Definitions
#include "defines.h"

//System
#include <atomic>

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <array>
#include <algorithm>
#include <concurrent_queue.h>
#include <bitset>
#include <list>
#include <map>
#include <stdarg.h>
#include <math.h>
#include <set>

//SDK
#include "plugin.h"

//Pathfinder
#include "PathFinder.h"

//Variables
#include "main.h"
#include "DPoint.h"

//The plugin
#include "natives.h"
#include "functions.h"

PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData ) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	for(int i = 0; i < MAX_NODES; ++i)
	{
		xNode[i].Exists = false;
		xNode[i].AddedToGraph = false;
		xNode[i].NodeID = NULL;
		for(int j = 0; j < MAX_CONNECTIONS; ++j)
		{
			xNode[i].CW[j].ID = (-1);
		}
	}

	Functions::ReadNodeData("scriptfiles/GPS.dat");
	for(int i = 0; i < MAX_NODES; ++i)
	{
		Thread_xNode[i].NodeID = xNode[i].NodeID;
		Thread_xNode[i].xPOS = xNode[i].xPOS;
		Thread_xNode[i].yPOS = xNode[i].yPOS;
		Thread_xNode[i].zPOS = xNode[i].zPOS;
	}
	std::cout << "---Loading---\r\n\tGamer_Z's Project Bundle: \r\n\t\tRoute Connector (a.k.a. GPS) R" << PLUGIN_VERSION << "\r\n---LOADED---";
	gIsThreadRunning = true;
	gIsThreadDone = false;
	QueueSize = 0;
	START_THREAD( BackgroundCalculator );
	return true;
}


#ifdef OS_WINDOWS
	void BackgroundCalculator( void *unused )
#else
	void *BackgroundCalculator( void *unused )
#endif
{
	QuedData			RecievedData;
	cell				CalculatedPathCost;
	std::vector <cell>	CalculatedPath;
	std::vector <cell>	PolygonTemp;
	std::vector <cell>  npX;
	std::vector <cell>  npY;
	std::vector <cell>  npZ;

	while(gIsThreadRunning)
    {
		if(QueueVector.try_pop(RecievedData))
		{
			--QueueSize;
			if (dgraph)
			{
				dgraph->findPath_r(Thread_xNode[RecievedData.start].NodeID, Thread_xNode[RecievedData.end].NodeID, CalculatedPath, CalculatedPathCost);
				dgraph->reset();

				if (RecievedData.CreatePolygon == 1)
				{
					if (CalculatedPath.size() > 3)
					{
						//black-magic-geometry-stuff
						DPoint temp[4];
						temp[0] = DPoint(Thread_xNode[CalculatedPath.at(0)].xPOS, Thread_xNode[CalculatedPath.at(0)].yPOS);
						temp[1] = DPoint(Thread_xNode[CalculatedPath.at(1)].xPOS, Thread_xNode[CalculatedPath.at(1)].yPOS);

						temp[2] = temp[0] - (function_r(temp[1] - temp[0]) * RecievedData.Width);
						temp[3] = temp[0] + (function_r(temp[1] - temp[0]) * RecievedData.Width);

						PolygonTemp.push_back(amx_ftoc(temp[2].X));
						PolygonTemp.push_back(amx_ftoc(temp[2].Y));
						PolygonTemp.push_back(amx_ftoc(temp[3].X));
						PolygonTemp.push_back(amx_ftoc(temp[3].Y));

						for (unsigned int k = 1; k < CalculatedPath.size() - 2; ++k)
						{
							temp[0] = DPoint(Thread_xNode[CalculatedPath.at(k)].xPOS, Thread_xNode[CalculatedPath.at(k)].yPOS);
							temp[1] = DPoint(Thread_xNode[CalculatedPath.at(k + 1)].xPOS, Thread_xNode[CalculatedPath.at(k + 1)].yPOS);
							temp[2] = DPoint(Thread_xNode[CalculatedPath.at(k - 1)].xPOS, Thread_xNode[CalculatedPath.at(k - 1)].yPOS);

							temp[3] = temp[0] + (function_r(function_u(temp[1] - temp[0]) - function_u(temp[2] - temp[0])) * RecievedData.Width);

							PolygonTemp.push_back(amx_ftoc(temp[3].X));
							PolygonTemp.push_back(amx_ftoc(temp[3].Y));
						}

						temp[0] = DPoint(Thread_xNode[CalculatedPath.at(CalculatedPath.size() - 1)].xPOS, Thread_xNode[CalculatedPath.at(CalculatedPath.size() - 1)].yPOS);
						temp[1] = DPoint(Thread_xNode[CalculatedPath.at(CalculatedPath.size() - 2)].xPOS, Thread_xNode[CalculatedPath.at(CalculatedPath.size() - 2)].yPOS);

						temp[2] = temp[0] - (function_r(temp[1] - temp[0]) * RecievedData.Width);
						temp[3] = temp[0] + (function_r(temp[1] - temp[0]) * RecievedData.Width);

						PolygonTemp.push_back(amx_ftoc(temp[2].X));
						PolygonTemp.push_back(amx_ftoc(temp[2].Y));
						PolygonTemp.push_back(amx_ftoc(temp[3].X));
						PolygonTemp.push_back(amx_ftoc(temp[3].Y));

						for (unsigned int k = CalculatedPath.size() - 2; k > 0; --k)
						{
							temp[0] = DPoint(Thread_xNode[CalculatedPath.at(k)].xPOS, Thread_xNode[CalculatedPath.at(k)].yPOS);
							temp[1] = DPoint(Thread_xNode[CalculatedPath.at(k + 1)].xPOS, Thread_xNode[CalculatedPath.at(k + 1)].yPOS);
							temp[2] = DPoint(Thread_xNode[CalculatedPath.at(k - 1)].xPOS, Thread_xNode[CalculatedPath.at(k - 1)].yPOS);

							temp[3] = temp[0] - (function_r(function_u(temp[1] - temp[0]) - function_u(temp[2] - temp[0])) * RecievedData.Width);

							PolygonTemp.push_back(amx_ftoc(temp[3].X));
							PolygonTemp.push_back(amx_ftoc(temp[3].Y));
						}
						//close the polygon
						PolygonTemp.push_back(PolygonTemp.at(0));
						PolygonTemp.push_back(PolygonTemp.at(1));
					}
					else
					{
						PolygonTemp.push_back(0);
					}
				}
				else
				{
					PolygonTemp.push_back(0);
				}
				if (RecievedData.GetNodePositions == 1)
				{
					for (int i = 0, y = CalculatedPath.size(); i < y; ++i)
					{
						npX.push_back(amx_ftoc(Thread_xNode[CalculatedPath.at(i)].xPOS));
						npY.push_back(amx_ftoc(Thread_xNode[CalculatedPath.at(i)].yPOS));
						npZ.push_back(amx_ftoc(Thread_xNode[CalculatedPath.at(i)].zPOS));
					}
				}
				else
				{
					npX.push_back(0);
					npY.push_back(0);
					npZ.push_back(0);
				}
				PassVector.push(PassData(CalculatedPath.begin(), CalculatedPath.end(), RecievedData.extraid, CalculatedPathCost, RecievedData.script, PolygonTemp.begin(), PolygonTemp.end(), npX.begin(), npX.end(), npY.begin(), npY.end(), npZ.begin(), npZ.end()));
				CalculatedPath.clear();
				PolygonTemp.clear();
				npX.clear();
				npY.clear();
				npZ.clear();
				CalculatedPathCost = 0;
			}
		}
		SLEEP(5);
		//-------------------------
    }
	gIsThreadDone = true;
}

PLUGIN_EXPORT void PLUGIN_CALL
	ProcessTick()
{
	if(PassVector.try_pop(LocalPass))
	{
		auto it = rcp_amxinfo.find(LocalPass.script);
		if (it != rcp_amxinfo.end()) 
		{
			int callback = 0;
			if(!amx_FindPublic(LocalPass.script, "GPS_WhenRouteIsCalculated", &callback))
			{
				amx_PushArray(LocalPass.script, &ProcessTick_amxaddr[4], 0, LocalPass.npZ.data(), LocalPass.npZ.size());
				amx_PushArray(LocalPass.script, &ProcessTick_amxaddr[3], 0, LocalPass.npY.data(), LocalPass.npY.size());
				amx_PushArray(LocalPass.script, &ProcessTick_amxaddr[2], 0, LocalPass.npX.data(), LocalPass.npX.size());
				amx_Push(LocalPass.script, LocalPass.Polygon.size());
				amx_PushArray(LocalPass.script, &ProcessTick_amxaddr[1], 0, LocalPass.Polygon.data(), LocalPass.Polygon.size());
				amx_Push(LocalPass.script, LocalPass.MoveCost);
				amx_Push(LocalPass.script, LocalPass.Paths.size());
				amx_PushArray(LocalPass.script, &ProcessTick_amxaddr[0], 0, LocalPass.Paths.data(), LocalPass.Paths.size());
				amx_Push(LocalPass.script, LocalPass.extraid);
				amx_Exec(LocalPass.script, NULL, callback);
				amx_Release(LocalPass.script,ProcessTick_amxaddr[0]);
				amx_Release(LocalPass.script,ProcessTick_amxaddr[1]);
				amx_Release(LocalPass.script,ProcessTick_amxaddr[2]);
				amx_Release(LocalPass.script,ProcessTick_amxaddr[3]);
				amx_Release(LocalPass.script,ProcessTick_amxaddr[4]);
			}
		}
	}
	if(g_Ticked++ == g_TickMax)
	{
		if(OnPCNIDCenable == true)
		{
			unsigned int playerid = 0;	
			unsigned int size = PlayerLoopList.size();
			for (unsigned int index = 0; index < size; ++index)
			{
				playerid = PlayerLoopList.at(index);
				
				int Nearest = -1;
				double prevdist = 4800000000.11f;//(40000*40000)*3+0.11
				double newdist;
				
				float X;			
				float Y;
				float Z;

				GetPlayerPos(playerid,&X,&Y,&Z);
				if(UseRealClosestDistance == true)
				{
					ChangeNode[playerid].lastID = ChangeNode[playerid].newID;
					for(int i = 0; i < MAX_NODES; ++i)
					{
						if(xNode[i].Exists == false)
							continue;
						newdist = sqrt(pow(xNode[i].xPOS-X,2.0f)+pow(xNode[i].yPOS-Y,2.0f)+pow(xNode[i].zPOS-Z,2.0f));
						if(newdist < prevdist)
						{
							prevdist = newdist;
							Nearest = i;
						}
					}
				}
				else
				{
					int Xloc = 0, Yloc = 0;
					GetArea(Xloc,Yloc,X,Y);
					ChangeNode[playerid].lastID = ChangeNode[playerid].newID;
					for(int i = 0,j = (int)Area[Xloc][Yloc].size(); i < j; ++i)
					{
						int NDX = Area[Xloc][Yloc].at(i).NodeID;
						if(xNode[NDX].Exists == false)
							continue;
						newdist = sqrt(pow(xNode[NDX].xPOS-X,2.0f)+pow(xNode[NDX].yPOS-Y,2.0f)+pow(xNode[NDX].zPOS-Z,2.0f));
						if(newdist < prevdist)
						{
							prevdist = newdist;
							Nearest = NDX;
						}
					}
				}
				ChangeNode[playerid].newID = Nearest;
				if(ChangeNode[playerid].lastID != ChangeNode[playerid].newID && ChangeNode[playerid].lastID != (-1))
				{
					Functions::OnPlayerClosestNodeIDChange(playerid, ChangeNode[playerid].lastID,ChangeNode[playerid].newID);
				}
			}
		}
		g_Ticked = 0;
	}
}

//void AmxLoad_delay( AMX *amx );

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	//Code from sscanf2.5, [PAWN]SSCANF Author: Y_Less
	int
		num,
		idx;
	// Operate on the raw AMX file, don't use the amx_ functions to avoid issues
	// with the fact that we've not actually finished initialisation yet.  Based
	// VERY heavilly on code from "amx.c" in the PAWN runtime library.
	AMX_HEADER *
		hdr = (AMX_HEADER *)amx->base;
	AMX_FUNCSTUB *
		func;
	num = NUMENTRIES(hdr, natives, libraries);
	for (idx = 0; idx != num; ++idx)
	{
		func = GETENTRY(hdr, natives, idx);
		if (!strcmp("GetPlayerPos", GETENTRYNAME(hdr, func)))
		{
			GetPlayerPosAddress = func->address;
			FakeAMX = *amx;
			FakeAMX.data = ((unsigned char*)&GetPlayerPosPositionData) + (2*sizeof(cell));
			func_GetPlayerPos = (n_GetPlayerPos*)GetPlayerPosAddress;
			break;
		}
	}
	//end sscanf cut
	rcp_amxinfo.insert(amx);
	return amx_Register( amx, Natives::AMXNatives, -1 );
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	rcp_amxinfo.erase(amx); 
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	std::cout << "---Unloading---\r\n\tGamer_Z's Project Bundle: \r\n\t\tRoute Connector (a.k.a. GPS)\r\n---UNLOADED---";
}
