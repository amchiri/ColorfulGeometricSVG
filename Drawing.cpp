#include "Drawing.h"
#include <stdlib.h>
#include <stdio.h>

Drawing* createDrawing(){
    //A COMPLETER
    Drawing* d = (Drawing*)malloc(sizeof(Drawing) * 100);
    d->cl = (Color*)malloc(sizeof(Color));
    d->cl[0] = BLACK;
    d->size = 0;
    return d;
}


void freeDrawing(Drawing** d){
    //A COMPLETER
    for(int i= 0 ; i< d[0]->size;  i++){
        if(d[0][i].shape == 3){
            free(d[0][i].f->txt.text);
        }else if(d[0][i].shape == 4 || d[0][i].shape == 99){
             free(d[0][i].f->pp.p);
        }
        free(d[0][i].f);
    }
    free(d[0]->cl);
    free(*d);
    *d=NULL;
}


void displayDrawing(Drawing* d){
    //A COMPLETER
    int decret=0;
    for(int i= 0 ; i< d->size;  i++){
    verifPolygon(d,i);
    if(d[i].shape != 99){
    switch (d[i].couleur){
        case 0 :
            printf("%d : Black ",i - decret);
            break;
        case 1 :
            printf("%d : White ",i - decret);
            break;
        case 2 :
            printf("%d : Red ",i - decret);
            break;
        case 3 :
            printf("%d : Blue ",i - decret);
            break;
        case 4 :
            printf("%d : Green ",i - decret);
            break;
        case 5 :
            printf("%d : Yellow ",i - decret);
            break;
        
    }}else{
        decret++;
    }
    if(d[i].shape == 0 )printf("Rectangle at (%d,%d) size %d x %d \n",d[i].f->r.x,d[i].f->r.y,d[i].f->r.width,d[i].f->r.height);
    else if(d[i].shape == 1)printf("Circle at (%d,%d) radius %d\n",d[i].f->cc.x,d[i].f->cc.y,d[i].f->cc.rayon);
    else if(d[i].shape == 2 )printf("Segment from (%d,%d) to (%d,%d)\n",d[i].f->s.x1,d[i].f->s.y1,d[i].f->s.x2,d[i].f->s.y2);
    else if(d[i].shape == 3 )printf("Text %c%s%c at (%d,%d)\n",'"',d[i].f->txt.text,'"',d[i].f->txt.x,d[i].f->txt.y);
    else if(d[i].shape == 4){
        printf("Polygon ");
        
        for(int k=0 ; k<d[i].f->pp.taille ; k++){
            
            printf("(%d,%d) ",d[i].f->pp.p[k].x,d[i].f->pp.p[k].y);
        }
        printf("\n");
    }
    }

    
}


void addRectangle(Drawing* d, int x, int y, int width, int height){
    //A COMPLETER
    verifPolygon(d,d->size-1);
    d->size++;
    d[d->size-1].f = (Rectangle*)malloc(sizeof(Rectangle));
    d[d->size-1].shape = 0;
    d[d->size-1].f->r.x=x;
    d[d->size-1].f->r.y=y;
    d[d->size-1].f->r.width=width;
    d[d->size-1].f->r.height=height;
    d[d->size-1].couleur= d->cl[0];
    
}
void addCircle(Drawing* d, int x, int y, int radius){
    verifPolygon(d,d->size-1);
    d->size++;
    d[d->size-1].f = (Cercle*)malloc(sizeof(Cercle));
    d[d->size-1].shape = 1;
    d[d->size-1].f->cc.x=x;
    d[d->size-1].f->cc.y=y;
    d[d->size-1].f->cc.rayon = radius;
    d[d->size-1].couleur = d->cl[0];
    
}
void addSegment(Drawing* d, int x1, int y1, int x2, int y2){
    verifPolygon(d,d->size-1);
    d->size++;
    d[d->size-1].f = (Segment*)malloc(sizeof(Segment));
    d[d->size-1].shape = 2;
    d[d->size-1].f->s.x1=x1;
    d[d->size-1].f->s.y1=y1;
    d[d->size-1].f->s.x2=x2;
    d[d->size-1].f->s.y2=y2;
    d[d->size-1].couleur = d->cl[0];
   

}
void addText(Drawing* d, int x, int y, char* text){
    verifPolygon(d,d->size-1);
    d->size++;
    d[d->size-1].f = (Text*)malloc(sizeof(Text));
    d[d->size-1].f->txt.x=x;
    d[d->size-1].f->txt.y=y;
    d[d->size-1].shape = 3;
    d[d->size-1].f->txt.text = (char*)malloc(sizeof(char) * (strlen(text)+1));
    strcpy(d[d->size-1].f->txt.text,text);
    d[d->size-1].couleur= d->cl[0];
    
   
}

