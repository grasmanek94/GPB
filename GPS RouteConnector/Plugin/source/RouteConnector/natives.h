#pragma once
namespace Natives
{
	AMX_NATIVE_INFO AMXNatives[ ] =
	{
		{"AddNode", n_AddNode},
		{"AddNodeEx" , n_AddNodeEx},
		{"GetNodePos", n_GetNodePos},
		{"ConnectNodes", n_ConnectNodes},
		{"WriteNodesToFile", n_WriteNodesToFile},
		{"ReadNodesFromFile", n_ReadNodesFromFile},
		{"NearestPlayerNode", n_NearestPlayerNode},
		{"NearestNodeFromPoint", n_NearestNodeFromPoint},
		{"CalculatePath",n_CalculatePath},
		{"IsNodeIntersection",n_IsNodeIntersection},
		{"GetAngleBetweenNodes",n_GetangleBetweenNodes},
		{"GetConnectedNodes",n_GetConnectedNodes},
		{"GetNextEmptyNodeID",n_GetNextEmptyNodeID},
		{"GetQueueSize",n_GetQueueSize},
		{"GetConnectedNodeID",n_GetConnectedNodeID},
		{"GetConnectedNodeDistance",n_GetConnectedNodeDistance},
		{"GetDistanceBetweenNodes",n_GetDistanceBetweenNodes},
		{"IsNodeInPathFinder",n_IsNodeInGraph},
		{"StoreRouteArray",n_StoreArray},
		{"GetRouteArray",n_ReturnArray},
		{"DeleteArray",n_DeleteArray},
		{"GetRouteAtPos",n_GetRouteAtPos},
		{"AddExistingNodeToPathFinder",n_AddNotAddedNodeToGraph},
		{"RemoveNode",n_RemoveNode},
		{"DisconnectNodeFromNode",n_DisconnectNodeFromNode},
		{"DisconnectAllFromNode",n_DisconnectAllFromNode},
		{"DeleteNodeSystemAtNode",n_ReturnDeletedNodeArray},
		{"GetNodeDirectionToConnect",n_GetNodeDirectionToConnect},
		{"SetNodeDirectionToConnect",n_SetNodeDirectionToConnect},
		{"NodeExists",n_NodeExists},
		{"GetPluginVersion",n_GetPluginVersion},
		{"GetGPSdatVersion",n_GetGPSdatVersion},
		{"RemoveAllRouteIDFromQueue",n_DeleteRouteIDFromQueue},
		{"gps_AddPlayer",n_AddPlayer},
		{"gps_RemovePlayer",n_RemovePlayer},
		{"GetRouteArrayFromTo",n_GetRouteFromTo},
		{"GetRouteArraySize",n_GetRouteArraySize},
		{"GetNextNodeInArray",n_GetNextNodeInArray},
		{"IsNodeInArray",n_IsNodeInArray},
		{"SetIndexMarkInArray",n_SetNodeFlagIndex},
		{"SetNodeIDMarkInArray",n_SetNodeFlagID},
		{"EnableOnPlayerNodeIDChange",n_EnableOPCNIC},
		{"DisableOnPlayerNodeIDChange",n_DisableOPCNIC},
		{"NodeChangeScanAllNodes",n_OPCNICuseRealDistance},
		{"NodeChangeScanAreaOnly",n_OPCNICuseArea},
		{"GetNodeIDMarkInArray",n_GetNodeFlagIndex},
		{"GetIndexMarkInArray",n_GetNodeFlagID},
		{"ChangeOPCNIURate",n_ChangeOPCNIURate},
		{"NearestNodeFromPointInArray",n_NearestNodeFromPointInArray},
		{"NearestNodeFromPlayerInArray",n_NearestNodeFromPlayerInArray},
		{"RebuildGraph",n_rebuildGraph},
		{"GetAmountOfFreeNodeSlots",n_freeNodeSlots},
		{0,                0}
	};

	static cell AMX_NATIVE_CALL n_ChangeOPCNIURate( AMX* amx, cell* params )
	{
		g_Ticked = 0;
		g_TickMax = params[1];
		if(g_TickMax < 1)
		{
			g_TickMax = 1;
		}
		return g_TickMax;
	}

	static cell AMX_NATIVE_CALL n_GetGPSdatVersion( AMX* amx, cell* params )
	{
		return GPSdatVersion;
	}

