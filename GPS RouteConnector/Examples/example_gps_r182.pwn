#include <a_samp>

#include <streamer>
#include <RouteConnector>

new icon = 0;

enum Data
{
	RouteID,
	Icons[1024],
	IconsSize,
	LostCount,
	Calculating,
	Destination
}

new Storage[MAX_PLAYERS][Data];

public GPS_WhenRouteIsCalculated(routeid,node_id_array[],amount_of_nodes,Float:distance,Float:Polygon[],Polygon_Size)
{
	if(amount_of_nodes > 1)
	{
		DestroyDynamicArea(Storage[routeid][RouteID]);
		Storage[routeid][RouteID] = CreateDynamicPolygon(Polygon,.maxpoints=Polygon_Size,.playerid=routeid);
		new Counter=0;
		for(new i = 0; i < Storage[routeid][IconsSize]; ++i)
		{
		    DestroyDynamicMapIcon(Storage[routeid][Icons][i]);
		}
		for(new i = 0,j=(Polygon_Size-2)/2; i < j; i+=8)
		{
			Storage[routeid][Icons][Counter++] = CreateDynamicMapIcon(Polygon[i],Polygon[i+1], 0.0, icon, 0x0000FFFF, .playerid = routeid, .streamdistance=300.0);
		}
		Storage[routeid][Destination] = node_id_array[amount_of_nodes-1];
		Storage[routeid][IconsSize] = Counter;
		Storage[routeid][Calculating] = 0;
		Storage[routeid][LostCount] = 0;
	}
	else
	{
		DestroyDynamicArea(Storage[routeid][RouteID]);
		Storage[routeid][RouteID] = (-1);
		for(new i = 0; i < Storage[routeid][IconsSize]; ++i)
		{
		    DestroyDynamicMapIcon(Storage[routeid][Icons][i]);
		}
		Storage[routeid][Destination] = (-1);
		Storage[routeid][IconsSize] = 0;
		Storage[routeid][Calculating] = 0;
		Storage[routeid][LostCount] = 0;
	}
	return 1;
}

public OnPlayerEnterDynamicArea(playerid,areaid)
{
	if(Storage[playerid][RouteID] == areaid)
	{
		Storage[playerid][LostCount] = 0;
    }
    return 1;
}

public OnPlayerLeaveDynamicArea(playerid,areaid)
{
	if(Storage[playerid][RouteID] == areaid)
	{
	    if(Storage[playerid][Calculating] == 0)
	    {
			CalculatePath(NearestPlayerNode(playerid),Storage[playerid][Destination],playerid,true,12.0);
			Storage[playerid][Calculating] = 1;
		}
	}
	return 1;
}

public OnPlayerConnect(playerid)
{
	gps_AddPlayer(playerid);
	Storage[playerid][RouteID] = (-1);
	Storage[playerid][IconsSize] = 0;
	Storage[playerid][LostCount] = 0;
	Storage[playerid][Calculating] = 0;
	Storage[playerid][Destination] = (-1);
	return 1;
}

public OnPlayerDisconnect(playerid,reason)
{
	gps_RemovePlayer(playerid);
	if(Storage[playerid][RouteID] != (-1))
	{
		DestroyDynamicArea(Storage[playerid][RouteID]);
		Storage[playerid][RouteID] = (-1);
	}
	if(Storage[playerid][IconsSize] != 0)
	{
		for(new i = 0; i < Storage[playerid][IconsSize]; ++i)
		{
		    DestroyDynamicMapIcon(Storage[playerid][Icons][i]);
		}
		Storage[playerid][IconsSize] = 0;
	}
	return 1;
}

public OnPlayerClosestNodeIDChange(playerid,old_NodeID,new_NodeID)
{
	if(Storage[playerid][RouteID] != (-1))
	{
	    if(Storage[playerid][Destination] != (-1))
		{
			if(old_NodeID == Storage[playerid][Destination] || new_NodeID == Storage[playerid][Destination])
	    	{
	    	    SendClientMessage(playerid,-1,"Destination reached");
				DestroyDynamicArea(Storage[playerid][RouteID]);
				for(new i = 0; i < Storage[playerid][IconsSize]; ++i)
				{
				    DestroyDynamicMapIcon(Storage[playerid][Icons][i]);
				}
				Storage[playerid][RouteID] = (-1);
				Storage[playerid][IconsSize] = 0;
				Storage[playerid][LostCount] = 0;
				Storage[playerid][Calculating] = 0;
				Storage[playerid][Destination] = (-1);
	        }
	        else
	        {
			    if(!IsPlayerInDynamicArea(playerid,Storage[playerid][RouteID]))
			    {
			        if(Storage[playerid][Calculating] == 0)
			        {
			            if(++Storage[playerid][LostCount] >= 4)
			            {
			                Storage[playerid][Calculating] = 1;
			                CalculatePath(NearestPlayerNode(playerid),Storage[playerid][Destination],playerid,true,9.5);
			            }
			        }
			    }
	        }
	    }
	    else
	    {
			DestroyDynamicArea(Storage[playerid][RouteID]);
			for(new i = 0; i < Storage[playerid][IconsSize]; ++i)
			{
			    DestroyDynamicMapIcon(Storage[playerid][Icons][i]);
			}
			Storage[playerid][RouteID] = (-1);
			Storage[playerid][IconsSize] = 0;
			Storage[playerid][LostCount] = 0;
			Storage[playerid][Calculating] = 0;
			Storage[playerid][Destination] = (-1);
	    }
	}
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    if(Storage[playerid][Calculating] == 0)
    {
        if(Storage[playerid][Destination] != (-1) || Storage[playerid][RouteID] !=(-1))
		{
			DestroyDynamicArea(Storage[playerid][RouteID]);
			for(new i = 0; i < Storage[playerid][IconsSize]; ++i)
			{
			    DestroyDynamicMapIcon(Storage[playerid][Icons][i]);
			}
			Storage[playerid][RouteID] = (-1);
			Storage[playerid][IconsSize] = 0;
			Storage[playerid][LostCount] = 0;
			Storage[playerid][Calculating] = 0;
			Storage[playerid][Destination] = (-1);
		}
		CalculatePath(NearestPlayerNode(playerid),NearestNodeFromPoint(fX,fY,fZ),playerid,true,12.0);
		Storage[playerid][Calculating] = 1;
	}
    return 1;
}
