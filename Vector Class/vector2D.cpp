#include <iostream>
#include <cmath>

class Vector2D {
public:
    double xs{}, ys{};
    double xe{}, ye{};

    Vector2D() = default;

    Vector2D(const double x_start, const double y_start,
             const double x_end, const double y_end)
        : xs(x_start), ys(y_start), xe(x_end), ye(y_end) {
    }

    [[nodiscard]] double x() const { return xe - xs; }
    [[nodiscard]] double y() const { return ye - ys; }

    [[nodiscard]] double length() const {
        return std::sqrt(x() * x() + y() * y());
    }

    [[nodiscard]] double dot(const Vector2D &other) const {
        return x() * other.x() + y() * other.y();
    }

    [[nodiscard]] static double cos_angle(const Vector2D &a,
                                          const Vector2D &b) {
        return a.dot(b) / (a.length() * b.length());
    }

    [[nodiscard]] static double angle_rad(const Vector2D &a,
                                          const Vector2D &b) {
        return std::acos(cos_angle(a, b));
    }

    Vector2D operator+(const Vector2D &other) const {
        return Vector2D(
            xs,
            ys,
            xs + x() + other.x(),
            ys + y() + other.y()
        );
    }

    Vector2D operator-(const Vector2D &other) const {
        return Vector2D(
            xs,
            ys,
            xs + x() - other.x(),
            ys + y() - other.y()
        );
    }

    Vector2D operator*(double k) const {
        return Vector2D(
            xs,
            ys,
            xs + x() * k,
            ys + y() * k
        );
    }

    void print() const {
        std::cout << "Vector: (" << xs << ", " << ys
                << ") -> (" << xe << ", " << ye << ")\n";
    }
};
