//
//  TransformTestTest.h
//  opengl tutorial
//
//  Created by Edmond Dantes on 5/16/16.
//  Copyright © 2016 Edmond Dantes. All rights reserved.
//

#ifndef TransformTestTest_h
#define TransformTestTest_h

#define RADIANS_TO_DEGREES(radians) ((radians) * (180.0 / M_PI))

static const float MaxVerticalAngle = 89.0f; //must be less than 90 to avoid gimbal lock

struct TransformTest
{
public:
    TransformTest();
    void Translate(float x, float y, float z);
    void Translate(const glm::vec3 &dir);
    void SetPosition(const glm::vec3 &pos);
    void SetYPosition(const float &pos);
    void Rotate(float x, float y, float z);
    void Rotate(const glm::vec3 &dir);
    void SetRotation(const glm::vec3 &rot);
    void Scale(const glm::vec3 &scale);
    void Scale(float x, float y, float z);
    const glm::vec3& GetScale();
    
    const glm::vec3& GetPosition();
    const glm::vec3& GetRotation();
    void LookAt(glm::vec3 targetPosition);
    glm::mat4 GetOrientation();
    
    glm::mat4 GetWorldMatrix();
    
    glm::vec3 Up();
    glm::vec3 Right();
    glm::vec3 Forward();
    
    //glm::mat4 GetOrientation();
    glm::mat4 GetTranslation();
    glm::mat4 GetScaling();
    
    void NormalizeAngles();
private:
    glm::vec3 m_Position, m_Rotation, m_Scale;
    glm::mat4 m_Translation, m_Orientation, m_Scaling;
    
};

inline TransformTest::TransformTest()
{
    m_Scale = glm::vec3(1,1,1);
}

inline void TransformTest::Translate(float x, float y, float z)
{
    m_Position += glm::vec3(x,y,z);
}

inline void TransformTest::Translate(const glm::vec3 &dir)
{
    m_Position += dir;
}

inline void TransformTest::SetRotation(const glm::vec3 &rot)
{
    m_Rotation = rot;
}

inline void TransformTest::Rotate(float x, float y, float z)
{
    
    m_Rotation += glm::vec3(x,y,z);
    
}

inline void TransformTest::Rotate(const glm::vec3 &rot)
{
    
    m_Rotation += rot;
}

inline const glm::vec3& TransformTest::GetRotation()
{
    return m_Rotation;
}


void TransformTest::NormalizeAngles()
{
    m_Rotation.y = fmodf(m_Rotation.y, 360.0f);
    //fmodf can return negative values, but this will make them all positive
    if(m_Rotation.y < 0.0f)
        m_Rotation.y += 360.0f;
    
    if(m_Rotation.x > MaxVerticalAngle)
        m_Rotation.x = MaxVerticalAngle;
    else if(m_Rotation.x < -MaxVerticalAngle)
        m_Rotation.x = -MaxVerticalAngle;
}

void TransformTest::LookAt(glm::vec3 targetPosition)
{
    if((targetPosition - m_Position) == glm::vec3(0,0,0)) return;
    glm::vec3 direction = glm::normalize(targetPosition - m_Position);
    m_Rotation.x = RADIANS_TO_DEGREES(asinf(-direction.y));
    m_Rotation.y = RADIANS_TO_DEGREES(-atan2f(-direction.x, -direction.z));
    
    NormalizeAngles();
}

glm::mat4 TransformTest::GetOrientation()
{
//    if(m_NeedUpdate)
//    {
        m_Orientation = glm::rotate(m_Rotation.x, glm::vec3(1,0,0));
        m_Orientation = glm::rotate(m_Orientation, m_Rotation.y, glm::vec3(0,1,0));
        m_Orientation = glm::rotate(m_Orientation, m_Rotation.z, glm::vec3(0,0,1));
//    }
//
    return m_Orientation;
}

glm::mat4 TransformTest::GetTranslation()
{
    m_Translation = glm::translate(m_Position);
    return m_Translation;
}

#endif /* TransformTestTest_h */
