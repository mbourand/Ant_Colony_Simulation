#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector
{
	private:
		int x;
		int y;

	public:
		Vector();
		Vector(const Vector& v);
		Vector(const int& x, const int& y);

		~Vector();

		void operator=(const Vector& other);
		bool operator==(const Vector& other) const;
		bool operator!=(const Vector& other) const;
		Vector operator+(const Vector& other) const;
		Vector operator-(const Vector& other) const;

		int distanceSq(const Vector& v2) const;

		int getX() const;
		int getY() const;
		void setX(const int& x);
		void setY(const int& y);
};

#endif