	static cell AMX_NATIVE_CALL n_NodeExists( AMX* amx, cell* params )
	{
		return Functions::NodeExists(params[1]);
	}

	static cell AMX_NATIVE_CALL n_GetPluginVersion( AMX* amx, cell* params )
	{
		return PLUGIN_VERSION;
	}

	static cell AMX_NATIVE_CALL n_ConnectNodes( AMX* amx, cell* params )
	{
		return Functions::ConnectNodes(params[1],params[2],params[3],params[4]);
	}

	static cell AMX_NATIVE_CALL n_NearestNodeFromPoint( AMX* amx, cell* params )
	{
		return Functions::NearestNodeFromPoint(amx_ctof(params[1]),amx_ctof(params[2]),amx_ctof(params[3]),amx_ctof(params[4]),params[5],params[6]);
	}

	static cell AMX_NATIVE_CALL n_NearestPlayerNode( AMX* amx, cell* params )
	{
		return Functions::NearestPlayerNode(params[1],amx_ctof(params[2]),params[3],params[4]);
	}

	static cell AMX_NATIVE_CALL n_AddNode( AMX* amx, cell* params )
	{
		return Functions::AddNode(amx_ctof(params[1]),amx_ctof(params[2]),amx_ctof(params[3]),params[4],params[5]);
	}

	static cell AMX_NATIVE_CALL n_AddNodeEx( AMX* amx, cell* params )
	{
		return Functions::AddNodeEx(params[1],amx_ctof(params[2]),amx_ctof(params[3]),amx_ctof(params[4]),params[5]);
	}

	static cell AMX_NATIVE_CALL n_GetConnectedNodes( AMX* amx, cell* params )
	{
		return Functions::GetConnectedNodes(params[1]);
	}

	static cell AMX_NATIVE_CALL n_GetQueueSize( AMX* amx, cell* params )
	{
		return QueueSize;
	}

	static cell AMX_NATIVE_CALL n_CalculatePath( AMX* amx, cell* params )
	{
		if(params[1] < 0 || params[1] > (MAX_NODES-1) || params[2] < 0 || params[2] > (MAX_NODES-1) || params[1] == params[2])
			return 0;

		QueueVector.push(QuedData(params[1],params[2],params[3],amx,params[4],amx_ctof(params[5]),params[6]));
		++QueueSize;
		return 1;
	}

	static cell AMX_NATIVE_CALL n_DeleteRouteIDFromQueue( AMX* amx, cell* params )
	{
		QueueVector.clear();
		QueueSize = 0;
		return 1;
	}

	static cell AMX_NATIVE_CALL n_WriteNodesToFile( AMX* amx, cell* params )
	{
		amx_StrParam(amx,params[1],g_sz_tmp);
		return Functions::WriteNodeData(g_sz_tmp);
	}

	static cell AMX_NATIVE_CALL n_ReadNodesFromFile( AMX* amx, cell* params )
	{
		amx_StrParam(amx,params[1],g_sz_tmp);
		return Functions::ReadNodeData(g_sz_tmp);
	}

	static cell AMX_NATIVE_CALL n_GetNodePos( AMX* amx, cell* params )
	{
		if(params[1] < 0 || params[1] > (MAX_NODES-1))
			return 0;
		if(xNode[params[1]].Exists == false)
			return -1;
		cell* cptr = NULL;
		amx_GetAddr(amx, params[2], &cptr);
		*cptr = amx_ftoc(xNode[params[1]].xPOS);
		amx_GetAddr(amx, params[3], &cptr);
		*cptr = amx_ftoc(xNode[params[1]].yPOS);
		amx_GetAddr(amx, params[4], &cptr);
		*cptr = amx_ftoc(xNode[params[1]].zPOS);
		cptr = NULL;
		return 1;
	}

