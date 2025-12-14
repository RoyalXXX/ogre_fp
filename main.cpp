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

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "FirstPersonController.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;


class MyAppContext : public ApplicationContext
{
public:
    MyAppContext() : ApplicationContext("OGRE 3D App")
    {
		mFSLayer->setHomePath("");
        mFSLayer->removeDirectory(std::string(getenv("USERPROFILE")) +
            "/Documents/OGRE 3D App");
    }
};

class BasicTutorial
    : public MyAppContext
    , public InputListener
{
private:
	FirstPersonController* mFPController = nullptr;
public:
    BasicTutorial() : MyAppContext() {}
    virtual ~BasicTutorial() 
    {
		if (mFPController)
			delete mFPController;
    }

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    bool frameRenderingQueued(const FrameEvent& evt);
};


void BasicTutorial::setup()
{
    
    ApplicationContext::setup();
    addInputListener(this);


    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();


    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);


	// First Person Controller setup
	setWindowGrab(); // Grab mouse cursor
	SceneNode* CharacterNode = scnMgr->getRootSceneNode()->createChildSceneNode("CharacterNode");
	Camera* camera = scnMgr->createCamera("Camera");
	Viewport* vp = getRenderWindow()->addViewport(camera);
	mFPController = new FirstPersonController(camera, CharacterNode);
	addInputListener(mFPController);
	CharacterNode->setPosition(0, 0, 10); // initial position of the Player
	// End First Person Controller setup


    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_TEXTURE_ADDITIVE);
	//scnMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox", 300);
	scnMgr->setSkyDome(true, "Examples/CloudySky", 5, 8, 300);
	Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
	scnMgr->setFog(Ogre::FOG_EXP, fadeColour, 0.002);


    Plane plane(Vector3::UNIT_Y, 0);

    MeshManager::getSingleton().createPlane(
        "ground", RGN_DEFAULT,
        plane,
		100, 100, // width, height
		10, 10, // x- and y-segments
		true, // normals
		1, // num texture sets
		10, 10, // u- and v-tiles
        Vector3::UNIT_Z);

    Entity* groundEntity = scnMgr->createEntity("ground");
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/GrassFloor");
   

    Light* directionalLight = scnMgr->createLight("DirectionalLight");
    directionalLight->setType(Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(ColourValue(1, 1, 1));
    directionalLight->setSpecularColour(ColourValue(1, 1, 1));
	directionalLight->setPowerScale(1.0f);
    
    
    SceneNode* directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    directionalLightNode->attachObject(directionalLight);
    directionalLightNode->setDirection(Vector3(1, -0.5, -1));
    
}

bool BasicTutorial::frameRenderingQueued(const FrameEvent& evt)
{
    if (mFPController)
        mFPController->update(evt);

    return true;
}

bool BasicTutorial::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
        getRoot()->queueEndRendering();
    return true;
}


int main(int argc, char** argv)
{
    try
    {
        BasicTutorial app;
        app.initApp();
        Ogre::Root* root = app.getRoot();
        root->addFrameListener(&app);
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;

}



