#pragma once

//#define GetPlayerPos(a,b,c,d) g_Invoke->callNative(&PAWN::GetPlayerPos,a,b,c,d)

namespace Functions
{
	//inline int GetPlayerPos(int playerid, float *x, float *y, float *z)
	//{
		//return g_Invoke->callNative(&PAWN::GetPlayerPos,playerid,x,y,z);
	//}
	
	int IsNodeAddedToGraph(int NodeID)
	{
		if(NodeID < 0 || NodeID > (MAX_NODES-1))
			return (-1);
		if(xNode[NodeID].AddedToGraph == true)
			return 1;
		return 0;
	}

	int AddNotAddedNodeToGraph(int NodeID)
	{
		if(NodeID < 0 || NodeID > (MAX_NODES-1))
			return (-1);
		if(xNode[NodeID].Exists == true && xNode[NodeID].AddedToGraph == false)
		{
			dgraph->addNode(NodeID,true,&xNode[NodeID].NodeID);
			xNode[NodeID].AddedToGraph = true;
			return 1;
		}
		return 0;
	}

	int AddNode(float X,float Y, float Z, int AddToGraph,int AddToAreaScanner)
	{
		for(int i = 0; i < MAX_NODES; ++i)
		{
			if(xNode[i].Exists == false)
			{
				xNode[i].Exists = true;
				xNode[i].xPOS = X;
				xNode[i].yPOS = Y;
				xNode[i].zPOS = Z;
				if(AddToAreaScanner == 1)
				{
					int Xlocation = //(int)floor((X+20000.0f)/50.0f);
						0;
					int Ylocation = //(int)floor((Y+20000.0f)/50.0f);
						0;
				
					GetArea(Xlocation,Ylocation,X,Y);

				
					if(Xlocation > 0)
					{
						if(Ylocation > 0)
						{
							/*
								[-1,+1][+0,+1][+1,+1]
								[-1,+0][+0,+0][+1,+0]
								[-1,-1][+0,-1][+1,-1]
							*/
							Area[Xlocation-1][Ylocation+1].push_back(NodesInfoScanner(i));
							Area[Xlocation-1][Ylocation].push_back(NodesInfoScanner(i));
							Area[Xlocation-1][Ylocation-1].push_back(NodesInfoScanner(i));

							Area[Xlocation][Ylocation+1].push_back(NodesInfoScanner(i));
							Area[Xlocation][Ylocation].push_back(NodesInfoScanner(i));
							Area[Xlocation][Ylocation-1].push_back(NodesInfoScanner(i));

							Area[Xlocation+1][Ylocation+1].push_back(NodesInfoScanner(i));
							Area[Xlocation+1][Ylocation].push_back(NodesInfoScanner(i));
							Area[Xlocation+1][Ylocation-1].push_back(NodesInfoScanner(i));
						}
						else
						{
							/*
								[-1,+1][+0,+1][+1,+1]
								[-1,+0][+0,+0][+1,+0]
							*/
							Area[Xlocation-1][Ylocation+1].push_back(NodesInfoScanner(i));
							Area[Xlocation-1][Ylocation].push_back(NodesInfoScanner(i));

							Area[Xlocation][Ylocation+1].push_back(NodesInfoScanner(i));
							Area[Xlocation][Ylocation].push_back(NodesInfoScanner(i));

							Area[Xlocation+1][Ylocation+1].push_back(NodesInfoScanner(i));
							Area[Xlocation+1][Ylocation].push_back(NodesInfoScanner(i));
						}
					}
					else
					{
						if(Ylocation > 0)
						{
							/*
								[+0,+1][+1,+1]
								[+0,+0][+1,+0]
								[+0,-1][+1,-1]
							*/

							Area[Xlocation][Ylocation+1].push_back(NodesInfoScanner(i));
							Area[Xlocation][Ylocation].push_back(NodesInfoScanner(i));
							Area[Xlocation][Ylocation-1].push_back(NodesInfoScanner(i));

							Area[Xlocation+1][Ylocation+1].push_back(NodesInfoScanner(i));
							Area[Xlocation+1][Ylocation].push_back(NodesInfoScanner(i));
							Area[Xlocation+1][Ylocation-1].push_back(NodesInfoScanner(i));
						}
						else
						{
							/*
								[+0,+1][+1,+1]
								[+0,+0][+1,+0]
							*/

							Area[Xlocation][Ylocation+1].push_back(NodesInfoScanner(i));
							Area[Xlocation][Ylocation].push_back(NodesInfoScanner(i));

							Area[Xlocation+1][Ylocation+1].push_back(NodesInfoScanner(i));
							Area[Xlocation+1][Ylocation].push_back(NodesInfoScanner(i));
						}
					}
				}
				if(AddToGraph == 1)
				{
					if(xNode[i].AddedToGraph == false)
					{
						dgraph->addNode(i,true,&xNode[i].NodeID);
						xNode[i].AddedToGraph = true;
					}
				}
				return i;
			}
		}
		return -1;
	}


