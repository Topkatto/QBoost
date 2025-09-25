#include <bits/stdc++.h>

namespace qboost
{
    namespace misc
    {
        /**
        ** Two-dimensional vector struct.
        */
        template <typename T>
        struct Vector2D {
            T pos_x = 0;
            T pos_y = 0;
            T direction = 90;

            /**
            ** Represents the vector in coordinates and direction (x,y,direction)
            */

            Vector2D() = default;
            std::string _rep() {
                return '(' + std::to_string(pos_x) + ',' + std::to_string(pos_y) + ',' +
                    std::to_string(direction) + ')';
            }

            Vector2D(T x, T y) {
                pos_x = x;
                pos_y = y;
            }

            Vector2D(T x, T y, T dir) {
                pos_x = x;
                pos_y = y;
                direction = dir;
            }

            Vector2D& operator=(Vector2D a) {
                pos_x = a.pos_x;
                pos_y = a.pos_y;
                direction = a.direction;
                return *this;
            }

            Vector2D& operator=(std::pair<T, std::pair<T, T>> a) {
                pos_x = a.first;
                pos_y = a.second.first;
                direction = a.second.second;
                return *this;
            }
        };
        /**
        ** Three-dimensional vector struct.
        */
        template <typename T>
        struct Vector3D {
            T pos_x = 0;
            T pos_y = 0;
            T pos_z = 0;
            T direction = 90;

            Vector3D() = default;

            /**
            ** Represents the vector in coordinates and direction (x,y,z,direction)
            */
            std::string _rep() {
                return '(' + std::to_string(pos_x) + ',' + std::to_string(pos_y) + ',' +
                    std::to_string(pos_z) + ',' + std::to_string(direction) + ')';
            }

            Vector3D(T x, T y, T z) {
                pos_x = x;
                pos_y = y;
                pos_z = z;
            }

            Vector3D(T x, T y, T z, T dir) {
                pos_x = x;
                pos_y = y;
                pos_z = z;
                direction = dir;
            }

            Vector3D& operator=(Vector3D a) {
                pos_x = a.pos_x;
                pos_y = a.pos_y;
                pos_z = a.pos_z;
                direction = a.direction;
                return *this;
            }

            Vector3D& operator=(std::pair<T, std::pair<T, std::pair<T, T>>> a) {
                pos_x = a.first;
                pos_y = a.second.first;
                pos_z = a.second.second.first;
                direction = a.second.second.second;
                return *this;
            }
        };

        /**
        ** Two-dimensional point struct.
        */
        template <typename T>
        struct Point2D {
            T pos_x = 0;
            T pos_y = 0;

            Point2D() = default;

            /**
            ** Represents the vector in coordinates and direction (x,y)
            */
            std::string _rep() {
                return '(' + std::to_string(pos_x) + ',' + std::to_string(pos_y) + ')';
            }

            Point2D(T x, T y) {
                pos_x = x;
                pos_y = y;
            }

            Point2D& operator=(Point2D a) {
                pos_x = a.pos_x;
                pos_y = a.pos_y;
                return *this;
            }

            Point2D& operator=(std::pair<T, T> a) {
                pos_x = a.first;
                pos_y = a.second;
                return *this;
            }
        };

        /**
        ** Three-dimensional point struct.
        */
        template <typename T>
        struct Point3D {

            Point3D() = default;
            T pos_x = 0;
            T pos_y = 0;
            T pos_z = 0;

            /**
            ** Represents the vector in coordinates and direction (x,y,z)
            */
            std::string _rep() {
                return '(' + std::to_string(pos_x) + ',' + std::to_string(pos_y) + ',' +
                    std::to_string(pos_z) + ')';
            }
            Point3D(T x, T y, T z) {
                pos_x = x;
                pos_y = y;
                pos_z = z;
            }

            Point3D& operator=(Point3D a) {
                pos_x = a.pos_x;
                pos_y = a.pos_y;
                pos_z = a.pos_z;
                return *this;
            }

            Point3D& operator=(std::pair<T, std::pair<T, T>> a) {
                pos_x = a.first;
                pos_y = a.second.first;
                pos_z = a.second.second;
                return *this;
            }
        };

        /**
        ** Two-dimensional line struct.
        */
        template <typename T>
        struct Line2D {

            Line2D() = default;
            Point2D<T> line_start;
            Point2D<T> line_end;

            Line2D(Point2D<T> a, Point2D<T> b) : line_start(a), line_end(b) {}
            Line2D(std::pair<Point2D<T>, Point2D<T>> a)
                : line_start(a.first), line_end(a.second) {}

            Line2D& operator=(Line2D<T> d) {
                line_start = d.line_start;
                line_end = d.line_end;
                return *this;
            }
            Line2D& operator=(std::pair<Point2D<T>, Point2D<T>> a) {
                line_start = a.first;
                line_end = a.second;
                return *this;
            }
        };

