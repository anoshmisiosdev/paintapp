#include <Drawing.h>
#include <cmath>

static float dist(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

static float distToSegment(float px, float py, float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float len2 = dx * dx + dy * dy;
    if (len2 < 1e-8f) {
        return dist(px, py, x1, y1);
    }
    float t = ((px - x1) * dx + (py - y1) * dy) / len2;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    float qx = x1 + t * dx;
    float qy = y1 + t * dy;
    return dist(px, py, qx, qy);
}

static bool pointInPolygon(float px, float py, const float* vx, const float* vy, int n) {
    bool inside = false;
    int j = n - 1;
    for (int i = 0; i < n; i++) {
        if (((vy[i] > py) != (vy[j] > py)) &&
            (px < (vx[j] - vx[i]) * (py - vy[i]) / (vy[j] - vy[i] + 1e-9f) + vx[i])) {
            inside = !inside;
        }
        j = i;
    }
    return inside;
}

static void getShapeVerts(ShapeKind kind, float cx, float cy, float hw, float hh,
                          float* vx, float* vy, int* count) {
    *count = 0;

    if (kind == CIRCLE_SHAPE) {
        int segs = 40;
        for (int i = 0; i < segs; i++) {
            float angle = 2.0f * M_PI * ((float)i / (float)segs);
            vx[i] = cx + hw * cos(angle);
            vy[i] = cy + hh * sin(angle);
        }
        *count = segs;
    }
    else if (kind == RECT_SHAPE) {
        vx[0] = cx - hw; vy[0] = cy - hh;
        vx[1] = cx + hw; vy[1] = cy - hh;
        vx[2] = cx + hw; vy[2] = cy + hh;
        vx[3] = cx - hw; vy[3] = cy + hh;
        *count = 4;
    }
    else if (kind == TRI_SHAPE) {
        vx[0] = cx;       vy[0] = cy - hh;
        vx[1] = cx - hw;  vy[1] = cy + hh;
        vx[2] = cx + hw;  vy[2] = cy + hh;
        *count = 3;
    }
    else if (kind == PENT_SHAPE) {
        for (int i = 0; i < 5; i++) {
            float angle = -M_PI / 2.0f + 2.0f * M_PI * ((float)i / 5.0f);
            vx[i] = cx + hw * cos(angle);
            vy[i] = cy + hh * sin(angle);
        }
        *count = 5;
    }
    else if (kind == STAR_SHAPE) {
        for (int i = 0; i < 10; i++) {
            float angle = -M_PI / 2.0f + M_PI * ((float)i / 5.0f);
            float rw = hw;
            float rh = hh;
            if (i % 2 != 0) {
                rw = hw * 0.45f;
                rh = hh * 0.45f;
            }
            vx[i] = cx + rw * cos(angle);
            vy[i] = cy + rh * sin(angle);
        }
        *count = 10;
    }
}

Drawing::Drawing() {
    color = {0, 0, 0};
}

Color Drawing::getColor() const {
    return color;
}

void Drawing::setColor(Color c) {
    color = c;
}

bool Drawing::isScribble() const {
    return false;
}

Drawing::~Drawing() {
    //
}

Scribble::Scribble() {
    color = {0, 0, 0};
}

Scribble::Scribble(Color c) {
    color = c;
}

void Scribble::addPoint(float x, float y) {
    xPoints.push_back(x);
    yPoints.push_back(y);
}

int Scribble::getPointCount() const {
    return (int)xPoints.size();
}

void Scribble::draw() const {
    if (xPoints.size() < 2) {
        return;
    }
    glColor3f(color.r, color.g, color.b);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    for (size_t i = 0; i < xPoints.size(); i++) {
        glVertex2f(xPoints[i], yPoints[i]);
    }
    glEnd();
    glLineWidth(1.0f);
}

bool Scribble::contains(float mx, float my) const {
    for (size_t i = 0; i < xPoints.size(); i++) {
        if (dist(mx, my, xPoints[i], yPoints[i]) < 0.03f) {
            return true;
        }
    }
    for (size_t i = 1; i < xPoints.size(); i++) {
        if (distToSegment(mx, my, xPoints[i-1], yPoints[i-1], xPoints[i], yPoints[i]) < 0.03f) {
            return true;
        }
    }
    return false;
}

void Scribble::moveBy(float dx, float dy) {
    for (size_t i = 0; i < xPoints.size(); i++) {
        xPoints[i] += dx;
        yPoints[i] += dy;
    }
}

void Scribble::resize(float factor) {
    if (xPoints.empty()) return;
    float avgX = 0, avgY = 0;
    for (size_t i = 0; i < xPoints.size(); i++) {
        avgX += xPoints[i];
        avgY += yPoints[i];
    }
    avgX /= xPoints.size();
    avgY /= yPoints.size();
    for (size_t i = 0; i < xPoints.size(); i++) {
        xPoints[i] = avgX + (xPoints[i] - avgX) * factor;
        yPoints[i] = avgY + (yPoints[i] - avgY) * factor;
    }
}

void Scribble::getBounds(float& left, float& bottom, float& right, float& top) const {
    if (xPoints.empty()) {
        left = bottom = right = top = 0;
        return;
    }
    left = xPoints[0]; right = xPoints[0];
    bottom = yPoints[0]; top = yPoints[0];
    for (size_t i = 1; i < xPoints.size(); i++) {
        if (xPoints[i] < left) left = xPoints[i];
        if (xPoints[i] > right) right = xPoints[i];
        if (yPoints[i] < bottom) bottom = yPoints[i];
        if (yPoints[i] > top) top = yPoints[i];
    }
}

bool Scribble::isScribble() const {
    return true;
}

Scribble::~Scribble() {
    //
}

ShapeDrawing::ShapeDrawing() {
    kind = CIRCLE_SHAPE;
    cx = 0; cy = 0;
    halfW = 0.1f; halfH = 0.1f;
    color = {0, 0, 0};
}

ShapeDrawing::ShapeDrawing(ShapeKind k, float x1, float y1, float x2, float y2, Color c) {
    kind = k;
    color = c;
    set(x1, y1, x2, y2);
}

void ShapeDrawing::set(float x1, float y1, float x2, float y2) {
    cx = (x1 + x2) / 2.0f;
    cy = (y1 + y2) / 2.0f;
    halfW = fabs(x2 - x1) / 2.0f;
    halfH = fabs(y2 - y1) / 2.0f;
}

void ShapeDrawing::draw() const {
    float vx[40];
    float vy[40];
    int n = 0;
    getShapeVerts(kind, cx, cy, halfW, halfH, vx, vy, &n);

    if (kind == STAR_SHAPE) {
        glColor3f(color.r, color.g, color.b);
        glLineWidth(4.0f);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < n; i++) {
            glVertex2f(vx[i], vy[i]);
        }
        glEnd();
        glLineWidth(1.0f);
        return;
    }

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(vx[i], vy[i]);
    }
    glEnd();

    glColor3f(0, 0, 0);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) {
        glVertex2f(vx[i], vy[i]);
    }
    glEnd();
}

bool ShapeDrawing::contains(float mx, float my) const {
    if (kind == CIRCLE_SHAPE) {
        float nx = (mx - cx) / (halfW + 1e-6f);
        float ny = (my - cy) / (halfH + 1e-6f);
        return (nx * nx + ny * ny) <= 1.0f;
    }
    if (kind == RECT_SHAPE) {
        return mx >= cx - halfW && mx <= cx + halfW &&
               my >= cy - halfH && my <= cy + halfH;
    }
    float vx[40];
    float vy[40];
    int n = 0;
    getShapeVerts(kind, cx, cy, halfW, halfH, vx, vy, &n);
    return pointInPolygon(mx, my, vx, vy, n);
}

void ShapeDrawing::moveBy(float dx, float dy) {
    cx += dx;
    cy += dy;
}

void ShapeDrawing::resize(float factor) {
    halfW *= factor;
    halfH *= factor;
}

void ShapeDrawing::getBounds(float& left, float& bottom, float& right, float& top) const {
    left = cx - halfW;
    right = cx + halfW;
    bottom = cy - halfH;
    top = cy + halfH;
}

ShapeDrawing::~ShapeDrawing() {
    //
}
