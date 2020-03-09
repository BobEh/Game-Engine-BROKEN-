#pragma once
#include <physics/interfaces/iClothComponent.h>
#include "cPhysicsComponent.h"
#include <string>
#include <phys\cRigidBody.h>
#include <phys/shapes.h>
using namespace phys;

namespace nPhysics
{
	class cClothComponent : public iClothComponent
	{
	public:
		cClothComponent(nPhysics::sClothDef theBallDef);
		~cClothComponent();

		virtual void GetTransform(glm::mat4& transformOut);
		virtual size_t NumNodes();
		virtual void GetPosition(glm::vec3& positionOut);
		virtual void SetPosition(glm::vec3 positionIn);
		virtual void GetVelocity(glm::vec3& velocityOut);
		virtual int GetMassType();
		virtual void SetMassType(int physicsType);
		virtual std::string GetPlaneType();
		cRigidBody* mBody;
	private:

		glm::mat4 transform;
		glm::vec3 position;
		glm::vec3 velocity;
		std::string planeType;
		int _physicsType;
	};
}