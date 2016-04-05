#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

std::vector<RVO::Vector2> goals;
std::vector<Sprite*> sprite;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
    RVOinit();
    
    scheduleUpdate();

    return true;
}


bool HelloWorld::RVOinit()
{
    
	mSim = new RVO::RVOSimulator();
    
    mSim->setTimeStep(0.25f);
    
    /* Specify the default parameters for agents that are subsequently added. */
    mSim->setAgentDefaults(15.0f, 10, 10.0f, 10.0f, 1.5f, 2.0f);
    
    /*
     * Add agents, specifying their start position, and store their goals on the
     * opposite side of the environment.
     */
    
    setPosition(Vec2(300,300));
    for (size_t i = 0; i < 250; ++i) {
        mSim->addAgent(200.0f *
                      RVO::Vector2(std::cos(i * 2.0f * M_PI / 250.0f),
                                   std::sin(i * 2.0f * M_PI / 250.0f)));
        auto pos = mSim->getAgentPosition(i);
        goals.push_back(-pos);
        sprite.push_back(Sprite::create("a.png"));
        sprite[i]->setPosition(Vec2(pos.x(), pos.y()));
        sprite[i]->setScale(0.05f);
        this->addChild(sprite[i]);
    }
    
    
    return true;
}



bool HelloWorld::reachedGoal()
{
    /* Check if all agents have reached their goals. */
    for (size_t i = 0; i < mSim->getNumAgents(); ++i) {
        if (RVO::absSq(mSim->getAgentPosition(i) - goals[i]) > mSim->getAgentRadius(i) * mSim->getAgentRadius(i)) {
            return false;
        }
    }
    
    return true;
}



void HelloWorld::update(float delta)
{
    
    auto count = mSim->getNumAgents();
    /* Output the current position of all the agents. */
    for (size_t i = 0; i < mSim->getNumAgents(); ++i) {
        auto pos = mSim->getAgentPosition(i);
        sprite[i]->setPosition(Vec2(pos.x(), pos.y()));
    }
    
    
    
    
    for (int i = 0; i < static_cast<int>(mSim->getNumAgents()); ++i) {
        RVO::Vector2 goalVector = goals[i] - mSim->getAgentPosition(i);
        
        if (RVO::absSq(goalVector) > 1.0f) {
            goalVector = RVO::normalize(goalVector);
        }
        
		mSim->setAgentPrefVelocity(i, goalVector);
    }
    
    
    mSim->doStep();
    
    
    if(reachedGoal())
    {
        delete mSim;
    }
    
}