        /**
        ** Three-dimensional line struct.
        */
        template <typename T>
        struct Line3D {
            Line3D() = default;
            Point3D<T> line_start;
            Point3D<T> line_end;
            Line3D(Point3D<T> a, Point3D<T> b) : line_start(a), line_end(b) {}
            Line3D(std::pair<Point3D<T>, Point3D<T>> a)
                : line_start(a.first), line_end(a.second) {}

            Line3D& operator=(std::pair<Point3D<T>, Point3D<T>> a) {
                line_start = a.first;
                line_end = a.second;
                return *this;
            }
            Line3D& operator=(Line3D<T> d) {
                line_start = d.line_start;
                line_end = d.line_end;
                return *this;
            }
        };

        /**
        ** Two-dimensional polygon struct.
        */
        template <typename T>
        struct Polygon2D {
            Polygon2D() = default;
            std::vector<Point2D<T>> vertices;
            Polygon2D(std::vector<Point2D<T>> _vertices) { vertices = _vertices; }
            Polygon2D& operator=(std::vector<Point2D<T>> _vertices) {
                vertices = _vertices;
                return *this;
            }
            Polygon2D& operator=(Polygon2D poly) {
                vertices = poly.vertices;
                return *this;
            }
        };

        /**
        ** Three-dimensional polygon struct.
        */
        template <typename T>
        struct Polygon3D {
            Polygon3D() = default;
            std::vector<Point3D<T>> vertices;
            Polygon3D(std::vector<Point3D<T>> _vertices) { vertices = _vertices; }
            Polygon3D& operator=(std::vector<Point3D<T>> _vertices) {
                vertices = _vertices;
                return *this;
            }
            Polygon3D& operator=(Polygon3D poly) {
                vertices = poly.vertices;
                return *this;
            }
        };

        /**
        ** Represents an fraction, as (a/b).
        *! Would not auto-reduce when constructed. To reduce fractions, use _reduce()
        *instead.
        */
        template <typename Num>
        struct Fraction {
            Num a = 1;
            Num b = 1;

            Fraction() = default;

            Fraction(std::pair<Num, Num> d) {
                a = d.first;
                b = d.second;
            }

            Fraction(Num _a, Num _b) {
                a = _a;
                b = _b;
            }

            /**
            ** Reduces the fraction.
            */
            void _reduce() {
                Num common = std::gcd(a, b);
                a /= common;
                b /= common;
            }

            bool _isSimplestForm() { return std::gcd(a, b) == 1; }

            /**
            ** Represents the fraction as string.
            */
            std::string _rep() { return std::to_string(a) + '/' + std::to_string(b); }

            /**
            ** Returns the decimal value of the fraction.
            */
            double value() { return static_cast<double>(a) / b; }

            Fraction& operator=(Fraction __A) {
                a = __A.a;
                b = __A.b;
                return *this;
            }

            Fraction& operator=(std::pair<Num, Num> __A) {
                a = __A.first;
                b = __A.second;
                return *this;
            }
        };

        template <typename T>
        class Keypoint
        {
            private:
                T key;
            public:
            T Get()
            {
                return key;
            }
            T Save(T object)
            {
                key = object;
            }
            Keypoint(T a)
            {
                key = a;
            }
        };

        template <typename T>
        struct Range
        {
            T min=0,max=0;
            Range()=default;
            Range(T m,T mx) {min=m;max=mx;}
            bool InRange(T t)
            {
                return (min >= t && t <= max);
            }
        };

        struct Iterator
        {
            long long pos = 0;
            Iterator() = default;
            Iterator(long long ps) {pos=ps;}
            void reset()
            {
                pos = 0;
            }
            void mleft()
            {
                pos--;
            }
            void mright()
            {
                pos++;
            }
        };

        template <typename A,typename B>
        class classification
        {
            private:A state;
            public:
            std::map<A, B> st;
            void add_state(A p, B k)
            {
                st[p]=k;
            }
            void remove_state(A p)
            {
                st.erase(p);
            }
            void set_state(A h)
            {
                state=h;
            }
            std::string get_state()
            {
                if (st.find(state) == st.end())
                {
                    return "";
                } else return st[state];
            }
            classification() = default;
            classification(std::map<A,B> k)
            {
                st = k;
            }
        };

        struct rgb
        {
            int r;
            int g;
            int b;
            rgb() = default;
            rgb(int rr, int rg, int rb)
            {
                r=rr;
                g=rg;
                b=rb;
            }
            void setColor(int rr, int rg, int rb)
            {
                r=rr;
                g=rg;
                b=rb;
            }
            bool operator==(const rgb& other) const {
                return r == other.r && g == other.g && b == other.b;
            }
            bool operator!=(const rgb& other) const {
                return r != other.r && g != other.g && b != other.b;
            }
        };
    }
}