#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <bobcat_ui/all.h>
#include <Enums.h>

class Toolbar : public bobcat::Group {
    bobcat::Image* pencilButton;
    bobcat::Image* eraserButton;
    bobcat::Image* mouseButton;
    bobcat::Image* circleButton;
    bobcat::Image* triangleButton;
    bobcat::Image* rectangleButton;
    bobcat::Button* pentagonButton;
    bobcat::Button* starButton;
    bobcat::Image* undoButton;
    bobcat::Button* redoButton;
    bobcat::Image* clearButton;
    bobcat::Button* frontButton;
    bobcat::Button* backButton;
    bobcat::Button* growButton;
    bobcat::Button* shrinkButton;

    TOOL selectedTool;
    ACTION action;

    void onClick(bobcat::Widget* sender);
    void visualizeSelectedTool() const;
    void deselectAllTools() const;

public:
    Toolbar(int x, int y, int w, int h);

    TOOL getSelectedTool() const;
    ACTION getAction() const;

    ~Toolbar();
};

#endif
