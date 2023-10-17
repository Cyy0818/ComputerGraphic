#pragma once
#include"ApplicationRoot.h"
#define M_PI       3.14159265358979323846   // pi
struct Vector3 {
    float x, y, z;
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};
struct Light {
    Vector3 position;
    COLORREF color;
};
class MyPhong:public ObjWrapper
{
private:
    float radius_,  x_,  y_,  z_;
public:
    MyPhong(float r, float x, float y, float z)
        :radius_(r), x_(x), y_(y), z_(z) {};
    void phongShading(Vector3 normal, Vector3 viewDir, Light light, COLORREF& color) {
        float ambientIntensity = 0.2;
        COLORREF ambientColor = RGB(GetRValue(color) * ambientIntensity,
            GetGValue(color) * ambientIntensity,
            GetBValue(color) * ambientIntensity);

        // 漫反射
        Vector3 lightDir(light.position.x - normal.x, light.position.y - normal.y, light.position.z - normal.z);
        float length = sqrt(lightDir.x * lightDir.x + lightDir.y * lightDir.y + lightDir.z * lightDir.z);
        lightDir.x /= length;
        lightDir.y /= length;
        lightDir.z /= length;

        float diffuseIntensity = max(0.0f, normal.x * lightDir.x + normal.y * lightDir.y + normal.z * lightDir.z);
        COLORREF diffuseColor = RGB(GetRValue(light.color) * diffuseIntensity,
            GetGValue(light.color) * diffuseIntensity,
            GetBValue(light.color) * diffuseIntensity);

        // 高光反射
        Vector3 reflectDir(2 * normal.x * diffuseIntensity - lightDir.x,
            2 * normal.y * diffuseIntensity - lightDir.y,
            2 * normal.z * diffuseIntensity - lightDir.z);
        float specularIntensity = pow(max(0.0f, viewDir.x * reflectDir.x + viewDir.y * reflectDir.y + viewDir.z * reflectDir.z), 32);
        COLORREF specularColor = RGB(GetRValue(light.color) * specularIntensity,
            GetGValue(light.color) * specularIntensity,
            GetBValue(light.color) * specularIntensity);

        float lightIntensity = ambientIntensity + diffuseIntensity + specularIntensity;

        // 将光的强度映射到颜色值，使光强的地方为白色，光弱的地方为灰色
        color = RGB(min(255, GetRValue(ambientColor) + GetRValue(diffuseColor) + GetRValue(specularColor)),
            min(255, GetGValue(ambientColor) + GetGValue(diffuseColor) + GetGValue(specularColor)),
            min(255, GetBValue(ambientColor) + GetBValue(diffuseColor) + GetBValue(specularColor)));
    }

    Vector3 calculateSpherePoint(float radius, float theta, float phi) {
        Vector3 point(
            radius * sin(phi) * cos(theta),
            radius * sin(phi) * sin(theta),
            radius * cos(phi)
        );
        return point;
    }

    std::vector<Pixel> drawPhongShadedSphere(float radius, float x, float y, float z) {
        std::vector<Pixel> buffer;
        int centerX = getmaxx() / 2;
        int centerY = getmaxy() / 2;

        // 光源信息
        Light light = { {x, y, z}, RGB(255, 255, 255) };

        // 视点信息
        Vector3 viewDir = { 300.0f, -400.0f, -500.0f };

        for (float phi = 0; phi <= M_PI; phi += 0.01) {
            for (float theta = 0; theta <= 2 * M_PI; theta += 0.01) {
                Vector3 vertex = calculateSpherePoint(radius, theta, phi);

                // 计算法向量
                Vector3 normal = vertex;

                // 归一化法向量
                float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
                normal.x /= length;
                normal.y /= length;
                normal.z /= length;

                // 计算Phong光照模型颜色（白色到灰色）
                COLORREF color = RGB(255, 255, 255); // 默认颜色为白色
                phongShading(normal, viewDir, light, color);

                buffer.push_back(Pixel(centerX + static_cast<int>(vertex.x), centerY - static_cast<int>(vertex.y), color));
              
            }
          
        }
        return buffer;

    }
    void plan() {
        ObjWrapper::Points = drawPhongShadedSphere(radius_, x_, y_, z_);
    }



};




