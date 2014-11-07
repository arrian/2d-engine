#pragma once

#include "Util.h"

#include "GameCore.h"
#include "WorldManager.h"
#include "ScriptManager.h"
#include "SettingsManager.h"

// Polycode Bindings

BOOST_PYTHON_MODULE(core_services) {
  python::class_<CoreServices>("CoreServices", python::no_init)
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
  python::class_<Core>("Core", python::no_init)
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
  	.def("get_services", &Core::getServices)
  	.def("get_fps", &Core::getFPS)
  	.def("is_fullscreen", &Core::isFullscreen)
  	.def("get_aa_level", &Core::getAALevel)
  	.def("get_input", &Core::getInput)
  	.def("get_x_res", &Core::getXRes)
  	.def("get_y_res", &Core::getYRes)
  	.def("get_screen_info", &Core::getScreenInfo)
  	.def("open_folder_picker", &Core::openFolderPicker)
  	.def("get_elapsed", &Core::getElapsed)
  	.def("get_ticks", &Core::getTicks)
  	.def("get_ticks_float", &Core::getTicksFloat)
  	.def("get_default_working_directory", &Core::getDefaultWorkingDirectory)
  	.def("get_user_home_directory", &Core::getUserHomeDirectory);
}

// Game Bindings

BOOST_PYTHON_MODULE(world_manager) {
  python::class_<WorldManager, shared_ptr<WorldManager> >("WorldManager", python::no_init)
    .def("update", &WorldManager::update);
}

BOOST_PYTHON_MODULE(settings_manager) {
  python::class_<SettingsManager, shared_ptr<SettingsManager> >("SettingsManager", python::no_init)
    .def("get_value", &SettingsManager::getValue)
    .def("set_value", &SettingsManager::setValue);
}

BOOST_PYTHON_MODULE(script_manager) {
  python::class_<ScriptManager, shared_ptr<ScriptManager> >("ScriptManager", python::no_init)
    .def("set_output", &ScriptManager::setOutput)
    .def("import", &ScriptManager::import)
    .def("execute", &ScriptManager::execute)
    .def("execute_file", &ScriptManager::executeFile)
    .def("get_error", &ScriptManager::getError)
    .def("create_interpreter", &ScriptManager::createInterpreter);
}

BOOST_PYTHON_MODULE(game_core) {
  python::class_<GameCore, shared_ptr<GameCore> >("GameCore", python::no_init)
  	.def("get_core", &GameCore::getCore)
    .def("get_script_manager", &GameCore::getScriptManager)
    .def("get_settings_manager", &GameCore::getSettingsManager)
    .def("get_world_manager", &GameCore::getWorldManager);
}



