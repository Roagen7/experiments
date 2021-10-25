//
// Created by roagen on 25.10.2021.
//

#ifndef UNTITLED5_MESH_H
#define UNTITLED5_MESH_H

struct mesh {




    VAO vao;


    glm::vec3 defaultColor = {1.0,0,0};

    std::vector<GLfloat> triangles;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> colors;

    glm::mat4 modelMatrix = glm::mat4(1.0);




    mesh(std::vector<GLfloat> triangles, std::vector<GLfloat> normals) : triangles(triangles), normals(normals){
        this->bindData();
    }

    mesh(std::vector<GLfloat> vertices) {
        for(int i = 0; i < vertices.size(); i+=6){
            triangles.push_back(vertices[i]);
            triangles.push_back(vertices[i+1]);
            triangles.push_back(vertices[i+2]);
            normals.push_back(vertices[i+3]);
            normals.push_back(vertices[i+4]);
            normals.push_back(vertices[i+5]);

        }

        this->bindData();


    }


    void bindData(){

        VBO vbo;
        vao.Bind();
        vbo.Bind();
        vbo.Data<GLfloat>(getVertices());
        vao.Reserve(9 * sizeof(GLfloat));
        vao.Add<GLfloat>(3);
        vao.Add<GLfloat>(3);
        vao.Add<GLfloat>(3);
        vao.Unbind();
        vbo.Unbind();


    }



    std::vector<GLfloat> getVertices(){
        std::vector<GLfloat> vertices;

        for(int i = 0; i < triangles.size(); i+=3){
            vertices.push_back(triangles[i]);
            vertices.push_back(triangles[i+1]);
            vertices.push_back(triangles[i+2]);

            vertices.push_back(normals[i]);
            vertices.push_back(normals[i+1]);
            vertices.push_back(normals[i+2]);

            vertices.push_back(defaultColor.x);
            vertices.push_back(defaultColor.y);
            vertices.push_back(defaultColor.z);




        }
        return vertices;

    }


    void draw(Shader shader, glm::mat4 cameraView){
        shader.Use();
        shader.Unif("modelMatrix",this->modelMatrix);
        shader.Unif("camMatrix",cameraView);


        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0 , getVertices().size()/9.0f);


    }









};


#endif //UNTITLED5_MESH_H
