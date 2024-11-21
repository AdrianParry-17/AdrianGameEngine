#ifndef __ENGINE_STRUCTURE_H__
#define __ENGINE_STRUCTURE_H__

#include "Engine_Define.h"
#include "Engine_Enum.h"

#include <math.h>

namespace Engine {
    struct Size;

    /// @brief The Point struct, represent a pair of two-dimensional integer coordinate (x, y). Usually for screen coordinate.
    struct Point {
    public:
        /// @brief The x value (position along the x-axis) of the Point.
        int X = 0;
        /// @brief The y value (position along the y-axis) of the Point.
        int Y = 0;

        /// @brief Create a new Point, and set all value to 0.
        Point() = default;
        /// @brief Create a new Point, with x and y are both set to the given value.
        /// @param XY The value of x and y to set.
        Point(int XY) : X(XY), Y(XY) {}
        /// @brief Create a new Point.
        /// @param X The x value (position along the x-axis) of the Point.
        /// @param Y The y value (position along the y-axis) of the Point.
        Point(int X, int Y) : X(X), Y(Y) {}
        /// @brief Create a new Point, with x and y value are the width and height of the given Size.
        /// @param s The Size to create.
        Point(const Size& s);

        /// @brief Create a copy of the given Point.
        /// @param p The Point to copy.
        Point(const Point& p) : X(p.X), Y(p.Y) {}

        operator Size() const;

        Point& operator=(const Point& p) { X = p.X; Y = p.Y; return *this; }
        Point& operator=(int xy) { X = xy; Y = xy; return *this; }

        Point& operator+=(const Point& p) { X += p.X; Y += p.Y; return *this; }
        Point& operator+=(int xy) { X += xy; Y += xy; return *this; }
        Point operator+(const Point& p) const { return {X + p.X, Y + p.Y}; }
        Point operator+(int xy) const { return {X + xy, Y + xy}; }
        friend Point operator+(int xy, const Point& p) { return {xy + p.X, xy + p.Y}; }

        Point& operator-=(const Point& p) { X -= p.X; Y -= p.Y; return *this; }
        Point& operator-=(int xy) { X -= xy; Y -= xy; return *this; }
        Point operator-(const Point& p) const { return {X - p.X, Y - p.Y}; }
        Point operator-(int xy) const { return {X - xy, Y - xy}; }
        friend Point operator-(int xy, const Point& p) { return {xy - p.X, xy - p.Y}; }

        Point& operator*=(const Point& p) { X *= p.X; Y *= p.Y; return *this; }
        Point& operator*=(int xy) { X *= xy; Y *= xy; return *this; }
        Point operator*(const Point& p) const { return {X * p.X, Y * p.Y}; }
        Point operator*(int xy) const { return {X * xy, Y * xy}; }
        friend Point operator*(int xy, const Point& p) { return {xy * p.X, xy * p.Y}; }

        bool operator==(const Point& p) const { return X == p.X && Y == p.Y; }
        bool operator==(int xy) const { return X == xy && Y == xy; }
        friend bool operator==(int xy, const Point& p) { return xy == p.X && xy == p.Y; }

        bool operator!=(const Point& p) const { return X != p.X || Y != p.Y; }
        bool operator!=(int xy) const { return X != xy || Y != xy; }
        friend bool operator!=(int xy, const Point& p) { return xy != p.X || xy != p.Y; }

        /// @brief Calculate the distance between the two given Point.
        /// @param a The first Point (the starting Point).
        /// @param b The second Point (the ending Point).
        /// @return The distance between the two given Point.
        static double Distance(const Point& a, const Point& b) { return hypot(b.X - a.X, b.Y - a.Y); }

        /// @brief The Zero Point, x and y value are 0 (0, 0)
        static const Point Zero;
        /// @brief The One Point, x and y value are 1 (1, 1)
        static const Point One;
        /// @brief The Up Point, x is 0 and y is 1 (0, 1) 
        static const Point Up;
        /// @brief The Down Point, x is 0 and y is -1 (0, -1) 
        static const Point Down;
        /// @brief The Left Point, x is -1 and y is 0 (-1, 0) 
        static const Point Left;
        /// @brief The Right Point, x is 1 and y is 0 (1, 0) 
        static const Point Right;
    };

    /// @brief The Size struct, represent the size of a two-dimensional integer rectangle. Usually for screen coordinate.
    struct Size {
    public:
        /// @brief The width of the Size (along the x-axis).
        int Width = 0;
        /// @brief The height of the Size (along the y-axis).
        int Height = 0;

