#include <glut.h>
#include "imageloader.h"
#include "texturemodel.h"
#include "model.h"
#include <math.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <vector>

namespace vd10 {
    Model name;
    GLuint _textureBrick, _textureDoor, _textureGrass, _textureRoof, _textureWindow, _textureSky, _textureSkyTop, _textureBed, _textureTable, _textureChair, _textureCabinet, _textureAirconditional, _textureLaptop;
    TextureModel sky, skyTop, grass, wall, roof, door, window, wallside, bed, table, chair, cabinet, airconditional, laptop;
    Vector3 sky_t, skyTop_t, grass_t, wall_t1, wall_t2, roof_t, door_t, wallside_t1, wallside_t2, window_t1, window_t2, window_t3, window_t4, bed_t, table_t, chair_t, cabinet_t, airconditional_t, laptop_t;
    float lx = 0.0f, lz = 0.0f;
    float x = 0.0f, z = 0.0f;
    float angle = -1.5f;
    float speed = 0.1f;
    float heightAngle = 0;
    float height_view = -1;
    const float Pi = 3.14159265358979323846f;

    // Structure to hold annotation data
    struct Annotation {
        std::string text;
        Vector3 pos;
        float scale;
    };
    std::vector<Annotation> chairAnnotations;

    void draw(TextureModel* m, Vector3 t) {
        glPushMatrix();
        glTranslatef(t.x, t.y, t.z);
        m->draw();
        glPopMatrix();
    }

