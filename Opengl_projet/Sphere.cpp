#include "Sphere.h"

void Sphere::init(GLuint vertexPositionID)
{
    int i, j;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    int indicator = 0;
    for (i = 0; i <= latitudes; i++) {
        double lat0 = glm::pi<double>() * (-0.5 + (double)(i - 1) / latitudes);
        double z0 = sin(lat0) * radius;
        double zr0 = cos(lat0) * radius;

        double lat1 = glm::pi<double>() * (-0.5 + (double)i / latitudes);
        double z1 = sin(lat1) * radius;
        double zr1 = cos(lat1) * radius;

        for (j = 0; j <= longitudes; j++) {
            double lng = 2 * glm::pi<double>() * (double)(j - 1) / longitudes;
            double x = cos(lng);
            double y = sin(lng);

            vertices.push_back(x * zr0);
            vertices.push_back(y * zr0);
            vertices.push_back(z0);
            indices.push_back(indicator);
            indicator++;

            vertices.push_back(x * zr1);
            vertices.push_back(y * zr1);
            vertices.push_back(z1);
            indices.push_back(indicator);
            indicator++;
        }
    }

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glGenBuffers(1, &m_vboVertex);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboVertex);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_vboIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    cout << glGetError() << endl;
    cout << numsToDraw << " nums to draw" << endl;
    numsToDraw = indices.size();
}

void Sphere::translation(float directionX, float directionY, float directionZ)
{
    float dx = directionX * velocity.x;
    float dy = directionY * velocity.y;
    float dz = directionZ * velocity.z;
    ThreeDimensionalFigure::translation(dx, dy, dz);
    center = glm::vec3(center.x + dx, center.y + dy, center.z + dz);

}

Sphere::Sphere(glm::vec3 center, float radius, Collider_Type type, float weight, glm::vec3 velocity) : Collider(type, weight, velocity)
{
	this->radius = radius;
	this->center = center;
	this->color = glm::vec3(1, 0, 0);
	this->matrix = glm::mat4(1.0f);
	ThreeDimensionalFigure::translation(center.x, center.y, center.z);
	this->latitudes = 40;
	this->longitudes = 40;
    this->m_vao = 0;
    this->m_vboVertex = 0;
    this->m_vboIndex = 0;
    this->numsToDraw = 0;
}

Sphere::~Sphere()
{
    if (m_vboVertex) {
        glDeleteBuffers(1, &m_vboVertex);
    }
    if (m_vboIndex) {
        glDeleteBuffers(1, &m_vboIndex);
    }
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
    }
}

void Sphere::render()
{
    // draw sphere
    cout << "draw sphere" << endl;
    glBindVertexArray(m_vao);
  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
    glDrawElements(GL_TRIANGLE_STRIP, numsToDraw, GL_UNSIGNED_INT, 0);
}

bool Sphere::isCollideWith(Sphere* neighbor)
{
    float distanceBetweenCenter = glm::length(neighbor->center - this->center);
    cout << distanceBetweenCenter << "distanceBetwenCenter" << endl;
    return distanceBetweenCenter <= (this->radius + neighbor->radius);
}

glm::vec3 Sphere::getCenter()
{
    return this->center;
}

float Sphere::getRadius() {
    return this->radius;
}