        /// @brief Create a new Size, and set all value to 0.
        Size() = default;
        /// @brief Create a new Size, with width and height are both set to the given value.
        /// @param WH The value of width and height to set.
        Size(int WH) : Width(WH), Height(WH) {}
        /// @brief Create a new Size.
        /// @param Width The width of the Size (along the x-axis).
        /// @param Height The height of the Size (along the y-axis).
        Size(int Width, int Height) : Width(Width), Height(Height) {}
        /// @brief Create a new Size, with width and height value are the x and y of the given Point.
        /// @param p The Point to create.
        Size(const Point& p) : Width(p.X), Height(p.Y) {}

        /// @brief Create a copy of the given Size.
        /// @param p The Size to copy.
        Size(const Size& p) : Width(p.Width), Height(p.Height) {}

        operator Point() const { return Point(Width, Height); }

        Size& operator=(const Size& s) { Width = s.Width; Height = s.Height; return *this; }
        Size& operator=(int wh) { Width = wh; Height = wh; return *this; }

        Size& operator+=(const Size& s) { Width += s.Width; Height += s.Height; return *this; }
        Size& operator+=(int wh) { Width += wh; Height += wh; return *this; }
        Size operator+(const Size& s) const { return {Width + s.Width, Height + s.Height}; }
        Size operator+(int wh) const { return {Width + wh, Height + wh}; }
        friend Size operator+(int wh, const Size& s) { return {wh + s.Width, wh + s.Height}; }

        Size& operator-=(const Size& s) { Width -= s.Width; Height -= s.Height; return *this; }
        Size& operator-=(int wh) { Width -= wh; Height -= wh; return *this; }
        Size operator-(const Size& s) const { return {Width - s.Width, Height - s.Height}; }
        Size operator-(int wh) const { return {Width - wh, Height - wh}; }
        friend Size operator-(int wh, const Size& s) { return {wh - s.Width, wh - s.Height}; }

        Size& operator*=(const Size& s) { Width *= s.Width; Height *= s.Height; return *this; }
        Size& operator*=(int wh) { Width *= wh; Height *= wh; return *this; }
        Size operator*(const Size& s) const { return {Width * s.Width, Height * s.Height}; }
        Size operator*(int wh) const { return {Width * wh, Height * wh}; }
        friend Size operator*(int wh, const Size& s) { return {wh * s.Width, wh * s.Height}; }

        bool operator==(const Size& s) const { return Width == s.Width && Height == s.Height; }
        bool operator==(int wh) const { return Width == wh && Height == wh; }
        friend bool operator==(int wh, const Size& s) { return wh == s.Width && wh == s.Height; }

        bool operator!=(const Size& s) const { return Width != s.Width || Height != s.Height; }
        bool operator!=(int wh) const { return Width != wh || Height != wh; }
        friend bool operator!=(int wh, const Size& s) { return wh != s.Width || wh != s.Height; }

        /// @brief Create a new Size with the width and height value are the absolute value of this Size width and height.
        /// @return The absolute Size of this Size.
        Size Absolute() const { return Size(abs(Width), abs(Height)); }

        /// @brief Calculate the ratio (width / height) of the Size.
        /// @return The ratio (width / height) of the Size.
        double Ratio() const { return fabs(Width) / fabs(Height); }
    
        /// @brief Check if the area of the Size represent is 0.
        /// @return true if the Size area is empty, false otherwise.
        bool IsEmptyArea() const { return Width == 0 || Height == 0; }

        /// @brief Calculate the area that the Size represent.
        /// @return The area of the Size.
        long long Area() const { return llabs(Width) * llabs(Height); }

        /// @brief Create a new Size with the given ratio (width / height).
        /// @param Ratio The ratio of the size (width / height) to create.
        /// @param Height The height of the size (along the y-axis).
        /// @return The newly created Size.
        static Size FromRatio(double Ratio, int Height) { return Size((int)abs(Ratio * Height), abs(Height)); }
        
        /// @brief Create a new Size with the given ratio (width / height) and width.
        /// @param Ratio The ratio of the size (width / height) to create.
        /// @param Width The width of the size (along the x-axis).
        /// @return The newly created Size.
        static Size FromRatioWithWidth(double Ratio, int Width) { return Size(abs(Width), (int)abs((double)Width / Ratio)); }

