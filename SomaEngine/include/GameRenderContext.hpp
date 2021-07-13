#pragma once

#include "rendering/RenderContext.hpp"
#include "math/Matrix.hpp"
#include "rendering/Model.hpp"
class GameRenderContext : public RenderContext {
public:
    GameRenderContext(RenderDevice& deviceIn, RenderTarget& targetIn, RenderDevice::DrawParams drawParamsIn,
        Shader& shaderIn, Sampler& samplerIn) :
        RenderContext(deviceIn, targetIn), m_drawParams(drawParamsIn), m_shader(shaderIn), m_sampler(samplerIn),
        currentTexture(nullptr) {}

    void renderMesh(Model* model, Matrix transform) {
        meshRenderBuffer[model].push_back(transform);
    }
    void flush() {
        for (Map<Model*, SOMA_Array<Matrix> >::iterator it
            = meshRenderBuffer.begin(); it != meshRenderBuffer.end(); ++it) {

            Matrix* transforms = &it->second[0];
            size_t numTransforms = it->second.size();
            if (numTransforms == 0)
                continue;
            /*Go thru each VAO and link the appropriate texture*/
            uint32 materialIndex = 0;
            for (VertexArray* vao : it->first->VAOs)
            {
                uint32 mIndex = it->first->materialIndices[materialIndex];                
                uint32 textureId = it->first->materials[mIndex].ids["diffuse"];  //Diffuse only for now
 
                m_shader.setSampler("diffuse", textureId, m_sampler, 0);
                
                vao->updateBuffer(4, transforms, numTransforms * sizeof(Matrix));
                this->draw(m_shader, *vao, m_drawParams, numTransforms);
                
                materialIndex++;
            }
            //if (textureId != currentTextureId) {
            //    m_shader.setSampler("diffuse", textureId, m_sampler, 0);
            //}

            it->second.clear();
        }
    }
private:
    RenderDevice::DrawParams m_drawParams;
    Shader& m_shader;
    Sampler& m_sampler;
    Texture* currentTexture;
    Map< Model*, SOMA_Array<Matrix> > meshRenderBuffer;
};