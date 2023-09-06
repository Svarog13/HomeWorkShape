#include<iostream>
#include<string>
#include <vector>
#include <fstream>

class Shape
{
private:
	std::string name;
	std::string type;

public:
	Shape() : name("no name"), type("no type") {}
	Shape(const std::string& n, const std::string& t) : name(n), type(t) {}

	virtual void Show() const
	{
		std::cout << "Name: " << name << std::endl;
		std::cout << "Type: " << type << std::endl;
	}

	void Save(const std::string& filename)
	{
		std::ofstream file(filename);
		if (file.is_open())
		{
			file << name << "\n";
			file << type << "\n";
			SaveAdditionalData(file);
			file.close();
		}
		else
		{
			std::cerr << "Unable to open the file for saving: " << filename << std::endl;
		}
	}

	void Load(const std::string& filename)
	{
		std::ifstream file(filename);

		if (file.is_open())
		{
			std::getline(file, name);
			std::getline(file, type);
			LoadAdditionalData(file);
			file.close();
		}
		else
		{
			std::cerr << "Unable to open the file for loading: " << filename << std::endl;
		}
	}

	virtual double GetArea() const
	{
		return 0.0;
	}

protected:
	virtual void SaveAdditionalData(std::ofstream& file) {}
	virtual void LoadAdditionalData(std::ifstream& file) {}
};

class Rectangle : public Shape
{
private:
	double width;
	double height;

public:
	Rectangle() : width(0.0), height(0.0) {}
	Rectangle(const std::string& n, double w, double h) : Shape(n, "Rectangle"), width(w), height(h) {}

	void Show() const override
	{
		Shape::Show();
		std::cout << "Width: " << width << " units" << std::endl;
		std::cout << "Height: " << height << " units" << std::endl;
	}

	double GetArea() const override
	{
		return width * height;
	}

protected:
	void SaveAdditionalData(std::ofstream& file) override
	{
		file << width << "\n";
		file << height << "\n";

	}

	void LoadAdditionalData(std::ifstream& file) override
	{
		file >> width;
		file >> height;
	}
};

class Circle : public Shape
{
private:
	double radius;

public:
	Circle() : radius(0.0) {}
	Circle(const std::string& n, double r) : Shape(n, "Circle"), radius(r) {}

	void Show() const override
	{
		Shape::Show();
		std::cout << "Radius: " << radius << " units" << std::endl;
	}

	double GetArea() const override
	{
		return 3.14159265359 * radius * radius;
	}

protected:
	void SaveAdditionalData(std::ofstream& file) override
	{
		file << radius << "\n";
	}

	void LoadAdditionalData(std::ifstream& file) override
	{
		file >> radius;
	}
};

class Triangle : public Shape
{
private:
	double base;
	double height;

public:
	Triangle() : base(0.0), height(0.0) {}
	Triangle(const std::string& n, double b, double h) : Shape(n, "Triangle"), base(b), height(h) {}

	void Show() const override
	{
		Shape::Show();
		std::cout << "Base: " << base << " units" << std::endl;
		std::cout << "Height: " << height << " units" << std::endl;
	}

	double GetArea() const override
	{
		return 0.5 * base * height;
	}

protected:
	void SaveAdditionalData(std::ofstream& file) override
	{
		file << base << "\n";
		file << height << "\n";
	}

	void LoadAdditionalData(std::ifstream& file) override
	{
		file >> base;
		file >> height;
	}
};

class Trapezoid : public Shape
{
private:
	double topBase;
	double bottomBase;
	double height;

public:
	Trapezoid() : topBase(0.0), bottomBase(0.0), height(0.0) {}
	Trapezoid(const std::string& n, double td, double bb, double h)
		: Shape(n, "Trapezoid"), topBase(td), bottomBase(bb), height(h) {}

	void Show() const override
	{
		Shape::Show();
		std::cout << "Top Base: " << topBase << " units" << std::endl;
		std::cout << "Bottom Base: " << bottomBase << " units" << std::endl;
		std::cout << "Height: " << height << " units" << std::endl;
	}

	double GetArea() const override
	{
		return 0.5 * (topBase + bottomBase) * height;
	}

protected:
	void SaveAdditionalData(std::ofstream& file) override
	{
		file << topBase << "\n";
		file << bottomBase << "\n";
		file << height << "\n";
	}

	void LoadAdditionalData(std::ifstream& file) override
	{
		file >> topBase;
		file >> bottomBase;
		file >> height;
	}
};

void TestShape(const Shape& shape)
{
	shape.Show();
	std::cout << "Area: " << shape.GetArea() << " square units" << std::endl;
}

int main()
{
	Rectangle rect("Rectangle 1", 4.0, 5.0);
	Circle circle("Circle 1", 3.0);
	Triangle triangle("Triangle 1", 3.0, 4.0);
	Trapezoid trapezoid("Trapezoid 1", 2.0, 4.0, 3.0);

	rect.Save("rect.txt");
	circle.Save("circle.txt");
	triangle.Save("triangle.txt");
	trapezoid.Save("trapezoid.txt");

	Rectangle loadedRect;
	Circle loadedCircle;
	Triangle loadedTriangle;
	Trapezoid loadedTrapezoid;

	loadedRect.Load("rect.txt");
	loadedCircle.Load("circle.txt");
	loadedTriangle.Load("triangle.txt");
	loadedTrapezoid.Load("trapezoid.txt");

	std::cout << "Shapes loading from file." << std::endl;
	TestShape(loadedRect);
	std::cout << std::endl;
	TestShape(loadedCircle);
	std::cout << std::endl;
	TestShape(loadedTriangle);
	std::cout << std::endl;
	TestShape(loadedTrapezoid);
	std::cout << "Shapes save to file." << std::endl;

	return 0;
}