        /// @brief The Zero Size, width and height value are 0 (0, 0)
        static const Size Zero;
        /// @brief The One Size, width and height value are 1 (1, 1)
        static const Size One;
        /// @brief The Up Size, width is 0 and height is 1 (0, 1) 
        static const Size Up;
        /// @brief The Down Size, width is 0 and height is -1 (0, -1) 
        static const Size Down;
        /// @brief The Left Size, width is -1 and height is 0 (-1, 0) 
        static const Size Left;
        /// @brief The Right Size, width is 1 and height is 0 (1, 0) 
        static const Size Right;
    };


    /// @brief The Rectangle struct, represent a two-dimensional integer rectangle. Usually for screen coordinate.
    struct Rectangle {
    public:
        /// @brief The x position of the Rectangle (usually top-left) corner.
        int X = 0;
        /// @brief The y position of the Rectangle (usually top-left) corner.
        int Y = 0;
        /// @brief The width of the Rectangle (along the x direction).
        int Width = 0;
        /// @brief The height of the Rectangle (along the y direction).
        int Height = 0;

        /// @brief Create a new empty Rectangle.
        Rectangle() = default;
        /// @brief Create a new Rectangle.
        /// @param p The position of the Rectangle (usually top-left) corner.
        /// @param s The size of the Rectangle.
        Rectangle(const Point& p, const Size& s) : X(p.X), Y(p.Y), Width(s.Width), Height(s.Height) {}
        /// @brief Create a new Rectangle.
        /// @param x The x position of the Rectangle (usually top-left) corner.
        /// @param y The y position of the Rectangle (usually top-left) corner.
        /// @param w The width of the Rectangle (along the x direction).
        /// @param h The height of the Rectangle (along the y direction).
        Rectangle(int x, int y, int w, int h) : X(x), Y(y), Width(w), Height(h) {}

        Rectangle(const Rectangle& r) : X(r.X), Y(r.Y), Width(r.Width), Height(r.Height) {}

        operator Point() const { return {X, Y}; }
        operator Size() const { return {Width, Height}; }

        Rectangle& operator=(const Rectangle& r) { X = r.X; Y = r.Y; Width = r.Width; Height = r.Height; return *this; }

        /// @brief Get a top-left Rectangle that identical to this Rectangle.
        /// @return A top-left Rectangle that identical to this Rectangle.
        Rectangle TopLeftRectangle() const { return {LeftSide(), RightSide(), abs(Width), abs(Height)}; }

        /// @brief Check if this Rectangle is a top-left Rectangle.
        /// @return true if this Rectangle is a top-left Rectangle, false otherwise.
        bool IsTopLeftRectangle() const { return Width >= 0 && Height >= 0; }
        /// @brief Check if this Rectangle is a top-right Rectangle.
        /// @return true if this Rectangle is a top-right Rectangle, false otherwise.
        bool IsTopRightRectangle() const { return Width < 0 && Height >= 0; }
        /// @brief Check if this Rectangle is a bottom-left Rectangle.
        /// @return true if this Rectangle is a bottom-left Rectangle, false otherwise.
        bool IsBottomLeftRectangle() const { return Width >= 0 && Height < 0; }
        /// @brief Check if this Rectangle is a bottom-right Rectangle.
        /// @return true if this Rectangle is a bottom-right Rectangle, false otherwise.
        bool IsBottomRightRectangle() const { return Width < 0 && Height < 0; }

        /// @brief Check if the area of the Rectangle is 0.
        /// @return true if the area of the Rectangle is empty, false otherwise.
        bool IsEmptyArea() const { return Width == 0 || Height == 0; }
        /// @brief Calculate the area of the Rectangle.
        /// @return The area of the Rectangle.
        long long Area() const { return llabs(Width) * llabs(Height); }

        /// @brief Set the position of the Rectangle (usually top-left) corner.
        /// @param p The position to set.
        void SetPosition(const Point& p) { X = p.X; Y = p.Y; }
        /// @brief Get the position of the Rectangle (usually top-left) corner.
        /// @return The position of the Rectangle.
        Point GetPosition() const { return {X, Y}; }

        /// @brief Set the size of the Rectangle.
        /// @param s The size to set.
        void SetSize(const Size& s) { Width = s.Width; Height = s.Height; }
        /// @brief Get the size of the Rectangle.
        /// @return The size of the Rectangle.
        Size GetSize() const { return {Width, Height}; }
        /// @brief Get the absolute size of the Rectangle (similar to GetSize().Absolute()).
        /// @return The absolute size of the Rectangle.
        Size GetAbsoluteSize() const { return {abs(Width), abs(Height)}; }

