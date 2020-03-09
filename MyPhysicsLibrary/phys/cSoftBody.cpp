#include "cSoftBody.h"
#include <numeric>

namespace phys
{
	cSoftBody::cSpring::cSpring(cNode* nodeA, cNode* nodeB, float springConstant) : NodeA(nodeA), NodeB(nodeB), RestingLength(glm::distance(nodeA->Position, nodeB->Position)), SpringConstant(springConstant), SpringForceAtoB(0.0f,0.0f,0.0f)
	{

	}
	void cSoftBody::cSpring::UpdateSpringForce()
	{
		// HOOKS LAW!
		glm::vec3 sep = NodeB->Position - NodeA->Position;
		float dist = glm::length(sep);
		float x = glm::abs(dist - RestingLength);
		SpringForceAtoB = glm::normalize(sep) * x * SpringConstant;
	}
	void cSoftBody::cSpring::ApplyForceToNodes()
	{
		if (!NodeB->IsFixed())
		{
			NodeB->Acceleration += SpringForceAtoB / NodeB->Mass;
		}
		if (!NodeA->IsFixed())
		{
			NodeA->Acceleration -= SpringForceAtoB / NodeA->Mass;
		}
		
	}
	cSoftBody::cNode::cNode(const sSoftBodyNodeDef& nodeDef) : Position(nodeDef.Position), Mass(nodeDef.Mass), Velocity(0.0f,0.0f,0.0f), Acceleration(0.0f,0.0f,0.0f), Radius(1.0f)
	{

	}
	cSoftBody::cNode* cSoftBody::cSpring::GetOther(cNode* node)
	{
		return node == NodeA ? NodeB : NodeA;
	}
	void cSoftBody::cNode::CalculateRadius()
	{

		float smallestDistance = std::numeric_limits<float>::max();
		size_t numNeighbors = this->Springs.size();
		for (size_t idx = 0; idx < numNeighbors; idx++)
		{
			// is this the smallest distance?
			float dist = glm::distance(Springs[idx]->GetOther(this)->Position, Position);
			if (dist < smallestDistance)
			{
				smallestDistance = dist;
			}
		}
		Radius = smallestDistance * 0.5f; // TODO: tweak this value, maybe make it a constant somewhere?
	}
	cSoftBody::cSoftBody(const sSoftBodyDef& def)
	{
		size_t numNodes = def.Nodes.size();
		mNodes.resize(numNodes);
		for (size_t idx = 0; idx < numNodes; idx++)
		{
			mNodes[idx] = new cNode(def.Nodes[idx]);
		}
		size_t numSprings = def.Springs.size();
		mSprings.resize(numSprings);
		for (size_t idx = 0; idx < numSprings; idx++)
		{
			mSprings[idx] = new cSpring(mNodes[def.Springs[idx].first], mNodes[def.Springs[idx].second], def.SpringConstant);
		}
	}
	cSoftBody::~cSoftBody()
	{
		size_t numNodes = mNodes.size();
		for (size_t idx = 0; idx < numNodes; idx++)
		{
			delete mNodes[idx];
		}
		mNodes.clear();
		size_t numSprings = mSprings.size();
		for (size_t idx = 0; idx < numSprings; idx++)
		{
			delete mSprings[idx];
		}
	}
	size_t cSoftBody::NumNodes()
	{
		return mNodes.size();
	}
	bool cSoftBody::GetNodeRadius(size_t index, float& radiusOut)
	{
		if (index >= mNodes.size())
			return false;
		radiusOut = mNodes[index]->Radius;
		return true;
	}
	bool cSoftBody::GetNodePosition(size_t index, glm::vec3& positionOut)
	{
		if (index >= mNodes.size())
			return false;
		positionOut = mNodes[index]->Position;
		return true;
	}
	void cSoftBody::IntegrateNode(cNode* node)
	{

	}
}