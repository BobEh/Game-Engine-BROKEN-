#include "cRigidBody.h"  // My header
#include <glm/gtc/matrix_transform.hpp>

namespace phys
{
	sRigidBodyDef::sRigidBodyDef() : Mass(0.0f), Position(glm::vec3(0.0f, 0.0f, 0.0f)), Velocity(glm::vec3(0.0f, 0.0f, 0.0f))
	{

	} 
	cRigidBody::cRigidBody(const sRigidBodyDef& def, iShape* shape) : mShape(shape), mPosition(def.Position), mVelocity(def.Velocity), mMass(def.Mass)
	{
		if (mMass == 0.0f)
		{
			mInvMass = 0.0f;
		}
		else
		{
			mInvMass = 1.f / mMass;
		}
	}

	int cRigidBody::GetMassType()
	{
		return 1;
	}
	void cRigidBody::SetMassType(int physicsType)
	{

	}

	cRigidBody::~cRigidBody()
	{
		delete this;
	}

	void cRigidBody::GetTransform(glm::mat4& transformOut)
	{
		transformOut = glm::mat4(1.0f);
		// rotations
		// translate is in gtx
		transformOut = glm::translate(transformOut, mPosition);
	}

	void cRigidBody::ApplyForce(const glm::vec3& force)
	{
		// TODO: Apply the force to this rigid body's acceleration
		//       Remember... F=ma  ...so an applied acceleration will be f/m
		mAcceleration += force / mInvMass;
	}
	void cRigidBody::GetPosition(glm::vec3& positionOut)
	{
		positionOut = this->mPosition;
	}
	void cRigidBody::SetPosition(glm::vec3 positionIn)
	{
	}
	void cRigidBody::GetVelocity(glm::vec3& velocityOut)
	{
	}
	std::string cRigidBody::GetPlaneType()
	{
		return std::string();
	}
}