        /// @brief Get the position (along the x direction) of the left side of the Rectangle.
        /// @return The position of the left side of the Rectangle.
        int LeftSide() const { return Width < 0 ? X + Width + 1 : X; }
        /// @brief Get the position (along the x direction) of the right side of the Rectangle.
        /// @return The position of the right side of the Rectangle.
        int RightSide() const { return Width > 0 ? X + Width - 1 : X; }
        /// @brief Get the position (along the x direction) of the center between the left and right the Rectangle.
        /// @return The position of the center between left and right side of the Rectangle.
        int CenterSide() const { return X + (Width / 2); }
        /// @brief Get the position (along the y direction) of the top side of the Rectangle.
        /// @return The position of the top side of the Rectangle.
        int TopSide() const { return Height < 0 ? Y + Height + 1 : Y; }
        /// @brief Get the position (along the y direction) of the bottom side of the Rectangle.
        /// @return The position of the bottom side of the Rectangle.
        int BottomSide() const { return Height > 0 ? Y + Height - 1 : Y; }
        /// @brief Get the position (along the y direction) of the middle between the top and bottom the Rectangle.
        /// @return The position of the middle between top and bottom side of the Rectangle.
        int MiddleSide() const { return X + (Height / 2); }

        /// @brief Get the top-left corner position of the Rectangle.
        /// @return The top-left position of the Rectangle.
        Point TopLeft() const { return {LeftSide(), TopSide()}; }
        /// @brief Get the top-center position of the Rectangle.
        /// @return The top-center position of the Rectangle.
        Point TopCenter() const { return {CenterSide(), TopSide()}; }
        /// @brief Get the top-right corner position of the Rectangle.
        /// @return The top-right position of the Rectangle.
        Point TopRight() const { return {RightSide(), TopSide()}; }
        /// @brief Get the middle-left position of the Rectangle.
        /// @return The middle-left position of the Rectangle.
        Point MiddleLeft() const { return {LeftSide(), MiddleSide()}; }
        /// @brief Get the middle-center position of the Rectangle.
        /// @return The middle-center position of the Rectangle.
        Point MiddleCenter() const { return {CenterSide(), MiddleSide()}; }
        /// @brief Get the middle-right position of the Rectangle.
        /// @return The middle-right position of the Rectangle.
        Point MiddleRight() const { return {RightSide(), MiddleSide()}; }
        /// @brief Get the bottom-left corner position of the Rectangle.
        /// @return The bottom-left position of the Rectangle.
        Point BottomLeft() const { return {LeftSide(), BottomSide()}; }
        /// @brief Get the bottom-center position of the Rectangle.
        /// @return The bottom-center position of the Rectangle.
        Point BottomCenter() const { return {CenterSide(), BottomSide()}; }
        /// @brief Get the bottom-right corner position of the Rectangle.
        /// @return The bottom-right position of the Rectangle.
        Point BottomRight() const { return {RightSide(), BottomSide()}; }

        /// @brief Check if the Rectangle is contain the given Point.
        /// @param p The Point to check.
        /// @return true if the Rectangle is contain the given Point, false otherwise.
        bool IsContain(const Point& p) const {
            return p.X >= LeftSide() && p.X <= RightSide() && p.Y >= TopSide() && p.Y <= BottomSide();
        }
        /// @brief Check if the Rectangle is contain the given Rectangle.
        /// @param r The Rectangle to check.
        /// @return true if this Rectangle is contain the given Rectangle, false otherwise.
        bool IsContain(const Rectangle& r) const {
            int left = LeftSide(), right = RightSide(), top = TopSide(), bottom = BottomSide();
            Point tl = r.TopLeft(), br = r.BottomRight();
            return tl.X >= left && tl.X <= right && tl.Y >= top && tl.Y <= bottom   // Top-Left check
                && br.X >= left && br.X <= right && br.Y >= top && br.Y <= bottom;  // Bottom-Right check
        }

        /// @brief Calculate the smallest Rectangle that contain this Rectangle and the given Point.
        /// @param p The Point to calculate.
        /// @return The smallest Rectangle that contain both this Rectangle and the given Point.
        Rectangle UnionWith(const Point& p) const { return Union(*this, p); }
        /// @brief Calculate the smallest Rectangle that contain this Rectangle and the given Rectangle.
        /// @param p The other Rectangle to calculate.
        /// @return The smallest Rectangle that contain both this and the given Rectangle.
        Rectangle UnionWith(const Rectangle& r) const { return Union(*this, r); }

