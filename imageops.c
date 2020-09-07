#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
#  include <math.h>
#  include <vips/vips.h>
#  include "utils.h"

/* methods for images */

/* This sometimes causes memory issues, needs to be updated */
void
openImg(char * path){
   char * open = strdup("xdg-open ");     
   char * command; 

   command=strcat(open,path);
   system(command);
}

struct utils *
average(struct symref * v) {
   double mean;
   struct utils * temp1 = v -> s -> value;
   if (vips_avg((((struct img * ) temp1) -> img), & mean, NULL)) {
      vips_error_exit(NULL);
   }
   //printf("Mean pixel value = %g\n", mean);
   return ((struct utils *)newdouble(mean,'+'));
}

struct utils * 
invert(struct symref * l,struct ast * v) {
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   if (vips_invert((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   //openImg(path);
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils * 
crop(struct symref * l,struct symref * r,struct ast * left,struct ast * top,struct ast * width,struct ast * height){
   VipsImage * out;
   char * path;
   double left_value=getValue(left);
   double top_value=getValue(top);
   double width_value=getValue(width);
   double height_value=getValue(height);
   struct utils * temp1 = l -> s -> value;

   if (vips_crop((((struct img * ) temp1) -> img), & out,left_value,top_value,width_value,height_value, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath( ((struct ast *) r) );

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   //openImg(path);
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

/* Crop an image down to a specified width and height by removing "boring" parts.  */
struct utils * 
smartCrop(struct symref * l,struct symref * r,struct ast * width,struct ast * height){
   VipsImage * out;
   char * path;
   double width_value=getValue(width);
   double height_value=getValue(height);
   struct utils * temp1 = l -> s -> value;

   if (vips_smartcrop((((struct img * ) temp1) -> img), & out, width_value, height_value, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath( ((struct ast *) r) );

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   //openImg(path);
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils * 
add(struct symref * l,struct symref * r,struct ast * p){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l-> s -> value;
   struct utils * temp2 = r-> s -> value;

   if (vips_add((((struct img * ) temp1) -> img),(((struct img * ) temp2) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(p);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   //openImg(path);

   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils * 
subtract_img(struct symref * l,struct symref * r,struct ast * p){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l-> s -> value;
   struct utils * temp2 = r-> s -> value;

   if (vips_subtract((((struct img * ) temp1) -> img),(((struct img * ) temp2) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(p);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   //openImg(path);

   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils * 
toColorSpace(struct symref * l,struct ast * v,struct ast * s){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   VipsInterpretation in_space=vips_image_guess_interpretation(((struct img * ) temp1) -> img);
   VipsInterpretation out_space=getSpace(s);
   (((struct img * ) temp1) -> img)->Type=in_space;

   if (vips_colourspace((((struct img * ) temp1) -> img), & out,  out_space,NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   //openImg(path);

   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils *
rotate(struct symref * l,struct ast * v,struct ast * s){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   double angle=getValue(s);

   if (vips_rotate((((struct img * ) temp1) -> img), & out, angle, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   //openImg(path);
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils *
getWidth(struct symref * v) {
   int val;
   struct utils * temp1 = v -> s -> value;
   val=vips_image_get_width(((struct img * ) temp1) -> img);
   //printf("image width = %d\n", val);
   return ((struct utils *)newint(val,'+'));
}

struct utils *
getHeight(struct symref * v) {
   int val;
   struct utils * temp1 = v -> s -> value;
   val=vips_image_get_height(((struct img * ) temp1) -> img);
   //printf("image height = %d\n", val);
   return ((struct utils *)newint(val,'+'));
}

struct utils *
getBands(struct symref * v) {
   int val;
   struct utils * temp1 = v -> s -> value;
   val=vips_image_get_bands(((struct img * ) temp1) -> img);
   //printf("number of bands = %d\n", val);
   return ((struct utils *)newint(val,'+'));
}

struct utils *
histeq(struct symref * l,struct ast * v){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   if (vips_hist_equal((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   //openImg(path);
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils *
norm(struct symref * l,struct ast * v){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   if (vips_hist_norm((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   //openImg(path);
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils *
gaussianBlur(struct symref * l,struct ast * v,struct ast * s){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   double sigma=getValue(s);

   if (vips_gaussblur((((struct img * ) temp1) -> img), & out, sigma, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   //openImg(path);
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils * 
canny(struct symref * l,struct ast * v) {
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   if (vips_canny((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   //openImg(path);
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}