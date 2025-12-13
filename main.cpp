#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

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
	SceneNode* FPBodyNode = scnMgr->getRootSceneNode()->createChildSceneNode("FPBodyNode");
	SceneNode* camNode = FPBodyNode->createChildSceneNode("CameraNode");
	camNode->setPosition(0, 2, 0); // Eye level
    Camera* cam = scnMgr->createCamera("Camera");
    camNode->attachObject(cam);
    mFPController = new FirstPersonController(cam, camNode, FPBodyNode);
    addInputListener(mFPController);
	FPBodyNode->setPosition(0, 0, 10); // initial position of the Player
	// End First Person Controller setup


    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(ColourValue(0.7, 0.8, 0.9));
    cam->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));


    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_TEXTURE_ADDITIVE);



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
    
    
    Entity* treeEntity = scnMgr->createEntity("SnowyPineTree", "SnowyPineTree.mesh");
	treeEntity->setCastShadows(true);
	SceneNode* treeNode = scnMgr->getRootSceneNode()->createChildSceneNode("SnowyPineTreeNode");
	treeNode->attachObject(treeEntity);
    treeNode->setPosition(0, 0, 0);
	treeNode->setScale(0.05f, 0.05f, 0.05f);
    

    
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

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char** argv)
#endif
{
    try
    {
        Ogre::LogManager* logManager = new Ogre::LogManager();
		logManager->createLog("Ogre.log", true, false, false);
        
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