#include <Canvas.h>

static void removePtr(std::vector<Drawing*>& vec, Drawing* d) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == d) {
            vec.erase(vec.begin() + i);
            return;
        }
    }
}

Canvas::Canvas(int x, int y, int w, int h) : bobcat::Canvas_(x, y, w, h) {
    selected = 0;
    currentScribble = 0;
    previewShape = 0;
    dragging = false;
    lastDragX = 0;
    lastDragY = 0;
    shapeStartX = 0;
    shapeStartY = 0;
}

void Canvas::startScribble(float x, float y, Color color) {
    if (currentScribble != 0) {
        delete currentScribble;
    }
    currentScribble = new Scribble(color);
    currentScribble->addPoint(x, y);
}

void Canvas::addScribblePoint(float x, float y) {
    if (currentScribble != 0) {
        currentScribble->addPoint(x, y);
    }
}

void Canvas::finishScribble() {
    if (currentScribble == 0) return;
    if (currentScribble->getPointCount() >= 2) {
        for (size_t i = 0; i < undone.size(); i++) {
            delete undone[i];
        }
        undone.clear();
        drawings.push_back(currentScribble);
        created.push_back(currentScribble);
        currentScribble = 0;
    }
    else {
        delete currentScribble;
        currentScribble = 0;
    }
}

void Canvas::startShape(ShapeKind kind, float x, float y, Color color) {
    if (previewShape != 0) {
        delete previewShape;
    }
    previewShape = new ShapeDrawing(kind, x, y, x, y, color);
    shapeStartX = x;
    shapeStartY = y;
}

void Canvas::updateShapePreview(float x, float y) {
    if (previewShape != 0) {
        previewShape->set(shapeStartX, shapeStartY, x, y);
    }
}

void Canvas::finishShape() {
    if (previewShape == 0) return;
    float left, bottom, right, top;
    previewShape->getBounds(left, bottom, right, top);
    if (right - left > 0.01f || top - bottom > 0.01f) {
        for (size_t i = 0; i < undone.size(); i++) {
            delete undone[i];
        }
        undone.clear();
        drawings.push_back(previewShape);
        created.push_back(previewShape);
        previewShape = 0;
    }
    else {
        delete previewShape;
        previewShape = 0;
    }
}

void Canvas::selectAt(float x, float y) {
    selected = 0;
    for (int i = (int)drawings.size() - 1; i >= 0; i--) {
        if (drawings[i]->contains(x, y)) {
            selected = drawings[i];
            return;
        }
    }
}

void Canvas::startMoveSelected(float x, float y) {
    if (selected != 0) {
        dragging = true;
        lastDragX = x;
        lastDragY = y;
    }
}

void Canvas::moveSelectedTo(float x, float y) {
    if (dragging && selected != 0) {
        float dx = x - lastDragX;
        float dy = y - lastDragY;
        selected->moveBy(dx, dy);
        lastDragX = x;
        lastDragY = y;
    }
}

void Canvas::eraseAt(float x, float y) {
    for (int i = (int)drawings.size() - 1; i >= 0; i--) {
        if (drawings[i]->contains(x, y)) {
            Drawing* d = drawings[i];
            removePtr(drawings, d);
            removePtr(created, d);
            removePtr(undone, d);
            if (selected == d) selected = 0;
            delete d;
            return;
        }
    }
}

void Canvas::clear() {
    for (size_t i = 0; i < drawings.size(); i++) {
        delete drawings[i];
    }
    drawings.clear();

    for (size_t i = 0; i < undone.size(); i++) {
        delete undone[i];
    }
    undone.clear();

    created.clear();

    if (currentScribble != 0) {
        delete currentScribble;
        currentScribble = 0;
    }
    if (previewShape != 0) {
        delete previewShape;
        previewShape = 0;
    }

    selected = 0;
}

void Canvas::undo() {
    if (created.empty()) return;
    Drawing* d = created.back();
    created.pop_back();
    removePtr(drawings, d);
    undone.push_back(d);
    if (selected == d) selected = 0;
}

void Canvas::redo() {
    if (undone.empty()) return;
    Drawing* d = undone.back();
    undone.pop_back();
    drawings.push_back(d);
    created.push_back(d);
}

void Canvas::bringToFront() {
    if (selected == 0) return;
    removePtr(drawings, selected);
    drawings.push_back(selected);
}

void Canvas::sendToBack() {
    if (selected == 0) return;
    removePtr(drawings, selected);
    drawings.insert(drawings.begin(), selected);
}

void Canvas::resizeSelected(float factor) {
    if (selected != 0) {
        selected->resize(factor);
    }
}

void Canvas::changeSelectedColor(Color c) {
    if (selected != 0) {
        selected->setColor(c);
    }
}

Drawing* Canvas::getSelected() const {
    return selected;
}

void Canvas::render() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (size_t i = 0; i < drawings.size(); i++) {
        drawings[i]->draw();
    }

    if (currentScribble != 0) {
        currentScribble->draw();
    }

    if (previewShape != 0) {
        previewShape->draw();
    }

    if (selected != 0) {
        float left, bottom, right, top;
        selected->getBounds(left, bottom, right, top);
        float pad = 0.02f;
        glColor3f(0.2f, 0.4f, 1.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(left - pad, bottom - pad);
        glVertex2f(right + pad, bottom - pad);
        glVertex2f(right + pad, top + pad);
        glVertex2f(left - pad, top + pad);
        glEnd();
        glLineWidth(1.0f);
    }
}

int Canvas::handle(int event) {
    if (event == FL_RELEASE) {
        if (currentScribble != 0) {
            finishScribble();
        }
        if (previewShape != 0) {
            finishShape();
        }
        dragging = false;
        redraw();
        return 1;
    }
    return bobcat::Canvas_::handle(event);
}

Canvas::~Canvas() {
    clear();
}
