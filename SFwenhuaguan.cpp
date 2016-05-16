// COMP 550 SI2- Refactoring 
// Sep. 6 2011
// Wenhua Guan

#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
using namespace std;

class Point {
public:
	int x;
	int y;
	
	Point(int x, int y){
		this->x = x;
		this->y = y;
	}
	~Point(){}
	//Comparison by x, breaking ties by y
	bool LessThan(Point *q){
		return (x < q->x)||((x == q->x) && (y < q->y));
	}
	//To check whether P0P2 is on the left of P0P1 
static	int  Orientation(Point *P0, Point *P1, Point *P2){
		long  x1 = P2->x - P0->x;
		long  y1 = P2->y - P0->y;
		long  x2 = P1->x - P0->x;
		long  y2 = P1->y - P0->y;

		long area = x1*y2 - x2*y1;
		if(area > 0){
			return 1;    //left orientation
		}else if(area < 0){
			return -1;   // right orientation
		}else{
			return 0;     // colinear
		}
	}
};

class Segment{
public: 
	//Members
	Point *start;
	Point *end;
	int color;
	
	//constructor
	Segment(Point *s, Point *e, int c){
		start = s;
		end = e;
		color= c;
	};

	~Segment(){
		delete start;
		delete end;
	};

	// Comparision: Side
	int Side(Point *P){
		int side = Point :: Orientation(start, end , P);
		if(side > 0){
			return 1;  // P is on the left of segment
		}else if(side < 0){
			return -1; // P is on the right of segment
		}else{
			return 0;  // colinear
		}
	}

	// Check whether two Segments: this and Seg have intersections
static bool SEGEMENT_INTERSECT(Segment *Seg1, Segment *Seg2){
        
		int d1 = Seg1->Side(Seg2->start);
		int d2 = Seg1->Side(Seg2->end);
		int d3 = Seg2->Side(Seg1->start);
		int d4 = Seg2->Side(Seg1->end);
		
		if(d1*d2<0 && d3*d4<0){
        		return true;
		}else{	   
			return false;
		}
	}
};

int main(){
	int m, n, k;
	cin >> m >> n >> k;
	vector<Segment *> RedSeg;
	vector<Segment *> BlueSeg;
	
	//Read coordinates of segments into variables
	for (int i=0; i < m; i++){
		int x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		Point *P = new Point(x1, y1), *Q = new Point(x2, y2);
		Segment *s = new Segment(P, Q,0);
		RedSeg.push_back(s); //  red: color = 0; blue : color = 1; 
	}
	for(int j=0; j < n; j++){
		int x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		Point *P = new Point(x1,y1), *Q= new Point(x2,y2);
		Segment *s = new Segment(P,Q,1);
		BlueSeg.push_back(s);	
	
	}
	
	// Compute the number of the intersection points
	int NumIntersecs = 0;
   	for(int i = 0; i < m; i++ ){
	    for( int j = 0; j < n; j++){
			if(Segment::SEGEMENT_INTERSECT(RedSeg[i],BlueSeg[j])){
				NumIntersecs  = NumIntersecs  + 1;
			}
		}
	}
	
	// Verify
	if (NumIntersecs  == k){
		printf("VERIFIED!\n");
	}else{
		printf("Error: Calculation is wrong!\n");
		cout<< "Computed Number of Intersections = "<< NumIntersecs << endl;
		cout<< "True  Value of Intersections = "<<k<<endl;
	}

	//delete
	for (int i = 0; i < m; i++){
		delete RedSeg[i];
	}
	
	for (int i = 0; i < n; i++){
		delete BlueSeg[i];
	}

	return 0;

}