	int AddNodeEx(int i,float X,float Y, float Z, int AddToGraph)
	{
		if(i < 0 || i > (MAX_NODES-1))
			return (-1);

		if(xNode[i].Exists == false)
		{
			xNode[i].Exists = true;
			xNode[i].xPOS = X;
			xNode[i].yPOS = Y;
			xNode[i].zPOS = Z;
			int Xlocation = //(int)floor((X+20000.0f)/50.0f);
				0;
			int Ylocation = //(int)floor((Y+20000.0f)/50.0f);
				0;
			GetArea(Xlocation,Ylocation,X,Y);
			Area[Xlocation][Ylocation].push_back(NodesInfoScanner(i));
			if(AddToGraph == 1)
			{
				if(xNode[i].AddedToGraph == false)
				{
					dgraph->addNode(i,true,&xNode[i].NodeID);
					xNode[i].AddedToGraph = true;
				}
			}
			return i;
		}
		return -1;
	}

	int GetNextEmptyNodeID()
	{
		for(int i = 0; i < MAX_NODES; ++i)
		{
			if(xNode[i].Exists == false)
			{
				return i;
			}
		}
		return -1;
	}

	int ConnectNodes(int NodeOne, int NodeTwo, int AddToGraph,int direction)
	{
		if(NodeOne < 0 || NodeOne > (MAX_NODES-1))
			return (-1);
		if(NodeTwo < 0 || NodeTwo > (MAX_NODES-1))
			return (-2);

		if( NodeOne == NodeTwo ) return -3;
		if( xNode[NodeOne].Exists == false ) return -4;
		if( xNode[NodeTwo].Exists == false ) return -5;

		for(int i = 0; i < MAX_CONNECTIONS; ++i)
		{
			if(xNode[NodeOne].CW[i].ID == NodeTwo) return -6;
			if(xNode[NodeTwo].CW[i].ID == NodeOne) return -7;
		}

		for(int i = 0; i < MAX_CONNECTIONS; ++i)
		{	
			if(xNode[NodeOne].CW[i].ID == -1)
			{
				for(int j = 0; j < MAX_CONNECTIONS; ++j)
				{
					if(xNode[NodeTwo].CW[j].ID == -1)
					{
						if(direction == 0)
						{	
							xNode[NodeOne].CW[i].ID = NodeTwo;
							xNode[NodeOne].CW[i].connect_direction = 0;
							xNode[NodeTwo].CW[j].ID = NodeOne;
							xNode[NodeTwo].CW[j].connect_direction = 0;
							xNode[NodeOne].CW[i].Distance = sqrt(pow(xNode[NodeOne].xPOS-xNode[NodeTwo].xPOS,2.0f)+pow(xNode[NodeOne].yPOS-xNode[NodeTwo].yPOS,2.0f)+pow(xNode[NodeOne].zPOS-xNode[NodeTwo].zPOS,2.0f));
							xNode[NodeTwo].CW[j].Distance = xNode[NodeOne].CW[i].Distance;
							if(AddToGraph == 1)
							{
								if(xNode[NodeOne].AddedToGraph == true && xNode[NodeTwo].AddedToGraph == true)
								{
									dgraph->connect_oneway(xNode[NodeOne].NodeID, xNode[NodeTwo].NodeID, xNode[NodeOne].CW[i].Distance );
									dgraph->connect_oneway(xNode[NodeTwo].NodeID, xNode[NodeOne].NodeID, xNode[NodeOne].CW[i].Distance );
								}
							}
							return i;
						}
						else if(direction == 1)
						{
							xNode[NodeOne].CW[i].ID = NodeTwo;
							xNode[NodeOne].CW[i].connect_direction = 1;
							xNode[NodeTwo].CW[j].ID = NodeOne;
							xNode[NodeTwo].CW[j].connect_direction = 2;
							xNode[NodeOne].CW[i].Distance = sqrt(pow(xNode[NodeOne].xPOS-xNode[NodeTwo].xPOS,2.0f)+pow(xNode[NodeOne].yPOS-xNode[NodeTwo].yPOS,2.0f)+pow(xNode[NodeOne].zPOS-xNode[NodeTwo].zPOS,2.0f));
							xNode[NodeTwo].CW[j].Distance = xNode[NodeOne].CW[i].Distance;
							if(AddToGraph == 1)
							{
								if(xNode[NodeOne].AddedToGraph == true && xNode[NodeTwo].AddedToGraph == true)
								{
									dgraph->connect_oneway(xNode[NodeOne].NodeID, xNode[NodeTwo].NodeID, xNode[NodeOne].CW[i].Distance );
								}
							}
							return i;
						}
					}
				}
			}
		}
		return -8;
	}

