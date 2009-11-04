#ifndef B2_FRICTION_JOINT_H
#define B2_FRICTION_JOINT_H

#include "b2Joint.h"

/// FrictionJoint: Attaches two bodies rigidly together
struct b2FrictionJointDef : public b2JointDef
{
	b2FrictionJointDef()
	{
		type = e_frictionJoint;
	}

	b2Vec2 frictionForce;

	/// Initialize the bodies.
	void Initialize(b2Body* body1);
};

/// A friction joint constrains all degrees of freedom between two bodies
/// Author: Jorrit Rouwe
/// See: www.jrouwe.nl/frictionjoint/ for more info
class b2FrictionJoint : public b2Joint
{
public:

	b2Vec2 GetReactionForce(float32 inv_dt) const;
	float32 GetReactionTorque(float32 inv_dt) const;

	b2Vec2 GetAnchor1() const;
	b2Vec2 GetAnchor2() const;


	//--------------- Internals Below -------------------

	b2FrictionJoint(const b2FrictionJointDef* data);

	void InitVelocityConstraints(const b2TimeStep& step);
	void SolveVelocityConstraints(const b2TimeStep& step);
	bool SolvePositionConstraints(float32 baumgarte);

	b2Vec2 m_frictionForce;

	// Initial state of the bodies
	b2Vec2 m_dp;	//< Distance between body->GetXForm().position between the two bodies at rest in the reference frame of body1
	//float32 m_a;	//< Angle between the bodies at rest
	//b2Mat22 m_R0;	//< Rotation matrix of m_a

	// Distance between center of masses for this time step (when the shapes of the bodies change, their local canters can change so we derive this from m_dp every frame)
	b2Vec2 m_d;		//< Distance between center of masses for both bodies at rest in the reference frame of body1

	// Effective mass and inertia for angle constraint
	float32 m_mass;
	float32 m_inertia;

	// Accumulated impulse for warm starting and returning the constraint force/torque
	float32 m_lambda_a;
	b2Vec2 m_lambda_p;
	float32 m_lambda_p_a;

};

#endif
