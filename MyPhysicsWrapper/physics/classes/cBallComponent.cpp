#include "cBallComponent.h"

nPhysics::cBallComponent::~cBallComponent()
{
}

void nPhysics::cBallComponent::GetTransform(glm::mat4& transformOut)
{
	mBody->GetTransform(transformOut);
}

void nPhysics::cBallComponent::GetPosition(glm::vec3& positionOut)
{
	positionOut = position;
}

void nPhysics::cBallComponent::SetPosition(glm::vec3 positionIn)
{
	position = positionIn;
}

void nPhysics::cBallComponent::GetVelocity(glm::vec3& velocityOut)
{
	velocityOut = velocity;
}

int nPhysics::cBallComponent::GetMassType()
{
	return _physicsType;
}

void nPhysics::cBallComponent::SetMassType(int physicsType)
{
	_physicsType = physicsType;
}

std::string nPhysics::cBallComponent::GetPlaneType()
{
	return planeType;
}

nPhysics::cBallComponent::cBallComponent(nPhysics::sBallDef theBallDef)
{
	phys::sRigidBodyDef physDef;
	physDef.Position = theBallDef.Position;
	physDef.Mass = theBallDef.Mass;
	physDef.Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	phys::iShape* shape = new phys::cSphere(theBallDef.Radius);
	mBody = new phys::cRigidBody(physDef, shape);
	
}
