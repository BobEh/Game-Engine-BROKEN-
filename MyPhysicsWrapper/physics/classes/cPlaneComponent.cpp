#include "cPlaneComponent.h"

nPhysics::cPlaneComponent::~cPlaneComponent()
{
}

void nPhysics::cPlaneComponent::GetTransform(glm::mat4& transformOut)
{
	mBody->GetTransform(transformOut);
}

void nPhysics::cPlaneComponent::GetPosition(glm::vec3& positionOut)
{
	positionOut = position;
}

void nPhysics::cPlaneComponent::SetPosition(glm::vec3 positionIn)
{
	position = positionIn;
}

void nPhysics::cPlaneComponent::GetVelocity(glm::vec3& velocityOut)
{
	velocityOut = velocity;
}

int nPhysics::cPlaneComponent::GetMassType()
{
	return _physicsType;
}

void nPhysics::cPlaneComponent::SetMassType(int physicsType)
{
	_physicsType = physicsType;
}

std::string nPhysics::cPlaneComponent::GetPlaneType()
{
	return planeType;
}

nPhysics::cPlaneComponent::cPlaneComponent(nPhysics::sPlaneDef thePlaneDef)
{
	phys::sRigidBodyDef physDef;
	physDef.Position = thePlaneDef.Position;
	physDef.Mass = thePlaneDef.Mass;
	physDef.Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	phys::iShape* shape = new phys::cPlane(thePlaneDef.Normal, thePlaneDef.Constant);
	mBody = new phys::cRigidBody(physDef, shape);
}