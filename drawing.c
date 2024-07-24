// Credit to https://gist.github.com/bert/9bb403b01a3029b988938a7ce8217735
//
// 	8/19/2022 added a destroy mutex object statement at the end of start_gtk()
//	changed thread_draw signature to void*() from void*(void*)
//
//	changed while loop from while(1) to while(status) and added status variable
//	added pthread_join call (status is set to 0 beforehand so that the while loop exits)
//
//	added signal(SIGINT, &handle_sigint) before gtk_main()
//	added handle_sigint() method

#include "drawing.h"

void* thread_draw(){
	while(status){
		usleep(1E6 / FRAME_RATE);
		
		if(surface ==(cairo_surface_t *)NULL)
			continue;
		
		pthread_mutex_lock(&mutex);
		
		cairo_t *context = cairo_create(surface);
		
		//Draw the background
		cairo_set_source_rgb(context, 1, 1, 1);
		cairo_rectangle(context, 0, 0, surface_width, surface_height);
		cairo_fill(context);
		
		cairo_set_line_width(context,1.0);
		
		cairo_set_source_rgb(context, 1.0, 0, 0);
		//draw the particles (squares of length sideLength centered at the x and y positions of the particles)
		int frameNumber = (frame*CALCULATIONS_PER_SECOND/FRAME_RATE) % NUM_FRAMES;
		
		fflush(stdout);
		printf("frame %d            \r",frameNumber);
		for(unsigned i=0;i<numParticles;i++){
			cairo_arc(context,buffer[frameNumber].particles[i].x[0],buffer[frameNumber].particles[i].x[1],5,0,2*M_PI);
			cairo_stroke(context);
			//cairo_rectangle(context,buffer[frameNumber].particles[i].x[0]-sideLength/2-.5,buffer[frameNumber].particles[i].x[1]-sideLength/2-.5,sideLength,sideLength);
		}
		
		cairo_stroke(context);
		cairo_destroy(context);
		frame++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
void handle_sigint(int sig){
	gtk_main_quit();
	printf("\n");
}
void start_gtk(){
	gtk_init(0,NULL);
	GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(main_window), TITLE);
	gtk_window_set_default_size(GTK_WINDOW(main_window), WIDTH, HEIGHT);
	GtkWidget *drawing_area = gtk_drawing_area_new();
	
	//Connect to the configure event to create the surface
	g_signal_connect(drawing_area, "configure-event", G_CALLBACK(drawing_area_configure_cb), NULL);
	
	gtk_container_add(GTK_CONTAINER(main_window), drawing_area);
	gtk_widget_show_all(main_window);
	
	//Create a new thread to update the stored surface
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&drawing_thread, NULL, thread_draw, NULL);
	
	//Create a	timer to invalidate our window at FRAME_RATE, and display the stored surface
	g_timeout_add(1000 / FRAME_RATE, invalidate_cb, drawing_area);
	
	//Connect our redraw callback
	g_signal_connect(drawing_area, "draw", G_CALLBACK(drawing_area_draw_cb), NULL);
	
	//Connect the destroy signal
	g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	signal(SIGINT, &handle_sigint);
	gtk_main();
	
	status = 0;
	pthread_join(drawing_thread,NULL);
	pthread_mutex_destroy(&mutex);
}

gboolean invalidate_cb(void *ptr){
	if(GTK_IS_WIDGET(ptr)){
		gtk_widget_queue_draw(GTK_WIDGET(ptr));
		return TRUE;
	}
	return FALSE;
}


gboolean drawing_area_configure_cb(GtkWidget *widget, GdkEventConfigure *event){
	if(event -> type == GDK_CONFIGURE){
		pthread_mutex_lock(&mutex);

		if(surface !=(cairo_surface_t *)NULL)
			cairo_surface_destroy(surface);

		GtkAllocation allocation;
		gtk_widget_get_allocation(widget, &allocation);
		surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, allocation.width, allocation.height);
		surface_width = allocation.width;
		surface_height = allocation.height;	

		pthread_mutex_unlock(&mutex);
	}

	return TRUE;
}

void drawing_area_draw_cb(GtkWidget *widget, cairo_t *context, void *ptr){
	//Copy the contents of the surface to the current context
	pthread_mutex_lock(&mutex);
	
	if(surface != (cairo_surface_t *)NULL){
		cairo_set_source_surface(context, surface, 0, 0);
		cairo_paint(context);
	}
	
	pthread_mutex_unlock(&mutex);
}
