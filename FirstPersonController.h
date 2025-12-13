#pragma once

#include "Ogre.h"
#include "OgreInput.h"

using namespace Ogre;
using namespace OgreBites;

class FirstPersonController : public InputListener
{
private:
	Camera* mCamera;
	SceneNode* mCameraNode; // The node that the camera is attached to
	SceneNode* mCameraParentNode; // The node that moves (the player's body)

    float mMoveSpeed;
	float mRunSpeed;
	float mCurrentSpeed;
    float mMouseSensitivity;
	float mMaxPitch;
	float mMinPitch;
    Vector3 mMovementDirection;
    float mYaw;
    float mPitch;
public:
	FirstPersonController(Camera* camera, SceneNode* cameraNode, SceneNode* cameraParentNode);
	virtual ~FirstPersonController();

	void setupCamera();
	void update(const FrameEvent& evt);

	virtual bool keyPressed(const KeyboardEvent& evt) override;
	virtual bool keyReleased(const KeyboardEvent& evt) override;
	virtual bool mouseMoved(const MouseMotionEvent& evt) override;
    virtual bool mousePressed(const MouseButtonEvent& evt) override;
    virtual bool mouseReleased(const MouseButtonEvent& evt) override;

    void setMoveSpeed(float speed) { mMoveSpeed = speed; }
	void setRunSpeed(float speed) { mRunSpeed = speed; }
    void setMouseSensitivity(float sensitivity) { mMouseSensitivity = sensitivity; }
	void setPitchLimits(float minDegree, float maxDegree) 
	{ 
		mMinPitch = Math::DegreesToRadians(minDegree); 
		mMaxPitch = Math::DegreesToRadians(maxDegree); 
	}
};