	static cell AMX_NATIVE_CALL n_GetangleBetweenNodes( AMX* amx, cell* params )
	{
		float C = 0.0f;
		if(params[1] < 0 || params[1] > (MAX_NODES-1))
			return amx_ftoc(C);
		if(params[2] < 0 || params[2] > (MAX_NODES-1))
			return amx_ftoc(C);
		if(params[3] < 0 || params[3] > (MAX_NODES-1))
			return amx_ftoc(C);

		double c = sqrt(((xNode[params[2]].xPOS - xNode[params[1]].xPOS) * (xNode[params[2]].xPOS - xNode[params[1]].xPOS)) + ((xNode[params[2]].yPOS - xNode[params[1]].yPOS) * (xNode[params[2]].yPOS - xNode[params[1]].yPOS)));
		double b = sqrt(((xNode[params[2]].xPOS - xNode[params[3]].xPOS) * (xNode[params[2]].xPOS - xNode[params[3]].xPOS)) + ((xNode[params[2]].yPOS - xNode[params[3]].yPOS) * (xNode[params[2]].yPOS - xNode[params[3]].yPOS)));
		double a = sqrt(((xNode[params[1]].xPOS - xNode[params[3]].xPOS) * (xNode[params[1]].xPOS - xNode[params[3]].xPOS)) + ((xNode[params[1]].yPOS - xNode[params[3]].yPOS) * (xNode[params[1]].yPOS - xNode[params[3]].yPOS)));
		C = (float)(acos(((a*a) - ((b*b) + (c*c))) / (-2.0 * b * c)) * 57.295779513082320876798154814105);

		return amx_ftoc(C);
	}

	static cell AMX_NATIVE_CALL n_GetConnectedNodeDistance( AMX* amx, cell* params )
	{
		float C = Functions::GetConnectedNodeDistance(params[1],params[2]);
		return amx_ftoc(C);
	}

	static cell AMX_NATIVE_CALL n_IsNodeIntersection( AMX* amx, cell* params )
	{
		int connects = Functions::GetConnectedNodes(params[1]);
		if(connects == -1)return -1;
		if(connects < 3)return 0;
		return 1;
	}

	static cell AMX_NATIVE_CALL n_GetNextEmptyNodeID( AMX* amx, cell* params )
	{
		return Functions::GetNextEmptyNodeID();
	}

	static cell AMX_NATIVE_CALL n_GetConnectedNodeID( AMX* amx, cell* params )
	{
		return Functions::GetConnectedNodeID(params[1],params[2]);
	}

	static cell AMX_NATIVE_CALL n_GetDistanceBetweenNodes( AMX* amx, cell* params )
	{
		float C = Functions::GetDistanceBetweenPoints(params[1],params[2]);
		return amx_ftoc(C);
	}

	static cell AMX_NATIVE_CALL n_IsNodeInGraph( AMX* amx, cell* params )
	{
		return Functions::IsNodeAddedToGraph(params[1]);
	}

	static cell AMX_NATIVE_CALL n_AddNotAddedNodeToGraph( AMX* amx, cell* params )
	{
		return Functions::AddNotAddedNodeToGraph(params[1]);
	}

	static cell AMX_NATIVE_CALL n_ReturnArray( AMX* amx, cell* params )
	{
		auto found = RouteMap.find(params[1]);

		if (found == RouteMap.end())
		{
			return 0;
		}

		cell *dest = NULL;
		amx_GetAddr(amx,params[2],&dest);
		for(int a = 0, b = params[3]; a < b; ++a)
		{
			dest[a] = found->second.Paths[a];
		}
		//dest = NULL;
		return found->second.Paths.size();
	}

	static cell AMX_NATIVE_CALL n_DeleteArray( AMX* amx, cell* params )
	{
		auto found = RouteMap.find(params[1]);

		if (found == RouteMap.end())
		{
			return 0;
		}

		RouteMap.erase(found);
		return 1;
	}

	static cell AMX_NATIVE_CALL n_StoreArray( AMX* amx, cell* params )
	{
		std::vector <cell> temppath;
		int IDcounter = RouteMap.size() ? RouteMap.rbegin()->first + 1 : 0;

		cell *dest = NULL;
		amx_GetAddr(amx,params[2],&dest);

		std::copy(dest, dest + params[1], std::back_inserter(temppath));
		RouteMap.emplace(std::pair<int, RouteData>(IDcounter, RouteData(temppath.begin(), temppath.end())));

		return IDcounter;
	}

