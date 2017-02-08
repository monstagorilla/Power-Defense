#pragma once

#include <vector>
#include <string>
#include "GUIObject.h"
#include "enumGUI.h"

class GUI {
public:
    static std::vector<std::string> paths;
    static void initGUI();
    static void addGUIObject(GUIObject* parent, GUIObject* newObject);
    static void addGUIObject(eGUI identifier, GUIObject* newObject);
};














