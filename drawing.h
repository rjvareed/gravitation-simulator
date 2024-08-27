// Credit to https://gist.github.com/bert/9bb403b01a3029b988938a7ce8217735

#ifndef __DRAWING_H
#define __DRAWING_H

#include <gtk/gtk.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>

#include "calc.h"

//local constants
extern const int FRAME_RATE;
extern const int WIDTH;
extern const int HEIGHT;
extern const char TITLE[];
extern unsigned frame;
extern unsigned const CALCULATIONS_PER_SECOND;

//local variables
extern Frame *buffer;
extern pthread_t drawing_thread;
extern pthread_mutex_t mutex;
extern cairo_surface_t *surface;
extern int surface_width;
extern int surface_height;
extern int status;

//Local function prototypes
gboolean invalidate_cb(void*);
gboolean drawing_area_configure_cb(GtkWidget *, GdkEventConfigure *);
void drawing_area_draw_cb(GtkWidget*, cairo_t*, void*);
void* thread_draw();
void start_gtk();
void handle_sigint(int);

#endif
