#include "Game.h"

Game::Game(bool fullscreen)
  : display(NULL),
  event_queue(NULL),
  timer(NULL),
  redraw(false),
  world(FileUtil::getWorldFile(), FileUtil::getDataFile()),
  minusPressed(false),
  debugFont(NULL)
{

  if(!al_init()) throw std::runtime_error("Failed to initialise allegro.");

  timer = al_create_timer(SECONDS_PER_FRAME);
  if(!timer) throw std::runtime_error("Failed to create timer.");

  al_init_image_addon();
  al_init_primitives_addon();
  al_init_font_addon();
  al_init_ttf_addon();


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
    throw std::runtime_error("Failed to create display.");
    
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

  al_set_window_title(display, TITLE.c_str());

  event_queue = al_create_event_queue();
  if(!event_queue) 
  {
    al_destroy_display(display);
    al_destroy_timer(timer);
    throw std::runtime_error("Failed to create event queue.");
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


  debugFont = FontUtil::acquire(DEBUG_FONT);
  
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
  FontUtil::release(DEBUG_FONT);

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
  
  
  al_clear_to_color(al_map_rgb(DEFAULT_CLEAR_COLOUR));
  world.draw(_display);

#ifdef _DEBUG
  al_draw_text(debugFont, al_map_rgb(255,255,255), 0.0f, 0.0f, 0, VERSION.c_str());
#endif

  al_flip_display();
  
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
    //throw FactoryException("This is a message.");
    Game game(false);
    game.run();
  }
  catch(const FactoryException& e)
  {
    #ifdef _WIN32
    MessageBoxA(0, e.what(), "Error", MB_OK | MB_ICONERROR);
    #else
    std::cerr << "Error" << e.what() << std::endl;
    #endif
  }
  catch(const std::exception& e)
  {
    std::string error("An exception occurred. " + std::string(e.what()));
    #ifdef _WIN32
    MessageBoxA(0, error.c_str(), "Error", MB_OK | MB_ICONERROR);
    #else
    std::cerr << "Error" << error.c_str() << std::endl;
    #endif
    return -1;
  }
  catch(...)
  {
    #ifdef _WIN32
    MessageBoxA(0, "An unknown exception occurred.", "Error", MB_OK | MB_ICONERROR);
    #else
    std::cerr << "An unknown exception occurred." << std::endl; 
    #endif
    //std::cerr << "An unknown error occurred." << std::endl;
    return -1;
  }
  return 0;
}