        /// @brief Calculate the global position of a local position that related to this Rectangle.
        /// @param LocalPosition The local position to calculate. (0, 0) mean the Rectangle top-left corner.
        /// @return The global position of the given local position that related to this Rectangle.
        Point LocalToGlobal(const Point& LocalPosition) const { return Point(LocalPosition.X + LeftSide(), LocalPosition.Y + TopSide()); }
        /// @brief Calculate the global rectangle of a local rectangle that related to this Rectangle.
        /// @param LocalRectangle The local rectangle to calculate.
        /// @param Alignment The alignment that the given Rectangle is related to this Rectangle. Default is TopLeft.
        /// @return The global rectangle of the given local rectangle that related to this Rectangle.
        Rectangle LocalToGlobal(const Rectangle& LocalRectangle, RectangleAlignment Alignment = RectangleAlignment::TopLeft) const {
            switch (Alignment)
            {
            case RectangleAlignment::TopCenter:
                return Rectangle(
                    LeftSide() + LocalRectangle.LeftSide() + ((abs(Width) - abs(LocalRectangle.Width)) / 2),
                    TopSide() + LocalRectangle.TopSide(),
                    abs(LocalRectangle.Width), abs(LocalRectangle.Height));
            case RectangleAlignment::TopRight:
                return Rectangle(
                    LeftSide() + LocalRectangle.LeftSide() + (abs(Width) - abs(LocalRectangle.Width)),
                    TopSide() + LocalRectangle.TopSide(),
                    abs(LocalRectangle.Width), abs(LocalRectangle.Height));
            case RectangleAlignment::MiddleLeft:
                return Rectangle(
                    LeftSide() + LocalRectangle.LeftSide(),
                    TopSide() + LocalRectangle.TopSide() + ((abs(Height) - abs(LocalRectangle.Height)) / 2),
                    abs(LocalRectangle.Width), abs(LocalRectangle.Height));
            case RectangleAlignment::MiddleCenter:
                return Rectangle(
                    LeftSide() + LocalRectangle.LeftSide() + ((abs(Width) - abs(LocalRectangle.Width)) / 2),
                    TopSide() + LocalRectangle.TopSide() + ((abs(Height) - abs(LocalRectangle.Height)) / 2),
                    abs(LocalRectangle.Width), abs(LocalRectangle.Height));
            case RectangleAlignment::MiddleRight:
                return Rectangle(
                    LeftSide() + LocalRectangle.LeftSide() + (abs(Width) - abs(LocalRectangle.Width)),
                    TopSide() + LocalRectangle.TopSide() + ((abs(Height) - abs(LocalRectangle.Height)) / 2),
                    abs(LocalRectangle.Width), abs(LocalRectangle.Height));
            case RectangleAlignment::BottomLeft:
                return Rectangle(
                    LeftSide() + LocalRectangle.LeftSide(),
                    TopSide() + LocalRectangle.TopSide() + (abs(Height) - abs(LocalRectangle.Height)),
                    abs(LocalRectangle.Width), abs(LocalRectangle.Height));
            case RectangleAlignment::BottomCenter:
                return Rectangle(
                    LeftSide() + LocalRectangle.LeftSide() + ((abs(Width) - abs(LocalRectangle.Width)) / 2),
                    TopSide() + LocalRectangle.TopSide() + (abs(Height) - abs(LocalRectangle.Height)),
                    abs(LocalRectangle.Width), abs(LocalRectangle.Height));
            case RectangleAlignment::BottomRight:
                return Rectangle(
                    LeftSide() + LocalRectangle.LeftSide() + (abs(Width) - abs(LocalRectangle.Width)),
                    TopSide() + LocalRectangle.TopSide() + (abs(Height) - abs(LocalRectangle.Height)),
                    abs(LocalRectangle.Width), abs(LocalRectangle.Height));
            default:
                return Rectangle(
                    LeftSide() + LocalRectangle.LeftSide(),
                    TopSide() + LocalRectangle.TopSide(),
                    abs(LocalRectangle.Width), abs(LocalRectangle.Height));
            }
        }

        /// @brief Calculate the local position that related to this Rectangle from a global position.
        /// @param GlobalPosition The global position to calculate.
        /// @return The local position that related to this Rectangle ((0, 0) mean the Rectangle top-left corner)
        /// of the given global position.
        Point GlobalToLocal(const Point& GlobalPosition) const { return Point(GlobalPosition.X - LeftSide(), GlobalPosition.Y - TopSide()); }

