#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/canvas.h>
#include <Drawing.h>
#include <vector>

class Canvas : public bobcat::Canvas_ {
    std::vector<Drawing*> drawings;
    std::vector<Drawing*> created;
    std::vector<Drawing*> undone;

    Drawing* selected;

    Scribble* currentScribble;
    ShapeDrawing* previewShape;

    bool dragging;
    float lastDragX;
    float lastDragY;
    float shapeStartX;
    float shapeStartY;

public:
    Canvas(int x, int y, int w, int h);

    void startScribble(float x, float y, Color color);
    void addScribblePoint(float x, float y);
    void finishScribble();

    void startShape(ShapeKind kind, float x, float y, Color color);
    void updateShapePreview(float x, float y);
    void finishShape();

    void selectAt(float x, float y);
    void startMoveSelected(float x, float y);
    void moveSelectedTo(float x, float y);

    void eraseAt(float x, float y);
    void clear();

    void undo();
    void redo();
    void bringToFront();
    void sendToBack();
    void resizeSelected(float factor);
    void changeSelectedColor(Color c);

    Drawing* getSelected() const;

    void render();
    int handle(int event);

    ~Canvas();
};

#endif