    void drawText(const char* text, Vector3 pos, float scale) {
        glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        glScalef(scale, scale, scale);
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow for visibility
        for (const char* c = text; *c; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }
        glPopMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    void drawCylinder(float radius, float height, int slices) {
        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE);
        gluQuadricNormals(quad, GLU_SMOOTH); // Ensure proper lighting
        glPushMatrix();
        gluCylinder(quad, radius, radius, height, slices, 1);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, height);
        gluDisk(quad, 0.0f, radius, slices, 1);
        glPopMatrix();
        gluDisk(quad, 0.0f, radius, slices, 1);
        glPopMatrix();
        gluDeleteQuadric(quad);
    }

    void drawChairLegs() {
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cerr << "OpenGL error before drawing chair legs: " << err << std::endl;
        }
        glPushMatrix();
        glTranslatef(chair_t.x, chair_t.y, chair_t.z);
        glBindTexture(GL_TEXTURE_2D, _textureChair);
        float legW = 0.06f; // Increased for visibility
        float legH = 0.4f;
        float w = 0.6f;
        float d = 0.6f;
        float legX[] = { -w / 2 + legW / 2, w / 2 - legW / 2 };
        float legZ[] = { -d / 2 + legW / 2, d / 2 - legW / 2 };
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                glPushMatrix();
                glTranslatef(legX[i], -1.5f, legZ[j]);
                glRotatef(-90, 1, 0, 0); // Adjusted rotation to align legs
                drawCylinder(0.03f, legH, 16); // Visible radius
                glPopMatrix();
            }
        }
        glPopMatrix();
        err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cerr << "OpenGL error after drawing chair legs: " << err << std::endl;
        }
    }

    void drawChairAnnotations() {
        glDisable(GL_TEXTURE_2D);
        for (const auto& anno : chairAnnotations) {
            drawText(anno.text.c_str(), anno.pos, anno.scale);
        }
        glEnable(GL_TEXTURE_2D);
    }

    void makeSky() {
        sky.clear();
        sky.setTextureFromBMP("data/sky.bmp");
        sky.addVertex(point3(-100, -100, -100));
        sky.addVertex(point3(100, -100, -100));
        sky.addVertex(point3(-100, 100, -100));
        sky.addVertex(point3(100, 100, -100));
        sky.addVertex(point3(-100, -100, 100));
        sky.addVertex(point3(100, -100, 100));
        sky.addVertex(point3(-100, 100, 100));
        sky.addVertex(point3(100, 100, 100));
        sky.addQuad(quadIndex(2, 3, 1, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        sky.addQuad(quadIndex(6, 7, 5, 4, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        sky.addQuad(quadIndex(2, 6, 4, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        sky.addQuad(quadIndex(3, 7, 5, 1, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        sky_t = point3(0, 0, 0);
    }

    void makeSkyTop() {
        skyTop.clear();
        skyTop.setTextureFromBMP("data/skytop.bmp");
        skyTop.addVertex(point3(-100, 100, -100));
        skyTop.addVertex(point3(100, 100, -100));
        skyTop.addVertex(point3(100, 100, 100));
        skyTop.addVertex(point3(-100, 100, 100));
        skyTop.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        skyTop_t = point3(0, 0, 0);
    }

    void makeGrass() {
        grass.clear();
        grass.setTextureFromBMP("data/nennha1.bmp");
        grass.addVertex(point3(-10, -1.5, 10));
        grass.addVertex(point3(-10, -1.5, -10));
        grass.addVertex(point3(10, -1.5, -10));
        grass.addVertex(point3(10, -1.5, 10));
        grass.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 100), texCoord2(100, 100), texCoord2(100, 0), texCoord2(0, 0)));
        grass_t = point3(0, 0, 0);
    }

    void makeWall() {
        wall.clear();
        wall.setTextureFromBMP("data/buctuong.bmp");
        wall.addVertex(point3(-4, 0, 1));
        wall.addVertex(point3(4, 0, 1));
        wall.addVertex(point3(4, -1.5, 1));
        wall.addVertex(point3(-4, -1.5, 1));
        wall.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 2), texCoord2(8, 2), texCoord2(8, 0), texCoord2(0, 0)));
        wall_t1 = point3(0, 0, -6);
        wall_t2 = point3(0, 0, -10);
    }

    void makeRoof() {
        roof.clear();
        roof.setTextureFromBMP("data/trannha.bmp");
        roof.addVertex(point3(-4, 0, 1));
        roof.addVertex(point3(4, 0, 1));
        roof.addVertex(point3(4, 0, -3));
        roof.addVertex(point3(-4, 0, -3));
        roof.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 4), texCoord2(8, 4), texCoord2(8, 0), texCoord2(0, 0)));
        roof_t = point3(0, 0, -6);
    }

    void makeName() {
        name.nVertices = 26;
        name.vertices[0] = point3(-0.8, 0.3, 0);
        name.vertices[1] = point3(-0.8, 0.7, 0);
        name.vertices[2] = point3(-0.9, 0.7, 0);
        name.vertices[3] = point3(-0.7, 0.7, 0);
        name.vertices[4] = point3(-0.6, 0.7, 0);
        name.vertices[5] = point3(-0.4, 0.7, 0);
        name.vertices[6] = point3(-0.4, 0.7, 0);
        name.vertices[7] = point3(-0.4, 0.3, 0);
        name.vertices[8] = point3(-0.4, 0.3, 0);
        name.vertices[9] = point3(-0.6, 0.3, 0);
        name.vertices[10] = point3(-0.6, 0.3, 0);
        name.vertices[11] = point3(-0.6, 0.7, 0);
        name.vertices[12] = point3(-0.3, 0.3, 0);
        name.vertices[13] = point3(-0.2, 0.7, 0);
        name.vertices[14] = point3(-0.2, 0.7, 0);
        name.vertices[15] = point3(-0.1, 0.3, 0);
        name.vertices[16] = point3(-0.25, 0.5, 0);
        name.vertices[17] = point3(-0.15, 0.5, 0);
        name.vertices[18] = point3(0.0, 0.3, 0);
        name.vertices[19] = point3(0.0, 0.7, 0);
        name.vertices[20] = point3(0.0, 0.7, 0);
        name.vertices[21] = point3(0.2, 0.3, 0);
        name.vertices[22] = point3(0.2, 0.3, 0);
        name.vertices[23] = point3(0.2, 0.7, 0);
        name.vertices[24] = point3(-0.25, 0.85, 0);
        name.vertices[25] = point3(-0.15, 0.8, 0);
        name.nEdges = 25;
        for (int i = 0; i < 25; i++) {
            name.edges[i][0] = i * 2;
            name.edges[i][1] = i * 2 + 1;
        }
    }

    void makeDoor() {
        door.clear();
        door.setTextureFromBMP("data/door1.bmp");
        door.addVertex(point3(-0.3, -0.4, 1.0001));
        door.addVertex(point3(0.3, -0.4, 1.0001));
        door.addVertex(point3(0.3, -1.5, 1.0001));
        door.addVertex(point3(-0.3, -1.5, 1.0001));
        door.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        door_t = point3(0, 0, -6);
    }

    void makeWindow() {
        window.clear();
        window.setTextureFromBMP("data/cuaso.bmp");
        window.addVertex(point3(-1.5, -0.3, 1.0001));
        window.addVertex(point3(-0.75, -0.3, 1.0001));
        window.addVertex(point3(-0.75, -0.8, 1.0001));
        window.addVertex(point3(-1.5, -0.8, 1.0001));
        window.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        window_t1 = point3(0, 0, -6);
        window_t2 = point3(4.25, 0, -6);
        window_t3 = point3(0, 0, -10.002);
        window_t4 = point3(4.25, 0, -10.002);
    }

    void makeWallside() {
        wallside.clear();
        wallside.setTextureFromBMP("data/buctuong.bmp");
        wallside.addVertex(point3(4, 0, 1));
        wallside.addVertex(point3(4, 0, -3));
        wallside.addVertex(point3(4, -1.5, -3));
        wallside.addVertex(point3(4, -1.5, 1));
        wallside.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 2), texCoord2(4, 2), texCoord2(4, 0), texCoord2(0, 0)));
        wallside_t1 = point3(0, 0, -6);
        wallside_t2 = point3(-8, 0, -6);
    }

    void makeBed() {
        bed.clear();
        bed.setTextureFromBMP("data/matgiuong.bmp");
        bed.addVertex(point3(-1, -1.5, -2.999));
        bed.addVertex(point3(1, -1.5, -2.999));
        bed.addVertex(point3(1, -1.5, 0.001));
        bed.addVertex(point3(-1, -1.5, 0.001));
        bed.addVertex(point3(-1, -1.25, -2.999));
        bed.addVertex(point3(1, -1.25, -2.999));
        bed.addVertex(point3(1, -1.25, 0.001));
        bed.addVertex(point3(-1, -1.25, 0.001));
        bed.addQuad(quadIndex(4, 5, 6, 7, texCoord2(0, 0), texCoord2(2, 0), texCoord2(2, 3), texCoord2(0, 3)));
        bed.addQuad(quadIndex(0, 1, 5, 4, texCoord2(0, 0), texCoord2(2, 0), texCoord2(2, 0.5), texCoord2(0, 0.5)));
        bed.addQuad(quadIndex(2, 3, 7, 6, texCoord2(0, 0), texCoord2(2, 0), texCoord2(2, 0.5), texCoord2(0, 0.5)));
        bed.addQuad(quadIndex(0, 4, 7, 3, texCoord2(0, 0), texCoord2(3, 0), texCoord2(3, 0.5), texCoord2(0, 0.5)));
        bed.addQuad(quadIndex(1, 2, 6, 5, texCoord2(0, 0), texCoord2(3, 0), texCoord2(3, 0.5), texCoord2(0, 0.5)));
        bed_t = point3(2, 0, -6);
    }

    void makeTable() {
        table.clear();
        table.setTextureFromBMP("data/matban.bmp");
        float w = 2.0f, d = 1.2f, h = 0.1f;
        float legH = 0.5f;
        int offset = 0;
        table.addVertex(point3(-w / 2, -1.5 + legH, -d / 2));
        table.addVertex(point3(w / 2, -1.5 + legH, -d / 2));
        table.addVertex(point3(-w / 2, -1.5 + legH + h, -d / 2));
        table.addVertex(point3(w / 2, -1.5 + legH + h, -d / 2));
        table.addVertex(point3(-w / 2, -1.5 + legH, d / 2));
        table.addVertex(point3(w / 2, -1.5 + legH, d / 2));
        table.addVertex(point3(-w / 2, -1.5 + legH + h, d / 2));
        table.addVertex(point3(w / 2, -1.5 + legH + h, d / 2));
        table.addQuad(quadIndex(0, 1, 3, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        table.addQuad(quadIndex(4, 5, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        table.addQuad(quadIndex(0, 4, 6, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        table.addQuad(quadIndex(1, 5, 7, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        table.addQuad(quadIndex(0, 1, 5, 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        table.addQuad(quadIndex(2, 3, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        offset += 8;
        float legW = 0.1f;
        float legX[] = { -w / 2 + legW / 2, w / 2 - legW / 2 };
        float legZ[] = { -d / 2 + legW / 2, d / 2 - legW / 2 };
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                float x = legX[i];
                float z = legZ[j];
                table.addVertex(point3(x - legW / 2, -1.5f, z - legW / 2));
                table.addVertex(point3(x + legW / 2, -1.5f, z - legW / 2));
                table.addVertex(point3(x - legW / 2, -1.5 + legH, z - legW / 2));
                table.addVertex(point3(x + legW / 2, -1.5 + legH, z - legW / 2));
                table.addVertex(point3(x - legW / 2, -1.5f, z + legW / 2));
                table.addVertex(point3(x + legW / 2, -1.5f, z + legW / 2));
                table.addVertex(point3(x - legW / 2, -1.5 + legH, z + legW / 2));
                table.addVertex(point3(x + legW / 2, -1.5 + legH, z + legW / 2));
                table.addQuad(quadIndex(offset + 0, offset + 1, offset + 3, offset + 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
                table.addQuad(quadIndex(offset + 4, offset + 5, offset + 7, offset + 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
                table.addQuad(quadIndex(offset + 0, offset + 4, offset + 6, offset + 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
                table.addQuad(quadIndex(offset + 1, offset + 5, offset + 7, offset + 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
                table.addQuad(quadIndex(offset + 0, offset + 1, offset + 5, offset + 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
                table.addQuad(quadIndex(offset + 2, offset + 3, offset + 7, offset + 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
                offset += 8;
            }
        }
        table_t = point3(-1, 0, -8.4);
    }

    void makeChair() {
        chair.clear();
        chair.setTextureFromBMP("data/matghe.bmp");
        float w = 0.6f;
        float d = 0.6f;
        float h = 0.05f;
        float legH = 0.4f;
        float backH = 0.5f;
        float backT = 0.05f;
        chair.addVertex(point3(-w / 2, -1.5 + legH, -d / 2));
        chair.addVertex(point3(w / 2, -1.5 + legH, -d / 2));
        chair.addVertex(point3(-w / 2, -1.5 + legH + h, -d / 2));
        chair.addVertex(point3(w / 2, -1.5 + legH + h, -d / 2));
        chair.addVertex(point3(-w / 2, -1.5 + legH, d / 2));
        chair.addVertex(point3(w / 2, -1.5 + legH, d / 2));
        chair.addVertex(point3(-w / 2, -1.5 + legH + h, d / 2));
        chair.addVertex(point3(w / 2, -1.5 + legH + h, d / 2));
        chair.addQuad(quadIndex(0, 1, 3, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        chair.addQuad(quadIndex(4, 5, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        chair.addQuad(quadIndex(0, 4, 6, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        chair.addQuad(quadIndex(1, 5, 7, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        chair.addQuad(quadIndex(0, 1, 5, 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        chair.addQuad(quadIndex(2, 3, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        int offset = 8;
        chair.addVertex(point3(-w / 2, -1.5 + legH + h, d / 2));
        chair.addVertex(point3(w / 2, -1.5 + legH + h, d / 2));
        chair.addVertex(point3(-w / 2, -1.5 + legH + h + backH, d / 2));
        chair.addVertex(point3(w / 2, -1.5 + legH + h + backH, d / 2));
        chair.addVertex(point3(-w / 2, -1.5 + legH + h, d / 2 - backT));
        chair.addVertex(point3(w / 2, -1.5 + legH + h, d / 2 - backT));
        chair.addVertex(point3(-w / 2, -1.5 + legH + h + backH, d / 2 - backT));
        chair.addVertex(point3(w / 2, -1.5 + legH + h + backH, d / 2 - backT));
        chair.addQuad(quadIndex(offset + 0, offset + 1, offset + 3, offset + 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        chair.addQuad(quadIndex(offset + 4, offset + 5, offset + 7, offset + 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        chair.addQuad(quadIndex(offset + 0, offset + 4, offset + 6, offset + 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        chair.addQuad(quadIndex(offset + 1, offset + 5, offset + 7, offset + 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        chair.addQuad(quadIndex(offset + 0, offset + 1, offset + 5, offset + 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        chair.addQuad(quadIndex(offset + 2, offset + 3, offset + 7, offset + 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        chair_t = point3(-1.0, 0, -7.5); // In front of table
        // Add annotations
        chairAnnotations.clear();
        chairAnnotations.push_back({ "Chair Width: 0.6", point3(chair_t.x, -0.9, chair_t.z - 0.3), 0.005f });
        chairAnnotations.push_back({ "Chair Depth: 0.6", point3(chair_t.x + 0.3, -0.9, chair_t.z), 0.005f });
        chairAnnotations.push_back({ "Chair Height: 0.45", point3(chair_t.x, -1.0, chair_t.z - 0.3), 0.005f });
        chairAnnotations.push_back({ "Backrest Height: 0.5", point3(chair_t.x, -0.8, chair_t.z - 0.3), 0.005f });
    }

    void makeCabinet() {
        cabinet.clear();
        cabinet.setTextureFromBMP("data/tu.bmp");

        // Kích thước tủ (đã thu nhỏ)
        float w = 1.0f; // rộng
        float h = 1.4f; // cao, phù hợp với chiều cao nhà (1.5)
        float d = 0.6f; // sâu

        // Các đỉnh của hình hộp (8 điểm)
        cabinet.addVertex(point3(-w / 2, -1.5, -d / 2)); // 0
        cabinet.addVertex(point3(w / 2, -1.5, -d / 2));  // 1
        cabinet.addVertex(point3(-w / 2, -1.5 + h, -d / 2)); // 2
        cabinet.addVertex(point3(w / 2, -1.5 + h, -d / 2));  // 3
        cabinet.addVertex(point3(-w / 2, -1.5, d / 2));  // 4
        cabinet.addVertex(point3(w / 2, -1.5, d / 2));   // 5
        cabinet.addVertex(point3(-w / 2, -1.5 + h, d / 2));  // 6
        cabinet.addVertex(point3(w / 2, -1.5 + h, d / 2));   // 7

        // Các mặt của hình hộp
        cabinet.addQuad(quadIndex(0, 1, 3, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt trước
        cabinet.addQuad(quadIndex(4, 5, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt sau
        cabinet.addQuad(quadIndex(0, 4, 6, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt trái
        cabinet.addQuad(quadIndex(1, 5, 7, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt phải
        cabinet.addQuad(quadIndex(2, 3, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt trên
        cabinet.addQuad(quadIndex(0, 1, 5, 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt dưới

        // Vị trí tủ: sát tường sau ghế
        cabinet_t = point3(-1.5, 0, -5.34); // x = -1.0 (cùng với ghế), z = -10 + 0.6/2 = -9.7
    }

    void makeAirconditional() {
        airconditional.clear();
        airconditional.setTextureFromBMP("data/airconditional.bmp");

        // Kích thước điều hòa
        float w = 0.4f; // rộng
        float h = 0.2f; // cao, nhỏ gọn để gắn trên tường
        float d = 1.0f; // sâu

        // Các đỉnh của hình hộp (8 điểm)
        airconditional.addVertex(point3(-w / 2, -0.2, -d / 2)); // 0
        airconditional.addVertex(point3(w / 2, -0.2, -d / 2));  // 1
        airconditional.addVertex(point3(-w / 2, -0.2 + h, -d / 2)); // 2
        airconditional.addVertex(point3(w / 2, -0.2 + h, -d / 2));  // 3
        airconditional.addVertex(point3(-w / 2, -0.2, d / 2));  // 4
        airconditional.addVertex(point3(w / 2, -0.2, d / 2));   // 5
        airconditional.addVertex(point3(-w / 2, -0.2 + h, d / 2));  // 6
        airconditional.addVertex(point3(w / 2, -0.2 + h, d / 2));   // 7

        // Các mặt của hình hộp
        airconditional.addQuad(quadIndex(0, 1, 3, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt trước
        airconditional.addQuad(quadIndex(4, 5, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt sau
        airconditional.addQuad(quadIndex(0, 4, 6, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt trái
        airconditional.addQuad(quadIndex(1, 5, 7, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt phải
        airconditional.addQuad(quadIndex(2, 3, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt trên
        airconditional.addQuad(quadIndex(0, 1, 5, 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Mặt dưới

        // Vị trí điều hòa: gắn trên tường sau, gần trần
        airconditional_t = point3(-3.7, -0.1, -8.5005); // x = -2.0, y = -0.1 (top at y=0), z = -10.001 + 1.0/2
    }
    //vẽ laptop ko đc nên chuyển sang vẽ sách
    void makeLaptop() {
        laptop.clear();
        laptop.setTextureFromBMP("data/matsach.bmp");
        float w = 0.6f; // Width
        float h = 0.05f; // Height (thin laptop)
        float d = 0.4f; // Depth
        // 8 vertices of the rectangular prism
        laptop.addVertex(point3(-w / 2, 0, -d / 2)); // 0
        laptop.addVertex(point3(w / 2, 0, -d / 2));  // 1
        laptop.addVertex(point3(-w / 2, h, -d / 2)); //  // 2
        laptop.addVertex(point3(w / 2, h, -d / 2));  // 3
        laptop.addVertex(point3(-w / 2, 0, d / 2));  // 4
        laptop.addVertex(point3(w / 2, 0, d / 2));   // 5
        laptop.addVertex(point3(-w / 2, h, d / 2)); // 6
        laptop.addVertex(point3(w / 2, h, d / 2));   // 7
        // 6 faces
        laptop.addQuad(quadIndex(0, 1, 3, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Front
        laptop.addQuad(quadIndex(4, 5, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Back
        laptop.addQuad(quadIndex(0, 4, 6, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Left
        laptop.addQuad(quadIndex(1, 5, 7, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Right
        laptop.addQuad(quadIndex(2, 3, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Top
        laptop.addQuad(quadIndex(0, 1, 5, 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Bottom
        // Position on table
        laptop_t = point3(-1.0, -0.875, -8.4); // x=-1.0, y=-0.9+0.05/2, z=-8.4
    }

    void drawName() {
        glPushMatrix();
        glLineWidth(4.0f);
        glColor3f(0.6, 0.17, 0.71);
        glScalef(10, 10, 10);
        glTranslatef(0, 9, -9.f);
        drawModelLines(&name);
        glPopMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    void resize(int width, int height) {
        if (height == 0) height = 1;
        const float ar = (float)width / (float)height;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, ar, 0.1f, 1000.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void renderScene(void) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(x, -1.0f, z,
            x + lx, height_view, z + lz,
            0.0f, 1.0f, 0.0f);
        glEnable(GL_TEXTURE_2D);
        draw(&sky, sky_t);
        draw(&skyTop, skyTop_t);
        for (int x1 = -5; x1 < 5; x1++) {
            for (int z1 = -5; z1 < 5; z1++) {
                Vector3 grass_t1;
                grass_t1.x = x1;
                grass_t1.z = z1;
                grass_t1.y = 0;
                draw(&grass, grass_t1);
            }
        }
        draw(&wall, wall_t1);
        draw(&wall, wall_t2);
        draw(&roof, roof_t);
        draw(&door, door_t);
        draw(&window, window_t1);
        draw(&window, window_t2);
        draw(&window, window_t3);
        draw(&window, window_t4);
        draw(&wallside, wallside_t1);
        draw(&wallside, wallside_t2);
        draw(&bed, bed_t);
        draw(&table, table_t);
        draw(&chair, chair_t);
        draw(&cabinet, cabinet_t);
        draw(&airconditional, airconditional_t); // Thêm điều hòa vào cảnh
        draw(&laptop, laptop_t); // Thêm laptop vào cảnh
        drawChairLegs();
        glDisable(GL_TEXTURE_2D);
        drawText("Width: 2.0", point3(table_t.x, -0.9, table_t.z - 0.6), 0.005f);
        drawText("Depth: 1.2", point3(table_t.x + 1.0, -0.9, table_t.z), 0.005f);
        drawText("Height: 0.5", point3(table_t.x, -1.0, table_t.z - 0.6), 0.005f);
        drawText("Distance from Bed: 1.599", point3(table_t.x, -0.8, table_t.z - 0.6), 0.005f);
        drawChairAnnotations();
        glEnable(GL_TEXTURE_2D);
        drawName();
        glutSwapBuffers();
    }

    void processKeys(unsigned char key, int xx, int yy) {
        switch (key) {
        case '>':
            speed += 0.1;
            break;
        case '<':
            speed -= 0.1;
            break;
        case 'w':
            if (heightAngle < Pi / 2) {
                heightAngle += 0.1;
                height_view = sin(heightAngle) - 1;
            }
            break;
        case 's':
            if (heightAngle > (-Pi / 2)) {
                heightAngle -= 0.1;
                height_view = sin(heightAngle) - 1;
            }
            break;
        case 'a':
            angle -= 0.02f;
            lx = cos(angle);
            lz = sin(angle);
            break;
        case 'd':
            angle += 0.02f;
            lx = cos(angle);
            lz = sin(angle);
            break;
        default:
            break;
        }
        glutPostRedisplay();
    }

    void processSpecialKeys(int key, int xx, int yy) {
        float fraction = speed;
        switch (key) {
        case GLUT_KEY_LEFT:
            x += lz * fraction;
            z -= lx * fraction;
            break;
        case GLUT_KEY_RIGHT:
            x -= lz * fraction;
            z += lx * fraction;
            break;
        case GLUT_KEY_UP:
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN:
            x -= lx * fraction;
            z -= lz * fraction;
            break;
        }
        glutPostRedisplay();
    }

    void init() {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        lx = cos(angle);
        lz = sin(angle);
        makeSky();
        makeSkyTop();
        makeGrass();
        makeWall();
        makeRoof();
        makeDoor();
        makeWindow();
        makeWallside();
        makeName();
        makeBed();
        makeTable();
        makeChair();
        makeCabinet();
        makeAirconditional(); // Khởi tạo điều hòa
        makeLaptop();
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING); // Avoid dark legs
    }
}

int vidu10(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D Scene with Chair, Cabinet, and Air Conditioner, and Laptop");
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(vd10::resize);
    glutKeyboardFunc(vd10::processKeys);
    glutSpecialFunc(vd10::processSpecialKeys);
    glutDisplayFunc(vd10::renderScene);
    vd10::init();
    glutMainLoop();
    return 0;
}