	static cell AMX_NATIVE_CALL n_GetNextNodeInArray( AMX* amx, cell* params )
	{
		auto found = RouteMap.find(params[1]);

		if (found == RouteMap.end())
		{
			return 0;
		}

		for(int x = 0, m = (int)found->second.Paths.size(); x < m; ++x)
		{
			if(found->second.Taken[x] == false)
			{
				if(params[2] == 1)
				{
					found->second.Taken[x] = true;
				}
				return found->second.Paths[x];
			}
		}
		return -1;
	}

	static cell AMX_NATIVE_CALL n_IsNodeInArray( AMX* amx, cell* params )
	{
		auto found = RouteMap.find(params[1]);

		if (found == RouteMap.end())
		{
			return 0;
		}


		for(int x = 0, m = (int)found->second.Paths.size(); x < m; ++x)
		{
			if (found->second.Paths[x] == params[2])
			{
				return 1;
			}
		}

		return 0;
	}

	static cell AMX_NATIVE_CALL n_SetNodeFlagID( AMX* amx, cell* params )
	{
		auto found = RouteMap.find(params[1]);

		if (found == RouteMap.end())
		{
			return 0;
		}

		for(int x = 0, m = (int)found->second.Paths.size(); x < m; ++x)
		{
			if(found->second.Paths[x] == params[2])
			{
				if(params[3] == 0)
				{
					found->second.Taken[x] = false;
					if(params[4] == 1)
					{
						for(int a = 0; a < x; ++a)
						{
							found->second.Taken[a] = false;
						}
					}
				}
				else
				{
					found->second.Taken[x] = true;
					if(params[4] == 1)
					{
						for(int a = 0; a < x; ++a)
						{
							found->second.Taken[a] = true;
						}
					}
				}
			}
		}
		return 1;

	}

	static cell AMX_NATIVE_CALL n_SetNodeFlagIndex( AMX* amx, cell* params )
	{
		auto found = RouteMap.find(params[1]);

		if (found == RouteMap.end())
		{
			return 0;
		}

		if(params[3] == 0)
		{
			found->second.Taken[params[2]] = false;
			if(params[4] == 1)
			{
				for(int a = 0; a < params[2]; ++a)
				{
					found->second.Taken[a] = false;
				}
			}
		}
		else
		{
			found->second.Taken[params[2]] = true;
			if(params[4] == 1)
			{
				for(int a = 0; a < params[2]; ++a)
				{
					found->second.Taken[a] = true;
				}
			}
		}

		return 1;
	}

	static cell AMX_NATIVE_CALL n_GetRouteAtPos( AMX* amx, cell* params )
	{
		auto found = RouteMap.find(params[1]);

		if (found == RouteMap.end())
		{
			return 0;
		}

		if((int)found->second.Paths.size() > params[2])
		{
			cell *dest = NULL;
			amx_GetAddr(amx,params[3],&dest);
			*dest = found->second.Paths.size();
			return found->second.Paths[params[2]];
		}

		return 0;
	}

	static cell AMX_NATIVE_CALL n_GetRouteFromTo(AMX* amx, cell* params)
	{
		auto found = RouteMap.find(params[1]);

		if (found == RouteMap.end())
		{
			return 0;
		}

		cell *dest = NULL;
		amx_GetAddr(amx, params[4], &dest);

		int a = params[2];
		int b = params[3];
		int c = 0;

		if (b >= (int)found->second.Paths.size())
		{
			return 0;
		}

		for(; a < b; ++a)
		{
			if(c == params[5])
			{
				return c;
			}
			dest[c++] = found->second.Paths[a];
		}

		return c;

	}

	static cell AMX_NATIVE_CALL n_GetRouteArraySize( AMX* amx, cell* params )
	{
		auto found = RouteMap.find(params[1]);

		if (found == RouteMap.end())
		{
			return 0;
		}

		return found->second.Paths.size();
	}

	static cell AMX_NATIVE_CALL n_RemoveNode( AMX* amx, cell* params )
	{
		return Functions::RemoveNode(params[1]);
	}

	static cell AMX_NATIVE_CALL n_DisconnectNodeFromNode( AMX* amx, cell* params )
	{
		return Functions::DisconnectNodeFromNode(params[1],params[2]);
	}

	static cell AMX_NATIVE_CALL n_DisconnectAllFromNode( AMX* amx, cell* params )
	{
		return Functions::DisconnectAllConnectionsFromNode(params[1]);
	}

