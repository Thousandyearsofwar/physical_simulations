
#include <iostream>
#include<vector>
using namespace std;

class point {
private:float x, y, z;
public:point();
	   point(float a, float b, float c);
	   ~point();
	   float getx();
	   float gety();
	   float getz();
	   float getdistance(point b) { return (pow((this->x - b.getx()), 2) + pow((this->y - b.gety()), 2) + pow((this->z - b.getz()), 2)); };
};
point::point() {};
point::point(float a, float b, float c) :x(a), y(b), z(c) {};
point::~point() {};
float point::getx() { return this->x; };
float point::gety() { return this->y; };
float point::getz() { return this->z; };

class vector3d {
private:float x, y, z;
		point start, end;
		float length_2;
public:
	vector3d();
	~vector3d();
	vector3d(point start, point end) {
		x = end.getx() - start.getx();
		y = end.gety() - start.gety();
		z = end.getz() - start.getz();
		this->start = start;
		this->end = end;
		length_2 = pow(x, 2) + pow(y, 2) + pow(z, 2);
	}
	vector3d(float x_, float y_, float z_) :x(x_), y(y_), z(z_) { length_2 = pow(x, 2) + pow(y, 2) + pow(z, 2); }
	float getx() { return this->x; };
	float gety() { return this->y; };
	float getz() { return this->z; };
	point getstart() { return this->start; };
	point getend() { return this->end; };
	float getlength_2() { return this->length_2; };
	vector3d operator *(vector3d a);
	vector3d operator -(vector3d a);
	float operator &(vector3d a);
};
vector3d::vector3d()
{
}
vector3d::~vector3d()
{
}
vector3d vector3d::operator*(vector3d a)
{
	float temp_x = this->gety()*a.getz() - a.gety()*this->getz();
	float temp_y = this->getz()*a.getx() - a.getz()*this->getx();
	float temp_z = this->getx()*a.gety() - a.getx()*this->gety();
	return vector3d(temp_x, temp_y, temp_z);
}
float vector3d::operator&(vector3d a)
{
	return (this->x*a.getx() + this->y * a.gety() + this->z * a.getz());
}

vector3d vector3d:: operator-(vector3d a)
{
	return vector3d(this->getx() - a.getx(), this->gety() - a.gety(), this->getz() - a.getz());
}

vector3d operator-(point a, point b)
{
	return vector3d(a.getx() - b.getx(), a.gety() - b.gety(), a.getz() - b.getz());
}



class ball {
private:
	point center;
	float radius;
public:
	ball(point a, float rad) :center(a), radius(rad) {}
	ball() {}
	point getcenter() { return this->center; };
	float getradius() { return this->radius; };

};

bool test(point a, vector<point>target, float radius) {
	vector<point>::iterator min_poi = target.begin();
	float center[3] = { 0,0,0 };
	for (vector<point>::iterator poi_ite = target.begin(); poi_ite != target.end(); ++poi_ite)
	{
		if ((*min_poi).getdistance(a) > (*poi_ite).getdistance(a))
			min_poi = poi_ite;
		center[0] += (*poi_ite).getx();
		center[1] += (*poi_ite).gety();
		center[2] += (*poi_ite).getz();
	}

	center[0] /= 8;
	center[1] /= 8;
	center[2] /= 8;
	vector3d v(abs(a.getx() - center[0]), abs(a.gety() - center[1]), abs(a.getz() - center[2]));
	vector3d h(*new point(0, 0, 0), *new point(abs(center[0]), abs(center[1]), abs(center[2])));
	vector3d  u = v - h;
	if (u.getx() < 0)
		u = vector3d(0, u.gety(), u.getz());
	if (u.gety() < 0)
		u = vector3d(u.getx(), 0, u.getz());
	if (u.getz() < 0)
		u = vector3d(u.getx(), u.gety(), 0);
	if (!(u.getx() && u.gety() && u.getz()))
	{
		if (v.getx() + radius > h.getx() && v.gety() + radius > h.gety() && v.getz() + radius > h.getz())
			return false;
		if (v.getx() + radius < h.getx() && v.gety() + radius < h.gety() && v.getz() + radius < h.getz())
			return false;
		else
			return true;
	}
	else
		return (u.getlength_2() <= radius * radius);
};

