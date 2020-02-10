#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

void LoadModel(std::string filename, std::vector<vector3>* vertex, std::vector<vector3>* normals, std::vector<vector2>* uv, std::vector<int>* triangles) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_FlipWindingOrder); 

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ModelLoader:LoaderModel: ERROR::" << import.GetErrorString() << std::endl;
        return;
    }
    std::string directory = filename.substr(0, filename.find_last_of('/'));

    for(unsigned int j = 0; j < scene->mNumMeshes; j++) {
        aiMesh *mesh = scene->mMeshes[j]; 
        std::cout << "NUM VERTICES " << mesh->mNumVertices << std::endl;
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            vector3 pos; 
            pos.x = mesh->mVertices[i].x;
            pos.y = mesh->mVertices[i].y;
            pos.z = mesh->mVertices[i].z; 
            vertex->push_back(pos);

            vector3 normal;
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;
            normals->push_back(normal);

            if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                vector2 vec;
                vec.x = mesh->mTextureCoords[0][i].x; 
                vec.y = mesh->mTextureCoords[0][i].y;
                uv->push_back(vec);
            }
            else
                uv->push_back(vector2(0.0f, 0.0f));
        }

        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                triangles->push_back(face.mIndices[j]);
        }
    }
}