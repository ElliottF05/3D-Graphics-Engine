#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

namespace graphics {

//---------------------------------------------------------------------------
// FORWARD DECLARATION OF STRUCTS
struct Vec3;

struct Point;
struct Line;
struct Triangle;

struct Camera;
struct World;

struct PixelArray;
struct ZBuffer;
struct Window;


//---------------------------------------------------------------------------
// DECLARING "Vec3"
struct Vec3 {
    float x,y,z;

    // constructors
    Vec3(float x, float y, float z);
    Vec3();

    // operations
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(const float scalar) const;
    Vec3 operator/(const float scalar) const;
    Vec3& operator+=(const Vec3& vec);
    Vec3& operator-=(const Vec3& vec);
    Vec3& operator*=(const float scalar);
    Vec3& operator/=(const float scalar);
    Vec3 cross(const Vec3& other) const;
    float dot(const Vec3& other) const;
    float mag() const;
    void normalize();
    float angleWith(const Vec3& other) const;

    // specific functions
    void rotateZ(float thetaZ);
    void rotateY(float thetaY);
    void rotate(float thetaZ, float thetaY);

    std::string toString();
};
// extra operators for Vec3
Vec3 operator*(const float scalar, const Vec3& vec);
Vec3 operator/(const float scalar, const Vec3& vec);



//---------------------------------------------------------------------------
// DECLARING "Point"
struct Point {
    Vec3 absolutePos, cameraPos, projectedPos, screenPos;
    float distToCamera;

    Point(Vec3 absolutePos);
    Point(float x, float y, float z);
    Point();

    void calculateCameraPos(const Camera& cam);
    void calculateProjectedPos();
    void calculateScreenPos(const Camera& cam, const Window& window);
    void calculateAll(const Camera& cam, const Window& window);

    void draw(const Camera& cam, const Window& window);

    std::string toString();
};


//---------------------------------------------------------------------------
// DECLARING "Line"
struct Line {
    Point p1, p2;

    Line(Point p1, Point p2);
    Line(Vec3 p1, Vec3 p2);
    Line();

    void draw(const Camera& cam, Window& window);
};


//---------------------------------------------------------------------------
// DECLARING "Triangle"
struct Triangle {
    static std::vector<Triangle> triangles;

    Point p1, p2, p3;
    Vec3 normal;
    int r,g,b;

    Triangle(Point p1, Point p2, Point p3);
    Triangle(Vec3 p1, Vec3 p2, Vec3 p3);
    Triangle();

    void draw(const Camera& cam, Window& window);
};



//---------------------------------------------------------------------------
// DECLARING "Camera"
struct Camera {
    Vec3 pos;
    float thetaZ, thetaY, fov, fov_rad, maxPlaneCoord;
    Vec3 direction;
    Vec3 floorDirection;

    Camera(Vec3 pos, float thetaZ, float thetaY, float fov);
    Camera();

    void moveRelative(float forward, float sideward, float upward);
    void rotate(float thetaZ, float thetaY);
    float getCameraYFromPixel(int x, int width) const;
    float getCameraZFromPixel(int y, int height) const;
};


//---------------------------------------------------------------------------
// DECLARING "World"
struct World { // TODO: incomplete and unused
    Camera cam;
    Vec3 sunDirection;
};



//---------------------------------------------------------------------------
// DECLARING "PixelArray"
struct PixelArray {
    int width, height;
    std::vector<int> data;

    PixelArray(int width, int height);

    int getIndex(int x, int y);
    void setPixel(int x, int y, int color);
    void setPixel(int x, int y, int r, int g, int b);
    int getPixelMonocolor(int x, int y);
    std::vector<int> getPixel(int x, int y);
    void clear();
};


//---------------------------------------------------------------------------
// DECLARING "ZBuffer"
struct ZBuffer {
    int width, height;
    std::vector<float> data;

    ZBuffer(int width, int height);

    int getIndex(int x, int y);
    void setDepth(int x, int y, float depth);
    float getDepth(int x, int y);
    void clear();
};


//---------------------------------------------------------------------------
// DECLARING "Window"
struct Window {
    int width, height;
    PixelArray pixelArray;
    ZBuffer zBuffer;
    sf::RenderWindow& sfmlWindow; // implementation specific

    Window(int width, int height, sf::RenderWindow& sfmlWindow);

    void drawPoint(Point& point);
    void drawLine(Line& line);
    void drawTriangle(Triangle& triangle, const Camera& cam);
    void draw(); // implementation specific
    void clear();
};


//---------------------------------------------------------------------------
// DECLARING "utils"
namespace utils {
    // using floats
    void sortPair(float& toLower, float& toHigher);
    void clampToRange(float& value, float min, float max);
    void clampToRange(float& value, float max);
    void sortAndClamp(float& toLower, float& toHigher, float min, float max);
    void sortAndClamp(float& toLower, float& toHigher, float max);

    // using ints
    void sortPair(int& toLower, int& toHigher);
    void clampToRange(int& value, int max);
    void sortAndClamp(int& toLower, int& toHigher, int max);
}

}