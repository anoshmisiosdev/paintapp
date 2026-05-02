#include <Application.h>

using namespace bobcat;

Application::Application() {
    window = new Window(25, 75, 850, 650, "Paint Application");

    canvas = new Canvas(50, 0, 800, 550);
    toolbar = new Toolbar(0, 0, 50, 650);
    colorSelector = new ColorSelector(50, 550, 800, 100);

    window->add(canvas);
    window->add(toolbar);
    window->add(colorSelector);

    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasMouseDrag);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_CHANGE(colorSelector, Application::onColorChange);

    window->show();
}

void Application::onCanvasMouseDown(Widget* sender, float x, float y) {
    Color color = colorSelector->getSelectedColor();
    TOOL tool = toolbar->getSelectedTool();

    if (tool == PENCIL) {
        canvas->startScribble(x, y, color);
    }
    else if (tool == ERASER) {
        canvas->eraseAt(x, y);
    }
    else if (tool == MOUSE) {
        canvas->selectAt(x, y);
        canvas->startMoveSelected(x, y);
    }
    else if (tool == CIRCLE) {
        canvas->startShape(CIRCLE_SHAPE, x, y, color);
    }
    else if (tool == TRIANGLE) {
        canvas->startShape(TRI_SHAPE, x, y, color);
    }
    else if (tool == RECTANGLE) {
        canvas->startShape(RECT_SHAPE, x, y, color);
    }
    else if (tool == PENTAGON) {
        canvas->startShape(PENT_SHAPE, x, y, color);
    }
    else if (tool == STAR) {
        canvas->startShape(STAR_SHAPE, x, y, color);
    }

    canvas->redraw();
}

void Application::onCanvasMouseDrag(Widget* sender, float x, float y) {
    TOOL tool = toolbar->getSelectedTool();

    if (tool == PENCIL) {
        canvas->addScribblePoint(x, y);
    }
    else if (tool == MOUSE) {
        canvas->moveSelectedTo(x, y);
    }
    else if (tool == CIRCLE || tool == TRIANGLE || tool == RECTANGLE ||
             tool == PENTAGON || tool == STAR) {
        canvas->updateShapePreview(x, y);
    }

    canvas->redraw();
}

void Application::onToolbarChange(Widget* sender) {
    ACTION action = toolbar->getAction();

    if (action == UNDO) {
        canvas->undo();
    }
    else if (action == REDO) {
        canvas->redo();
    }
    else if (action == CLEAR_ALL) {
        canvas->clear();
    }
    else if (action == FRONT) {
        canvas->bringToFront();
    }
    else if (action == BACK) {
        canvas->sendToBack();
    }
    else if (action == GROW) {
        canvas->resizeSelected(1.15f);
    }
    else if (action == SHRINK) {
        canvas->resizeSelected(1.0f / 1.15f);
    }

    canvas->redraw();
}

void Application::onColorChange(Widget* sender) {
    Color c = colorSelector->getSelectedColor();
    canvas->changeSelectedColor(c);
    canvas->redraw();
}

Application::~Application() {
    delete canvas;
    delete toolbar;
    delete colorSelector;
    delete window;
}
