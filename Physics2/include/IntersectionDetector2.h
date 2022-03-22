#pragma once

#include "AABB.h"
#include "Vec2.h"
#include "Ray2.h"
#include "Box2.h"
#include "Line2.h"
#include "Maths.h"
#include "Circle.h"
#include "RaycastResult.h"

struct IntersectionDetector2 {
    /**********************
     * Point vs Primitive *
     **********************/
    
    //line : y = ax + b, a = dy/dx avec dy = Ey - Sy (E : End of line, S : start of line)
    //                               et dx = Ex - Sx (E : End of line, S : start of line)
    //                   b = y - ax
    static bool pointOnLine(const Vec2& point, const Line2& line) {
        float dy = line.end.y - line.start.y;
        float dx = line.end.x - line.start.x;
        if(dx == 0.0f) {
            return compare(point.x, line.start.x);
        }
        float m = dy / dx;

        float b = line.end.y - (m * line.end.x);
        
        return point.y == (m * point.x + b);
    }

    //vector length <= radius length
    static bool pointInCircle(const Vec2& point, Circle circle) {
        Vec2 circleCenter = circle.getCenter();
        Vec2 centerToPoint = point - circleCenter;

        //on calcule via le carré pcq sqrt très lent niveau calcul
        return centerToPoint.lengthSquared() <= circle.radius * circle.radius;
    }

    //vector x between min.x and max.x, and same for y
    static bool pointInAABB(const Vec2& point, AABB box) {
        Vec2 min = box.getMin();
        Vec2 max = box.getMax();

        bool testX = point.x <= max.x && min.x <= point.x;
        bool testY = point.y <= max.y && min.y <= point.y;

        return testX && testY;
    }

    //rotate point in box's local space
    static bool pointInBox2(const Vec2& point, Box2 box) {
        //translate point in local space
        Vec2 pointRotated = point;
        rotate(pointRotated, box.rb->rotation, box.rb->position);

        Vec2 min = box.getMin();
        Vec2 max = box.getMax();

        bool testX = point.x <= max.x && min.x <= point.x;
        bool testY = point.y <= max.y && min.y <= point.y;

        return testX && testY;
    }

    /*********************
     * Line vs Primitive *
     *********************/

    //FIXME: inverser rotation ? par rapport au fait qu'origine == top left
    static bool lineAndCircle(const Line2& line, Circle circle) {
        if(pointInCircle(line.start, circle) || pointInCircle(line.end, circle)) return true;

        Vec2 ab = line.end - line.start;
        // project point (center) onto ab
        // parameterized position t
        Vec2 circleCenter = circle.getCenter();
        Vec2 centerToLineStart = circleCenter - line.start;
        
        // A dot B / B dot B == |A||B|cos(TH)/|B||B|cos(TH) == |A|/|B|
        // sans faire de sqrt pcq trop couteux
        float t = centerToLineStart.dot(ab) / ab.dot(ab);

        if(t < 0.0f || t > 1.0f) {
            return false;
        }

        //find closest point to line segment
        Vec2 closestPoint  = line.start + (ab * t);
        std::cout << closestPoint << std::endl; 

        return pointInCircle(closestPoint, circle);
    }

    static bool lineAndAABB(const Line2& line, AABB box) {
        if(pointInAABB(line.start, box) || pointInAABB(line.end, box)) {
            return true;
        }

        Vec2 unitVec = line.end - line.start;
        unitVec.normalize();

        unitVec.x =  (unitVec.x != 0) ? (1.0f / unitVec.x) : 0.0f;
        unitVec.y =  (unitVec.y != 0) ? (1.0f / unitVec.y) : 0.0f;
        
        Vec2 min = box.getMin();
        min = (min - line.start) * unitVec;
        Vec2 max = box.getMax();
        max = (max - line.start) * unitVec;

        float tmin = std::max(std::min(min.x, max.x), std::min(min.y, max.y));
        float tmax = std::min(std::max(min.x, max.x), std::max(min.y, max.y));

        if(tmax < 0.0f || tmin > tmax) {
            return false;
        }

        float t = (tmin < 0.0f) ? tmax : tmin;
        return t > 0.0f && t * t < line.lengthSquared();
    }

