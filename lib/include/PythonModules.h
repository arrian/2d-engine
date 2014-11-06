#pragma once

#include <boost/python.hpp>
using namespace boost;

#include <Polycode.h>
using namespace Polycode;

#include "GameCore.h"
#include "WorldManager.h"
#include "ScriptManager.h"
#include "SettingsManager.h"

// Polycode Bindings

BOOST_PYTHON_MODULE(core_services) {
  class_<CoreServices>("CoreServices", boost::python::no_init)
  	.def("get_renderer", &CoreServices::getRenderer)
  	.def("install_module", &CoreServices::installModule)
  	.def("get_material_manager", &CoreServices::getMaterialManager)
  	.def("get_screen_manager", &CoreServices::getScreenManager)
  	.def("get_scene_manager", &CoreServices::getSceneManager)
  	.def("get_timer_manager", &CoreServices::getTimerManager)
  	.def("get_tween_manager", &CoreServices::getTweenManager)
  	.def("get_resource_manager", &CoreServices::getResourceManager)
  	.def("get_sound_manager", &CoreServices::getSoundManager)
  	.def("get_font_manager", &CoreServices::getFontManager)
  	.def("get_logger", &CoreServices::getLogger)
  	.def("get_config", &CoreServices::getConfig);
}

BOOST_PYTHON_MODULE(core) {
  class_<Core>("Core", boost::python::no_init)
  	.def("enable_mouse", &Core::enableMouse)
  	.def("capture_mouse", &Core::captureMouse)
  	.def("set_cursor", &Core::setCursor)
  	.def("warp_cursor", &Core::warpCursor)
  	.def("copy_string_to_clipboard", &Core::copyStringToClipboard)
  	.def("create_folder", &Core::createFolder)
  	.def("set_video_mode", &Core::setVideoMode)
  	.def("resize_to", &Core::resizeTo)
  	.def("open_url", &Core::openURL)
  	.def("get_clipboard_string", &Core::getClipboardString)
  	.def("get_services", &Core::getServices)
  	.def("get_fps", &Core::getFPS)
  	.def("is_fullscreen", &Core::isFullscreen)
  	.def("get_a_a_level", &Core::getAALevel)
  	.def("get_input", &Core::getInput)
  	.def("get_x_res", &Core::getXRes)
  	.def("get_y_res", &Core::getYRes)
  	.def("get_video_modes", &Core::getVideoModes)
  	.def("open_folder_picker", &Core::openFolderPicker)
  	.def("get_elapsed", &Core::getElapsed)
  	.def("get_ticks", &Core::getTicks)
  	.def("get_ticks_float", &Core::getTicksFloat)
  	.def("get_default_working_directory", &Core::getDefaultWorkingDirectory)
  	.def("get_user_home_directory", &Core::getUserHomeDirectory);
}

// Game Bindings

BOOST_PYTHON_MODULE(world_manager) {
  class_<WorldManager, boost::shared_ptr<WorldManager> >("WorldManager", boost::python::no_init)
    .def("update", &WorldManager::update);
}

BOOST_PYTHON_MODULE(settings_manager) {
  class_<SettingsManager, boost::shared_ptr<SettingsManager> >("SettingsManager", boost::python::no_init)
    .def("get_value", &SettingsManager::getScriptManager)
    .def("set_value", &SettingsManager::getSettingsManager);
}

BOOST_PYTHON_MODULE(script_manager) {
  class_<ScriptManager, boost::shared_ptr<ScriptManager> >("ScriptManager", boost::python::no_init)
    .def("import", &ScriptManager::import)
    .def("run", &ScriptManager::run);
}

BOOST_PYTHON_MODULE(game_core) {
  class_<GameCore, boost::shared_ptr<GameCore> >("GameCore", boost::python::no_init)
  	.def("get_core", &GameCore::getCore)
    .def("get_script_manager", &GameCore::getScriptManager)
    .def("get_settings_manager", &GameCore::getSettingsManager)
    .def("get_world_manager", &GameCore::getWorldManager);
}



