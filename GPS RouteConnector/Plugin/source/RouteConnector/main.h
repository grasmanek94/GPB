#pragma once

#ifdef OS_WINDOWS
	using namespace Concurrency;
#else
	using namespace tbb;
	using namespace tbb::strict_ppl;
#endif

//no need to change the code in here at all.
namespace Natives
{
	static cell AMX_NATIVE_CALL n_NodeExists( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_ConnectNodes( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_NearestNodeFromPoint( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_NearestPlayerNode( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_AddNode( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_AddNodeEx( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetConnectedNodes( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetQueueSize( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_CalculatePath( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_WriteNodesToFile( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_ReadNodesFromFile( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetNodePos( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetangleBetweenNodes( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetConnectedNodeDistance( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_IsNodeIntersection( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetNextEmptyNodeID( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetConnectedNodeID( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetDistanceBetweenNodes( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_IsNodeInGraph( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_AddNotAddedNodeToGraph( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_ReturnArray( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_DeleteArray( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_StoreArray( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetRouteAtPos( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetRouteFromTo( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetRouteArraySize( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetNextNodeInArray( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_SetNodeFlagIndex( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_SetNodeFlagID( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_IsNodeInArray( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_RemoveNode( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_DisconnectNodeFromNode( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_DisconnectAllFromNode( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetNodeDirectionToConnect( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_SetNodeDirectionToConnect( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_DeleteRouteIDFromQueue( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetGPSdatVersion( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetPluginVersion( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_ReturnDeletedNodeArray( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_AddPlayer( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_RemovePlayer( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_EnableOPCNIC( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_DisableOPCNIC( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_OPCNICuseRealDistance( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_OPCNICuseArea( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_rebuildGraph( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetNodeFlagIndex( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_GetNodeFlagID( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_ChangeOPCNIURate( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_NearestNodeFromPointInArray( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_NearestNodeFromPlayerInArray( AMX* amx, cell* params );
	static cell AMX_NATIVE_CALL n_freeNodeSlots( AMX* amx, cell* params );
};//namespace Natives

struct RM
{
	int ID;
	bool closed;
	RM(int ID_,bool closed_)
	{
		ID = ID_;
		closed = closed_;
	}
};

namespace Functions
{
	void constructGaph();
	void OnPlayerClosestNodeIDChange(int playerid, int oldnode, int newnode);

	int DisconnectAllConnectionsFromNode(int Node);
	int DisconnectNodeFromNode(int Node_One,int Node_Two);
	int RemoveNode(int Node);
	int RemoveWholeNodePath(int NodeID);
	int NodeExists(int NodeID);
	int GetNodeDirectionToConnect(int NodeID, int ConnectID);
	int SetNodeDirectionToConnect(int NodeID, int ConnectID,int Direction);
	int RemoveWholeNodePath(int NodeID);
	int IsNodeAddedToGraph(int NodeID);
	int AddNotAddedNodeToGraph(int NodeID);
	int AddNode(float X,float Y, float Z, int AddToGraph,int AddToAreaScanner);
	int AddNodeEx(int i,float X,float Y, float Z, int AddToGraph);
	int GetNextEmptyNodeID();
	int ConnectNodes(int NodeOne, int NodeTwo, int AddToGraph,int direction);
	int NearestPlayerNode(int playerid, float MaxDist, int ignorenode, int UseArea);
	int NearestNodeFromPoint(float X, float Y, float Z, float MaxDist, int ignorenode, int UseArea);
	int ReadNodeData(char * file);
	int WriteNodeData(char * file);
	int GetConnectedNodes(int NodeID);
	int GetNodeDirectionToConnect(int NodeID, int ConnectID);
	int GetConnectedNodeID(int NodeID,int ConnectID);

	float GetConnectedNodeDistance(int NodeID,int ConnectID);
	float GetDistanceBetweenPoints(int NodeID1,int NodeID2);

	bool inList(int ID, std::vector<RM>* pList);
	int NearestNodeFromPointInArray(int ArrayID, float X, float Y, float Z, float MaxDist, int ignorenode, int IgnoreFlagged);

	bool rebuildGaph();

};//namespace Functions


std::atomic<bool> gIsThreadRunning;
std::atomic<bool> gIsThreadDone;

bool constructed = false;
bool OnPCNIDCenable = true;
bool UseRealClosestDistance = false;
int GPSdatVersion = 0;
int g_Ticked  = 0;
int g_TickMax = PLUGIN_PRIVATE_UPDATE_AC;
char * g_sz_tmp;
char buffer[2048];

Graph* dgraph;

struct ConnectInfo
{
	int ID;
	float Distance;
	int connect_direction;
};

struct NodesInfo
{
	bool Exists;
	float xPOS;
	float yPOS;
	float zPOS;
	bool AddedToGraph;
	Node* NodeID;
	ConnectInfo CW[MAX_CONNECTIONS];
};

struct ThreadNodesInfo
{
	Node* NodeID;
	float xPOS;
	float yPOS;
	float zPOS;
};

struct NodesInfoScanner
{
	int NodeID;
	NodesInfoScanner(int i_NodeID)
	{
		NodeID = i_NodeID;
	}
};

struct QuedData
{
	int start;
	int end;
	int extraid;
	AMX * script;
	int CreatePolygon;
	float Width;
	int GetNodePositions;
	QuedData()
	{
		start = 0;
		end = 0;
		extraid = 0;
		script = NULL;
		CreatePolygon = 0;
		Width = 0.0f;
		GetNodePositions = 0;
	}
	QuedData(int start_,int end_,int extraid_, AMX * script_, int CreatePolygon_, float Width_, int GetNodePos_)
	{
		start = start_;
		end = end_;
		extraid = extraid_;
		script = script_;
		CreatePolygon = CreatePolygon_;
		Width = Width_;
		GetNodePositions = GetNodePos_;
	}
};

struct PassData //thanks to DeadMG for improvements.
{ 
    std::vector<cell> Paths;
	std::vector<cell> Polygon;
	std::vector<cell> npX;
	std::vector<cell> npY;
	std::vector<cell> npZ;
	int extraid;
	AMX * script;
	cell MoveCost;
	PassData()
	{
		extraid = 0;
		script = NULL;
		MoveCost = 0;
		Paths.clear();
		Polygon.clear();
		npX.clear();
		npY.clear();
		npZ.clear();
	}
    template<typename Iterator,typename Piterator, typename tpX, typename tpY, typename tpZ> PassData(Iterator begin, Iterator end, int extraid_, cell MoveCost_, AMX * script_, Piterator Pbegin, Piterator Pend, tpX Xb, tpX Xe, tpY Yb, tpY Ye, tpZ Zb, tpZ Ze)
        : Paths(begin, end),Polygon(Pbegin,Pend),npX(Xb,Xe),npY(Yb,Ye),npZ(Zb,Ze)
    { 
        extraid = extraid_; 
		MoveCost = MoveCost_;
		script = script_;
    }
	~PassData()
	{
		Paths.clear();
		Polygon.clear();
		npX.clear();
		npY.clear();
		npZ.clear();
	}
};

struct RouteData //thanks to DeadMG for improvements.
{ 
    std::vector<cell> Paths;
    std::deque<bool> Taken; // no deque<bool> spec

    template<typename Iterator> RouteData(Iterator begin, Iterator end)
        : Paths(begin, end)
        , Taken(Paths.size())
    { }
};
//

struct NewLast
{
	int lastID;
	int newID;
};

cell				ProcessTick_amxaddr[5] =		{NULL,NULL,NULL,NULL,NULL};

std::map			<int, RouteData>				RouteMap;
std::vector			<int>							PlayerLoopList;
std::set			<AMX*>							rcp_amxinfo;
std::vector			<RM>							RemoveNodes;
concurrent_queue	<QuedData>						QueueVector;
std::vector			<NodesInfoScanner>				Area[535][535];//160.801 Areas, -20.000 to 20.000 (40.000x40.000 = 1.600.000.000 square units), is an 100x100 units area with each unit holding nodes. (6000x6000 area, if all nodes spread evenly each area unit holds 38 nodes, not one big area with 35k nodes :p)
concurrent_queue	<PassData>						PassVector;
PassData											LocalPass;
NewLast												ChangeNode[MAX_PLAYERS];
NodesInfo											xNode[MAX_NODES];
ThreadNodesInfo										Thread_xNode[MAX_NODES];

std::atomic<unsigned int> QueueSize;

extern void * pAMXFunctions;

///////////////////////////////////////////////////////
// From "amx.c", part of the PAWN language runtime:
// http://code.google.com/p/pawnscript/source/browse/trunk/amx/amx.c

ucell GetPlayerPosAddress = NULL;
cell GetPlayerPosPositionData[5] = {4*sizeof(cell),NULL,NULL,NULL,NULL};
AMX FakeAMX;

#define USENAMETABLE(hdr) \
	((hdr)->defsize==sizeof(AMX_FUNCSTUBNT))

#define NUMENTRIES(hdr,field,nextfield) \
	(unsigned)(((hdr)->nextfield - (hdr)->field) / (hdr)->defsize)

#define GETENTRY(hdr,table,index) \
	(AMX_FUNCSTUB *)((unsigned char*)(hdr) + (unsigned)(hdr)->table + (unsigned)index*(hdr)->defsize)

#define GETENTRYNAME(hdr,entry) \
	(USENAMETABLE(hdr) ? \
		(char *)((unsigned char*)(hdr) + (unsigned)((AMX_FUNCSTUBNT*)(entry))->nameofs) : \
		((AMX_FUNCSTUB*)(entry))->name)

typedef ucell AMX_NATIVE_CALL n_GetPlayerPos( AMX* amx, cell* params );
n_GetPlayerPos* func_GetPlayerPos = NULL;

int GetPlayerPos(int playerid,float *x,float *y,float *z)//AMX HACK BY GAMER_Z
{
	GetPlayerPosPositionData[0] = 4*sizeof(cell);
	GetPlayerPosPositionData[1] = playerid;
	GetPlayerPosPositionData[2] = 0;
	GetPlayerPosPositionData[3] = sizeof(cell);
	GetPlayerPosPositionData[4] = 2*sizeof(cell);
	func_GetPlayerPos(&FakeAMX,GetPlayerPosPositionData);
	*x = amx_ctof(GetPlayerPosPositionData[2]);
	*y = amx_ctof(GetPlayerPosPositionData[3]);
	*z = amx_ctof(GetPlayerPosPositionData[4]);
	return 1;
}
///////////////////////////////////////////////////////
