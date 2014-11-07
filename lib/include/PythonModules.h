#pragma once

#include "Util.h"

#include <Polycode.h>
#include "PolyCoreServices.h"
#include "PolyModule.h"

#include "PolyMaterialManager.h"
#include "PolySceneManager.h"
#include "PolyTimerManager.h"
#include "PolyTweenManager.h"
#include "PolyResourceManager.h"
#include "PolySoundManager.h"
#include "PolyFontManager.h"
#include "PolyLogger.h"
#include "PolyConfig.h"


#include "GameCore.h"
#include "WorldManager.h"
#include "ScriptManager.h"
#include "SettingsManager.h"

#include "Interpreter.h"
#include "Channel.h"

// Polycode Bindings

BOOST_PYTHON_MODULE(core_services) {
  python::class_<CoreServices, noncopyable>("CoreServices", python::no_init)
  	.def("get_renderer", &CoreServices::getRenderer, python::return_value_policy<python::reference_existing_object>())
  	.def("install_module", &CoreServices::installModule)
  	.def("get_material_manager", &CoreServices::getMaterialManager, python::return_value_policy<python::reference_existing_object>())
  	.def("get_scene_manager", &CoreServices::getSceneManager, python::return_value_policy<python::reference_existing_object>())
  	.def("get_timer_manager", &CoreServices::getTimerManager, python::return_value_policy<python::reference_existing_object>())
  	.def("get_tween_manager", &CoreServices::getTweenManager, python::return_value_policy<python::reference_existing_object>())
  	.def("get_resource_manager", &CoreServices::getResourceManager, python::return_value_policy<python::reference_existing_object>())
  	.def("get_sound_manager", &CoreServices::getSoundManager, python::return_value_policy<python::reference_existing_object>())
  	.def("get_font_manager", &CoreServices::getFontManager, python::return_value_policy<python::reference_existing_object>())
  	.def("get_logger", &CoreServices::getLogger, python::return_value_policy<python::reference_existing_object>())
  	.def("get_config", &CoreServices::getConfig, python::return_value_policy<python::reference_existing_object>());
}

BOOST_PYTHON_MODULE(core) {
  python::class_<Core, noncopyable>("Core", python::no_init)
  	.def("enable_mouse", &Core::enableMouse)
  	.def("capture_mouse", &Core::captureMouse)
  	.def("set_cursor", &Core::setCursor)
  	.def("warp_cursor", &Core::warpCursor)
    .def("copy_string_to_clipboard", &Core::copyStringToClipboard)
  	.def("get_clipboard_string", &Core::getClipboardString)
    .def("create_folder", &Core::createFolder)
  	.def("set_video_mode", &Core::setVideoMode)
  	.def("resize_to", &Core::resizeTo)
  	.def("open_url", &Core::openURL)
  	.def("get_services", &Core::getServices, python::return_value_policy<python::reference_existing_object>())
  	.def("get_fps", &Core::getFPS)
  	.def("is_fullscreen", &Core::isFullscreen)
  	.def("get_aa_level", &Core::getAALevel)
  	.def("get_input", &Core::getInput, python::return_value_policy<python::reference_existing_object>())
    .def("get_x_res", &Core::getXRes)
    .def("get_y_res", &Core::getYRes)
    .def("get_screen_width", &Core::getScreenWidth)
    .def("get_screen_height", &Core::getScreenHeight)
  	.def("open_folder_picker", &Core::openFolderPicker)
  	.def("get_elapsed", &Core::getElapsed)
  	.def("get_ticks", &Core::getTicks)
  	.def("get_ticks_float", &Core::getTicksFloat)
  	.def("get_default_working_directory", &Core::getDefaultWorkingDirectory)
  	.def("get_user_home_directory", &Core::getUserHomeDirectory);
}

// Game Bindings

BOOST_PYTHON_MODULE(world_manager) {
  python::class_<WorldManager, shared_ptr<WorldManager>, noncopyable>("WorldManager", python::no_init)
    .def("update", &WorldManager::update);
}

BOOST_PYTHON_MODULE(settings_manager) {
  python::class_<SettingsManager, shared_ptr<SettingsManager>, noncopyable>("SettingsManager", python::no_init)
    .def("get_value", &SettingsManager::getValue<int>)
    .def("set_value", &SettingsManager::setValue<int>)
    .def("get_value", &SettingsManager::getValue<double>)
    .def("set_value", &SettingsManager::setValue<double>)
    .def("get_value", &SettingsManager::getValue<string>)
    .def("set_value", &SettingsManager::setValue<string>);
}

BOOST_PYTHON_MODULE(script_manager) {
  python::class_<ScriptManager, shared_ptr<ScriptManager>, noncopyable>("ScriptManager", python::no_init)
    .def("set_output", &ScriptManager::setOutput)
    .def("import", &ScriptManager::import)
    .def("execute", &ScriptManager::execute)
    .def("execute_file", &ScriptManager::executeFile)
    .def("get_error", &ScriptManager::getError)
    .def("create_interpreter", &ScriptManager::createInterpreter);
}

BOOST_PYTHON_MODULE(game_core) {
  python::class_<GameCore, shared_ptr<GameCore>, noncopyable>("GameCore", python::no_init)
  	.def("get_core", &GameCore::getCore, python::return_value_policy<python::reference_existing_object>())
    .def("get_script_manager", &GameCore::getScriptManager, python::return_value_policy<python::reference_existing_object>())
    .def("get_settings_manager", &GameCore::getSettingsManager, python::return_value_policy<python::reference_existing_object>())
    .def("get_world_manager", &GameCore::getWorldManager, python::return_value_policy<python::reference_existing_object>());
}



