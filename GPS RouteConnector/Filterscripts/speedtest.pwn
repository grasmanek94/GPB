//Load this script with "loadfs" from the console AFTER the whole gamemode has been loaded and all other stuff.

#include <a_samp>

#include "RouteConnector"
new Timers[2];

#define ROUTES_TO_CALCULATE 10

public OnFilterScriptInit()
{
    Timers[0] = tickcount();
    for(new i = 0; i < ROUTES_TO_CALCULATE; ++i)
    {
        CalculatePath(1702,27932,i);
    }
	return 1;
}

public GPS_WhenRouteIsCalculated(routeid,node_id_array[],amount_of_nodes,Float:distance)
{
	printf("%d route calculated, total running time: %d",routeid,tickcount()-Timers[0]);
	if(routeid == ROUTES_TO_CALCULATE-1)
	{
	    Timers[1] = tickcount();
	    printf("Time taken to calculate and callback %d routes: %d ms, one route: %f",ROUTES_TO_CALCULATE,Timers[1]-Timers[0],( float(Timers[1])-float(Timers[0]) )/ROUTES_TO_CALCULATE.0);
	}
	return 1;
}
