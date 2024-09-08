#include "Frame.hpp"
#include "DrawMode.hpp"

class Canvas {
private:
  Frame* current_frame {};
  DrawMode draw_mode {DrawMode::PENCIL};
  int x {}; //top left coordinate
  int y {}; //top left coordinate
  int width {}; //in pixels (not bits)
  int height {}; // in pixels (not bits)
  int bit_width {}; // number of pixels wide for 1 bit of the Frame

public:
  Canvas(int x, int y, int width, int height, Frame* frame);
  Canvas(Frame* frame);
  void set_width(int w);
  void set_height(int h);
  void set_pos_on_screen(int x, int y);
  void set_frame(Frame* new_frame);
  void update_frame(int x, int y, bool val);
  void draw();
  void set_draw_mode(DrawMode new_mode);
  
  
};
