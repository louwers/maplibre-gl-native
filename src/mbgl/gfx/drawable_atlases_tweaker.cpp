#include <mbgl/gfx/drawable_atlases_tweaker.hpp>

#include <mbgl/gfx/drawable.hpp>
#include <mbgl/renderer/tile_render_data.hpp>
#include <mbgl/shaders/shader_program_base.hpp>

namespace mbgl {
namespace gfx {

void DrawableAtlasesTweaker::setupTextures(gfx::Drawable& drawable) {
    if (const auto& shader = drawable.getShader()) {
        if (const auto samplerLocation = shader->getSamplerLocation(glyphName)) {
            if (const auto iconSamplerLocation = shader->getSamplerLocation(iconName)) {
                assert(*samplerLocation != *iconSamplerLocation);
                drawable.setTexture(atlases ? atlases->glyph : nullptr, *samplerLocation);
                drawable.setTexture(atlases ? atlases->icon : nullptr, *iconSamplerLocation);
            } else {
                drawable.setTexture(atlases ? (isText ? atlases->glyph : atlases->icon) : nullptr, *samplerLocation);
            }
        }
    }
}

void DrawableAtlasesTweaker::init(gfx::Drawable& drawable) {
    setupTextures(drawable);
}

void DrawableAtlasesTweaker::execute(gfx::Drawable& drawable, const PaintParameters&) {
    setupTextures(drawable);
}

} // namespace gfx
} // namespace mbgl