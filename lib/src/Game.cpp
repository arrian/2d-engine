#include "Game.h"

Game::Game()
{
  core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

  CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
  CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

  Scene *scene = new Scene(Scene::SCENE_2D);
  scene->getDefaultCamera()->setOrthoSize(640, 480);
  image = new SceneImage("Resources/polycode_logo.png");
  scene->addChild(image);
}

Game::~Game(void)
{

}

bool Game::update()
{
  std::cout << "updating" << std::endl;

  return core->updateAndRender();
}

void HelloPolycodeApp::handleEvent(Event *e)
{

}

int main(int argc, char **argv)
{
  try 
  {
    Game game;
    game.run();
  }
  catch(const std::exception& e)
  {
    std::string error("An exception occurred. " + std::string(e.what()));
    std::cerr << "Error" << error.c_str() << std::endl;
    return -1;
  }
  catch(...)
  {
    std::cerr << "An unknown exception occurred." << std::endl; 
    return -1;
  }
  return 0;
}

