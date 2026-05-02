#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include <bobcat_ui/all.h>
#include <FL/Fl_Value_Slider.H>
#include <Color.h>

class ColorSelector : public bobcat::Group {
    Fl_Value_Slider* rSlider;
    Fl_Value_Slider* gSlider;
    Fl_Value_Slider* bSlider;

    static void sliderChanged(Fl_Widget* w, void* data);
    void handleSliderChange();

public:
    ColorSelector(int x, int y, int w, int h);

    Color getSelectedColor() const;

    ~ColorSelector();
};

#endif