        /// @brief Calculate the smallest Rectangle that contain the two given Point.
        /// @param a The first Point.
        /// @param b The second Point.
        /// @return The result Rectangle.
        static Rectangle FromTwoPoint(const Point& a, const Point& b) {
            return {ENGINE_MIN(a.X, b.X), ENGINE_MIN(a.Y, b.Y), abs(b.X - a.X) + 1, abs(b.Y - a.Y) + 1};
        }

        /// @brief Calculate the intersection of the given two Rectangle.
        /// @param r1 The first Rectangle.
        /// @param r2 The second Rectangle.
        /// @return The Rectangle represent the intersection, or an empty Rectangle if there're no intersection.
        static Rectangle Intersect(const Rectangle& r1, const Rectangle& r2) {
            if (r1.IsEmptyArea() || r2.IsEmptyArea())
                return Rectangle::Empty;
            Point tl1 = r1.TopLeft(), tl2 = r2.TopLeft(), br1 = r1.BottomRight(), br2 = r2.BottomRight();
            int left = ENGINE_MAX(tl1.X, tl2.X), top = ENGINE_MAX(tl1.Y, tl2.Y), right = ENGINE_MIN(br1.X, br2.X), bottom = ENGINE_MIN(br1.Y, br2.Y);
            if (right < left || bottom < top) return Rectangle::Empty;
            return {left, top, right - left + 1, bottom - top + 1};
        }

        /// @brief Calculate the smallest Rectangle that contain the two given Rectangle and Point.
        /// @param r The given Rectangle to calculate.
        /// @param p The given Point to calculate.
        /// @return The smallest Rectangle that contain the two given Rectangle and Point.
        static Rectangle Union(const Rectangle& r, const Point& p) {
            if (r.IsEmptyArea())
                return FromTwoPoint(r.GetPosition(), p);
            int left = r.LeftSide(), top = r.TopSide(), right = r.RightSide(), bottom = r.BottomSide();
            int x = ENGINE_MIN(left, p.X), y = ENGINE_MIN(top, p.Y);
            return {x, y, ENGINE_MAX(right, p.X) - x + 1,  ENGINE_MAX(bottom, p.Y) - y + 1};
        }

        /// @brief Calculate the smallest Rectangle that contain the two given Rectangle.
        /// @param r1 The first Rectangle.
        /// @param r2 The second Rectangle.
        /// @return The smallest Rectangle that contain the two given Rectangle.
        static Rectangle Union(const Rectangle& r1, const Rectangle& r2) {
            if (r1.IsEmptyArea())
                return Union(r2, r1.GetPosition());
            if (r2.IsEmptyArea())
                return Union(r1, r2.GetPosition());
            int left1 = r1.LeftSide(), top1 = r1.TopSide(), right1 = r1.RightSide(), bottom1 = r1.BottomSide();
            int left2 = r2.LeftSide(), top2 = r2.TopSide(), right2 = r2.RightSide(), bottom2 = r2.BottomSide();
            int x = ENGINE_MIN(left1, left2), y = ENGINE_MIN(top1, top2);
            return {x, y, ENGINE_MAX(right1, right2) - x + 1, ENGINE_MAX(bottom1, bottom2) - y + 1};
        }

        /// @brief The empty Rectangle with all value are 0.
        static const Rectangle Empty;
    };
}

const Engine::Point Engine::Point::Zero = Engine::Point(0, 0);
const Engine::Point Engine::Point::One = Engine::Point(1, 1);
const Engine::Point Engine::Point::Up = Engine::Point(0, 1);
const Engine::Point Engine::Point::Down = Engine::Point(0, -1);
const Engine::Point Engine::Point::Left = Engine::Point(-1, 0);
const Engine::Point Engine::Point::Right = Engine::Point(1, 0);

const Engine::Size Engine::Size::Zero = Engine::Size(0, 0);
const Engine::Size Engine::Size::One = Engine::Size(1, 1);
const Engine::Size Engine::Size::Up = Engine::Size(0, 1);
const Engine::Size Engine::Size::Down = Engine::Size(0, -1);
const Engine::Size Engine::Size::Left = Engine::Size(-1, 0);
const Engine::Size Engine::Size::Right = Engine::Size(1, 0);

const Engine::Rectangle Engine::Rectangle::Empty = Engine::Rectangle(0, 0, 0, 0);

Engine::Point::Point(const Engine::Size& s) : X(s.Width), Y(s.Height) {}
Engine::Point::operator Engine::Size() const { return Size(X, Y); }

#endif // __ENGINE_STRUCTURE_H__