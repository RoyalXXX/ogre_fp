#include "FirstPersonController.h"

FirstPersonController::FirstPersonController(Camera* camera, SceneNode* cameraNode, SceneNode* cameraNodeParent)
	: mCamera(camera)
	, mCameraNode(cameraNode)
	, mCameraParentNode(cameraNodeParent)
	, mMoveSpeed(5.0f)
	, mRunSpeed(10.0f)
	, mCurrentSpeed(5.0f)
	, mMouseSensitivity(0.1f)
	, mMaxPitch(Math::HALF_PI - 0.1f) // 0.1 radian margin to avoid gimbal lock
	, mMinPitch(-Math::HALF_PI + 0.1f) // 0.1 radian margin to avoid gimbal lock
	, mYaw(0.0f)
	, mPitch(0.0f)
{
	setupCamera();
}
FirstPersonController::~FirstPersonController()
{
}

void FirstPersonController::setupCamera()
{
	mCamera->setNearClipDistance(0.1f);
	mCamera->setFarClipDistance(1000.0f);
	mCamera->setAutoAspectRatio(true);

	mMovementDirection = Vector3::ZERO;
}

void FirstPersonController::update(const FrameEvent& evt)
{
	if (mMovementDirection != Vector3::ZERO)
	{
		Vector3 direction = mMovementDirection;
		direction.normalise();

		Vector3 moveDir = mCameraParentNode->getOrientation() * direction;

		mCameraParentNode->translate(
			moveDir * mCurrentSpeed * evt.timeSinceLastFrame,
			Node::TransformSpace::TS_WORLD
		);
	}
}
bool FirstPersonController::keyPressed(const KeyboardEvent& evt)
{
	Keycode key = evt.keysym.sym;

	if (key == 'w') mMovementDirection.z = -1;
	if (key == 's') mMovementDirection.z = 1;
	if (key == 'a') mMovementDirection.x = -1;
	if (key == 'd') mMovementDirection.x = 1;

	if (key == SDLK_LSHIFT)
	{
		mCurrentSpeed = mRunSpeed;
	}

	return true;
}
bool FirstPersonController::keyReleased(const KeyboardEvent& evt)
{
	Keycode key = evt.keysym.sym;
	

	if (key == 'w') mMovementDirection.z = 0;
	if (key == 's') mMovementDirection.z = 0;
	if (key == 'a') mMovementDirection.x = 0;
	if (key == 'd') mMovementDirection.x = 0;

	if (evt.keysym.sym == SDLK_LSHIFT)
	{
		mCurrentSpeed = mMoveSpeed;
	}

	return true;
}

bool FirstPersonController::mouseMoved(const MouseMotionEvent& evt)
{
	
	mYaw += -evt.xrel * mMouseSensitivity * 0.01f;
	mPitch += -evt.yrel * mMouseSensitivity * 0.01f;

	mPitch = std::max(mMinPitch, std::min(mMaxPitch, mPitch));
	
	mCameraParentNode->resetOrientation();
	mCameraParentNode->yaw(Radian(mYaw), Node::TransformSpace::TS_WORLD);

	mCameraNode->resetOrientation();
	mCameraNode->pitch(Radian(mPitch), Node::TransformSpace::TS_LOCAL);

	return true;
}

bool FirstPersonController::mousePressed(const MouseButtonEvent& evt)
{
	// Implement if needed
	return true;
}

bool FirstPersonController::mouseReleased(const MouseButtonEvent& evt)
{
	// Implement if needed
	return true;
}