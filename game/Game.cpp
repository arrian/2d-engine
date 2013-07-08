#include "Game.h"

/*
WorldPosition toW(Display* display, std::string test, ScreenPosition p)
{
  WorldPosition wp(display->getWorldPosition(p));
  std::cout << test << ": " << wp.x << "," << wp.y << "," << wp.xCell << "," << wp.yCell << std::endl; 
  return wp;
}

ScreenPosition toS(Display* display, std::string test, WorldPosition p)
{
  ScreenPosition sp(display->getScreenPosition(p));
  std::cout << test << ": " << sp.x << "," << sp.y << std::endl; 
  return sp;
}

void testCoordSystem(Display* display)
{
  toS(display, "to screen", toW(display, "to world", ScreenPosition(0,0)));
  std::cout << "--------------" << std::endl;
  toS(display, "to screen", toW(display, "to world", ScreenPosition(100,100)));
  std::cout << "--------------" << std::endl;
  toS(display, "to screen", toW(display, "to world", ScreenPosition(-100,-100)));
  std::cout << "--------------" << std::endl;
  toS(display, "to screen", toW(display, "to world", ScreenPosition(CELL_SIZE+1,CELL_SIZE+1)));
  std::cout << "--------------" << std::endl;
  toW(display, "to world", toS(display, "to screen", WorldPosition(0,0,-4,3)));
  std::cout << "--------------" << std::endl;
    toW(display, "to world", toS(display, "to screen", WorldPosition(CELL_SIZE,CELL_SIZE,-4,3)));
  std::cout << "--------------" << std::endl;


}
*/


Game::Game(bool fullscreen)
  : display(NULL),
  event_queue(NULL),
  timer(NULL),
  redraw(false),
  world(FileUtil::getWorldFile(), FileUtil::getDataFile()),
  minusPressed(false)
{

  if(!al_init()) throw std::exception("Failed to initialise allegro.");

  timer = al_create_timer(SECONDS_PER_FRAME);
  if(!timer) throw std::exception("Failed to create timer.");

  al_init_image_addon();
  al_init_primitives_addon();


  int width = DEFAULT_WIDTH;
  int height = DEFAULT_HEIGHT;

  if(fullscreen)
  {
    ALLEGRO_DISPLAY_MODE disp_data;

    al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    width = disp_data.width;
    height = disp_data.height;
  }

  {//enable AA
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

  }

  display = al_create_display(width, height);
  if(!display) 
  {
    al_destroy_timer(timer);
    throw std::exception("Failed to create display.");
    
  }

  {//check if AA enabled
    if(al_get_display_option(display, ALLEGRO_SAMPLE_BUFFERS)) 
    {
      printf("With multisampling, level %i\n",
      al_get_display_option(display, ALLEGRO_SAMPLES));
    }
    else 
    {
      printf("Without multisampling.\n");
    }
  }

  _display = new Display(display);
  //testCoordSystem(_display);

  al_set_window_title(display, TITLE);

  event_queue = al_create_event_queue();
  if(!event_queue) 
  {
    al_destroy_display(display);
    al_destroy_timer(timer);
    throw std::exception("Failed to create event queue.");
  }

  
  WorldPosition tl(_display->getScreenTopLeftWorldPosition());
  WorldPosition br(_display->getScreenBottomRightWorldPosition());


  std::cout << _display->getScreenPosition(tl).x << "," << _display->getScreenPosition(tl).y << "," <<  tl.xCell << std::endl;
  //load all needed cells
  for(int i = _display->getXMinCell(); i <= _display->getXMaxCell(); i++)
  {
    
    for(int j = _display->getYMinCell(); j <= _display->getYMaxCell(); j++)
    {
      std::cout << "loading " << i << "," << j << std::endl;
      

      if(i == 0 && j == 0) cell = world.loadCell(i,j);
      else world.loadCell(i,j);
    }
  }

  //need to check results here
  al_install_keyboard();
  al_install_mouse();

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_mouse_event_source());
  al_register_event_source(event_queue, al_get_keyboard_event_source());

  al_clear_to_color(al_map_rgb(DEFAULT_CLEAR_COLOUR));
  al_flip_display();
}

Game::~Game(void)
{
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_timer(timer);

  delete _display;
}

void Game::run()
{
  al_start_timer(timer);

  while(true)
  {
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);

    if(ev.type == ALLEGRO_EVENT_TIMER) 
    {
      redraw = true;
    }
    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
    {
      break;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
      //std::cout << "got down key" << std::endl;
      if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE) world.getPlayer()->jump();
      else if(ev.keyboard.keycode == ALLEGRO_KEY_LEFT) world.getPlayer()->setMovingLeft(true);
      else if(ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) world.getPlayer()->setMovingRight(true);
      else if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;
      else if(ev.keyboard.keycode == ALLEGRO_KEY_MINUS) minusPressed = true;
      else cell->addRectangle(world.getPlayer()->getPosition());
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
      if(ev.keyboard.keycode == ALLEGRO_KEY_MINUS) minusPressed = false;
      else if(ev.keyboard.keycode == ALLEGRO_KEY_LEFT) world.getPlayer()->setMovingLeft(false);
      else if(ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) world.getPlayer()->setMovingRight(false);
    }
    else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
    }
    else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
    }
    
    

    if(redraw && al_is_event_queue_empty(event_queue)) 
    {
      redraw = false;
      update(SECONDS_PER_FRAME);
      draw();
    }
  }
}

void Game::draw()
{
  al_flip_display();
  
  al_clear_to_color(al_map_rgb(DEFAULT_CLEAR_COLOUR));
  world.draw(_display);

  
}

void Game::update(double elapsedSeconds)
{
  if(minusPressed) _display->setWorldScale(_display->getWorldScale() - elapsedSeconds);
  _display->setDisplayCentre(world.getPlayer()->getPosition());
  world.update(elapsedSeconds);
}

int main(int argc, char **argv)
{
  try 
  {
    Game game(false);
    game.run();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return -1;
  }
  catch(...)
  {
    std::cerr << "An unknown error occurred." << std::endl;
    return -1;
  }
  return 0;
}

