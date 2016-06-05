#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

//#include <GL/glew.h>
#include "include/glm/glm.hpp"
#include <OpenGL/GL.h>
#include <string>
#include <vector>
#include "obj_loader.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtx/transform.hpp"
#include "camera.h"

struct Vertex
{
public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
    {
        this->pos = pos;
        this->texCoord = texCoord;
        this->normal = normal;
    }
    
    glm::vec3* GetPos() { return &pos; }
    glm::vec2* GetTexCoord() { return &texCoord; }
    glm::vec3* GetNormal() { return &normal; }
    
private:
    glm::vec3 pos;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

enum MeshBufferPositions
{
    POSITION_VB,
    TEXCOORD_VB,
    NORMAL_VB,
    INDEX_VB
};

class Mesh
{
public:
    Mesh(const std::string& fileName);
    Mesh(const std::string& fileName, int flag);
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
    
    void Draw();
    
    virtual ~Mesh();
//protected:
//private:
    static const unsigned int NUM_BUFFERS = 4;
    void operator=(const Mesh& mesh) {}
    Mesh(const Mesh& mesh) {}
    
    void InitMesh(const IndexedModel& model);
    void InitTexMesh(const IndexedModel& model);
    
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_numIndices;
    
    ///////
//public:
    void transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
    {
        glPushMatrix();
        this->pos = pos;
        this->rot = rot;
        this->scale = scale;
        glPopMatrix();
    }
    
    inline glm::mat4 GetModel() const
    {
        glm::mat4 posMat = glm::translate(pos);
        glm::mat4 scaleMat = glm::scale(scale);
        glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
        glm::mat4 rotMat = rotX * rotY * rotZ;
        
        return posMat * rotMat * scaleMat;
    }
    
    inline glm::mat4 GetMVP(const Camera& camera) const
    {
        glm::mat4 VP = camera.GetViewProjection();
        glm::mat4 M = GetModel();
        
        return VP * M;//camera.GetViewProjection() * GetModel();
    }
    
    inline glm::vec3* GetPos() {         glPushMatrix();
        return &pos;        glPopMatrix();
 }
    inline glm::vec3* GetRot() {         glPushMatrix();
        return &rot;        glPopMatrix();
 }
    inline glm::vec3* GetScale() {         glPushMatrix();
        return &scale;        glPopMatrix();
 }
    
    inline void SetPos(glm::vec3& pos) {
        glPushMatrix();
        this->pos = pos;
        glPopMatrix();
    }
    inline void SetRot(glm::vec3& rot) { this->rot = rot; }
    inline void SetScale(glm::vec3& scale) { this->scale = scale; }
//private:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
};

#endif
