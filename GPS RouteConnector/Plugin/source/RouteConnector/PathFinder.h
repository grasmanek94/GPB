#pragma once

//Forward declare Node so Edge can see it
class Node;

struct Edge
{
	Edge(Node* node, float cost) : pNode(node), moveCost(cost){}
	Node* pNode;
	float moveCost;
};

class Node
{
public:
	Node(void);
	Node(int name, bool exists);
	~Node(void);

	void createEdge(Node* pTarget, float moveCost);

	void setGCost(float cost);
	void setClosed(bool closed);
	void setParent(Node* pParent);

	float getGCost(void);
	float getFCost(void);
	bool getClosed(void);
	Node* getParent(void);
	int getName(void);
	bool DoesExist(void);
	bool DoesExist_yes(void);
	std::vector<Edge*>* getEdges(void);

	void calcFCost(void);
	void reset(void);
private:
	float mGCost;
	float mTotal;
	bool mClosed;
	Node* mpParent;
	int mName;
	bool mHeur;
	std::vector<Edge*> mEdges;
};

class Graph
{
public:
	Graph(void);
	~Graph(void);

	//void addNode(int name, bool exists);
	void addNode(int name, bool exists, Node** NodeID );
	void connect_oneway(int ppFirst, int ppSecond, float moveCost);
	void connect_oneway(Node* pFirst, Node* pSecond, float moveCost);
	//int * findPath_r(int start, int end);
	void findPath_r(Node* pStart, Node* pEnd, std::vector<cell> &road, cell &costMx);
	void reset(void);
private:
	void findNodesx(int firstName, Node** ppFirstNode);
	bool inList(Node* pNode, std::vector<Node*>* pList);
	static bool compareNodes(Node* pFirst, Node* pSecond);
	std::vector<Node*> mNodes;
};

Graph::Graph(void)
{
}

Graph::~Graph(void)
{
	while(!mNodes.empty())
	{
		delete mNodes.back();
		mNodes.pop_back();
	}
}

void Graph::addNode(int name, bool exists, Node** NodeID )
{
	Node* pStart = NULL;
	mNodes.push_back(new Node(name,exists));
	std::vector<Node*>::iterator itr;
	itr = mNodes.begin()+mNodes.size()-1;
	pStart = (*itr);
	if(exists == true)pStart->DoesExist_yes();
	*NodeID = pStart;
}

void Graph::connect_oneway(Node* pFirst, Node* pSecond, float moveCost)
{
	if(pFirst != NULL && pSecond != NULL)
	{
		pFirst->createEdge(pSecond, moveCost);
	}
}

void Graph::findPath_r(Node* pStart, Node* pEnd, std::vector<cell> &road, cell &costMx)
{
	if(pStart == pEnd || pEnd == nullptr || pStart == nullptr)
	{
		return;
	}

	std::vector<Node*> openList;
	openList.push_back(pStart);
	Node* pCurrNode = NULL;

	while(!openList.empty())
	{
		//Get best node from open list (lowest F value).
		//Since we sort the list at the end of the previous loop we know
		//the front node is the best
		pCurrNode = openList.front();

		//Exit if we're are the goal
		if (pCurrNode == pEnd || pCurrNode == nullptr || pEnd == nullptr)
			break;

		//Remove the node from the open list and place it in the closed
		openList.erase(openList.begin());
		pCurrNode->setClosed(true); //We use a flag instead of a list for speed
		//Test all of the edge nodes from the current node
		std::vector<Edge*>* pEdges = pCurrNode->getEdges();
		Node* pEdgeNode = NULL;
		for(std::vector<Edge*>::iterator i = pEdges->begin(); i != pEdges->end(); ++i)
		{
			pEdgeNode = (*i)->pNode;
			//If it's closed we've already analysed it
			if(pEdgeNode != nullptr && !pEdgeNode->getClosed() && pCurrNode->DoesExist() == true)
			{
				if(!inList(pEdgeNode,&openList))
				{
					openList.push_back(pEdgeNode);
					pEdgeNode->setGCost(pCurrNode->getGCost()+(*i)->moveCost);
					pEdgeNode->calcFCost();
					pEdgeNode->setParent(pCurrNode);
				}
				else
				{
					//If this is a better node (lower G cost)
					if(pEdgeNode->getGCost() > pCurrNode->getGCost()+(*i)->moveCost)
					{
						pEdgeNode->setGCost(pCurrNode->getGCost()+(*i)->moveCost);
						pEdgeNode->calcFCost();
						pEdgeNode->setParent(pCurrNode);
					}
				}
			}
		}
		//Place the lowest F cost item in the open list at the top, so we can
		//access it easily next iteration
		std::sort(openList.begin(), openList.end(),  Graph::compareNodes);
	}
	//Make sure we actually found a path
	if(pEnd != nullptr && pEnd->getParent() != NULL)
	{
		//Output the path
		//Use a stack because it is LIFO
		std::stack<Node*> path;
		while(pCurrNode != NULL)
		{
			path.push(pCurrNode);
			pCurrNode = pCurrNode->getParent();
		}
		float totalcost = 0.0f;
		while(!path.empty())
		{
			road.push_back(path.top()->getName());
			totalcost = path.top()->getGCost();
			path.pop();
		}
		costMx = amx_ftoc(totalcost);
		return;
	}
	return;
}

bool Graph::inList(Node* pNode, std::vector<Node*>* pList)
{
	for(std::vector<Node*>::iterator i = pList->begin(); i != pList->end(); ++i)
	{
		if((*i) == pNode)
		{
			return true;
		}
	}

	return false;
}

bool Graph::compareNodes(Node* pFirst, Node* pSecond)
{
	return pFirst->getFCost() < pSecond->getFCost();
}

void Graph::reset(void)
{
	for(std::vector<Node*>::iterator i = mNodes.begin(); i != mNodes.end(); ++i)
	{
		(*i)->reset();
	}
}


Node::Node(void)
{
}

Node::Node(int name, bool exists) : mGCost(0.0f), mTotal(0.0f), mClosed(false), mpParent(NULL), mName(name), mHeur(exists)
{
}

Node::~Node(void)
{
	while(!mEdges.empty())
	{
		delete mEdges.back();
		mEdges.pop_back();
	}
}

int Node::getName(void)
{
	return mName;
}

void Node::createEdge(Node* pTarget, float moveCost)
{
	mEdges.push_back(new Edge(pTarget, moveCost));
}

void Node::setClosed(bool closed)
{
	mClosed = closed;
}

bool Node::getClosed(void)
{
	return mClosed;
}

std::vector<Edge*>* Node::getEdges(void)
{
	return &mEdges;
}

float Node::getGCost(void)
{
	return mGCost;
}

void Node::setGCost(float cost)
{
	mGCost = cost;
}

void Node::calcFCost(void)
{
	mTotal = mGCost;
}

void Node::setParent(Node* pParent)
{
	mpParent = pParent;
}

float Node::getFCost(void)
{
	return mTotal;
}

bool Node::DoesExist(void)
{
	return mHeur;
}

bool Node::DoesExist_yes(void)
{
	mHeur = true;
	return true;
}

Node* Node::getParent(void)
{
	return mpParent;
}

void Node::reset(void)
{
	mGCost = 0.0f;
	mTotal = 0.0f;
	mClosed = false;
	mpParent = NULL;
}