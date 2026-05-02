#include <Toolbar.h>

using namespace bobcat;

Toolbar::Toolbar(int x, int y, int w, int h) : Group(x, y, w, h) {
    int bw = 50;
    int bh = 36;
    int px = x + 2;
    int py = y + 2;

    pencilButton = new Image(px, py, bw, bh, "./assets/pencil.png");     px += bw;
    eraserButton = new Image(px, py, bw, bh, "./assets/eraser.png");     px += bw;
    mouseButton = new Image(px, py, bw, bh, "./assets/mouse.png");       px += bw;
    circleButton = new Image(px, py, bw, bh, "./assets/circle.png");     px += bw;
    triangleButton = new Image(px, py, bw, bh, "./assets/triangle.png"); px += bw;
    rectangleButton = new Image(px, py, bw, bh, "./assets/rectangle.png"); px += bw;
    pentagonButton = new Button(px, py, bw, bh, "Pent");                 px += bw;
    starButton = new Button(px, py, bw, bh, "Star");                     px += bw;

    px += 10;

    undoButton = new Image(px, py, bw, bh, "./assets/undo.png");         px += bw;
    redoButton = new Button(px, py, bw, bh, "Redo");                     px += bw;
    clearButton = new Image(px, py, bw, bh, "./assets/clear.png");       px += bw;
    frontButton = new Button(px, py, bw, bh, "Frnt");                    px += bw;
    backButton = new Button(px, py, bw, bh, "Back");                     px += bw;
    growButton = new Button(px, py, bw, bh, "+");                        px += bw;
    shrinkButton = new Button(px, py, bw, bh, "-");

    pencilButton->box(FL_BORDER_BOX);
    eraserButton->box(FL_BORDER_BOX);
    mouseButton->box(FL_BORDER_BOX);
    circleButton->box(FL_BORDER_BOX);
    triangleButton->box(FL_BORDER_BOX);
    rectangleButton->box(FL_BORDER_BOX);
    pentagonButton->box(FL_BORDER_BOX);
    starButton->box(FL_BORDER_BOX);
    undoButton->box(FL_BORDER_BOX);
    redoButton->box(FL_BORDER_BOX);
    clearButton->box(FL_BORDER_BOX);
    frontButton->box(FL_BORDER_BOX);
    backButton->box(FL_BORDER_BOX);
    growButton->box(FL_BORDER_BOX);
    shrinkButton->box(FL_BORDER_BOX);

    ON_CLICK(pencilButton, Toolbar::onClick);
    ON_CLICK(eraserButton, Toolbar::onClick);
    ON_CLICK(mouseButton, Toolbar::onClick);
    ON_CLICK(circleButton, Toolbar::onClick);
    ON_CLICK(triangleButton, Toolbar::onClick);
    ON_CLICK(rectangleButton, Toolbar::onClick);
    ON_CLICK(pentagonButton, Toolbar::onClick);
    ON_CLICK(starButton, Toolbar::onClick);
    ON_CLICK(undoButton, Toolbar::onClick);
    ON_CLICK(redoButton, Toolbar::onClick);
    ON_CLICK(clearButton, Toolbar::onClick);
    ON_CLICK(frontButton, Toolbar::onClick);
    ON_CLICK(backButton, Toolbar::onClick);
    ON_CLICK(growButton, Toolbar::onClick);
    ON_CLICK(shrinkButton, Toolbar::onClick);

    selectedTool = PENCIL;
    action = NONE;
    visualizeSelectedTool();
}

TOOL Toolbar::getSelectedTool() const {
    return selectedTool;
}

ACTION Toolbar::getAction() const {
    return action;
}

void Toolbar::onClick(bobcat::Widget* sender) {
    deselectAllTools();

    action = NONE;

    if (sender == pencilButton) {
        selectedTool = PENCIL;
    }
    else if (sender == eraserButton) {
        selectedTool = ERASER;
    }
    else if (sender == mouseButton) {
        selectedTool = MOUSE;
    }
    else if (sender == circleButton) {
        selectedTool = CIRCLE;
    }
    else if (sender == triangleButton) {
        selectedTool = TRIANGLE;
    }
    else if (sender == rectangleButton) {
        selectedTool = RECTANGLE;
    }
    else if (sender == pentagonButton) {
        selectedTool = PENTAGON;
    }
    else if (sender == starButton) {
        selectedTool = STAR;
    }
    else if (sender == undoButton) {
        action = UNDO;
    }
    else if (sender == redoButton) {
        action = REDO;
    }
    else if (sender == clearButton) {
        action = CLEAR_ALL;
    }
    else if (sender == frontButton) {
        action = FRONT;
    }
    else if (sender == backButton) {
        action = BACK;
    }
    else if (sender == growButton) {
        action = GROW;
    }
    else if (sender == shrinkButton) {
        action = SHRINK;
    }

    if (onChangeCb) {
        onChangeCb(this);
    }

    visualizeSelectedTool();
    redraw();
}

void Toolbar::visualizeSelectedTool() const {
    if (selectedTool == PENCIL) {
        pencilButton->color(FL_WHITE);
    }
    else if (selectedTool == ERASER) {
        eraserButton->color(FL_WHITE);
    }
    else if (selectedTool == MOUSE) {
        mouseButton->color(FL_WHITE);
    }
    else if (selectedTool == CIRCLE) {
        circleButton->color(FL_WHITE);
    }
    else if (selectedTool == TRIANGLE) {
        triangleButton->color(FL_WHITE);
    }
    else if (selectedTool == RECTANGLE) {
        rectangleButton->color(FL_WHITE);
    }
    else if (selectedTool == PENTAGON) {
        pentagonButton->color(FL_WHITE);
    }
    else if (selectedTool == STAR) {
        starButton->color(FL_WHITE);
    }
}

void Toolbar::deselectAllTools() const {
    pencilButton->color(FL_BACKGROUND_COLOR);
    eraserButton->color(FL_BACKGROUND_COLOR);
    mouseButton->color(FL_BACKGROUND_COLOR);
    circleButton->color(FL_BACKGROUND_COLOR);
    triangleButton->color(FL_BACKGROUND_COLOR);
    rectangleButton->color(FL_BACKGROUND_COLOR);
    pentagonButton->color(FL_BACKGROUND_COLOR);
    starButton->color(FL_BACKGROUND_COLOR);
}

Toolbar::~Toolbar() {
    delete pencilButton;
    delete eraserButton;
    delete mouseButton;
    delete circleButton;
    delete triangleButton;
    delete rectangleButton;
    delete pentagonButton;
    delete starButton;
    delete undoButton;
    delete redoButton;
    delete clearButton;
    delete frontButton;
    delete backButton;
    delete growButton;
    delete shrinkButton;
}
