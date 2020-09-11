/* methods for images */

struct utils * getWidth(struct symref * v);
struct utils * getHeight(struct symref * v);
struct utils * getBands(struct symref * v);
struct utils * min(struct symref * v);
struct utils * max(struct symref * v);
struct utils * average(struct symref * v);
struct utils * invert(struct symref * l,struct ast * v);                                  //Inverts the image
void saveImage(char * in, VipsImage * out, char * path);
struct utils * toColorSpace(struct symref * l,struct ast * v,struct ast * s);
struct utils * crop(struct symref * l,struct symref * r,struct ast * left,struct ast * top,struct ast * width,struct ast * height);
struct utils * smartCrop(struct symref * l,struct symref * r,struct ast * width,struct ast * height);
struct utils * add(struct symref * l,struct symref * r,struct ast * p);                   //Sums 2 images
struct utils * subtract_img(struct symref * l,struct symref * r,struct ast * p);          //Subtracts 2 images
void openImg(char * path);
struct utils * rotate(struct symref * l,struct ast * v,struct ast * s);
struct utils * histeq(struct symref * l,struct ast * v);
struct utils * norm(struct symref * l,struct ast * v);
struct utils * gaussianBlur(struct symref * l,struct ast * v,struct ast * s);
struct utils * canny(struct symref * l,struct ast * v);
struct utils * sobel(struct symref * l,struct ast * v);
struct utils * sharpen(struct symref * l,struct ast * v);
struct utils * flip(struct symref * l,struct ast * v,struct ast * s);
struct utils * zoom(struct symref * l,struct symref * r,struct ast * xfactor,struct ast * yfactor);
struct utils * convert(struct symref * l,struct ast * v);