    static bool lineAndBox2(const Line2& line, Box2 box) {
        float th = -box.rb->rotation; //box.rb->rotation;
        Vec2 center = box.rb->position;
        Vec2 localStart = line.start;
        Vec2 localEnd = line.end;

        rotate(localStart, th, center);
        rotate(localEnd, th, center);

        Line2 localLine{localStart, localEnd};
        AABB aabb{box.getMin(), box.getMax()};
        return lineAndAABB(localLine, aabb);
    }

    /************
     * Raycasts *
     ************/

    /**
     * @brief raycast against a circle
     * 
     * @param circle 
     * @param ray 
     * @param result additionnal results of the raycasting (optionnal)
     * @return true 
     * @return false 
     */
    static bool raycast(Circle circle, Ray2 ray, RaycastResult* result = nullptr) {
        RaycastResult::reset(*result);

        Vec2 originToCircle = circle.getCenter() - ray.origin;
        float radiusSquared = circle.radius * circle.radius;
        float orCirLengthSquared = originToCircle.lengthSquared();

        //project vector from ray origin onto direction of ray
        float a = originToCircle.dot(ray.direction);
        float bSquared = orCirLengthSquared - (a * a);
        if(radiusSquared - bSquared < 0.0f) {
            return false;
        }

        float f = sqrtf(radiusSquared - bSquared);
        float t = 0;
        if(orCirLengthSquared < radiusSquared) {
            //ray start inside the circle
            t = a + f;
        } else {
            t = a - f;
        }

        Vec2 point = ray.origin + (ray.direction * t);
        Vec2 normal = point - circle.getCenter();
        normal.normalize();

        result->init(point, normal, t, true);

        return true;
    }

    /**
     * @brief raycast against Axis-Aligned Bounding Box
     * 
     * @param box 
     * @param ray 
     * @param result additionnal results of the raycasting (optionnal)
     * @return true 
     * @return false 
     */
    static bool raycast(AABB box, Ray2 ray, RaycastResult* result = nullptr) {
        RaycastResult::reset(*result);
        
        Vec2 unitVec = ray.direction;
        unitVec.normalize();
        unitVec.x = (unitVec.x < 0.0f) ? 1.0f / unitVec.x : 0.0f;
        unitVec.y = (unitVec.y < 0.0f) ? 1.0f / unitVec.y : 0.0f;

        Vec2 min = box.getMin();
        min = (min - ray.origin) * unitVec;
        Vec2 max = box.getMax();
        max = (max - ray.origin) * unitVec;

        float tmin = std::max(std::min(min.x, max.x), std::min(min.y, max.y));
        float tmax = std::min(std::max(min.x, max.x), std::max(min.y, max.y));
        if(tmax < 0 || tmin > tmax) {
            return false;
        }

        float t = (tmin < 0.0f) ? tmax : tmin;
        bool hit = t > 0.0f;
        if(!hit) {
            return false;
        }

        Vec2 point = ray.origin + (ray.direction * t);
        Vec2 normal = ray.origin - point;
        normal.normalize();

        result->init(point, normal, t, true);

        return true;
    }

