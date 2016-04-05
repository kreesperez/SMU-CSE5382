#include "GeometryProvider.h"

#include <vector>

using namespace std;

GeometryProvider::~GeometryProvider()
{
}

void GeometryProvider::Icosahedron(std::vector<Vector3>& vertices, std::vector<GLushort>& indices)
{

    float X = 0.525731112119133606f;
    Log::Info << " X: " << X << std::endl;
    float Z = 0.850650808352039932f;
    Log::Info << " Z: " << Z << std::endl;
    vector<Vector3> icosahedronVerts =
    {
        Vector3(-X, 0.f, Z),
        Vector3(X, 0.f, Z),
        Vector3(-X, 0.f, -Z),
        Vector3(X, 0.f, -Z),
        Vector3(0.f, Z, X),
        Vector3(0.f, Z, -X),
        Vector3(0.f, -Z, X),
        Vector3(0.f, -Z, -X),
        Vector3(Z, X, 0.f),
        Vector3(-Z, X, 0.f),
        Vector3(Z, -X, 0.f),
        Vector3(-Z, -X, 0.f)
    };
    
    vertices.insert(end(vertices), begin(icosahedronVerts), end(icosahedronVerts));
    
    vector<GLushort> icosahedronIndices =
    {
        0, 4, 1,
        0, 9, 4,
        9, 5, 4,
        4, 5, 8,
        4, 8, 1,
        8, 10, 1,
        8, 3, 10,
        5, 3, 8,
        5, 2, 3,
        2, 7, 3,
        7, 10, 3,
        7, 6, 10,
        7, 11, 6,
        11, 0, 6,
        0, 1, 6,
        6, 1, 10,
        9, 0, 11,
        9, 11, 2,
        9, 2, 5,
        7, 2, 11
    };
    
    indices.insert(end(indices), begin(icosahedronIndices), end(icosahedronIndices));
}



//subract x y z// pythag thrm

//distance between two objects = D = |B-A| - Ra - Rb
//colide if D < 0


//ship =  translation * worldMatrix;
//Asteroid = Translation


//c = center
//c+[r,0,0] = p

//take center and mult by world matrix, gives us center in world space

//this is done in onUpdate of the game class


//--------- generating shperes

/*

i->0, indices.size()

    int i0 = indives[i]
    int i1 = indices[i+1]
 
 newpoint exists already
 {
    string name =
    to.string(i0)+ "-" + to.string[i1]
 
    name = to.string(min(i0,i1)
 }
 
 Va = verts[i0]
 Vb = verts[i1]
 
 m = (Va + Vb)/2
 
 newVerts.push
 
*/



