#pragma once

#include <memory>
#include <stdlib.h>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <Deliberation/Core/Math/Sphere.h>

#include "GameLib.h"
#include "Voxel.h"

namespace deliberation
{
class Ray3D;
class Transform3D;
}

class VoxelShapeTree final
{
public:
    VoxelShapeTree(const glm::uvec3 & size);

    void updateVoxel(const glm::uvec3 & voxel, bool set);

    bool lineCast(const Transform3D & transform, const Ray3D & ray, glm::uvec3 & voxel) const;

    std::string toString() const;

private:
    static constexpr size_t NO_LEAF = std::numeric_limits<size_t>::max();

private:
    template<typename T>
    struct Subtree final
    {
        Subtree(const glm::uvec3 & size, const glm::uvec3 & maxChunkSize);

        void updateVoxel(size_t index, const glm::uvec3 & voxel, bool set);
        void updateVoxelLeaf(size_t index, const glm::uvec3 & voxel, bool set);

        void lineCast(size_t index, const Ray3D & ray, std::vector<glm::uvec3> & voxels) const;
        void lineCastLeaf(size_t index, const Ray3D & ray, std::vector<glm::uvec3> & voxels) const;

        std::shared_ptr<Subtree<T>> clone() const;

        void toString(std::stringstream & stream, size_t index, size_t indentation) const;
        void leafToString(std::stringstream & stream, size_t index, size_t indentation) const;

        struct Node
        {
            glm::uvec3  llf;
            glm::uvec3  urb;
            Sphere      bounds;
            size_t      leaf = NO_LEAF;
            size_t      numVoxels = 0;
        };

        std::vector<Node>   nodes;
        std::vector<T>      leaves;
    };

private:
    using VoxelLeaf = bool;
    using ChunkLeaf = std::shared_ptr<Subtree<VoxelLeaf>>;

private:
    glm::uvec3          m_size;
    Subtree<ChunkLeaf>  m_tree;
};