	static cell AMX_NATIVE_CALL n_ReturnDeletedNodeArray( AMX* amx, cell* params )
	{
		Functions::RemoveWholeNodePath(params[1]);
		cell *dest = NULL;
		amx_GetAddr(amx,params[2],&dest);
		int b = 0;
		b = params[3];
		if(b > (int)RemoveNodes.size())
			b = (int)RemoveNodes.size();

		for(int a = 0; a < b; ++a)
		{
			dest[a] = RemoveNodes.at(a).ID;
		}
		return RemoveNodes.size();
	}

	static cell AMX_NATIVE_CALL n_GetNodeDirectionToConnect( AMX* amx, cell* params )
	{
		return Functions::GetNodeDirectionToConnect(params[1],params[2]);
	}

	static cell AMX_NATIVE_CALL n_SetNodeDirectionToConnect( AMX* amx, cell* params )
	{
		return Functions::SetNodeDirectionToConnect(params[1],params[2],params[3]);
	}

	static cell AMX_NATIVE_CALL n_AddPlayer( AMX* amx, cell* params )
	{
		int size = PlayerLoopList.size();
		for (int index=0; index < size; ++index)
		{
			if(PlayerLoopList.at(index) == params[1])
			{
				return 2;
			}
		}
		ChangeNode[params[1]].newID = -1;
		ChangeNode[params[1]].lastID = -1;
		PlayerLoopList.push_back(params[1]);	
		return 1;
	}

	static cell AMX_NATIVE_CALL n_RemovePlayer( AMX* amx, cell* params )
	{
		int size = PlayerLoopList.size();
		for (int index=0; index < size; ++index)
		{
			if(PlayerLoopList.at(index) == params[1])
			{
				PlayerLoopList.erase(PlayerLoopList.begin()+index);
				return 1;
			}
		}
		return 0;
	}
	//
	static cell AMX_NATIVE_CALL n_EnableOPCNIC( AMX* amx, cell* params )
	{
		OnPCNIDCenable = true;
		return 1;
	}

	static cell AMX_NATIVE_CALL n_DisableOPCNIC( AMX* amx, cell* params )
	{
		OnPCNIDCenable = false;
		return 1;
	}

	static cell AMX_NATIVE_CALL n_OPCNICuseRealDistance( AMX* amx, cell* params )
	{
		UseRealClosestDistance = true;
		return 1;
	}

	static cell AMX_NATIVE_CALL n_OPCNICuseArea( AMX* amx, cell* params )
	{
		UseRealClosestDistance = false;
		return 1;
	}

	static cell AMX_NATIVE_CALL n_rebuildGraph( AMX* amx, cell* params )
	{
		return Functions::rebuildGaph();
	}

	static cell AMX_NATIVE_CALL n_freeNodeSlots( AMX* amx, cell* params )
	{
		int freenodes = 0;
		for(int i = 0; i < MAX_NODES; ++i)
		{
			if(xNode[i].Exists == false)
				++freenodes;
		}
		return freenodes;
	}

	static cell AMX_NATIVE_CALL n_GetNodeFlagID( AMX* amx, cell* params )
	{
		auto found = RouteMap.find(params[1]);

		if (found == RouteMap.end())
		{
			return -1;
		}

		for(int x = 0, m = (int)found->second.Paths.size(); x < m; ++x)
		{
			if(found->second.Paths[x] == params[2])
			{
				return found->second.Taken[x];
			}
		}
		return -1;

	}

	static cell AMX_NATIVE_CALL n_GetNodeFlagIndex( AMX* amx, cell* params )
	{
		auto found = RouteMap.find(params[1]);

		if (found == RouteMap.end())
		{
			return -1;
		}

		return found->second.Taken[params[2]];
	}

	static cell AMX_NATIVE_CALL n_NearestNodeFromPointInArray( AMX* amx, cell* params )
	{
		return Functions::NearestNodeFromPointInArray(params[1], amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]), params[6], params[7]);
	}

	static cell AMX_NATIVE_CALL n_NearestNodeFromPlayerInArray( AMX* amx, cell* params )
	{
		float X = NULL;
		float Y = NULL;
		float Z = NULL;
		GetPlayerPos(params[1],&X,&Y,&Z);

		return Functions::NearestNodeFromPointInArray(params[2], X, Y, Z, amx_ctof(params[3]), params[4], params[5]);
	}
};//namespace Natives