void setColor(Drawing* d, Color c ){
    if(c < 0 || c > 5){
        c = BLACK;
    }
    d->cl[0] = c ;
}

void startPolygon(Drawing* d){
    verifPolygon(d,d->size-1);
    d->size++;
    d[d->size-1].f = (Polygon*)malloc(sizeof(Polygon) );
    d[d->size-1].f->pp.p = (Point*)malloc(sizeof(Point) * 100);
    d[d->size-1].shape = 4;
    d[d->size-1].f->pp.taille=0;
    d[d->size-1].couleur= d->cl[0];
}

void addPoint(Drawing* d, int x, int y){
    if(d[d->size-1].shape != 4){
        printf("Error : no polygon started\n");
        return;
    }
    int t = d[d->size-1].f->pp.taille;
    d[d->size-1].f->pp.p[t].x = x;
    d[d->size-1].f->pp.p[t].y = y;
    d[d->size-1].f->pp.taille = t + 1;
}

void verifPolygon(Drawing* d, int index){
    if(d[index].shape != 4 ) return;
    int t = d[index].f->pp.taille;
    if(t>2) return;
    if(t<2){
        d[index].shape = 99;
    }else if(t==2){
    int x1,y1,x2,y2;
    x1=d[index].f->pp.p[0].x;
    x2=d[index].f->pp.p[1].x;
    y1=d[index].f->pp.p[0].y;
    y2=d[index].f->pp.p[1].y;
    free(d[index].f->pp.p);
    free(d[index].f);
    d[index].f = (Segment*)malloc(sizeof(Segment));
    d[index].shape = 2;
    d[index].f->s.x1=x1;
    d[index].f->s.y1=y1;
    d[index].f->s.x2=x2;
    d[index].f->s.y2=y2;
    }
}

void exportSVG(Drawing* d, char* filename){
    FILE* ptitsvg = fopen(filename,"w");
    fprintf(ptitsvg, "<svg width=\"500\" height=\"500\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    char temptext[500];
    for(int i= 0 ; i< d->size;  i++)
    {
        verifPolygon(d,i);
        if(d[i].shape != 99)
        {
            switch (d[i].couleur)
            {
            case 0 :
                strcpy(temptext, "Black");
                break;
            case 1 :
                strcpy(temptext, "White");
                break;
            case 2 :
               strcpy(temptext, "Red");
                break;
            case 3 :
                strcpy(temptext, "Blue");
                break;
            case 4 :
                strcpy(temptext, "Green");
                break;
            case 5 :
                strcpy(temptext,"Yellow");
                break;
            }
            
        }
        
        if(d[i].shape == 0 )
        {
            fprintf(ptitsvg, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"%s\" stroke=\"%s\" opacity=\"1\" stroke-width=\"1\"/>\n",
                    d[i].f->r.x, d[i].f->r.y, d[i].f->r.width, d[i].f->r.height, temptext,temptext);
        }
        else if(d[i].shape == 1){
            fprintf(ptitsvg,"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"%s\"  stroke=\"%s\" stroke-width=\"1\"/>",d[i].f->cc.x,d[i].f->cc.y,d[i].f->cc.rayon,temptext,temptext);
        }
        else if(d[i].shape == 2 ){
            fprintf(ptitsvg,"<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"%s\" stroke-width=\"2\"/>",d[i].f->s.x1,d[i].f->s.y1,d[i].f->s.x2,d[i].f->s.y2,temptext);
        }
        else if(d[i].shape == 3 ){
            fprintf(ptitsvg,"<text x=\"%d\" y=\"%d\" fill=\"%s\">%s</text>",d[i].f->txt.x,d[i].f->txt.y,temptext,d[i].f->txt.text);
        }
        else if(d[i].shape == 4){
            fprintf(ptitsvg,"<polygon points=\"");
            for(int k=0 ; k<d[i].f->pp.taille ; k++)
            {
            fprintf(ptitsvg,"%d,%d ",d[i].f->pp.p[k].x,d[i].f->pp.p[k].y);
            }
            fprintf(ptitsvg,"\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" />",temptext,temptext);
        }
    
    }
    fprintf(ptitsvg,"</svg>\n");
    fclose(ptitsvg);
    
}