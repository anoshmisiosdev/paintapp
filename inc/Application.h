#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include <Canvas.h>
#include <Toolbar.h>
#include <ColorSelector.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Canvas* canvas;
    Toolbar* toolbar;
    ColorSelector* colorSelector;

    void onCanvasMouseDown(bobcat::Widget* sender, float x, float y);
    void onCanvasMouseDrag(bobcat::Widget* sender, float x, float y);
    void onToolbarChange(bobcat::Widget* sender);
    void onColorChange(bobcat::Widget* sender);

public:
    Application();

    ~Application();
};

#endif
