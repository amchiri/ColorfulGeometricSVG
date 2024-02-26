#ifndef __DRAWING__H
#define __DRAWING__H

typedef enum {
    BLACK,
    WHITE,
    RED,
    BLUE,
    GREEN,
    YELLOW,
}Color;


typedef struct {
    //A vous de completer à votre convenance
    int x;
    int y;
    int width;
    int height;
    
}Rectangle;

typedef struct {
    //A vous de completer à votre convenance
    int x;
    int y;
    
}Point;

typedef struct {
    //A vous de completer à votre convenance
    Point* p;
    int taille;
    
}Polygon;

typedef struct {
    //A vous de completer à votre convenance
    int x;
    int y;
    int rayon;
    
}Cercle;

typedef struct {
    //A vous de completer à votre convenance
    int x1;
    int y1;
    int x2;
    int y2;
    
}Segment;

typedef struct {
    //A vous de completer à votre convenance
    int x;
    int y;
    char* text;
    
}Text;

typedef union{
    Rectangle r; // 0
    Cercle cc;   // 1
    Segment s;   // 2
    Text txt;    // 3
    Polygon pp;  // 4
    
}Form;


typedef struct {
    //A vous de completer à votre convenance
    int size;
    int shape;
    Form* f;
    Color* cl;
    Color couleur;
}Drawing;

Drawing* createDrawing();
void freeDrawing(Drawing** d);
void displayDrawing(Drawing* d);
void addRectangle(Drawing* d, int x, int y, int width, int height);
void addCircle(Drawing* d, int x, int y, int radius);
void addSegment(Drawing* d, int x1, int y1, int x2, int y2);
void addText(Drawing* d, int x, int y, char* text);
void setColor(Drawing* d, Color c);
void startPolygon(Drawing* d);
void addPoint(Drawing* d, int x, int y);
void verifPolygon(Drawing* d, int index);
void exportSVG(Drawing* d, char* filename);

#endif