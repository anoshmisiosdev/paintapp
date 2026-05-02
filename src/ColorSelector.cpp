#include <ColorSelector.h>

using namespace bobcat;

ColorSelector::ColorSelector(int x, int y, int w, int h) : Group(x, y, w, h) {
    rSlider = new Fl_Value_Slider(x + 30, y + 8, 300, 25, "R");
    rSlider->type(FL_HORIZONTAL);
    rSlider->bounds(0, 255);
    rSlider->step(1);
    rSlider->value(0);
    rSlider->callback(sliderChanged, this);

    gSlider = new Fl_Value_Slider(x + 30, y + 38, 300, 25, "G");
    gSlider->type(FL_HORIZONTAL);
    gSlider->bounds(0, 255);
    gSlider->step(1);
    gSlider->value(0);
    gSlider->callback(sliderChanged, this);

    bSlider = new Fl_Value_Slider(x + 30, y + 68, 300, 25, "B");
    bSlider->type(FL_HORIZONTAL);
    bSlider->bounds(0, 255);
    bSlider->step(1);
    bSlider->value(0);
    bSlider->callback(sliderChanged, this);
}

Color ColorSelector::getSelectedColor() const {
    Color c;
    c.r = (float)rSlider->value() / 255.0f;
    c.g = (float)gSlider->value() / 255.0f;
    c.b = (float)bSlider->value() / 255.0f;
    return c;
}

void ColorSelector::sliderChanged(Fl_Widget* w, void* data) {
    ColorSelector* cs = (ColorSelector*)data;
    cs->handleSliderChange();
}

void ColorSelector::handleSliderChange() {
    if (onChangeCb) {
        onChangeCb(this);
    }
}

ColorSelector::~ColorSelector() {
    delete rSlider;
    delete gSlider;
    delete bSlider;
}
