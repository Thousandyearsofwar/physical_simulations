#include <iostream>
#include<algorithm>
#include<map>
#include<vector>
#include<stack>

using namespace std;
class point {
private:int x, y, z;
public:point();
	   point(int a, int b, int c);
	   ~point();
	   int getx();
	   int gety();
	   int getz();
	   int getdistance(point b) { return (pow((this->x - b.getx()), 2) + pow((this->y - b.gety()), 2) + pow((this->y - b.gety()), 2)); };
};
point::point() {};
point::point(int a, int b, int c) :x(a), y(b), z(c) {};
point::~point() {};
int point::getx() { return this->x; };
int point::gety() { return this->y; };
int point::getz() { return this->z; };



class vector3d {
private:int x, y, z;
		point start, end;
public:
	vector3d();
	~vector3d();
	vector3d(point start, point end) {
		x = end.getx() - start.getx();
		y = end.gety() - start.gety();
		z = end.getz() - start.getz();
		this->start = start;
		this->end = end;
	}
	vector3d(int x_, int y_, int z_) :x(x_), y(y_), z(z_) {}
	int getx() { return this->x; };
	int gety() { return this->y; };
	int getz() { return this->z; };
	point getstart() { return this->start; };
	point getend() { return this->end; };
	vector3d operator *(vector3d a);
	int operator &(vector3d a);
};
vector3d::vector3d()
{
}
vector3d::~vector3d()
{
}
vector3d vector3d::operator*(vector3d a)
{
	int temp_x = this->gety()*a.getz() - a.gety()*this->getz();
	int temp_y = this->getz()*a.getx() - a.getz()*this->getx();
	int temp_z = this->getx()*a.gety() - a.getx()*this->gety();
	return vector3d(temp_x, temp_y, temp_z);
}
int vector3d::operator&(vector3d a)
{
	return (this->x*a.getx() + this->y * a.gety() + this->z * a.getz());
}
vector3d operator-(point a, point b)
{
	return vector3d(a.getx() - b.getx(), a.gety() - b.gety(), a.getz() - b.getz());
}




class plane {
private:int A, B, C, D;
		vector3d normal;
public:
	plane();
	~plane();
	plane(int a, int b, int c, int d);
	plane(vector3d a, vector3d b, point c);
	vector3d getnormal();
	int getA();
	int getB();
	int getC();
	int getD();

};
plane::plane()
{
}
plane::~plane()
{
}
plane::plane(int a, int b, int c, int d) :A(a), B(b), C(c), D(d), normal(a, b, c) {};
plane::plane(vector3d a, vector3d b, point c) {
	this->normal = a * b;
	this->A = normal.getx();
	this->B = normal.gety();
	this->C = normal.getz();
	this->D = -(c.getx()*normal.getx() + c.gety()*normal.gety() + c.getz()*normal.getz());
};
vector3d plane::getnormal() { return this->normal; }
int plane::getA() { return this->A; };
int plane::getB() { return this->B; };
int plane::getC() { return this->C; };
int plane::getD() { return this->D; };


class ball {
private:
	point center;
	int radius;
public:
	ball(point a, int rad) :center(a), radius(rad) {}
	point getcenter() { return this->center; };
	int getradius() { return this->radius; };

};

bool test(point a, vector<point>target, int radius) {
	for (vector<point>::iterator poi_ite = target.begin(); poi_ite != target.end(); ++poi_ite)
		if (a.getdistance(*poi_ite) <= radius*radius)
			return true;
	return false;
}


class cuboid {
private:vector< point > point_vec;
		vector< plane > plane_set;
public:
	cuboid() {};
	~cuboid() {};
	cuboid(vector<point> point_set) {
		for (int i = 0; i < point_set.size(); i++)
			this->point_vec.push_back(point_set[i]);
		int point_size = point_set.size();
		vector<vector3d> temp_vector_set;
		int point1 = 0;
		int point2 = point1 + 1;
		int flag = 0;
		for (; point2 < point_size; ++point2)
			temp_vector_set.push_back(*new vector3d(point_set[point1], point_set[point2]));
		for (int i = 0; i < temp_vector_set.size() && flag != 1; i++) {
			for (int j = i + 1; j < temp_vector_set.size() && flag != 1; j++)
			{
				if ((temp_vector_set[i] & temp_vector_set[j]) == 0)
					for (int k = 0; k < temp_vector_set.size() && flag != 1; k++)
						if (k != i && k != j && !(temp_vector_set[k] & temp_vector_set[j]))
						{
							this->plane_set.push_back(*(new plane(temp_vector_set[i], temp_vector_set[j], temp_vector_set[k].getstart())));
							this->plane_set.push_back(*(new plane(temp_vector_set[i], temp_vector_set[j], temp_vector_set[k].getend())));
							this->plane_set.push_back(*(new plane(temp_vector_set[j], temp_vector_set[k], temp_vector_set[i].getstart())));
							this->plane_set.push_back(*(new plane(temp_vector_set[j], temp_vector_set[k], temp_vector_set[i].getend())));
							this->plane_set.push_back(*(new plane(temp_vector_set[i], temp_vector_set[k], temp_vector_set[j].getstart())));
							this->plane_set.push_back(*(new plane(temp_vector_set[i], temp_vector_set[k], temp_vector_set[j].getend())));
							flag = 1;
						}
			};
		};
	};
	vector<point> getpoint_set() { return this->point_vec; };
};


int main()
{
	int sample_num = 0;
	int x, y, z;
	int radius;
	cin >> sample_num;
	vector<cuboid> cube_set;
	vector<point> * point_set_ptr;
	vector<ball> ball_set;
	while (sample_num > 0)
	{
		point_set_ptr = new vector<point>;
		for (int i = 0; i < 8; i++) {
			cin >> x >> y >> z;
			point_set_ptr->push_back(*(new point(x, y, z)));
		}
		cube_set.push_back(*point_set_ptr);


		cin >> x >> y >> z>>radius;
		ball_set.push_back (*(new ball(*(new point(x, y, z)),radius)));
		sample_num--;
	}
	vector<cuboid>::iterator cube_ptr = cube_set.begin();
	for (vector<ball>::iterator ball_ptr = ball_set.begin() ; ball_ptr != ball_set.end(); ++ball_ptr,++cube_ptr) {
		if (test((*ball_ptr).getcenter(), (*cube_ptr).getpoint_set(), (*ball_ptr).getradius()))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}