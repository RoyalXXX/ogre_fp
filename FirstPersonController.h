/*
	Ogre First Person Controller
	
	Copyright (c) 2025 Royal_X (MIT License)
 
 	https://github.com/RoyalXXX
  	https://royalxxx.itch.io
   	https://sourceforge.net/u/royal-x
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

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
	SceneNode* mCharacterNode; // The node that moves (the player's body)

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
	FirstPersonController(Camera* camera, SceneNode* characterNode);
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
