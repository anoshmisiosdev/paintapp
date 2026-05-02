#include <Toolbar.h>

using namespace bobcat;

Toolbar::Toolbar(int x, int y, int w, int h) : Group(x, y, w, h) {
    int bh = 42;
    int row = 0;

    pencilButton = new Image(x, y + bh * row++, 50, bh, "./assets/pencil.png");
    eraserButton = new Image(x, y + bh * row++, 50, bh, "./assets/eraser.png");
    mouseButton = new Image(x, y + bh * row++, 50, bh, "./assets/mouse.png");
    circleButton = new Image(x, y + bh * row++, 50, bh, "./assets/circle.png");
    triangleButton = new Image(x, y + bh * row++, 50, bh, "./assets/triangle.png");
    rectangleButton = new Image(x, y + bh * row++, 50, bh, "./assets/rectangle.png");
    pentagonButton = new Button(x, y + bh * row++, 50, bh, "Pent");
    starButton = new Button(x, y + bh * row++, 50, bh, "Star");
    undoButton = new Image(x, y + bh * row++, 50, bh, "./assets/undo.png");
    redoButton = new Button(x, y + bh * row++, 50, bh, "Redo");
    clearButton = new Image(x, y + bh * row++, 50, bh, "./assets/clear.png");
    frontButton = new Button(x, y + bh * row++, 50, bh, "Frnt");
    backButton = new Button(x, y + bh * row++, 50, bh, "Back");
    growButton = new Button(x, y + bh * row++, 50, bh, "+");
    shrinkButton = new Button(x, y + bh * row++, 50, bh, "-");

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