	int NearestPlayerNode(int playerid, float MaxDist, int ignorenode, int UseArea)
	{
		float X = NULL;
		float Y = NULL;
		float Z = NULL;
		GetPlayerPos(playerid,&X,&Y,&Z);
		return NearestNodeFromPoint(X, Y, Z, MaxDist, ignorenode, UseArea);
	}

	int NearestNodeFromPoint(float X, float Y, float Z, float MaxDist, int ignorenode, int UseArea)
	{
		if(ignorenode < 0 || ignorenode > (MAX_NODES-1))
			ignorenode = (-1);
		int Nearest = -1;
		float prevdist = MaxDist;
		float newdist = 0.0f;

		if(UseArea == 0)
		{
			for(int i = 0; i < MAX_NODES; ++i)
			{
				if(i == ignorenode)
					continue;
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
			for(int i = 0,j = (int)Area[Xloc][Yloc].size(); i < j; ++i)
			{
				int NDX = Area[Xloc][Yloc].at(i).NodeID; 
				if(NDX == ignorenode)
					continue;
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
		return Nearest;
	}

	int NearestNodeFromPointInArray(int ArrayID, float X, float Y, float Z, float MaxDist, int ignorenode, int IgnoreFlagged)
	{
		if(ignorenode < 0 || ignorenode > (MAX_NODES-1))
			ignorenode = (-1);

		int Nearest = -1;
		float prevdist = MaxDist;
		float newdist;

		auto found = RouteMap.find(ArrayID);

		if (found == RouteMap.end())
		{
			return -1;
		}

		for(int i = 0, j = found->second.Paths.size(), NodeID = 0; i < j; ++i)
		{
			NodeID = found->second.Paths.at(i);
			if(NodeID == ignorenode)
				continue;
			if(IgnoreFlagged == 1)
			{
				if (found->second.Taken.at(i) == 1)
				{
					continue;
				}
			}
			newdist = (pow(xNode[NodeID].xPOS-X,2.0f)+pow(xNode[NodeID].yPOS-Y,2.0f)+pow(xNode[NodeID].zPOS-Z,2.0f));
			if(newdist < prevdist)
			{
				prevdist = newdist;
				Nearest = NodeID;
			}
		}

		return Nearest;
	}

	int ReadNodeData(char * file)
	{
		std::ifstream fin(file);
		if (fin.good() == true)
		{
			float X = 0.0f;
			float Y = 0.0f;
			float Z = 0.0f;
			int ID = 0;
			int ID2 = 0;
			int direction = (-1);
			int empty = 0;
			int count = 0;
			int count2 = 0;
			int count3 = 0;

			while(!fin.eof())
			{
					fin.getline(buffer, 2048);

					if(sscanf_s(buffer,"%d",&empty) > 0)
					{	
						if(empty == 0)
						{
							sscanf_s(buffer,"%d %f %f %f %d %d",&empty,&X,&Y,&Z,&empty,&ID);
							AddNodeEx(ID,X,Y,Z,0);
							++count2;
						}
						else if(empty == 1)
						{
							sscanf_s(buffer,"%d %d %d %d",&empty,&ID,&ID2,&direction);
							if(ConnectNodes(ID,ID2,0,direction) == 1)
							++count3;
						}
						else if(empty == 3)
						{
							sscanf_s(buffer,"%d %d",&empty,&GPSdatVersion);
						}
					}
					++count;
			}
			constructGaph();
			std::cout << "Read " << count << " lines, added " << count2 << " nodes and " << count3 << " connections.\r\n" << std::endl;
			return 1;
		}
	
		return 0;
	}

	int WriteNodeData(char * file)
	{
		std::ofstream myfile;
		myfile.open (file);
		if (myfile.good())
		{
			sprintf_s(buffer,"3 %d 1\r\n",GPSdatVersion);
			myfile.write(buffer,strlen(buffer));
			for(int i = 0; i < MAX_NODES; ++i)
			{
				if(xNode[i].Exists == true)
				{
					sprintf_s(buffer,"0 %f %f %f -1 %d\r\n",xNode[i].xPOS,xNode[i].yPOS,xNode[i].zPOS,i);
					myfile.write(buffer,strlen(buffer));
				}
			}
			for(int i = 0; i < MAX_NODES; ++i)
			{
				if(xNode[i].Exists == true)
				{
					for(int j = 0; j < MAX_CONNECTIONS; ++j)
					{
						if(xNode[i].CW[j].ID == (-1))
							continue;
						sprintf_s(buffer,"1 %d %d %d\r\n",i,xNode[i].CW[j].ID,xNode[i].CW[j].connect_direction);
						myfile.write(buffer,strlen(buffer));
					}
				}
			}
			myfile.close();
			return 1;
		}
		return 0;
	}

	int GetConnectedNodes(int NodeID)
	{
		if(NodeID < 0 || NodeID > (MAX_NODES-1))
			return (-1);

		int ConnectedNodes = 0;
		for(int i = 0; i < MAX_CONNECTIONS; ++i)
		{
			if(xNode[NodeID].CW[i].ID == (-1))
				continue;
			++ConnectedNodes;
		}
		return ConnectedNodes;
	}

	int GetNodeDirectionToConnect(int NodeID, int ConnectID)
	{
		if(NodeID < 0 || NodeID > (MAX_NODES-1) || ConnectID < 0 || ConnectID > (MAX_CONNECTIONS-1))
			return (-1);
		return xNode[NodeID].CW[ConnectID].connect_direction;
	}

	int SetNodeDirectionToConnect(int NodeID, int ConnectID,int Direction)
	{
		if(NodeID < 0 || NodeID > (MAX_NODES-1) || ConnectID < 0 || ConnectID > (MAX_CONNECTIONS-1) || Direction > 2 || Direction < 0)
			return (0);
		xNode[NodeID].CW[ConnectID].connect_direction = Direction;
		for(int i = 0; i < MAX_CONNECTIONS; ++i)
		{
			if(xNode[(xNode[NodeID].CW[ConnectID].ID)].CW[i].ID == NodeID)
			{
				if(Direction == 0)
					xNode[ xNode[NodeID].CW[ConnectID].ID ].CW[i].connect_direction = 0;
				if(Direction == 1)
					xNode[ xNode[NodeID].CW[ConnectID].ID ].CW[i].connect_direction = 2;
				if(Direction == 2)
					xNode[ xNode[NodeID].CW[ConnectID].ID ].CW[i].connect_direction = 1;
				return 1;
			}
		}
		return 0;
	}

	int GetConnectedNodeID(int NodeID,int ConnectID)
	{
		if(NodeID < 0 || NodeID > (MAX_NODES-1) || ConnectID < 0 || ConnectID > (MAX_CONNECTIONS-1))
			return (-1);

		return xNode[NodeID].CW[ConnectID].ID;
	}

	float GetConnectedNodeDistance(int NodeID,int ConnectID)
	{
		if(NodeID < 0 || NodeID > (MAX_NODES-1) || ConnectID < 0 || ConnectID > (MAX_CONNECTIONS-1))
			return (0.0);

		return xNode[NodeID].CW[ConnectID].Distance;
	}

	float GetDistanceBetweenPoints(int NodeID1,int NodeID2)
	{
		if(NodeID1 < 0 || NodeID1 > (MAX_NODES-1) || NodeID2 < 0 || NodeID2 > (MAX_NODES-1) )
			return (0.0);

		return sqrt(pow((xNode[NodeID2].xPOS-xNode[NodeID1].xPOS),2.0f)+pow((xNode[NodeID2].yPOS-xNode[NodeID1].yPOS),2.0f)+pow((xNode[NodeID2].zPOS-xNode[NodeID1].zPOS),2.0f));
	}

	void constructGaph()
	{
		dgraph = new Graph();
		int count = 0;
		std::cout << "Constructing graph...\r\n" << std::endl;
		for(int i = 0; i < MAX_NODES; ++i)
		{
			if(xNode[i].Exists == false)continue;
			dgraph->addNode(i,true,&xNode[i].NodeID);
			xNode[i].AddedToGraph = true;
			++count;
		}
		constructed = true;

		std::cout << "Connecting points...\r\n" << std::endl;
		int i, j;
		for(i = 0; i < MAX_NODES; i++)
		{
			if(xNode[i].Exists == false)
				continue;
			for(j = 0; j < MAX_CONNECTIONS; j++)
			{
				if(xNode[i].CW[j].ID == (-1))
					continue;
				if(xNode[ xNode[i].CW[j].ID ].Exists == false)
					continue;
				if(xNode[i].CW[j].connect_direction == 0)
				{
					dgraph->connect_oneway(xNode[i].NodeID, xNode[xNode[i].CW[j].ID].NodeID, xNode[i].CW[j].Distance );
				}
				else
				if(xNode[i].CW[j].connect_direction == 1)
				{
					dgraph->connect_oneway(xNode[i].NodeID, xNode[xNode[i].CW[j].ID].NodeID,xNode[i].CW[j].Distance );
				}
			}
		}
		constructed = true;
		std::cout << "Done!\r\n";
	}

	bool rebuildGaph()
	{
		if(constructed)
		{
			gIsThreadRunning = false;
			while(!gIsThreadDone){}
			dgraph->~Graph();
			dgraph = new Graph();
			int count = 0;
			std::cout << "Constructing graph...\r\n" << std::endl;
			int i, j;
			for(i = 0; i < MAX_NODES; ++i)
			{
				if(xNode[i].Exists == false)continue;
				dgraph->addNode(i,true,&xNode[i].NodeID);
				xNode[i].AddedToGraph = true;
				++count;
			}
			std::cout << "Connecting points...\r\n" << std::endl;
			for(i = 0; i < MAX_NODES; ++i)
			{
				Thread_xNode[i].NodeID = xNode[i].NodeID;
				Thread_xNode[i].xPOS = xNode[i].xPOS;
				Thread_xNode[i].yPOS = xNode[i].yPOS;
				Thread_xNode[i].zPOS = xNode[i].zPOS;
				if(xNode[i].Exists == false)
					continue;
				for(j = 0; j < MAX_CONNECTIONS; j++)
				{
					if(xNode[i].CW[j].ID == (-1))
						continue;
					if(xNode[ xNode[i].CW[j].ID ].Exists == false)
						continue;
					if(xNode[i].CW[j].connect_direction == 0)
					{
						dgraph->connect_oneway(xNode[i].NodeID, xNode[xNode[i].CW[j].ID].NodeID, xNode[i].CW[j].Distance );
					}
					else
					if(xNode[i].CW[j].connect_direction == 1)
					{
						dgraph->connect_oneway(xNode[i].NodeID, xNode[xNode[i].CW[j].ID].NodeID,xNode[i].CW[j].Distance );
					}
				}
			}
			gIsThreadRunning = true;
			gIsThreadDone = false;
			START_THREAD( BackgroundCalculator );
			std::cout << "Done!\r\n";
			return true;
		}
		return false;
	}

	int DisconnectAllConnectionsFromNode(int Node)
	{
		if(Node < 0 || Node > (MAX_NODES-1))
			return (-1);

		if( xNode[Node].Exists == false) return 0;

		for(int i = 0; i < MAX_CONNECTIONS; ++i)
		{
			if(xNode[Node].CW[i].ID != (-1))
			{
				for(int j = 0; j < MAX_CONNECTIONS; ++j)
				{
					if(xNode[ xNode[Node].CW[i].ID ].CW[j].ID == Node)
					{
						xNode[ xNode[Node].CW[i].ID ].CW[j].ID = (-1);
					}
				}
				xNode[Node].CW[i].ID = (-1);
			}
		}
		return 1;
	}

	int DisconnectNodeFromNode(int Node_One,int Node_Two)
	{
		if(Node_One < 0 || Node_One > (MAX_NODES-1))
			return (-1);

		if( xNode[Node_One].Exists == false) return 0;

		if(Node_Two < 0 || Node_Two > (MAX_NODES-1))
			return (-1);

		if( xNode[Node_Two].Exists == false) return 0;

		for(int i = 0; i < MAX_CONNECTIONS; ++i)
		{
			if(xNode[Node_One].CW[i].ID == Node_Two)
			{
				xNode[Node_One].CW[i].ID = (-1);
				for(int j = 0; j < MAX_CONNECTIONS; ++j)
				{
					if(xNode[Node_Two].CW[j].ID == Node_One)
					{
						xNode[Node_One].CW[j].ID = (-1);
						break;
					}
				}
				return 1;
			}
		}
		return 0;
	}

	int RemoveNode(int Node)
	{
		if(Node < 0 || Node > (MAX_NODES-1))
			return (-1);

		if( xNode[Node].Exists == false) return 0;

		DisconnectAllConnectionsFromNode(Node);
		xNode[Node].Exists = false;
		return 1;
	}

	void OnPlayerClosestNodeIDChange(int playerid, int oldnode, int newnode)
	{
		int callback = 0;
		for (std::set<AMX *>::iterator a = rcp_amxinfo.begin(); a != rcp_amxinfo.end(); ++a)
		{	
			if(!amx_FindPublic(*a, "OnPlayerClosestNodeIDChange", &callback))
			{
				amx_Push(*a, newnode);
				amx_Push(*a, oldnode);
				amx_Push(*a, playerid);
				amx_Exec(*a, NULL, callback);
			}
		}
	}

	bool inList(int ID, std::vector<RM>* pList)
	{
		for(std::vector<RM>::iterator i = pList->begin(); i != pList->end(); ++i)
		{
			if((*i).ID == ID)
			{
				return true;
			}
		}
		return false;
	}

	int NodeExists(int NodeID)
	{
		if(NodeID < 0 || NodeID > (MAX_NODES-1))
			return (-1);
		if( xNode[NodeID].Exists == false)
			return 0;
		return 1;
	}

	int RemoveWholeNodePath(int NodeID)
	{
		if(NodeID < 0 || NodeID > (MAX_NODES-1))
			return (-1);
		RemoveNodes.empty();
		RemoveNodes.push_back(RM(NodeID,true));
		for(int i = 0; i < MAX_CONNECTIONS; ++i)
		{
			int id = GetConnectedNodeID(NodeID,i);
			if(id != -1)
			{
				RemoveNodes.push_back(RM(id,false));
			}
		}
		bool not_done = true;
		while(not_done)
		{
			for(unsigned int i = 0; i < RemoveNodes.size(); ++i)
			{
				if(RemoveNodes.at(i).closed == false)
				{
					for(int g = 0; g < MAX_CONNECTIONS; ++g)
					{
						int id = GetConnectedNodeID(RemoveNodes.at(i).ID,g);
						if(id != -1)
						{
							if(Functions::inList(id, &RemoveNodes) == false)
							{
								RemoveNodes.push_back(RM(id,false));
							}
						}
					}
					RemoveNodes.at(i).closed = true;
				}
			}
			not_done = false;
			for(unsigned int i = 0; i < RemoveNodes.size(); ++i)
			{
				if(RemoveNodes.at(i).closed == false)
				{
					not_done = true;
					break;
				}
			}
		}
		return 0;
	}
};//namespace Functions