class cuboid {
private:vector< point > point_vec;
		vector< vector3d > vec3d_vec;
public:
	cuboid() {};
	~cuboid() {};
	vector<point> getpoint_set() { return this->point_vec; };
	cuboid(vector<point> point_set) {
		point_vec.insert(point_vec.begin(), point_set.begin(), point_set.end());
	};
};


int main()
{
	int sample_num = 0;
	float x, y, z;
	float radius;
	cin >> sample_num;
	int num = sample_num;
	cuboid *cube_set = new cuboid[sample_num];
	vector<point> * point_set_ptr;
	ball * ball_set = new ball[sample_num];
	for (int i = 0; i < sample_num; i++)
	{
		point_set_ptr = new vector<point>;
		for (int i = 0; i < 8; i++) {
			cin >> x >> y >> z;
			point_set_ptr->push_back(*(new point(x, y, z)));
		}
		cube_set[i] = cuboid(*point_set_ptr);


		cin >> x >> y >> z >> radius;
		ball_set[i] = ball(*(new ball(*(new point(x, y, z)), radius)));
		sample_num--;
	}

	for (int i = 0; i < num; i++) {
		if (test(ball_set[i].getcenter(), cube_set[i].getpoint_set(), ball_set[i].getradius()))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}

/*class vector3d {
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
*/

/*#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include<algorithm>
#define T double
T c(T x, T y, T r) { return sqrt(x*x + y * y) - r; }
T u(T x, T y, T t) { return x * cos(t) + y * sin(t); }
T v(T x, T y, T t) { return y * cos(t) - x * sin(t); }
T fa(T x, T y) { return fmin(c(x, y, 0.5), c(x*0.47 + 0.15, y + 0.25, 0.3)); }
T no(T x, T y) { return c(x*1.2 + 0.97, y + 0.25, 0.2); }
T nh(T x, T y) { return fmin(c(x + 0.9, y + 0.25, 0.03), c(x + 0.75, y + 0.25, 0.03)); }
T ea(T x, T y) { return fmin(c(x*1.7 + 0.3, y + 0.7, 0.15), c(u(x, y, 0.25)*1.7, v(x, y, 0.25) + 0.65, 0.15)); }
T ey(T x, T y) { return fmin(c(x + 0.4, y + 0.35, 0.1), c(x + 0.15, y + 0.35, 0.1)); }
T pu(T x, T y) { return fmin(c(x + 0.38, y + 0.33, 0.03), c(x + 0.13, y + 0.33, 0.03)); }
T fr(T x, T y) { return c(x*1.1 - 0.3, y + 0.1, 0.15); }
T mo(T x, T y) { return fmax(c(x + 0.15, y - 0.05, 0.2), -c(x + 0.15, y, 0.25)); }
T o(T x, T y, T(*f)(T, T), T i) { T r = f(x, y); return fabs(r) < 0.02 ? (atan2(f(x, y + 1e-3) - r, f(x + 1e-3, y) - r) + 0.3)*1.273 + 6.5 : r < 0 ? i : 0; }
T s(T x, T y, T(*f)(T, T), T i) { return f(x, y) < 0 ? i : 0; }
T f(T x, T y) { return o(x, y, no, 1) ? fmax(o(x, y, no, 1), s(x, y, nh, 12)) : fmax(o(x, y, fa, 1), fmax(o(x, y, ey, 11), fmax(o(x, y, ea, 1), fmax(o(x, y, mo, 1), fmax(s(x, y, fr, 13), s(x, y, pu, 12)))))); }
int main(int a, char**b) { 
	for (T y = -1, s = a > 8 ? strtod(b[8], 0) : 8 ; y < 0.6; y += 0.05 / s, putchar('\n'))
	for (T x = -1; x < 0.6; x += 0.025 / s)
		putchar(" .|/=\\|/=\\| @!"[(int)f(u(x, y, 0.3), v(x, y, 0.3))]); 
}*/

/*作者：Milo Yip
链接：https ://zhuanlan.zhihu.com/p/37031514
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
/*class cuboid {
private:vector< point > point_vec;
		vector< plane > plane_set;
public:
	cuboid() {};
	~cuboid() {};
	vector<point> getpoint_set() { return this->point_vec; };
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
*/
/*
1
0 0 0 0 0 4 0 4 0 4 0 0 4 4 0 4 0 4 0 4 4 4 4 4
1 1 1 1
*/