    /**
     * @brief raycast against Oriented Bounding Box
     * 
     * @param box 
     * @param ray 
     * @param result additionnal results of the raycasting (optionnal)
     * @return true 
     * @return false 
     */
    static bool raycast(Box2 box, Ray2 ray, RaycastResult* result = nullptr) {
        RaycastResult::reset(*result);
        
        Vec2 size = box.halfSize;
        Vec2 xAxis{1.0f, 0.0f};
        Vec2 yAxis{0.0f, 1.0f};
        rotate(xAxis, -box.rb->rotation, Vec2{0.0f, 0.0f});
        rotate(yAxis, -box.rb->rotation, Vec2{0.0f, 0.0f});

        Vec2 p = box.rb->position - ray.origin;
        //project direction of ray onto each axis of box
        Vec2 f{xAxis.dot(ray.direction), yAxis.dot(ray.direction)};
        //next project p onto every axis of the box
        Vec2 e{xAxis.dot(p), yAxis.dot(p)};

        //min x, max x, min y, max y
        float tMinsMaxs[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        for(int i = 0 ; i < 2 ; i++) {
            //if compare(f.get(i), 0) ?? f.get(i) c'est quoi ? pas trouvé dans la doc de lwjgl
            if(compare(f.get(i), 0.0f)) {
                if(-e.get(i) - size.get(i) > 0 || -e.get(i) + size.get(i) < 0) {
                    return false;
                }
                f.set(i, 0.00001f); //small val to avoid /0
            }

            tMinsMaxs[i * 2] = (e.get(i) + size.get(i)) / f.get(i); //tmax
            tMinsMaxs[i * 2 + 1] = (e.get(i) - size.get(i)) / f.get(i); //tmin
        }

        float tmin = std::max(std::min(tMinsMaxs[0], tMinsMaxs[1]), std::min(tMinsMaxs[2], tMinsMaxs[3]));
        float tmax = std::min(std::max(tMinsMaxs[0], tMinsMaxs[1]), std::max(tMinsMaxs[2], tMinsMaxs[3]));

        float t = (tmin < 0.0f) ? tmax : tmin;
        bool hit = t > 0.0f;
        if(!hit) {
            return false;
        }

        Vec2 point = ray.origin + (ray.direction * t);
        Vec2 normal = ray.origin - point;
        normal.normalize();

        result->init(point, normal, t, true);

        return true;
    }

    /***********************
     * Circle vs Primitive *
     ***********************/

    /**
     * @brief Alias of lineAndCircle
     * 
     * @param circle 
     * @param line 
     * @return true 
     * @return false 
     */
    static bool circleAndLine(Circle circle, const Line2& line) {
        return lineAndCircle(line, circle);
    }

    static bool circleAndCircle(Circle circle1, Circle circle2) {
        Vec2 btweenCenters = circle1.getCenter() - circle2.getCenter();
        float radiusSum = circle1.radius + circle2.radius;
        return btweenCenters.lengthSquared() <= radiusSum * radiusSum;
    }

    static bool circleAndAABB(Circle circle, AABB box) {
        Vec2 min = box.getMin();
        Vec2 max = box.getMax();

        Vec2 closestToCircle = circle.getCenter();
        if(closestToCircle.x < min.x) {
            closestToCircle.x = min.x;
        } else if(closestToCircle.x > max.x) {
            closestToCircle.x = max.x;
        }

        if(closestToCircle.y < min.y) {
            closestToCircle.y = min.y;
        } else if(closestToCircle.y > max.y) {
            closestToCircle.y = max.y;
        }

        Vec2 circleToBox = circle.getCenter() - closestToCircle;
        return circleToBox.lengthSquared() <= circle.radius * circle.radius;
    }

    static bool circleAndBox2(Circle circle, Box2 box) {
        // Treat the box just like an aabb, after we rotate the stuff
        Vec2 min{};
        Vec2 max = box.halfSize * 2;

        // Create circle in box's local space
        Vec2 r = circle.getCenter() - box.rb->position;
        rotate(r, -box.rb->rotation, Vec2{});
        Vec2 localCirclePos = r + box.halfSize;

        Vec2 closestToCircle = localCirclePos;
        if(closestToCircle.x < min.x) {
            closestToCircle.x = min.x;
        } else if(closestToCircle.x > max.x) {
            closestToCircle.x = max.x;
        }

        if(closestToCircle.y < min.y) {
            closestToCircle.y = min.y;
        } else if(closestToCircle.y > max.y) {
            closestToCircle.y = max.y;
        }

        Vec2 circleToBox = localCirclePos - closestToCircle;
        return circleToBox.lengthSquared() <= circle.radius * circle.radius;
    }
};

// bool testLineCircle() {
//     Line2 l(Vec2{0.0f, 0.0f}, Vec2{100.0f, 100.0f});
//     RigidBody2 r(Vec2{50.0f, 20.0f}, 0.0f);
//     Circle c(29.0f); //wtf ça renvoie vrai ?????????? fais les calculs si tu peux, apparemment pt plus proche == 35, 35 ; nan c'est good
//     c.rb = &r;

//     return IntersectionDetector2::lineAndCircle(l,c);
// }