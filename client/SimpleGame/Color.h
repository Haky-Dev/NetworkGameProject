#pragma

class Color {
public:
	Color() :r(1.f), g(1.f), b(1.f), a(1.f) {};
	Color(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {};
	~Color() {};

	float r, g, b, a;

public:
	const Color operator+(const Color& other) { return Color(this->r + other.r, this->g + other.g, this->b + other.b, this->a + other.a);}
	const Color operator-(const Color& other) { return Color(this->r - other.r, this->g - other.g, this->b - other.b, this->a - other.a);}
	const Color operator*(const float& value) { return Color(this->r * value, this->g * value, this->b * value, this->a * value); }
	const Color operator/(const float& value) { return Color(this->r / value, this->g / value, this->b / value, this->a / value); }

	Color& operator=(const Color& other) { this->r = other.r; this->g = other.g; return *this; }
	Color& operator+=(const Color& other) { this->r += other.r; this->g += other.g; return *this; }
	Color& operator-=(const Color& other) { this->r -= other.r; this->g -= other.g; return *this; }
	Color& operator*=(const float& value) { this->r *= value; this->g *= value; return *this; }
	Color& operator/=(const float& value) { this->r /= value; this->g /= value; return *this; }
	bool operator==(const Color& other) { return (this->r == other.r) && (this->g == other.g); }
};